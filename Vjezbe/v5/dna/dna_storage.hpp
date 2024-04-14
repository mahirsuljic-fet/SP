#pragma once

#include <iosfwd>
#include <vector>

class DNAStorage
{
  public:
    // Ispisuje sve poznate članove lanca.
    void print(std::ostream&) const;

    // Ispisuje sa pozicije <pos> najvise <len> clanova.
    void print(std::ostream&, int pos, int len) const;

    // Na poziciju <pos> ubacuje elemente lanac.
    void insert(int pos, std::string lanac);

    // Brise najvise <len> elemenata sa pozicije <pos>.
    // Vratiti broj elemenata koji su obrisani.
    int remove(int pos, int len);

    // Spremiti sadrzaj u file (slicno kao print).
    void store(std::string filename) const;

    // Ucitati sadrzaj iz filea.
    // baca iznimku tipa std::runtime_error ukoliko file ne postoji.
    void load(std::string filename);

  private:
    std::vector<char> data;
};
