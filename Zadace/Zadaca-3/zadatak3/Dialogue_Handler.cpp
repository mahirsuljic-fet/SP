#include "Dialogue_Handler.hpp"
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

// bilo mi je veoma mrsko pravit ovaj "menu" dio zadatka
// ako iko bude citao, izvinjavam se unaprijed

void Dialogue_Handler::add_location()
{
  std::string name;
  double latitude, longitude;
  int error_count = 0;

  auto error_message = [&error_count](const char* field) {
    system("clear");
    std::cout << "Invalid " << field << "!" << std::endl
              << std::endl;
    ++error_count;
  };

  std::cout << "ADD LOCATION" << std::endl
            << std::endl
            << "Location name: ";

  cin_reset();
  while (!std::getline(std::cin, name) && error_count < MAX_ERROR_COUNT)
  {
    error_message("name");
    std::cout << "ADD LOCATION" << std::endl
              << std::endl
              << "Location name: ";
  }

  if (planner.location_exists(name)) throw std::invalid_argument("Location already exists in database");

  error_count = 0;
  while (error_count < MAX_ERROR_COUNT)
  {
    std::cout << "Latitude: ";
    if (!(std::cin >> latitude))
    {
      error_message("latitude");
      continue;
    }

    if (latitude > 90 || latitude < -90)
    {
      error_message("latitude");
      continue;
    }

    std::cout << "Longitude: ";
    if (!(std::cin >> longitude))
    {
      error_message("longitude");
      continue;
    }

    if (longitude > 180 || longitude < -180)
    {
      error_message("longitude");
      continue;
    }

    break;
  }

  try
  {
    planner.add_location(name, latitude, longitude);
    std::cout << std::endl
              << "Location added successfully!" << std::endl;
  }
  catch (const std::exception& err)
  {
    std::cout << err.what() << std::endl;
  }

  std::cout << std::endl;

  pause();
}

void Dialogue_Handler::edit_location()
{
  std::string name;
  double latitude, longitude;
  int error_count = 0;

  auto error_message = [&error_count](const char* field) {
    system("clear");
    std::cout << "Invalid " << field << "!" << std::endl
              << std::endl;
    ++error_count;
  };

  std::cout << "EDIT LOCATION" << std::endl
            << std::endl
            << "Location name: ";

  cin_reset();
  while (!std::getline(std::cin, name) && error_count < MAX_ERROR_COUNT)
  {
    error_message("name");
    std::cout << "EDIT LOCATION" << std::endl
              << std::endl
              << "Location name: ";
  }

  if (!planner.location_exists(name)) throw std::invalid_argument("Location does not exist in database");

  error_count = 0;
  while (error_count < MAX_ERROR_COUNT)
  {
    std::cout << "Latitude: ";
    if (!(std::cin >> latitude))
    {
      error_message("latitude");
      continue;
    }

    if (latitude > 90 || latitude < -90)
    {
      error_message("latitude");
      continue;
    }

    std::cout << "Longitude: ";
    if (!(std::cin >> longitude))
    {
      error_message("longitude");
      continue;
    }

    if (longitude > 180 || longitude < -180)
    {
      error_message("longitude");
      continue;
    }

    break;
  }

  try
  {
    planner.edit_location(name, latitude, longitude);
    std::cout << std::endl
              << "Location edited successfully!" << std::endl;
  }
  catch (const std::exception& err)
  {
    std::cout << err.what() << std::endl;
  }

  std::cout << std::endl;

  pause();
}

void Dialogue_Handler::remove_location()
{
  std::string name;
  int error_count = 0;

  std::cout << "REMOVE LOCATION" << std::endl
            << std::endl
            << "Location name: ";

  cin_reset();
  while (!std::getline(std::cin, name) && error_count < MAX_ERROR_COUNT)
  {
    system("clear");
    std::cout << "Invalid name!" << std::endl
              << std::endl
              << "REMOVE LOCATION" << std::endl
              << std::endl
              << "Location name: ";
    ++error_count;
  }

  try
  {
    planner.remove_location(name);
    std::cout << std::endl
              << "Location removed successfully!" << std::endl;
  }
  catch (const std::exception& err)
  {
    std::cout << err.what() << std::endl;
  }

  std::cout << std::endl;

  pause(false);
}

void Dialogue_Handler::add_stop()
{
  std::string name;
  int error_count = 0;

  std::cout << "ADD STOP" << std::endl
            << std::endl
            << "Stop name: ";

  cin_reset();
  while (!std::getline(std::cin, name) && error_count < MAX_ERROR_COUNT)
  {
    system("clear");
    std::cout << "Invalid name!" << std::endl
              << std::endl
              << "ADD STOP" << std::endl
              << std::endl
              << "Stop name: ";
  }

  try
  {
    planner.add_stop(name);
    std::cout << std::endl
              << "Stop added successfully!" << std::endl;
  }
  catch (const std::exception& err)
  {
    std::cout << err.what() << std::endl;
  }

  std::cout << std::endl;

  pause(false);
}

