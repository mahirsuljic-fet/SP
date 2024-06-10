#include <cstddef>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

int main()
{
  std::map<std::string, std::vector<int>> dictionary;

  std::ifstream file("story.txt");

  if (!file)
  {
    std::cout << "Desila se greska pri citanju fajla" << std::endl;
    return 0;
  }

  std::string word;
  size_t line_number = 0;

  while (file >> word)
    dictionary[word].push_back(++line_number);

  for (const auto& word : dictionary)
  {
    std::cout << "Rijec '" << word.first << "' se nalazi na pozicijama:" << std::endl;
    for (const auto& el : word.second)
      std::cout << el << ", ";
    std::cout << std::endl;
  }

  file.close();

  return 0;
}
