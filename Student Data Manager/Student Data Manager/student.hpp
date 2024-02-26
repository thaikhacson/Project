#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <iostream>
#include <string>
#include <list>

using namespace std;

typedef enum Gender {
	MALE,
	FEMALE
} Gender;

typedef enum Rank {
	EXCELLEENT,
	GOOD,
	AVERAGE,
	POOR

} Rank;

class Student {
private:
	int id;
	string name;
	int age;
	Gender student_gender;
	double math_score;
	double physics_score;
	double chemistry_score;
public:
	Student(string name, int age, Gender gender, double math, double physics, double chemistry) :
		name(name), age(age), student_gender(gender), math_score(math), physics_score(physics), chemistry_score(chemistry)
	{
		static int ID = 20145000;
		id = ID;
		ID++;
	};

	void setName(string s_name);
	string getName();
	void setGender(Gender g_gender);
	Gender getGender();
	void setAge(int i_age);
	int getAge();
	void setMathScore(double d_math);
	double getMathScore();
	void setPhysicsScore(double d_physics);
	double getPhysicsScore();
	void setChemistryScore(double d_chemistry);
	double getChemistryScore();
	double getAverage();
	Rank getRank();
	void setID(int i_ID);
	int getID();
};


#endif