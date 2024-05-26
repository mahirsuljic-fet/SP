#include "TripPlanner.hpp"
#include "Location.hpp"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

TripPlanner::TripPlanner(const std::string& file_name) { load_database(file_name); }

TripPlanner::TripPlanner(TripPlanner&& other) : locations_ { std::move(other.locations_) }, stops_ { std::move(other.stops_) } { }

TripPlanner::TripPlanner(const TripPlanner& other) : locations_ { other.locations_ }, stops_ { std::move(other.stops_) } { }

TripPlanner& TripPlanner::operator=(TripPlanner&& other)
{
  this->locations_ = std::move(other.locations_);
  this->stops_ = std::move(other.stops_);
  return *this;
}

TripPlanner& TripPlanner::operator=(const TripPlanner& other)
{
  this->locations_ = other.locations_;
  this->stops_ = other.stops_;
  return *this;
}

void TripPlanner::add_location(const std::string& name, double latitude, double longitude)
{
  // Location new_location { name, latitude, longitude };
  // if (location_exists(name))
  // {
  //   std::string message = "Location \"" + name + "\" (" + std::to_string(latitude) + ", " + std::to_string(longitude) + ") already exists";
  //   throw std::runtime_error(std::move(message));
  // }

  locations_.push_back(Location { name, latitude, longitude });
}

void TripPlanner::edit_location(const std::string& name, double latitude, double longitude)
{
  auto it = std::find_if(locations_.begin(), locations_.end(), [&name](const Location& location) { return location.name() == name; });
  *it = Location { name, latitude, longitude };
}

void TripPlanner::remove_location(const std::string& name)
{
  auto it = std::find_if(locations_.begin(), locations_.end(), [&name](const Location& location) { return location.name() == name; });

  if (it == locations_.end())
  {
    std::string message = "Location \"" + name + "\" doesn't exist";
    throw std::runtime_error(std::move(message));
  }

  try
  {
    remove_stop(name);
  }
  catch (...)
  {
  }

  locations_.erase(it);
}

void TripPlanner::add_stop(const std::string& name)
{
  auto location_ptr = get_location_ptr(name);
  if (location_ptr == nullptr)
  {
    std::string message = "Location \"" + name + "\" does not exist";
    throw std::runtime_error(std::move(message));
  }

  stops_.push_back(location_ptr);
}

void TripPlanner::insert_stop(const std::string& name, size_t pos)
{
  if (pos > stops_.size()) throw std::out_of_range("Invalid stop position");

  const Location* location_ptr = get_location_ptr(name);
  if (location_ptr == nullptr)
  {
    std::string message = "Location \"" + name + "\" does not exist";
    throw std::runtime_error(std::move(message));
  }

  auto it = stops_.begin();
  for (auto i = 0; i < pos; ++i) ++it;

  stops_.insert(it, location_ptr);
}

void TripPlanner::remove_stop(const std::string& name)
{
  auto it = stops_.begin();
  while (it != stops_.end() && (*it)->name() != name) ++it;

  if (it == stops_.end())
  {
    std::string message = "Stop \"" + name + "\" does not exist";
    throw std::runtime_error(std::move(message));
  }

  stops_.erase(it);
}

void TripPlanner::print_trip(std::ostream& out) const
{
  if (stops_.empty()) throw std::runtime_error("No stops added to trip");

  int i = 1;
  for (auto it = stops_.begin(); it != stops_.end(); ++it)
    out << i++ << ". " << (*it)->name() << std::endl;
}

void TripPlanner::save_trip(const std::string& file_name) const
{
  std::ofstream file(file_name);
  if (!file) throw std::runtime_error("Error while saving trip to file \"" + file_name + "\"");

  auto it = stops_.begin();
  for (; it != stops_.rbegin(); ++it)
    file << (*it)->name() << ":" << (*it)->latitude() << ":" << (*it)->longitude() << std::endl;
  file << (*it)->name() << ":" << (*it)->latitude() << ":" << (*it)->longitude();

  file.close();
}

