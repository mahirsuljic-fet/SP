#include "Student.hpp"
#include "StudentService.hpp"
#include <cstdlib>
#include <exception>
#include <ios>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>

#define MAX_OPTION 9

static StudentService service;

int menu_option();
void print_menu();
void handle_option(int);

void dialogue_add_student();
void dialogue_edit_student();
void dialogue_delete_student();
void dialogue_print_students_by_name();
void dialogue_print_students_by_last_name();
void dialogue_print_students_by_grades();
void dialogue_print_students_by_year();
void dialogue_print_students_average_above();
void dialogue_print_year_report();

void cin_reset();

int main()
{
  int option = -1;

  while (option)
  {
    option = menu_option();
    handle_option(option);
  }

  return 0;
}

void print_menu()
{
  std::cout << "STUDENTSKA SLUZBA" << std::endl
            << std::endl
            << "1 - Dodaj studenta" << std::endl
            << "2 - Izmijeni studenta" << std::endl
            << "3 - Izbrisi studenta" << std::endl
            << "4 - Ispis studenta sortiranih po imenu" << std::endl
            << "5 - Ispis studenta sortiranih po prezimenu" << std::endl
            << "6 - Ispis studenta sortiranih po prosjeku" << std::endl
            << "7 - Ispis studenta po godini studija" << std::endl
            << "8 - Ispis studenta sa datim prosjekom" << std::endl
            << "9 - Izvjestaj o godini studija" << std::endl
            << "0 - Izlaz" << std::endl
            << std::endl
            << "Izbor: ";
}

int menu_option()
{
  unsigned int option = 0;

  do
  {
    print_menu();
    std::cin >> option;
    system("clear");

    if (option > MAX_OPTION)
      std::cout << "Izbor nije validan!\n\n";
  }
  while (option > MAX_OPTION);

  return option;
}

void handle_option(int option)
{
  switch (option)
  {
  case 1:
    dialogue_add_student();
    break;
  case 2:
    dialogue_edit_student();
    break;
  case 3:
    dialogue_delete_student();
    break;
  case 4:
    dialogue_print_students_by_name();
    break;
  case 5:
    dialogue_print_students_by_last_name();
    break;
  case 6:
    dialogue_print_students_by_grades();
    break;
  case 7:
    dialogue_print_students_by_year();
    break;
  case 8:
    dialogue_print_students_average_above();
    break;
  case 9:
    dialogue_print_year_report();
    break;
  case 0:
  default:
    return;
  }
}

void dialogue_add_student()
{
  std::string name;
  std::string last_name;
  std::string index_number;
  std::string grades_str;
  year_t study_year;
  grades_t grades;
  grade_t grade;

  while (true)
  {
    try
    {
      system("clear");
      std::cout << "UNOS STUDENTA" << std::endl;
      std::cout << std::endl;

      std::cout << "Unesite ime studenta: ";
      if (!(std::cin >> name)) throw std::invalid_argument("Unos imena nije validan!");

      std::cout << "Unesite prezime studenta: ";
      if (!(std::cin >> last_name)) throw std::invalid_argument("Unos prezimena nije validan!");

      std::cout << "Unesite broj indeksa studenta: ";
      if (!(std::cin >> index_number))
        throw std::invalid_argument("Unos broja indeksa nije validan!");
      else if (service.student_exists(index_number))
        throw std::invalid_argument("Student sa datim brojem indeksa vec postoji!");

      std::cout << "Unesite godinu studija studenta (" << MIN_YEAR << " <= unos <= " << MAX_YEAR << "): ";
      if (!(std::cin >> study_year))
        throw std::invalid_argument("Unos godine studija nije validan!");
      else if (study_year < MIN_YEAR || study_year > MAX_YEAR)
        throw std::out_of_range("Godina studija nije u validnom opsegu!");

      std::cout << "Unesite ocjene studenta (" << MIN_GRADE << " <= unos <= " << MAX_GRADE << "), razdvojene razmakom, prekid unosa sa ENTER: ";
      cin_reset();
      std::getline(std::cin, grades_str);
      std::stringstream oss { grades_str };
      while (oss >> grade)
      {
        if (grade >= MIN_GRADE && grade <= MAX_GRADE)
          grades.push_back(grade);
        else
          throw std::out_of_range("Unesna ocjena nije u validnom opsegu!");
      }

      service.add_student(Student { name, last_name, index_number, study_year, grades });

      system("clear");
      std::cout << "Student uspjesno unesen!" << std::endl;
      std::cout << std::endl;
      return;
    }
    catch (const std::exception& ex)
    {
      std::cout << std::endl;
      std::cout << ex.what() << std::endl;
      std::cout << "Pritisnite bilo koju tipku za ponovni unos ili 0 za povratak nazad: ";
      if (grades_str.empty()) cin_reset();
      char c = std::cin.get();
      if (c == '0') return;
    }
  }
}

