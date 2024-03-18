#pragma once

#include <iostream>
#include <string>

class Radnik
{
  public:
    friend std::istream& operator>>(std::istream&, Radnik&);

    const std::string& ime() const
    {
      return ime_;
    }
    void ime(const std::string& ime)
    {
      ime_ = ime;
    }

    const std::string& prezime() const
    {
      return prezime_;
    }
    void prezime(const std::string& prezime)
    {
      prezime_ = prezime;
    }

    int godine() const
    {
      return godine_;
    }
    void godine(int godina)
    {
      godine_ = godina;
    }

    int godineStaza() const
    {
      return godine_staza_;
    }

    void godineStaza(int godine_staza)
    {
      godine_staza_ = godine_staza;
    }

    double plata() const
    {
      return plata_;
    }

    void plata(double plata)
    {
      plata_ = plata;
    }

    const std::string& brojTelefona() const
    {
      return broj_telefona_;
    }

    void brojTelefona(const std::string& broj_telefona)
    {
      broj_telefona_ = broj_telefona;
    }

    void brojTelefona(std::string&& broj_telefona)
    {
      broj_telefona_ = std::move(broj_telefona);
    }

  private:
    std::string ime_;
    std::string prezime_;
    int godine_;
    int godine_staza_;
    double plata_;
    std::string broj_telefona_;
};

std::ostream& operator<<(std::ostream&, const Radnik&);
