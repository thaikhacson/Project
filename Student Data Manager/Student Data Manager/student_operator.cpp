#include "student_operator.hpp"
#include <iomanip>

list<Student> database;

void addStudent(list<Student>& database) {
	string name;
	int age;
	Gender gender;
	double math, physics, chemistry;
	int sex, input;

	do {
		cout << "Enter Name: ";
		cin.ignore(); // Clear the newline character from the buffer
		getline(cin, name);

		cout << "Enter Age: ";
		cin >> age;

		// Input validation for age
		while (age < 0 || age > 110) {
			cout << "Invalid age. Please enter a valid age: ";
			cin.clear();
			cin.ignore();
			cin >> age;
		}

		do {
			cout << "Enter Gender: (0 - MALE / 1 - FEMALE): ";
			cin >> sex;

			// Input validation for gender
			if (sex == 0) {
				gender = MALE;
			}
			else if (sex == 1) {
				gender = FEMALE;
			}
			else {
				cout << "Invalid gender. Please enter 0 or 1." << endl;
			}

		} while (sex != 0 && sex != 1);

		cout << "Enter Math Score: ";
		cin >> math;

		// Input validation for scores
		while (math < 0 || math > 10) {
			cout << "Invalid math score. Please enter a valid score: ";
			cin.clear();
			cin.ignore();
			cin >> math;
		}

		cout << "Enter Physic Score: ";
		cin >> physics;

		while (physics < 0 || physics > 10) {
			cout << "Invalid physics score. Please enter a valid score: ";
			cin.clear();
			cin.ignore();
			cin >> physics;
		}

		cout << "Enter Chemistry Score: ";
		cin >> chemistry;

		while (chemistry < 0 || chemistry > 10) {
			cout << "Invalid chemistry score. Please enter a valid score: ";
			cin.clear();
			cin.ignore();
			cin >> chemistry;
		}

		// Construct and add a Student directly
		database.push_back(Student(name, age, gender, math, physics, chemistry));

		cout << "Student added successfully!" << endl;
		cout << "1. Add more students" << endl;
		cout << "2. Exit" << endl;
		cout << "Your choice: ";
		cin >> input;

	} while (input == 1);
}


void editStudent(list<Student>& database) {
	string name;
	int age;
	Gender gender;
	double math, physics, chemistry;
	int sex, input;

	do {
		cout << "Enter the Name to edit: ";
		cin.ignore();  // Clear the newline character from the buffer
		getline(cin, name);

		// Print students with the entered name
		printbyName(database, name);

		int ID;
		cout << "Enter the ID of the student you want to edit: ";
		cin >> ID;

		bool found = false;

		for (auto& it : database) {
			if (it.getID() == ID) {
				cout << "Enter an edit Name: ";
				cin.ignore();  // Clear the newline character from the buffer
				getline(cin, name);

				cout << "Enter the edit Age: ";
				cin >> age;
				cin.ignore();  // Clear the newline character

				do {
					cout << "Enter Gender edit: (0 - MALE / 1 - FEMALE): ";
					cin >> sex;
					if (sex == 0) {
						gender = MALE;
					}
					else if (sex == 1) {
						gender = FEMALE;  // Fix the assignment here
					}
				} while (sex != 0 && sex != 1);

				cout << "Enter edit Math Score: ";
				cin >> math;

				cout << "Enter edit Physic Score: ";
				cin >> physics;

				cout << "Enter edit Chemistry Score: ";
				cin >> chemistry;

				// Update the student's information
				it.setName(name);
				it.setAge(age);
				it.setGender(gender);
				it.setMathScore(math);
				it.setPhysicsScore(physics);
				it.setChemistryScore(chemistry);

				cout << "Edit student successfully!" << endl;
				found = true;
				break;  // Exit the loop after editing one student
			}
		}

		if (!found) {
			cout << "Student with ID " << ID << " not found." << endl;
		}

		cout << "1. Edit another Student" << endl;
		cout << "2. Exit" << endl;
		cout << "Your choice: ";
		cin >> input;

	} while (input == 1);
}



