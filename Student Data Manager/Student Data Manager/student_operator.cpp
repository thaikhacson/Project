#include "student_operator.hpp"
#include <iomanip>
#include <algorithm>
#include <fstream>

extern list<Student> database;

/*
 * Function: addStudent
 * Description: Add a new student to the list of students.
 * Input:
 *   - Prompt the user to enter information such as name, age, gender, math score, physics score, and chemistry score.
 *   - Validate input for age, gender, and scores.
 * Output:
 *   - Add a new student to the list with the provided information.
 *   - Display a success message after each successful addition.
 *   - Allow the user to add more students or exit the process.
 */
void addStudent() {
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

/*
 * Function: editStudent
 * Description: Edit student information based on the given name and ID.
 * Input:
 *   - None
 * Output:
 *   - Modifies the student's information in the database.
 *   - Displays a message indicating success or failure.
 */
void editStudent() {
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
		printbyName(name);

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

/*
 * Function: deleteStudent
 * Description: Delete a student by name or ID.
 * Input:
 *   - None
 * Output:
 *   - Deletes the student information from the database.
 *   - Displays a message indicating success or failure.
 */
void deleteStudent() {
	int input;

	do
	{
		string name;
		cout << "Enter the Name to delete: ";
		cin.ignore();  // Clear the newline character from the buffer
		getline(cin, name);

		// Print students with the entered name
		printbyName(name);

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

/*
 * Function: searchStudent
 * Description: Search for a student by name or ID.
 * Input:
 *   - None
 * Output:
 *   - Displays the found student information or a message indicating that the student was not found.
 */
void searchStudent() {
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
					printbyName(name);
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
					printbyID(ID);
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

/*
 * Function: compareName
 * Description: Compare the last part of two names.
 * Input:
 *   - a: First name to compare.
 *   - b: Second name to compare.
 * Output:
 *   - Returns true if the last part of name a is less than the last part of name b.
 */
bool compareName(const string& a, const string& b) {
	size_t posA = a.find_last_of(' ');
	size_t posB = b.find_last_of(' ');

	if (posA != string::npos && posB != string::npos) {
		return a.substr(posA + 1) < b.substr(posB + 1);
	}

	return a < b; // Sort by the entire name if no space is found
}

/*
 * Function: sortByStudentID
 * Description: Sort the student list by ID.
 * Output:
 *   - Display a message indicating that the student list has been sorted by ID.
 *   - Display the sorted student list using the display function.
 */
void sortByStudentID() {
	// Sort the student list by ID
	database.sort([](Student& a, Student& b) {
		return a.getID() < b.getID();
		});

	cout << "\nStudent list sorted by ID." << endl;
	display();
}

/*
 * Function: sortByStudentName
 * Description: Sort the student list based on the last part of the name.
 *   - Utilizes the compareName function for sorting.
 * Output:
 *   - Display a message indicating that the student list has been sorted by Name.
 *   - Display the sorted student list using the display function.
 */
void sortByStudentName() {
	// Sort the student list based on the last part of the name
	database.sort([](Student& a, Student& b) {
		return compareName(a.getName(), b.getName());
		});

	cout << "\nStudent list sorted by Name." << endl;
	display();
}

/*
 * Function: printTableHeader
 * Description: Display the header of the table with columns: ID, Name, Gender, Average Score, Classification.
 * Output:
 *   - Display the header of the table with proper column widths and separators.
 */
void printTableHeader() {
	cout << left << setw(12) << "ID" << "|";
	cout << left << setw(10) << "Name" << "|";
	cout << left << setw(12) << "Gender" << "|";
	cout << left << setw(16) << "AverageScore" << "|";
	cout << left << "Classification" << endl;

	cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
}

/*
 * Function: printbyName
 * Description: Display the information of students with a specific name.
 * Input:
 *   - name: The name of the students to display.
 *   - Output the table header with columns: ID, Name, Gender, Average Score, Classification.
 *   - Iterate through each student in the list and display the information of the students with the matching name.
 * Output:
 *   - Display the information of students with the specified name.
 *   - If no student is found with the given name, display an error message.
 */
void printbyName(string name) {
	bool found = false;

	printTableHeader();

	for (auto it : database) {
		if (it.getName() == name) {
			found = true;
			cout << left << setw(12) << it.getID() << "|";
			cout << left << setw(10) << it.getName() << "|";
			cout << left << setw(12) << it.getGender() << "|";
			cout << left << setw(16) << it.getAverage() << "|";

			// Map rank enum to corresponding strings
			string rankStr;
			switch (it.getRank()) {
			case 0:
				rankStr = "Excellent";
				break;
			case 1:
				rankStr = "Good";
				break;
			case 2:
				rankStr = "Average";
				break;
			case 3:
				rankStr = "Poor";
				break;
			}

			cout << left << rankStr << endl;
		}
	}

	if (!found) {
		cout << "Student with Name " << name << " not found." << endl;
	}
}

/*
 * Function: printbyID
 * Description: Display the information of a student with a specific ID.
 * Input:
 *   - ID: The ID of the student to display.
 *   - Output the table header with columns: ID, Name, Gender, Average Score, Classification.
 *   - Iterate through each student in the list and display the information of the student with the matching ID.
 * Output:
 *   - Display the information of the student with the specified ID.
 *   - If no student is found with the given ID, display an error message.
 */
void printbyID(int ID) {
	bool found = false;

	printTableHeader();

	for (auto it : database) {
		if (it.getID() == ID) {
			found = true;
			cout << left << setw(12) << it.getID() << "|";
			cout << left << setw(10) << it.getName() << "|";
			cout << left << setw(12) << it.getGender() << "|";
			cout << left << setw(16) << it.getAverage() << "|";

			// Map rank enum to corresponding strings
			string rankStr;
			switch (it.getRank()) {
			case 0:
				rankStr = "Excellent";
				break;
			case 1:
				rankStr = "Good";
				break;
			case 2:
				rankStr = "Average";
				break;
			case 3:
				rankStr = "Poor";
				break;
			}

			cout << left << rankStr << endl;
		}
	}

	if (!found) {
		cout << "Student with ID " << ID << " not found." << endl;
	}
}

/*
 * Function: display
 * Description: Display the information of all students in the list.
 * Input:
 *   - Output the table header with columns: ID, Name, Gender, Average Score, Classification.
 *   - Iterate through each student in the list and display their information in a formatted table.
 * Output:
 *   - Display the information of all students in the list.
 */
void display() {
	printTableHeader();

	for (auto it : database) {
		cout << left << setw(12) << it.getID() << "|";
		cout << left << setw(10) << it.getName() << "|";
		cout << left << setw(12) << it.getGender() << "|";
		cout << left << setw(16) << it.getAverage() << "|";

		// Map rank enum to corresponding strings
		string rankStr;
		switch (it.getRank()) {
		case 0:
			rankStr = "Excellent";
			break;
		case 1:
			rankStr = "Good";
			break;
		case 2:
			rankStr = "Average";
			break;
		case 3:
			rankStr = "Poor";
			break;
		}

		cout << left << rankStr << endl;
	}
}

/*
 * Function: saveFile
 * Description: Save the student data from the list to a CSV file.
 * Input:
 *   - Open a CSV file for writing and check if it is opened successfully.
 *   - Write the header of the CSV file with columns: ID, Name, Age, Gender, Math Score, Physics Score, Chemistry Score.
 *   - Iterate through each student in the list and write their information to the file.
 *   - Close the file after writing.
 * Output:
 *   - Display a success message after saving the data to the 'database_sv.csv' file.
 */
void saveFile() {
	// Open the CSV file for writing
	ofstream outputFile("database_sv.csv");

	// Check if the file is opened successfully
	if (!outputFile.is_open()) {
		cout << "Error: Unable to open file for writing." << endl;
		return;
	}

	// Write the header of the CSV file
	outputFile << "ID,Name,Age,Gender,Math Score,Physics Score,Chemistry Score" << endl;

	// Write the data of each student to the file
	for (auto& Student : database) {
		outputFile << Student.getID() << ","
			<< Student.getName() << ","
			<< Student.getAge() << ","
			<< (Student.getGender() == MALE ? "Male" : "Female") << ","
			<< Student.getMathScore() << ","
			<< Student.getPhysicsScore() << ","
			<< Student.getChemistryScore() << endl;
	}

	// Close the file after writing
	outputFile.close();

	cout << "Data saved to 'database_sv.csv'." << endl;
}