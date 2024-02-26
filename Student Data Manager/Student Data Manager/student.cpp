#include "student.hpp"

list<Student> database;

// Function to set the name of the student
void Student::setName(string s_name) {
	this->name = s_name;
}

// Function to get the name of the student
string Student::getName() {
	return this->name;
}

// Function to set the gender of the student
void Student::setGender(Gender g_gender) {
	this->student_gender = g_gender;
}

// Function to get the gender of the student
Gender Student::getGender() {
	return this->student_gender;
}

// Function to set the age of the student
void Student::setAge(int i_age) {
	this->age = i_age;
}

// Function to get the age of the student
int Student::getAge() {
	return this->age;
}

// Function to set the math score of the student
void Student::setMathScore(double d_math) {
	this->math_score = d_math;
}

// Function to get the math score of the student
double Student::getMathScore() {
	return this->math_score;
}

// Function to set the physics score of the student
void Student::setPhysicsScore(double d_physics) {
	this->physics_score = d_physics;
}

// Function to get the physics score of the student
double Student::getPhysicsScore() {
	return this->physics_score;
}

// Function to set the chemistry score of the student
void Student::setChemistryScore(double d_chemistry) {
	this->chemistry_score = d_chemistry;
}

// Function to get the chemistry score of the student
double Student::getChemistryScore() {
	return this->chemistry_score;
}

// Function to calculate and return the average score of the student
double Student::getAverage() {
	return (this->math_score + this->physics_score + this->chemistry_score) / 3;
}

// Function to determine and return the rank of the student based on their average score
Rank Student::getRank() {
	if (getAverage() >= 8.0) {
		return EXCELLEENT;
	}
	else if (getAverage() >= 6.5) {
		return GOOD;
	}
	else if (getAverage() >= 5.0) {
		return AVERAGE;
	}
	else {
		return POOR;
	}
}

// Function to set the ID of the student
void Student::setID(int i_ID) {
	this->id = i_ID;
}

// Function to get the ID of the student
int Student::getID() {
	return this->id;
}