void TripPlanner::load_trip(const std::string& file_name, std::ostream& out, std::istream& in)
{
  std::ifstream file(file_name);
  if (!file) throw std::runtime_error("Error while loading trip \"" + file_name + "\"");

  std::string line;
  std::vector<std::string> resolved_conflicts;
  std::vector<std::string> skipped_locations;
  while (std::getline(file, line))
  {
    Location current_location;
    std::istringstream iss(line);
    std::string unit;

    std::getline(iss, current_location.name_, ':');
    std::getline(iss, unit, ':');
    current_location.latitude_ = std::stod(unit);
    std::getline(iss, unit);
    current_location.longitude_ = std::stod(unit);

    if (std::find(skipped_locations.begin(), skipped_locations.end(), current_location.name_) != skipped_locations.end()) break;

    auto location_ptr = get_location_ptr(current_location.name_);
    if (location_ptr != nullptr)
    {
      if (current_location != *location_ptr)
      {
        if (std::find(resolved_conflicts.begin(), resolved_conflicts.end(), current_location.name_) != resolved_conflicts.end())
        {
          stops_.push_back(location_ptr);
          break;
        }

        system("clear");
        out << "LOCATION CONFLICT" << std::endl;
        out << "Location from database: " << location_ptr->name_ << "(" << location_ptr->latitude_ << ", " << location_ptr->longitude_ << ")" << std::endl;
        out << "Location from file:     " << current_location.name_ << "(" << current_location.latitude_ << ", " << current_location.longitude_ << ")" << std::endl;

        char c;
        out << "d - keep location from database" << std::endl
            << "f - keep location from file (overwrite working database)" << std::endl
            << "s - skip location (don't load location to trip)" << std::endl
            << "Option: ";
        while (in >> c)
        {
          if (c == 'd')
          {
            stops_.push_back(location_ptr);
            resolved_conflicts.push_back(current_location.name_);
            break;
          }

          if (c == 'f')
          {
            *location_ptr = current_location;
            stops_.push_back(location_ptr);
            resolved_conflicts.push_back(current_location.name_);
            break;
          }

          if (c == 's')
          {
            skipped_locations.push_back(current_location.name_);
            break;
          }

          system("clear");
          out << "Invalid input" << std::endl
              << "d - keep location from database" << std::endl
              << "f - keep location from file (overwrite working database)" << std::endl
              << "s - skip location (don't load location to trip)" << std::endl
              << "Option: ";
        }
      }
      else
        stops_.push_back(location_ptr);
    }
    else
      stops_.push_back(location_ptr);
  }

  file.close();
}

void TripPlanner::save_database(const std::string& file_name) const
{
  std::ofstream file(file_name);
  if (!file) throw std::runtime_error("Error while saving trip to file \"" + file_name + "\"");

  auto it = locations_.begin();
  for (; it != locations_.rbegin(); ++it)
    file << it->name() << ":" << it->latitude() << ":" << it->longitude() << std::endl;
  file << it->name() << ":" << it->latitude() << ":" << it->longitude();

  file.close();
}

void TripPlanner::load_database(const std::string& file_name)
{
  locations_.clear();
  stops_.clear();

  std::ifstream file(file_name);
  if (!file) throw std::runtime_error("Error while opening file \"" + file_name + "\"");

  bool name = false;
  std::string line;
  std::string current_location_name;
  double current_location_latitude;
  double current_location_longitude;
  while (std::getline(file, line))
  {
    for (int i = 0; i < line.size(); ++i)
    {
      if (line[i] == ':')
      {
        if (!name)
        {
          current_location_name = line.substr(0, i);
          name = true;
        }
        else
        {
          current_location_latitude = std::stod(line.substr(current_location_name.size() + 1, i));
          current_location_longitude = std::stod(line.substr(i + 1, line.size()));
          locations_.push_back(Location { current_location_name, current_location_latitude, current_location_longitude });
          name = false;
          break;
        }
      }
    }
  }

  current_database_file_name_ = file_name;

  file.close();
}

double TripPlanner::trip_distance() const
{
  if (stops_.empty()) return 0.0;

  double distance = 0.0;
  auto it_current = stops_.begin();
  auto it_previous = it_current++;
  while (it_current != stops_.end())
  {
    distance += stops_distance(*it_previous, *it_current);
    it_previous = it_current++;
  }
  return distance;
}

