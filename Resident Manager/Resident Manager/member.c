#include <stdio.h>
#include <stdlib.h>
#include "member.h"

TreeNode* root = NULL;

/*
 * Function: create_node
 * Description: Create a new node in the tree and assign member data.
 * Input:
 *   - member: Member data to be assigned to the new node.
 * Output:
 *   - Returns a pointer to the newly created node.
 *   - If there is not enough memory, display an error message and exit the program.
 */
TreeNode* create_node(Member memmber) {
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    if (new_node == NULL) {
        printf("Not enough memory.\n");
        exit(EXIT_FAILURE);
    }

    new_node->member = memmber;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

/*
 * Function: insert
 * Description: Add a new member to the binary search tree.
 *              This function is used to maintain the binary search tree property.
 * Input:
 *   - rootPtr: Pointer to the root pointer of the tree.
 *   - member: Member data to be added.
 * Output:
 *   - Returns a pointer to the node containing the added member information in the tree.
 */
TreeNode* insert(TreeNode** rootPtr, Member member) {
    if (*rootPtr == NULL) {
        *rootPtr = create_node(member);
        return *rootPtr;
    }

    if (strcmp(member.name, (*rootPtr)->member.name) < 0) {
        (*rootPtr)->left = insert(&((*rootPtr)->left), member);
    }
    else if (strcmp(member.name, (*rootPtr)->member.name) > 0) {
        (*rootPtr)->right = insert(&((*rootPtr)->right), member);
    }

    return *rootPtr;
}

/*
 * Function: edit_member_info
 * Description: Modify the information of a member in the binary search tree based on UID.
 *              Search for the node containing the member to be edited using UID,
 *              then update the member information from a provided struct Member.
 * Input:
 *   - root: Pointer to the root node of the tree.
 *   - uid: UID string of the member to be edited.
 *   - updated_member: Pointer to the struct Member containing the new information to be updated.
 * Output:
 *   - If a member with the corresponding UID is found, the information is updated.
 *   - If not found, print an error message.
 */
void edit_member_info(TreeNode* root, const char* uid, const Member* updated_member) {
    TreeNode* node = find_by_uid(root, uid);
    if (node != NULL) {
        // Cập nhật thông tin từ updated_member vào node tìm được
        strcpy(node->member.roomNumber, updated_member->roomNumber);
        strcpy(node->member.name, updated_member->name);
        strcpy(node->member.licensePlate, updated_member->licensePlate);
        // Bạn có thể thêm các trường khác cần cập nhật tại đây
    }
    else {
        printf("Khong tim thay thanh vien voi UID: %s\n", uid);
    }
}

/*
 * Function: find_by_uid
 * Description: Search for member information in the binary search tree based on UID.
 *              The tree is traversed in an ordered manner based on UID, assuming that the tree
 *              has been sorted by the UID field of the member.
 * Input:
 *   - root: Pointer to the root node of the tree.
 *   - uid: UID string to search for.
 * Output:
 *   - Returns a pointer to the node containing the member information with the corresponding UID.
 *   - If not found, returns NULL.
 */
TreeNode* find_by_uid(TreeNode* root, const char* uid) {
    if (root == NULL || strcmp(uid, root->member.uid) == 0) {
        return root;
    }

    if (strcmp(uid, root->member.uid) < 0) {
        return find_by_uid(root->left, uid);
    }
    else {
        return find_by_uid(root->right, uid);
    }
}

/*
 * Function: find_by_license_plate
 * Description: Search for member information in the binary search tree based on license plate.
 *              The tree is traversed in both directions (left and right) to search for information,
 *              as there is no specific sorting based on the license plate.
 * Input:
 *   - root: Pointer to the root node of the tree.
 *   - licensePlate: License plate string to search for.
 * Output:
 *   - Returns a pointer to the node containing the member information with the corresponding license plate.
 *   - If not found, returns NULL.
 */
TreeNode* find_by_license_plate(TreeNode* root, const char* licensePlate) {
    if (root == NULL) {
        return NULL;
    }

    // Check the current node
    if (strcmp(licensePlate, root->member.licensePlate) == 0) {
        return root;
    }

    // Search in the left and right subtrees
    TreeNode* leftSearch = find_by_license_plate(root->left, licensePlate);
    if (leftSearch != NULL) {
        return leftSearch;
    }

    return find_by_license_plate(root->right, licensePlate);
}

/*
 * Function: display_tree
 * Description: Display the information of all members in the binary search tree.
 *              Traverse the tree in in-order (left, root, right) to ensure information is displayed in name order.
 * Input:
 *   - root: Pointer to the root node of the tree.
 * Output:
 *   - No return value. The information of each member is printed to the screen,
 *     including UID, room number, name, and license plate.
 */
void display_tree(TreeNode* root) {
    if (root != NULL) {
        display_tree(root->left);
        printf("UID: %s, Room Number: %s, Name: %s, License Plate: %s\n",
            root->member.uid, root->member.roomNumber, root->member.name, root->member.licensePlate);
        display_tree(root->right);
    }
}

/*
 * Function: free_tree
 * Description: Free the memory allocated for all nodes in the binary search tree.
 *              This function uses the post-order traversal method to ensure
 *              that all child nodes are freed before freeing the parent node, avoiding
 *              invalid memory access errors.
 * Input:
 *   - root: Pointer to the root node of the tree.
 * Output:
 *   - No return value. All memory of the tree is freed.
 */
void free_tree(TreeNode* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}