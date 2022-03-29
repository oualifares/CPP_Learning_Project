#include "aircraft_manager.hpp"

#include <utility>

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    assert(aircraft);
    aircrafts.emplace_back(std::move(aircraft));
}

bool AircraftManager::update()
{
    sortAircrafts();

    aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(),
                                   [this](std::unique_ptr<Aircraft>& aircft)
                                   {
                                       try
                                       {
                                           return !aircft->update();
                                       } catch (const AircraftCrash& crash)
                                       {
                                           std::cerr << crash.what() << std::endl;
                                           crashs++;
                                           return true;
                                       }
                                   }),
                    aircrafts.end());

    return true;
}

int AircraftManager::get_required_fuel()
{
    return accumulate(aircrafts.begin(), aircrafts.end(), 0.0,
                      [](float sum, const std::unique_ptr<Aircraft>& aircraft)
                      {
                          if (aircraft->is_low_on_fuel() && aircraft->is_at_terminal)
                          {
                              return sum + (MAX_FUEL - aircraft->fuel);
                          }
                          return sum;
                      });
}