void Dialogue_Handler::insert_stop()
{
  int error_count = 0;
  std::string name;
  int pos;

  auto error_message = [&error_count](const char* field) {
    system("clear");
    std::cout << "Invalid " << field << "!" << std::endl
              << std::endl;
    ++error_count;
  };

  std::cout << "INSERT STOP" << std::endl
            << std::endl
            << "Stop name: ";

  cin_reset();
  while (!std::getline(std::cin, name) && error_count < MAX_ERROR_COUNT)
  {
    error_message("name");
    std::cout << "Stop name: ";
  }

  system("clear");
  error_count = 0;
  while (error_count < MAX_ERROR_COUNT)
  {
    std::cout << "INSERT STOP" << std::endl
              << std::endl
              << "Stop name: " << name << std::endl
              << std::endl;

    if (planner.stop_count() > 0) planner.print_trip();

    std::cout << planner.stop_count() + 1 << ". EMPTY" << std::endl
              << std::endl
              << "Stop Position: ";

    if (!(std::cin >> pos))
    {
      error_message("position");
      continue;
    }

    --pos;

    if (pos < 0 || pos > planner.location_count())
    {
      error_message("position");
      continue;
    }

    break;
  }

  try
  {
    if (pos == planner.stop_count())
      planner.add_stop(name);
    else
      planner.insert_stop(name, pos);

    std::cout << std::endl
              << "Stop inserted successfully!" << std::endl;
  }
  catch (const std::exception& err)
  {
    std::cout << err.what() << std::endl;
  }

  std::cout << std::endl;

  pause();
}

void Dialogue_Handler::remove_stop()
{
  std::string name;
  int error_count = 0;

  std::cout << "REMOVE STOP" << std::endl
            << std::endl;

  if (planner.stop_count() > 0) planner.print_trip();

  std::cout << std::endl
            << "Stop name: ";

  cin_reset();
  while (!std::getline(std::cin, name) && error_count < MAX_ERROR_COUNT)
  {
    system("clear");
    std::cout << "Invalid name!" << std::endl
              << std::endl
              << "REMOVE STOP" << std::endl
              << std::endl;

    if (planner.stop_count() > 0) planner.print_trip();

    std::cout << std::endl
              << "Stop name: ";
    ++error_count;
  }

  try
  {
    planner.remove_stop(name);
    std::cout << std::endl
              << "Stop removed successfully!" << std::endl;
  }
  catch (const std::exception& err)
  {
    std::cout << err.what() << std::endl;
  }

  std::cout << std::endl;

  pause(false);
}

void Dialogue_Handler::print_trip()
{
  system("clear");
  std::cout << "CURRENT TRIP" << std::endl
            << std::endl;
  try
  {
    planner.print_trip();
  }
  catch (const std::exception& err)
  {
    std::cout << err.what() << std::endl;
  }
  std::cout << std::endl;
  pause();
}

void Dialogue_Handler::show_trip_distance()
{
  system("clear");
  std::cout << "Current trip distance: " << planner.trip_distance() << std::endl;
  std::cout << std::endl;
  pause();
}

void Dialogue_Handler::render_trip()
{
  system("clear");

  if(planner.stop_count() == 0) throw std::runtime_error("Can't render trip with no stops");

  std::string file_name;
  std::cout << "Output file name (no spaces and no extension): ";
  std::cin >> file_name;

  file_name += ".html";

  std::cout << std::endl
            << "Rendering trip..." << std::endl;

  planner.render_trip(file_name);

  system("clear");
  std::cout << "Trip rendered." << std::endl
            << std::endl;

  std::cout << "Would you like to open the rendered trip? (y/n) ";

  char c;
  while (std::cin >> c)
  {
    cin_reset();
    if (c == 'y')
    {
      planner.open_trip_render(file_name);
      break;
    }

    if (c == 'n')
    {
      c = 0;
      break;
    }

    system("clear");
    std::cout << "Invalid input!" << std::endl
              << "Would you like to open the rendered trip? (y/n) ";
  }
}

void Dialogue_Handler::print_locations()
{
  system("clear");
  std::cout << "LOCATIONS" << std::endl
            << std::endl;
  try
  {
    planner.print_locations();
  }
  catch (const std::exception& err)
  {
    std::cout << err.what() << std::endl;
  }
  std::cout << std::endl;
  pause();
}

void Dialogue_Handler::load_database()
{
  system("clear");

  std::string file_name;
  std::cout << "Database file name (with or without extension (uses .txt as default)): ";
  std::cin >> file_name;

  auto index = file_name.find('.');
  if (index == -1) file_name += ".txt";

  std::cout << std::endl
            << "Loading database..." << std::endl;

  planner.load_database(file_name);

  system("clear");
  std::cout << "Database loaded." << std::endl
            << std::endl;

  pause();
}

void Dialogue_Handler::save_database()
{
  system("clear");

  if (planner.location_count() == 0) throw std::runtime_error("Can't save empty database");

  std::string file_name;
  std::cout << "Database file name (with or without extension (uses .txt as default))" << (planner.database_loaded() ? " or 'c' to write to current database file: " : ": ");
  std::cin >> file_name;

  if (file_name == "c")
    file_name = planner.current_database_file();
  else if (file_name.find('.') == -1)
    file_name += ".txt";

  if (file_name == "") throw std::invalid_argument("Database file name can't be empty");

  std::cout << std::endl
            << "Saving database..." << std::endl;

  planner.save_database(file_name);

  system("clear");
  std::cout << "Database saved." << std::endl
            << std::endl;

  pause();
}

void Dialogue_Handler::pause(bool reset)
{
  std::cout << "Press any key to continue...";
  if (reset) cin_reset();
  getchar();
}

void Dialogue_Handler::cin_reset()
{
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
