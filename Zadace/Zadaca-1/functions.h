#pragma once

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

template <typename T>
void load_from_file(const std::string& file_name, std::vector<T>& vec)
{
  std::string current_line;
  std::ifstream input(file_name);

  if (!input) throw std::runtime_error("Nije moguce otvoriti fajl \"" + file_name + "\"");

  auto line_count = [&input]() {
    size_t lines = 0;
    std::string temp;
    while (std::getline(input, temp)) ++lines;
    input.clear();
    input.seekg(0, input.beg); // vrati na pocetak fajla
    return lines;
  };

  std::cout << "Citanje fajla \"" << file_name << "\"..." << std::endl;

  vec.reserve(line_count());

  std::getline(input, current_line); // odbacivanje prve linije fajla
  while (std::getline(input, current_line))
  {
    try
    {
      vec.push_back(T(current_line));
    }
    catch (std::invalid_argument err)
    {
      std::cout << "Greska pri citanju \"" << current_line << "\": " << err.what() << std::endl;
    }
    catch (...)
    {
      std::cout << "Desila se nepoznata greska pri citanju: " << current_line << std::endl;
    }
  }

  input.close();
  std::cout << "Fajl ucitan" << std::endl;
}

template <typename T>
void store_to_file(const std::string& file_name, std::vector<T>& vec)
{
  std::cout << "Ispisivanje u fajl \"" << file_name << "\"..." << std::endl;
  std::ofstream output(file_name);

  if (!output) throw std::runtime_error("Nije moguce pisati u fajl \"" + file_name + "\"");

  for (const auto& item : vec)
    output << item << std::endl;
  output.close();

  std::cout << "Fajl spremljen" << std::endl;
}
