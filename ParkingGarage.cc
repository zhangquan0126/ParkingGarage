#include <iostream>
#include <string>
#include <map>
#include <queue>

using namespace std;

enum CarType {
    Small_Car = 0,
    Middle_Car = 1,
    Large_Car = 2,
};

enum LotType {
    Small = 0,
    Middle = 1,
    Large = 2,
};

class Car {
private:
    string m_plate;
    CarType m_type;
public:
    Car(string&& plate, CarType type)
        : m_plate(std::move(plate)),
        m_type(type) 
    {        
    }
    string GetPlate() const { return m_plate; }
    CarType GetType() const { return m_type; }
};

class Lot {
private: 
    uint64_t m_id;
    LotType m_type;
public:
    LotType GetType() const { return m_type; }
};

class Garage {
private:
    map<enum LotType, queue<Lot>> m_availableLots;
    map<string, Lot> m_occupiedMap;
public:
    bool Enter(const Car& car) {
        switch (car.GetType()) {
            case Large_Car:
            if (m_availableLots[Large].empty()) {
                return false;
            }
            m_occupiedMap[car.GetPlate()] = m_availableLots[Large].front();
            m_availableLots[Large].pop();
            break;
            case Middle_Car:
            if (m_availableLots[Middle].empty()) {
                if (m_availableLots[Large].empty()) {
                    return false;
                }
                m_occupiedMap[car.GetPlate()] = m_availableLots[Large].front();
                m_availableLots[Large].pop();
            } else {
                m_occupiedMap[car.GetPlate()] = m_availableLots[Middle].front();
                m_availableLots[Middle].pop();
            }
            break;
            case Small_Car:
            if (m_availableLots[Small].empty()) {
                if (m_availableLots[Middle].empty()) {
                    if (m_availableLots[Large].empty()) {
                        return false;
                    }
                    m_occupiedMap[car.GetPlate()] = m_availableLots[Large].front();
                    m_availableLots[Large].pop();
                } else {
                    m_occupiedMap[car.GetPlate()] = m_availableLots[Middle].front();
                    m_availableLots[Middle].pop();
                }
            } else {
                m_occupiedMap[car.GetPlate()] = m_availableLots[Small].front();
                m_availableLots[Small].pop();
            }
            break;
        }
        return true;
    }
    
    void Leave(const Car& car) {
        Lot lot = m_occupiedMap[car.GetPlate()];
        m_availableLots[lot.GetType()].push(lot);
    }
};

int main()
{
    Garage garage;
    return 0;
}
