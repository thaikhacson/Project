#include <stdio.h>
#include <string.h>
#include "manager.h"
#include "member.h"

extern TreeNode* root;

/*
 * Function: addMember
 * Description: Add a new member to the file and the binary search tree.
 * Input:
 *   - filename: Name of the file to add member information.
 *   - member: Data of the member to be added.
 * Output:
 *   - Write member information to the file and add a new node to the tree.
 *   - Display a message indicating success or an error during the addition process.
 */
void addMember(const char* filename, Member member) {
    FILE* file = fopen(filename, "a");

    if (file == NULL) {
        printf("Cannot open File!\n");
        return;
    }

    // Check the size of the file to determine if it is empty
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);

    if (fileSize > 0) {
        fprintf(file, "\n");  // Add a newline character before adding a new member
    }

    // Write member information to the file
    fprintf(file, "%s,%s,%s,%s", member.uid, member.roomNumber, member.name, member.licensePlate);

    fclose(file);

    insert(&root, member);

    printf("Member added successfully!\n");
}

/*
 * Function: deleteMember
 * Description: Delete member information from the file and update the binary search tree.
 * Input:
 *   - filename: Name of the file containing member information.
 *   - uid: Unique Identifier (UID) string of the member to be deleted.
 * Output:
 *   - If the member is successfully deleted, display a message and update the binary search tree.
 *   - If the member is not found, display a message indicating that the member was not found.
 */
void deleteMember(const char* filename, const char* uid) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("Cannot open File!\n");
        return;
    }

    // Create a temporary file to store new data after deletion
    const char* tempFileName = "tempFile.csv";
    FILE* tempFile = fopen(tempFileName, "w");
    if (tempFile == NULL) {
        printf("Cannot create temporary file.\n");
        fclose(file);  // Close the original file before exiting
        return;
    }

    char line[256]; // Read each line from the file
    int found = 0;   // Variable to check if the keyword has been found

    // Find UID
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, uid) == NULL) {
            fputs(line, tempFile);
        }
        else {
            found = 1;
        }
    }

    // Close the original file and the temporary file
    fclose(tempFile);
    fclose(file);

    // Copy data from the temporary file to the original file
    file = fopen(filename, "w");
    tempFile = fopen(tempFileName, "r");
    if (file == NULL || tempFile == NULL) {
        printf("Error when copying data.\n");
        return;
    }

    // Copy each character from the temporary file to the original file
    int ch;
    while ((ch = fgetc(tempFile)) != EOF) {
        fputc(ch, file);
    }

    // Close both files
    fclose(file);
    fclose(tempFile);

    // Delete the temporary file
    remove(tempFileName);

    if (found) {
        printf("Removed member with UID %s.\n", uid);
    }
    else {
        printf("No members found with UID %s.\n", uid);
    }
}

/*
 * Function: editMember
 * Description: Modify member information in the CSV file based on UID and update in the binary search tree.
 * Input:
 *   - filename: Name of the CSV file containing member information.
 *   - updatedMember: New information of the member to be updated.
 *   - uid: UID of the member to be edited.
 * Output:
 *   - Data in the CSV file and the binary search tree will be updated if the member is found and edited.
 *   - If the member is not found, display the corresponding message.
 */
void editMember(const char* filename, Member updatedMember, const char* uid) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("Cannot open File!\n");
        printf("Fail\n");
        return;
    }

    const char* tempFileName = "temFile.csv";
    FILE* tempFile = fopen(tempFileName, "w");
    if (tempFile == NULL) {
        printf("Cannot create temporary file.\n");
        fclose(file);
        return;
    }

    char line[256];
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, uid) == NULL) {
            fputs(line, tempFile);
        }
        else {
            fprintf(tempFile, "%s,%s,%s,%s", updatedMember.uid, updatedMember.roomNumber, updatedMember.name, updatedMember.licensePlate);
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    tempFile = fopen(tempFileName, "r");
    file = fopen(filename, "w");
    if (file == NULL || tempFile == NULL) {
        printf("Error when copying data.\n");
        return;
    }

    int ch;
    while ((ch = fgetc(tempFile)) != EOF) {
        fputc(ch, file);
    }

    fclose(file);
    fclose(tempFile);

    remove(tempFileName);

    edit_member_info(root, uid, updatedMember);

    if (found) {
        printf("Update member with UID %s.\n", uid);
    }
    else {
        printf("No Update member with UID %s.\n", uid);
    }
}


