#include "Student.hpp"
#include <ostream>
#include <stdexcept>

Student::Student(
  const std::string& name,
  const std::string& last_name,
  const std::string& index_number,
  year_t study_year,
  const grades_t& grades)
  : name_ { name }, last_name_ { last_name }, index_number_ { index_number }, study_year_ { study_year }, grades_ { grades }
{
  if (study_year < MIN_YEAR || study_year > MAX_YEAR)
    throw std::out_of_range("Godina studija nije validna");
  for (const auto& grade : grades)
    if (grade < MIN_GRADE || grade > MAX_GRADE)
      throw std::out_of_range("Ocjena nije validna");
}

double Student::average() const
{
  if (grades_.empty()) return 0.0;
  double result = 0.0;
  for (const auto& grade : grades_) result += grade;
  return result / grades_.size();
}

std::ostream& operator<<(std::ostream& out, const Student& student)
{
  out << "Ime:\t\t" << student.name_ << std::endl;
  out << "Prezime:\t" << student.last_name_ << std::endl;
  out << "Broj indeksa:\t" << student.index_number_ << std::endl;
  out << "Godina studija:\t" << +student.study_year_ << std::endl;
  out << "Ocjene:\t\t";
  if (!student.grades_.empty())
  {
    for (auto it = student.grades_.begin(); it < student.grades_.end() - 1; ++it)
      out << +*it << ", ";
    out << +student.grades_.back();
  }

  return out << std::endl;
}
