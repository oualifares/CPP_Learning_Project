#pragma once

#include "GL/dynamic_object.hpp"
#include "aircraft.hpp"

#include <memory>
#include <vector>

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;
    long crashs = 0;

public:
    void add(std::unique_ptr<Aircraft> aircraftr);

    bool update() override;
    int get_required_fuel();
    void sortAircrafts()
    {
        std::sort(aircrafts.begin(), aircrafts.end(),
                  [](std::unique_ptr<Aircraft>& a, std::unique_ptr<Aircraft>& b)
                  {
                      if (a->has_terminal() == b->has_terminal())
                          return a->getFuel() <= b->getFuel();
                      return a->has_terminal();
                  });
    }

    void printAircrafts()
    {
        std::for_each(aircrafts.begin(), aircrafts.end(),
                      [](std::unique_ptr<Aircraft>& aircft)
                      { std::cout << "fuel level :" << aircft->getFuel() << std::endl; });
        
    }

    
void coutCrashed() const {
    std::cout << crashs << " aircrafts crashed" << std::endl;
}
};
