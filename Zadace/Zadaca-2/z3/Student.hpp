#pragma once

#include <cstdint>
#include <ostream>
#include <string>
#include <vector>

#define MIN_YEAR 1
#define MAX_YEAR 4
#define MIN_GRADE 6
#define MAX_GRADE 10

using year_t = uint16_t;
using grade_t = uint16_t;
using grades_t = std::vector<grade_t>;

class Student
{
  public:
    Student() : study_year_ { 0 } { }
    Student(
      const std::string& name,
      const std::string& last_name,
      const std::string& index_number,
      year_t study_year,
      const grades_t& grades = grades_t());
    Student(Student&&) = default;
    Student(const Student&) = default;
    Student& operator=(Student&&) = default;
    Student& operator=(const Student&) = default;
    ~Student() = default;

    double average() const;

    friend std::ostream& operator<<(std::ostream&, const Student&);
    friend class StudentService;

  private:
    std::string name_;
    std::string last_name_;
    std::string index_number_;
    year_t study_year_;
    grades_t grades_;
};
