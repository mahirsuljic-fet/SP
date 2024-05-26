#pragma once

#include "TripPlanner.hpp"
class Dialogue_Handler
{
  public:
    Dialogue_Handler(TripPlanner& planner) : planner { planner } { }

    void add_location();
    void edit_location();
    void remove_location();
    void add_stop();
    void insert_stop();
    void remove_stop();
    void print_trip();
    void show_trip_distance();
    void render_trip();
    void print_locations();
    void load_database();
    void save_database();

  private:
    constexpr static const int MAX_ERROR_COUNT = 3;
    TripPlanner& planner;

    static void pause(bool reset = true);
    static void cin_reset();
};
