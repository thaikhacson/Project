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
			cout << "-----ADD STUDENT-----" << endl;
			addStudent();
			break;

		case 2:
			cout << "-----EDIT STUDENT-----" << endl;
			editStudent();
			break;

		case 3:
			cout << "-----DELETE STUDENT-----" << endl;
			deleteStudent();
			break;

		case 4:
			cout << "-----SEARCH STUDENT-----" << endl;
			searchStudent();
			break;

		case 5:
			cout << "-----ARRANGE STUDENT-----" << endl;
			int arrangeInput;
			do
			{
				cout << "1. Arrange Student by Name" << endl;
				cout << "2. Arrange Student by ID" << endl;
				cout << "3. Exit" << endl;
				cout << "Enter your choice: ";
				cin >> arrangeInput;

				switch (arrangeInput) {
				case 1:
					sortByStudentName();
					break;
				case 2:
					sortByStudentID();
					break;
				case 3:
					break;
				default:
					break;
				}
			} while (arrangeInput != 3);

		case 6:
			cout << "-----PRINT OUT THE STUDENT LIST-----" << endl;
			int printInput;
			do
			{
				cout << "1. Print out the Student list by Name" << endl;
				cout << "2. Print out the Student list by ID" << endl;
				cout << "3. Print the entire list" << endl;
				cout << "4. Exit" << endl;
				cout << "Enter your choice: ";
				cin >> printInput;

				switch (printInput)
				{
				case 1: {
					string name;
					cout << "Enter the Name you want to print" << endl;
					getline(cin, name);
					printbyName(name);
					break;
				}
				
				case 2: {
					int ID;
					cout << "Enter the ID you want to print" << endl;
					cin >> ID;
					printbyID(ID);
					break;
				}
				
				case 3:
					display();
					break;

				case 4:
					break;

				default:
					printf("Invalid choice. Please enter a valid option.\n");
					break;
				}
			} while (printInput != 4);
			break;

		case 7:
			cout << "-----SAVE TO FILE-----" << endl;
			saveFile();
			break;

		case 8:
			break;

		default:
			printf("Invalid choice. Please enter a valid option.\n");
			break;
		}
	} while (choice != 8);

	return 0;
}