#include "student.hpp"

void Student::setName(string s_name) {
	this->name = s_name;
}

string Student::getName() {
	return this->name;
}

void Student::setGender(Gender g_gender) {
	this->student_gender = g_gender;
}

Gender Student::getGender() {
	return this->student_gender;
}

void Student::setAge(int i_age) {
	this->age = i_age;
}

int Student::getAge() {
	return this->age;
}

void Student::setMathScore(double d_math) {
	this->math_score = d_math;
}

double Student::getMathScore() {
	return this->math_score;
}

void Student::setPhysicsScore(double d_physics) {
	this->physics_score = d_physics;
}

double Student::getPhysicsScore() {
	return this->physics_score;
}

void Student::setChemistryScore(double d_chemistry) {
	this->chemistry_score = d_chemistry;
}

double Student::getChemistryScore() {
	return this->chemistry_score;
}

double Student::getAverage() {
	return (this->math_score + this->physics_score + this->chemistry_score) / 3;
}

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

void Student::setID(int i_ID) {
	this->id = i_ID;
}

int Student::getID() {
	return this->id;
}