void deleteStudent(list<Student>& database) {
	int input;

	do
	{
		string name;
		cout << "Enter the Name to delete: ";
		cin.ignore();  // Clear the newline character from the buffer
		getline(cin, name);

		// Print students with the entered name
		printbyName(database, name);

		int ID;
		cout << "Enter the ID of the student you want to delete: ";
		cin >> ID;

		bool found = false;
		for (auto it = database.begin(); it != database.end(); ++it) {
			if (it->getID() == ID) {
				it = database.erase(it);
				found = true;
				cout << "Delete Student successfully!" << endl;
				break;
			}
		}

		if (!found) {
			cout << "Student with ID " << ID << " not found." << endl;
		}

		cout << "1. Continue deleting Students" << endl;
		cout << "2. Exit" << endl;
		cout << "Your choice: ";
		cin >> input;

	} while (input == 1);
}


void searchStudent(list<Student>& database) {
	string name;
	int ID;
	int input1;
	bool found;

	do {
		cout << "1. Search by Name" << endl;
		cout << "2. Search by ID" << endl;
		cout << "3. Exit" << endl;
		cout << "Your choice: ";
		cin >> input1;

		switch (input1) {
		case 1:
			cout << "Enter search Name: ";
			cin.ignore();
			getline(cin, name);

			found = false;

			printTableHeader();

			for (auto it = database.begin(); it != database.end(); it++) {
				if (it->getName() == name) {
					found = true;
					printbyName(database, name);
				}
			}

			if (!found) {
				cout << "Student with Name " << name << " not found." << endl;
			}

			break;

		case 2:
			cout << "Enter search ID: ";
			cin >> ID;

			found = false;

			printTableHeader();

			for (auto it = database.begin(); it != database.end(); it++) {
				if (it->getID() == ID) {
					found = true;
					printbyID(database, ID);
				}
			}

			if (!found) {
				cout << "Student with ID " << ID << " not found." << endl;
			}

			break;

		default:
			break;
		}

	} while (input1 != 1 && input1 != 2 && input1 != 3);
}


void printTableHeader() {
	cout << left << setw(12) << "ID" << "|";
	cout << left << setw(10) << "Name" << "|";
	cout << left << setw(12) << "Gender" << "|";
	cout << left << setw(16) << "AverageScore" << "|";
	cout << left << "Classification" << endl;

	cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
}

void printbyName(list<Student>& database, string name) {
	bool found = false;

	printTableHeader();

	for (auto it : database) {
		if (it.getName() == name) {
			found = true;
			cout << left << setw(12) << it.getID() << "|";
			cout << left << setw(10) << it.getName() << "|";
			cout << left << setw(12) << it.getGender() << "|";
			cout << left << setw(16) << it.getAverage() << "|";
			cout << left << it.getRank() << endl;
		}
	}

	if (!found) {
		cout << "Student with Name " << name << " not found." << endl;
	}
}


void printbyID(list<Student>& database, int ID) {
	bool found = false;

	printTableHeader();

	for (auto it : database) {
		if (it.getID() == ID) {
			found = true;
			cout << left << setw(12) << it.getID() << "|";
			cout << left << setw(10) << it.getName() << "|";
			cout << left << setw(12) << it.getGender() << "|";
			cout << left << setw(16) << it.getAverage() << "|";
			cout << left << it.getRank() << endl;
		}
	}

	if (!found) {
		cout << "Student with ID " << ID << " not found." << endl;
	}
}


void display(list<Student> database) {
	printTableHeader();

	for (auto it : database) {
		cout << left << setw(12) << it.getID() << "|";
		cout << left << setw(10) << it.getName() << "|";
		cout << left << setw(12) << it.getGender() << "|";
		cout << left << setw(16) << it.getAverage() << "|";
		cout << left << it.getRank() << endl;
	}
}