void dialogue_edit_student()
{
  std::string name;
  std::string last_name;
  std::string index_number;
  std::string grades_str;
  year_t study_year;
  grades_t grades;
  grade_t grade;

  while (true)
  {
    try
    {
      system("clear");
      std::cout << "IZMJENA STUDENTA" << std::endl;
      std::cout << std::endl;

      std::cout << "Unesite broj indeksa studenta: ";
      if (!(std::cin >> index_number))
        throw std::invalid_argument("Unos broja indeksa nije validan!");
      else if (!service.student_exists(index_number))
        throw std::invalid_argument("Student sa datim brojem indeksa ne postoji!");

      std::cout << std::endl;
      std::cout << "STUDENT" << std::endl;
      std::cout << service.get_student(index_number) << std::endl;

      std::cout << "Unesite novo ime studenta: ";
      if (!(std::cin >> name)) throw std::invalid_argument("Unos imena nije validan!");

      std::cout << "Unesite novo prezime studenta: ";
      if (!(std::cin >> last_name)) throw std::invalid_argument("Unos prezimena nije validan!");

      std::cout << "Unesite novu godinu studija studenta (" << MIN_YEAR << " <= unos <= " << MAX_YEAR << "): ";
      if (!(std::cin >> study_year))
        throw std::invalid_argument("Unos godine studija nije validan!");
      else if (study_year < MIN_YEAR || study_year > MAX_YEAR)
        throw std::out_of_range("Godina studija nije u validnom opsegu!");

      std::cout << "Unesite nove ocjene studenta (" << MIN_GRADE << " <= unos <= " << MAX_GRADE << ", prekid unosa sa ENTER): ";
      cin_reset();
      std::getline(std::cin, grades_str);
      std::stringstream oss { grades_str };
      while (oss >> grade)
      {
        if (grade >= MIN_GRADE && grade <= MAX_GRADE)
          grades.push_back(grade);
        else
          throw std::out_of_range("Unesna ocjena nije u validnom opsegu!");
      }

      service.edit_student(index_number, Student { name, last_name, index_number, study_year, grades });

      system("clear");
      std::cout << "Student uspjesno izmijenjen!" << std::endl;
      std::cout << std::endl;
      return;
    }
    catch (const std::exception& ex)
    {
      std::cout << std::endl;
      std::cout << ex.what() << std::endl;
      std::cout << "Pritisnite bilo koju tipku za ponovni unos ili 0 za povratak nazad: ";
      if (grades_str.empty()) cin_reset();
      char c = std::cin.get();
      if (c == '0') return;
    }
  }
}

void dialogue_delete_student()
{
  std::string index_number;

  while (true)
  {
    try
    {
      system("clear");
      std::cout << "BRISANJE STUDENTA" << std::endl;
      std::cout << std::endl;

      std::cout << "Unesite broj indeksa studenta: ";
      if (!(std::cin >> index_number))
        throw std::invalid_argument("Unos broja indeksa nije validan!");
      else if (!service.student_exists(index_number))
        throw std::invalid_argument("Student sa datim brojem indeksa ne postoji!");

      service.delete_student(index_number);

      system("clear");
      std::cout << "Student uspjesno izbrisan!" << std::endl;
      std::cout << std::endl;
      return;
    }
    catch (const std::exception& ex)
    {
      std::cout << std::endl;
      std::cout << ex.what() << std::endl;
      std::cout << "Pritisnite bilo koju tipku za ponovni unos ili 0 za povratak nazad: ";
      cin_reset();
      char c = std::cin.get();
      if (c == '0') return;
    }
  }
}

void dialogue_print_students_by_name()
{
  system("clear");
  std::cout << "STUDENTI SORTIRANI PO IMENU" << std::endl;
  std::cout << std::endl;
  service.print_students_sorted_by_name();
  std::cout << std::endl;
  std::cout << "Pritisnite bilo koju tipku za nastavak... ";
  cin_reset();
  std::cin.get();
  system("clear");
  return;
}

void dialogue_print_students_by_last_name()
{
  system("clear");
  std::cout << "STUDENTI SORTIRANI PO PREZIMENU" << std::endl;
  std::cout << std::endl;
  service.print_students_sorted_by_last_name();
  std::cout << std::endl;
  std::cout << "Pritisnite bilo koju tipku za nastavak... ";
  cin_reset();
  std::cin.get();
  system("clear");
  return;
}

