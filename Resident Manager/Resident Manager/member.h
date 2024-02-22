#ifndef MEMBER_H
#define MEMBER_H

typedef struct Member {
    char uid[20];
    char roomNumber[10];
    char name[50];
    char licensePlate[20];
} Member;

typedef struct TreeNode {
    struct Member member;
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;

TreeNode* create_node(Member memmber);

TreeNode* insert(TreeNode* root, Member member);

TreeNode* find_by_uid(TreeNode* root, const char* uid);

TreeNode* find_by_license_plate(TreeNode* root, const char* licensePlate);

void edit_member_info(TreeNode* root, const char* uid, Member updated_member);

void display_tree(TreeNode* root);

void free_tree(TreeNode* root);

#endif
