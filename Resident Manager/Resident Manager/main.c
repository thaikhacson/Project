#include <stdio.h>
#include <string.h>
#include "manager.h"
#include "member.h"

int main() {
    extern TreeNode* root;

    const char* filename = "MyFile.csv";
    FILE* file = fopen(filename, "a");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    /// Move the file pointer to the beginning of the file and check if the file is empty
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0) {
        fprintf(file, "uID,roomNumber,name,licensePlates");
    }

    int choice;
    do {
        printf("\n===== Menu =====\n");
        printf("1. Add Member\n");
        printf("2. Delete Member\n");
        printf("3. Edit Member\n");
        printf("4. Search Member By UID\n");
        printf("5. Search Member By License Plate\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: {
            Member member;
            printf("Enter UID: ");
            scanf("%s", member.uid);

            // Remove the newline character from the input buffer
            while (getchar() != '\n');

            printf("Enter room number: ");
            scanf("%s", member.roomNumber);

            while (getchar() != '\n');

            printf("Enter name: ");
            //scanf("%s", member.name);
            fgets(member.name, sizeof(member.name), stdin);
            member.name[strcspn(member.name, "\n")] = '\0';

            printf("Enter license plate: ");
            scanf("%s", member.licensePlate);

            while (getchar() != '\n');

            addMember(filename, member);
            display_tree(root);
            printf("\n");
            break;
        }
        case 2: {
            char uidToDelete[20];
            printf("Enter UID to delete: ");
            scanf("%s", uidToDelete);
            deleteMember(filename, uidToDelete);
            break;
        }

        case 3: {
            char uidToEdit[20];
            printf("Enter UID to edit: ");
            scanf("%s", uidToEdit);
            Member updatedMember;
            printf("Enter updated UID: ");
            scanf("%s", updatedMember.uid);

            while (getchar() != '\n');

            printf("Enter updated room number: ");
            scanf("%s", updatedMember.roomNumber);

            while (getchar() != '\n');

            printf("Enter updated name: ");
            fgets(updatedMember.name, sizeof(updatedMember.name), stdin);
            updatedMember.name[strcspn(updatedMember.name, "\n")] = '\0';

            printf("Enter updated license plate: ");
            scanf("%s", updatedMember.licensePlate);

            editMember(filename, updatedMember, uidToEdit);

            display_tree(root);
            break;
        }
        case 4: {
            const char* uidToSearch[10];
            printf("Enter UID to Search: ");
            scanf("%s", uidToSearch);
            TreeNode* found_node = find_by_uid(root, uidToSearch);
            if (found_node != NULL) {
                printf("\nFound person with UID %s:\n", uidToSearch);
                printf("Name: %s, Room Number: %s, License Plate: %s\n",
                    found_node->member.name, found_node->member.roomNumber, found_node->member.licensePlate);
            }
            else {
                printf("\nPerson with UID %s not found.\n", uidToSearch);
            }
            break;
        }
        case 5: {
            const char* licensePlate[10];
            printf("Enter License Plate to Search: ");
            scanf("%s", licensePlate);
            TreeNode* found_node = find_by_license_plate(root, licensePlate);
            if (found_node != NULL) {
                printf("\nFound person with License Plate %s:\n", licensePlate);
                printf("UID: %s, Name: %s, Room Number: %s\n",
                    found_node->member.uid, found_node->member.name, found_node->member.roomNumber);
            }
            else {
                printf("\nPerson with License Plate %s not found.\n", licensePlate);
            }
            break;
        }
        case 6:
            printf("Exiting program.\n");
            return 0;
            break;

        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 6);

    return 0;
}