void dialogue_print_students_by_grades()
{
  system("clear");
  std::cout << "STUDENTI SORTIRANI PO PROSJEKU" << std::endl;
  std::cout << std::endl;
  service.print_students_sorted_by_grades();
  std::cout << std::endl;
  std::cout << "Pritisnite bilo koju tipku za nastavak... ";
  cin_reset();
  std::cin.get();
  system("clear");
  return;
}

void dialogue_print_students_by_year()
{
  year_t study_year;

  while (true)
  {
    try
    {
      system("clear");
      std::cout << "ISPIS STUDENTA PO GODINI STUDIJA" << std::endl;
      std::cout << std::endl;

      std::cout << "Unesite godinu studija studenta (" << MIN_YEAR << " <= unos <= " << MAX_YEAR << "): ";
      if (!(std::cin >> study_year))
        throw std::invalid_argument("Unos godine studija nije validan!");
      else if (study_year < MIN_YEAR || study_year > MAX_YEAR)
        throw std::out_of_range("Godina studija nije u validnom opsegu!");

      system("clear");
      std::cout << "STUDENTI SA " << study_year << " STUDIJSKE GODINE" << std::endl;
      std::cout << std::endl;
      service.print_students_by_year(study_year);
      std::cout << std::endl;

      std::cout << "Pritisnite bilo koju tipku za nastavak... ";
      cin_reset();
      std::cin.get();
      system("clear");
      return;
    }
    catch (const std::exception& ex)
    {
      std::cout << std::endl;
      std::cout << ex.what() << std::endl;
      std::cout << "Pritisnite bilo koju tipku za ponovni unos ili 0 za povratak nazad: ";
      cin_reset();
      char c = std::cin.get();
      if (c == '0') return;
    }
  }
}

void dialogue_print_students_average_above()
{
  double grade_limit;

  while (true)
  {
    try
    {
      system("clear");
      std::cout << "ISPIS STUDENTA SA PROSJEKOM IZNAD NAVEDENOG" << std::endl;
      std::cout << std::endl;

      std::cout << "Unesite prosjek (" << MIN_GRADE << " <= unos <= " << MAX_GRADE << "): ";
      if (!(std::cin >> grade_limit))
        throw std::invalid_argument("Uneseni prosjek nije validan!");
      else if (grade_limit < MIN_GRADE || grade_limit > MAX_GRADE)
        throw std::out_of_range("Unesini prosjek nije u validnom opsegu!");

      system("clear");
      std::cout << "STUDENTI SA PROSJEKOM IZNAD " << grade_limit << std::endl;
      std::cout << std::endl;
      service.print_students_average_above(grade_limit);
      std::cout << std::endl;

      std::cout << "Pritisnite bilo koju tipku za nastavak... ";
      cin_reset();
      std::cin.get();
      system("clear");
      return;
    }
    catch (const std::exception& ex)
    {
      std::cout << std::endl;
      std::cout << ex.what() << std::endl;
      std::cout << "Pritisnite bilo koju tipku za ponovni unos ili 0 za povratak nazad: ";
      cin_reset();
      char c = std::cin.get();
      if (c == '0') return;
    }
  }
}

void dialogue_print_year_report()
{
  year_t study_year;

  while (true)
  {
    try
    {
      system("clear");
      std::cout << "IZVJESTAJ GODINE STUDIJA" << std::endl;
      std::cout << std::endl;

      std::cout << "Unesite godinu studija (" << MIN_YEAR << " <= unos <= " << MAX_YEAR << "): ";
      if (!(std::cin >> study_year))
        throw std::invalid_argument("Unos godine studija nije validan!");
      else if (study_year < MIN_YEAR || study_year > MAX_YEAR)
        throw std::out_of_range("Godina studija nije u validnom opsegu!");

      system("clear");
      std::cout << "IZVJESTAJ " << study_year << " STUDIJSKE GODINE" << std::endl;
      std::cout << std::endl;
      service.print_year_report(study_year);
      std::cout << std::endl;

      std::cout << "Pritisnite bilo koju tipku za nastavak... ";
      cin_reset();
      std::cin.get();
      system("clear");
      return;
    }
    catch (const std::exception& ex)
    {
      std::cout << std::endl;
      std::cout << ex.what() << std::endl;
      std::cout << "Pritisnite bilo koju tipku za ponovni unos ili 0 za povratak nazad: ";
      cin_reset();
      char c = std::cin.get();
      if (c == '0') return;
    }
  }
}

void cin_reset()
{
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
