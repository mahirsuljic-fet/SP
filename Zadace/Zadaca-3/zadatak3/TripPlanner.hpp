#pragma once

#include "../zadatak1/DoubleLinkedList.hpp"
#include "Location.hpp"
#include <cstddef>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>

class TripPlanner
{
  public:
    TripPlanner() = default;
    TripPlanner(const std::string& file_name);
    TripPlanner(TripPlanner&&);
    TripPlanner(const TripPlanner&);
    TripPlanner& operator=(TripPlanner&&);
    TripPlanner& operator=(const TripPlanner&);
    ~TripPlanner() = default;

    void add_location(const std::string& name, double latitude, double longitute);
    void edit_location(const std::string& name, double latitude, double longitude);
    void remove_location(const std::string& name);
    void add_stop(const std::string& name);
    void insert_stop(const std::string& name, size_t pos);
    void remove_stop(const std::string& name);
    void print_trip(std::ostream& out = std::cout) const;
    void save_trip(const std::string& file_name) const;
    void load_trip(const std::string& file_name, std::ostream& out = std::cout, std::istream& in = std::cin);
    void save_database(const std::string& file_name) const;
    void load_database(const std::string& file_name);
    double trip_distance() const;
    void render_trip(const std::string& file_name) const;
    void open_trip_render(const std::string& file_name) const;
    void print_locations(std::ostream& out = std::cout) const;
    bool database_loaded() const { return current_database_file_name_.size(); }
    std::string current_database_file() const { return current_database_file_name_; }
    bool location_exists(const std::string& name) const;
    int location_count() const { return locations_.size(); }
    int stop_count() const { return stops_.size(); }

  private:
    DoubleLinkedList<Location> locations_;
    DoubleLinkedList<const Location*> stops_;
    std::string current_database_file_name_;

    Location* get_location_ptr(const std::string& name) const;
    DoubleLinkedList<Location>::Iterator get_location_it(const std::string& name) const;
    static double stops_distance(const Location*, const Location*);
    static std::string get_HTML_template();
};
