#ifndef STUDENT_OPERATOR_HPP
#define STUDENT_OPERATOR_HPP

#include "student.hpp"
#include <list>


void addStudent(list<Student>& database);
void editStudent(list<Student>& database);
void deleteStudent(list<Student>& database);
void searchStudent(list<Student>& database);
void sortStudent(list<Student>& database);
void printTableHeader();
void printbyName(list<Student>& database, string name);
void printbyID(list<Student>& database, int ID);
void display(list<Student>& database);
// void saveFile();

#endif
