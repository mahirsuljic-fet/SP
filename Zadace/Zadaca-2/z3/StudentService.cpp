#include "StudentService.hpp"
#include "Student.hpp"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

void StudentService::add_student(const Student& student)
{
  students_.push_back(student);
}

void StudentService::add_student(Student&& student)
{
  students_.push_back(std::move(student));
}

void StudentService::add_student(const std::string& name, const std::string& last_name, const std::string& index_number, year_t study_year)
{
  students_.push_back(Student { name, last_name, index_number, study_year });
}

void StudentService::add_student(const std::string& name, const std::string& last_name, const std::string& index_number, year_t study_year, grades_t grades)
{
  students_.push_back(Student { name, last_name, index_number, study_year, grades });
}

void StudentService::edit_student(const std::string& index_number, const Student& new_student)
{
  *find_student_(index_number) = new_student;
}

void StudentService::delete_student(const std::string& index_number)
{
  students_.erase(find_student_(index_number));
}

void StudentService::print_students_sorted_by_name() const
{
  auto sorted_students = students_;
  auto predicate = [](const Student& s1, const Student& s2) { return s1.name_ < s2.name_; };
  std::sort(sorted_students.begin(), sorted_students.end(), predicate);
  for (const auto& student : sorted_students) std::cout << student << std::endl;
}

void StudentService::print_students_sorted_by_last_name() const
{
  auto sorted_students = students_;
  auto predicate = [](const Student& s1, const Student& s2) { return s1.last_name_ < s2.last_name_; };
  std::sort(sorted_students.begin(), sorted_students.end(), predicate);
  for (const auto& student : sorted_students) std::cout << student << std::endl;
}

void StudentService::print_students_sorted_by_grades() const
{
  auto sorted_students = students_;
  auto predicate = [](const Student& s1, const Student& s2) { return s1.average() > s2.average(); };
  std::sort(sorted_students.begin(), sorted_students.end(), predicate);
  for (const auto& student : sorted_students) std::cout << student << std::endl;
}

void StudentService::print_students_by_year(year_t year) const
{
  students_t filtered_students;
  auto predicate = [&year](const Student& s) { return s.study_year_ == year; };
  std::copy_if(students_.begin(), students_.end(), std::back_inserter(filtered_students), predicate);
  for (const auto& student : filtered_students) std::cout << student << std::endl;
}

void StudentService::print_students_average_above(double average) const
{
  students_t filtered_students;
  auto predicate = [&average](const Student& s) { return s.average() >= average; };
  std::copy_if(students_.begin(), students_.end(), std::back_inserter(filtered_students), predicate);
  for (const auto& student : filtered_students) std::cout << student << std::endl;
}

void StudentService::print_year_report(year_t year) const
{
  students_t filtered_students;
  auto predicate = [&year](const Student& s) { return s.study_year_ == year; };
  std::copy_if(students_.begin(), students_.end(), std::back_inserter(filtered_students), predicate);

  size_t total_grades_count = 0;
  std::map<grade_t, size_t> grades_count;
  double average = 0;

  for (const auto& student : filtered_students)
  {
    total_grades_count += student.grades_.size();
    for (const auto& grade : student.grades_)
    {
      ++grades_count[grade];
      average += grade;
    }
  }

  average /= total_grades_count;

  std::cout << "Broj studenata:\t\t" << filtered_students.size() << std::endl
            << "Broj upisanih ocjena:\t" << total_grades_count << std::endl;
  for (int i = MAX_GRADE; i >= MIN_GRADE; --i)
    std::cout << "Broj ocjena " << i << ":\t\t" << grades_count[i] << std::endl;
  std::cout << "Prosjek u godini:\t" << average << " (" << std::round(average) << ")" << std::endl;
}

students_t::iterator StudentService::find_student_(const std::string& index_number)
{
  auto predicate = [&index_number](const Student& s) { return s.index_number_ == index_number; };
  return std::find_if(students_.begin(), students_.end(), predicate);
}

Student StudentService::get_student(const std::string& index_number)
{
  return *find_student_(index_number);
}

bool StudentService::student_exists(const std::string& index_number)
{
  return find_student_(index_number) != students_.end();
}
