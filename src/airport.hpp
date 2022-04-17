#pragma once

#include "GL/displayable.hpp"
#include "GL/dynamic_object.hpp"
#include "GL/texture.hpp"
#include "aircraft_manager.hpp"
#include "airport_type.hpp"
#include "geometry.hpp"
#include "img/image.hpp"
#include "runway.hpp"
#include "terminal.hpp" 
#include "tower.hpp"

#include <vector>

class Airport : public GL::Displayable, public GL::DynamicObject
{
private:
    const AirportType& type;
    const Point3D pos;
    const GL::Texture2D texture;
    std::vector<Terminal> terminals;
    Tower tower;
    int fuel_stock       = 0;
    int ordered_fuel     = 0;
    int next_refill_time = 0;
    AircraftManager& manager;

    // reserve a terminal
    // if a terminal is free, return
    // 1. a sequence of waypoints reaching the terminal from the runway-end and
    // 2. the number of the terminal (used for liberating the terminal later)
    // otherwise, return an empty waypoint-vector and any number
    std::pair<WaypointQueue, size_t> reserve_terminal(Aircraft& aircraft)
    {
        const auto it =
            std::find_if(terminals.begin(), terminals.end(), [](const Terminal& t) { return !t.in_use(); });

        if (it != terminals.end())
        {
            it->assign_craft(aircraft);
            const auto term_idx = std::distance(terminals.begin(), it);
            return { type.air_to_terminal(pos, 0, term_idx), term_idx };
        }
        else
        {
            return { {}, 0u };
        }
    }

    WaypointQueue start_path(const size_t terminal_number) const
    {
        assert(terminal_number < terminals.size());
        return type.terminal_to_air(pos, 0, terminal_number);
    }

    Terminal& get_terminal(const size_t terminal_num)
    {
        assert(terminal_num < terminals.size());
        return terminals.at(terminal_num);
    }

public:
    Airport(const AirportType& type_, const Point3D& pos_, const img::Image* image, AircraftManager& m,
            const float z_ = 1.0f) :

        GL::Displayable { z_ },
        type { type_ },
        pos { pos_ },
        texture { image },
        terminals { type.create_terminals() },
        tower { *this },
        manager { m }

    {}

    Tower& get_tower() { return tower; }

    void display() const override { texture.draw(project_2D(pos), { 2.0f, 2.0f }); }

    bool update() override
    {
        if (next_refill_time == 0)
        {
            fuel_stock += ordered_fuel;
            ordered_fuel     = std::min<int>(manager.get_required_fuel(), 5000);
            next_refill_time = 100;
            if (ordered_fuel > 0)
                std::cout << "fuel to command :(" << ordered_fuel << "), fuel in stock :" << fuel_stock
                          << std::endl;
        }
        else
        {
            --next_refill_time;
        }

        for (auto& t : terminals)
        {
            t.update();
            if (fuel_stock > 0)
                t.refill_aircraft_if_needed(fuel_stock);
        }

        return true;
    }

    friend class Tower;
};
