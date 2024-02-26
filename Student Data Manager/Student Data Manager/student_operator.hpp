#ifndef STUDENT_OPERATOR_HPP
#define STUDENT_OPERATOR_HPP

#include "student.hpp"
#include <list>
#include <functional>

void addStudent();
void editStudent();
void deleteStudent();
void searchStudent();
void sortByStudentName();
void sortByStudentID();
void printTableHeader();
void printbyName(std::string name);
void printbyID(int ID);
void display();
void saveFile();

#endif
