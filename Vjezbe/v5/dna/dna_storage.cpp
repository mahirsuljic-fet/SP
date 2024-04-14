#include "dna_storage.hpp"
#include <ostream>
#include <string>

void DNAStorage::print(std::ostream& out) const
{
  for (const auto& c : data)
    out << c;
  out << std::endl;
}

void DNAStorage::print(std::ostream&, int pos, int len) const { }

void DNAStorage::insert(int pos, std::string lanac)
{
  if (pos > data.size())
    data.resize(pos, ' ');
  data.insert(data.begin() + pos, lanac.begin(), lanac.end());
}

int DNAStorage::remove(int pos, int len)
{
  auto endit = data.begin() + pos + len;
  if (endit > data.end())
    endit = data.end();
  data.erase(data.begin() + pos, data.begin() + pos + len);
  return len;
}

void DNAStorage::store(std::string filename) const { }

void DNAStorage::load(std::string filename) { }
