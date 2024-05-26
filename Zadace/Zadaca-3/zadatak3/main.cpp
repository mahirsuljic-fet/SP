#include "Dialogue_Handler.hpp"
#include "TripPlanner.hpp"
#include <cstdlib>
#include <exception>
#include <iostream>

constexpr static const int MAX_OPTION = 12;

static TripPlanner planner;
static Dialogue_Handler handler(planner);

void print_main_menu();
int get_main_menu_option();
void handle_main_menu_option(int);

int main()
{
  int option = -1;
  while (option)
  {
    option = get_main_menu_option();

    try
    {
      handle_main_menu_option(option);
      system("clear");
    }
    catch (const std::exception& err)
    {
      system("clear");
      std::cout << err.what() << std::endl
                << std::endl;
    }
  }

  return 0;
}

void print_main_menu()
{
  std::cout << "TRIP PLANNER" << std::endl
            << std::endl
            << "1  - Add Location" << std::endl
            << "2  - Edit Location" << std::endl
            << "3  - Remove Location" << std::endl
            << "4  - Add Stop" << std::endl
            << "5  - Insert Stop" << std::endl
            << "6  - Remove Stop" << std::endl
            << "7  - Print Trip" << std::endl
            << "8  - Show Trip Distance" << std::endl
            << "9  - Render Trip" << std::endl
            << "10 - Print Locations" << std::endl
            << "11 - Load Database (close current)" << std::endl
            << "12 - Save Database" << std::endl
            << "0  - Exit" << std::endl
            << std::endl
            << "Option: ";
}

int get_main_menu_option()
{
  unsigned int option = 0;

  do
  {
    print_main_menu();
    std::cin >> option;
    system("clear");

    if (option > MAX_OPTION)
      std::cout << "Invalid option!" << std::endl
                << std::endl;
  }
  while (option > MAX_OPTION);

  return option;
}

void handle_main_menu_option(int option)
{
  switch (option)
  {
  case 1:
    handler.add_location();
    break;
  case 2:
    handler.edit_location();
    break;
  case 3:
    handler.remove_location();
    break;
  case 4:
    handler.add_stop();
    break;
  case 5:
    handler.insert_stop();
    break;
  case 6:
    handler.remove_stop();
    break;
  case 7:
    handler.print_trip();
    break;
  case 8:
    handler.show_trip_distance();
    break;
  case 9:
    handler.render_trip();
    break;
  case 10:
    handler.print_locations();
    break;
  case 11:
    handler.load_database();
    break;
  case 12:
    handler.save_database();
    break;
  case 0:
    return;
  }
}
