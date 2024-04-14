#include "dna_storage.hpp"
#include <iostream>
#include <sstream>

void print_prompt()
{
  std::cout
    << "Welcome to DNA storage. Please enter one of the following options:\n"
    << "- print\n"
    << "- print <pos> <len>\n"
    << "- insert <pos> <lanac>\n"
    << "- remove <pos> <len>\n"
    << "- store <file>\n"
    << "- load <file>\n"
    << "- exit\n"
    << std::endl;
}

int main()
{
  DNAStorage storage;
  std::string input;
  while (true)
  {
    print_prompt();
    std::cout << "> ";
    std::getline(std::cin, input);
    std::stringstream ss { std::move(input) };
    ss >> input;
    if (!ss)
    {
      std::cout << "Input failed" << std::endl;
    }
    else if (input == "print")
    {
      storage.print(std::cout);
    }
    else if (input == "insert")
    {
      int pos;
      ss >> pos >> input;
      if (ss)
        storage.insert(pos, input);
    }
    else if (input == "remove")
    {
      int pos, len;
      ss >> pos >> len;
      if (ss)
        storage.remove(pos, len);
      else
        std::cout << "Error!" << std::endl;
    }
    else if (input == "store")
    {
    }
    else if (input == "load")
    {
    }
    else if (input == "exit")
    {
      return 0;
    }
  }
}