void TripPlanner::render_trip(const std::string& file_name) const
{
  constexpr static const int STROKE_WIDTH = 4;
  constexpr static const int CIRCLE_RADIUS = STROKE_WIDTH * 2;
  constexpr static const int NAME_SIZE = CIRCLE_RADIUS * 2.5;
  constexpr static const int NUMBER_SIZE = CIRCLE_RADIUS * 1.75;
  constexpr static const char* NAME_COLOR = "black";
  constexpr static const char* CIRCLE_COLOR = "red";
  constexpr static const char* STROKE_COLOR = "green";
  constexpr static const char* NUMBER_COLOR = "black";
  constexpr static const char* NAME_WEIGHT = "";
  constexpr static const char* NUMBER_WEIGHT = "bold";
  constexpr static const double NUMBER_OFFSET = CIRCLE_RADIUS * 0.6;
  constexpr static const double NAME_OFFSET = CIRCLE_RADIUS * 2;
  constexpr static const double IMAGEWIDTH = 1063.0;
  constexpr static const double IMAGEHEIGHT = 1014.0;
  constexpr static const double NORTHEDGE = 45.4;
  constexpr static const double SOUTHEDGE = 42.4;
  constexpr static const double WESTEDGE = 15.5;
  constexpr static const double EASTEDGE = 19.9;

  std::ostringstream oss;
  oss << get_HTML_template();

  double x1, y1, x2, y2;
  auto it_current = stops_.begin();

  // za slucaj da ima samo jedan stop
  x2 = ((*it_current)->longitude() - WESTEDGE) / (EASTEDGE - WESTEDGE) * IMAGEWIDTH;
  y2 = ((*it_current)->latitude() - NORTHEDGE) / (SOUTHEDGE - NORTHEDGE) * IMAGEHEIGHT;

  auto it_previous = it_current++;
  int i = 1;

  auto add_line = [&oss](double x1, double y1, double x2, double y2) {
    oss << "<line x1=\"" << x1 << "\" y1=\"" << y1 << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\" stroke=\"" << STROKE_COLOR << "\" stroke-width=\"" << STROKE_WIDTH << "\"></line>";
  };

  auto add_circle = [&oss](double x, double y) {
    oss << "<circle cx=\"" << x << "\" cy=\"" << y << "\" r=\"" << CIRCLE_RADIUS << "\" fill=\"" << CIRCLE_COLOR << "\"></circle>";
  };

  auto add_number = [&oss](double x, double y, int n) {
    oss << "<text x=\"" << x << "\" y=\"" << y + NUMBER_OFFSET << "\" fill=\"" << NUMBER_COLOR << "\" font-size=\"" << NUMBER_SIZE << "\" text-anchor=\"middle\" font-weight=\"" << NUMBER_WEIGHT << "\">" << n << "</text>";
  };

  auto add_name = [&oss](double x, double y, const std::string& name) {
    oss << "<text x=\"" << x << "\" y=\"" << y - NAME_OFFSET << "\" fill=\"" << NAME_COLOR << "\" font-size=\"" << NAME_SIZE << "\" text-anchor=\"middle\" font-weight=\"" << NAME_WEIGHT << "\">" << name << "</text>";
  };

  while (it_current != stops_.end())
  {
    x1 = ((*it_previous)->longitude() - WESTEDGE) / (EASTEDGE - WESTEDGE) * IMAGEWIDTH;
    y1 = ((*it_previous)->latitude() - NORTHEDGE) / (SOUTHEDGE - NORTHEDGE) * IMAGEHEIGHT;
    x2 = ((*it_current)->longitude() - WESTEDGE) / (EASTEDGE - WESTEDGE) * IMAGEWIDTH;
    y2 = ((*it_current)->latitude() - NORTHEDGE) / (SOUTHEDGE - NORTHEDGE) * IMAGEHEIGHT;

    oss << std::endl;
    add_line(x1, y1, x2, y2);
    oss << std::endl;
    add_circle(x1, y1);
    oss << std::endl;
    add_number(x1, y1, i++);
    oss << std::endl;
    add_name(x1, y1, (*it_previous)->name());

    it_previous = it_current++;
  }

  oss << std::endl;
  add_circle(x2, y2);
  oss << std::endl;
  add_number(x2, y2, i++);
  oss << std::endl;
  add_name(x2, y2, (*it_previous)->name());

  oss << std::endl;
  oss << "</svg>";

  std::ofstream output_file(file_name);
  if (!output_file) throw std::runtime_error("Error while writing rendered trip");
  output_file << oss.str();
  output_file.close();
}

void TripPlanner::open_trip_render(const std::string& file_name) const
{
  system(("open " + file_name).c_str());
}

void TripPlanner::print_locations(std::ostream& out) const
{
  if (locations_.empty()) throw std::runtime_error("No locations added");

  for (auto it = locations_.begin(); it != locations_.rbegin(); ++it)
    out << *it << std::endl;
  out << *locations_.rbegin();
}

DoubleLinkedList<Location>::Iterator TripPlanner::get_location_it(const std::string& name) const
{
  return std::find_if(locations_.begin(), locations_.end(), [&name](const Location& location) { return location.name() == name; });
}

Location* TripPlanner::get_location_ptr(const std::string& name) const
{
  return &std::find_if(locations_.begin(), locations_.end(), [&name](const Location& location) { return location.name() == name; }).node()->data;
}

bool TripPlanner::location_exists(const std::string& name) const
{
  return get_location_it(name) != locations_.end();
}

double TripPlanner::stops_distance(const Location* first, const Location* second)
{
  constexpr static const double R = 6371;
  double sin_lat_avg = std::sin((second->latitude() - first->latitude()) / 2);
  double sin_lon_avg = std::sin((second->longitude() - first->longitude()) / 2);
  double cos_lat_first = std::cos(first->latitude());
  double cos_lat_second = std::cos(second->latitude());
  return 2 * R * std::asin(std::sqrt(sin_lat_avg * sin_lat_avg + cos_lat_first * cos_lat_second * sin_lon_avg * sin_lon_avg) * M_PI / 180);
}

std::string TripPlanner::get_HTML_template()
{
  std::ifstream file("./outputTemplateP1.html");
  if (!file) throw std::runtime_error("HTML template not found");

  std::ostringstream oss;
  oss << file.rdbuf();

  file.close();
  return oss.str();
}
