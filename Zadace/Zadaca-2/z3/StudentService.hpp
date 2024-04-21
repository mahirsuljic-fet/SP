#pragma once

#include "Student.hpp"
#include <string>
#include <vector>

using students_t = std::vector<Student>;

class StudentService
{
  public:
    StudentService() = default;
    StudentService(StudentService&&) = default;
    StudentService(const StudentService&) = default;
    StudentService& operator=(StudentService&&) = default;
    StudentService& operator=(const StudentService&) = default;
    ~StudentService() = default;

    void add_student(const Student&);
    void add_student(Student&& student);
    void add_student(const std::string&, const std::string&, const std::string&, year_t);
    void add_student(const std::string&, const std::string&, const std::string&, year_t, grades_t);
    void edit_student(const std::string& index_number, const Student&);
    void delete_student(const std::string& index_number);

    void print_students_sorted_by_name() const;
    void print_students_sorted_by_last_name() const;
    void print_students_sorted_by_grades() const;
    void print_students_by_year(year_t year) const;
    void print_students_average_above(double average) const;
    void print_year_report(year_t year) const;

    Student get_student(const std::string& index_number);
    bool student_exists(const std::string& index_number);

  private:
    students_t students_;
    students_t::iterator find_student_(const std::string& index_number);
};
