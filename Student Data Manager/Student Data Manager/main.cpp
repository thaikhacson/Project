#include "student.hpp"
#include "student_operator.hpp"


int main() {

	extern list<Student> database;

	int choice;
	do
	{
		cout << "-----MANAGER STUDENT-----" << endl;
		cout << "1. Add Student" << endl;
		cout << "2. Edit Student information" << endl;
		cout << "3. Delete Student" << endl;
		cout << "4. Search Student" << endl;
		cout << "5. Arrange Students" << endl;
		cout << "6. Print out the Student list" << endl;
		cout << "7. Save to file database_sv.csv" << endl;
		cout << "8. Exit" << endl;

		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			//addStudent(database);
			break;

		case 2:
			//editStudent(database);
			break;

		case 3:
			//deleteStudent(database);
			break;

		case 4:
			//searchStudent(database);
			break;

		case 5:

		case 6:
			//display(database);
		case 7:

		default:
			return 0;
			break;
		}
	} while (true);
}