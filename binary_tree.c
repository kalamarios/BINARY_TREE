#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left; //points to the left child
    struct node *right; //points to the right child
};
typedef struct node tree_node;
typedef struct node *tree_ptr;

void tree_init(tree_ptr *root); //initializes the root of the tree
int node_data(tree_ptr p); //returns the number that is stored into the node that p points to
void insert_root(tree_ptr *root, int num); //inserts the root, only if the tree is empty
void insert_left(tree_ptr node, int num); //inserts a left child to the node that is inserted as an argument, only if a left child doesn't exist already
void insert_right(tree_ptr node, int num); //the same for the right child
void print_node(tree_ptr root); //prints the content of the node that root points to
void preorder(tree_ptr root);
void inorder(tree_ptr root);
void postorder(tree_ptr root);
tree_ptr binaryTreeSearch(tree_ptr root, int key); //searches the tree for the value, if found, it returns a pointer to the node, otherwise null
void binaryTreeInsert(tree_ptr *root, int key); //inserts an element to the binary tree
void destroy_tree(tree_ptr root); //destroys the tree and frees the memory
int height(tree_ptr root); //returns the tree's height

int main() {
    int data;
    tree_ptr root;

    tree_init(&root);
    binaryTreeInsert(&root, 10);
    binaryTreeInsert(&root, 7);
    binaryTreeInsert(&root, 4);
    binaryTreeInsert(&root, 5);
    binaryTreeInsert(&root, 19);
    binaryTreeInsert(&root, 25);
    binaryTreeInsert(&root, 2);
    binaryTreeInsert(&root, 1);
    binaryTreeInsert(&root, 3);

    printf("\nInorder:\n");
    inorder(root);
    printf("\nPreorder:\n");
    preorder(root);
    printf("\nPostorder:\n");
    postorder(root);
    printf("\n\n");
    printf("Type a number to search for: ");
    scanf("%d", &data);
    if (binaryTreeSearch(root,data))
        printf("\nThe value %d is present in the tree\n", data);
    else
        printf("\nThe value %d is not present in the tree\n", data);

    printf("\nHeight of the tree: %d\n", height(root));

    destroy_tree(root);


    return 0;
}

void tree_init(tree_ptr *root) {
    *root = NULL;
}

int node_data(tree_ptr p) {
    return p -> data;
}

void insert_root(tree_ptr *root, int num) {
    if (*root != NULL) {
        printf("Tree is not empty!");
        return; //return if the tree isn't empty
    }
    tree_ptr new_node = (tree_ptr) malloc(sizeof(tree_node));
    if (new_node == NULL) {
        printf("Not enough space!");
        return;
    }
    new_node -> data = num;
    new_node -> left = NULL;
    new_node -> right = NULL;
    *root = new_node; //creates root and replaces the temporary pointer
}

void insert_left(tree_ptr node, int num) {
    if (node -> left != NULL) {
        printf("This node already has a left child!");
        return;
    }
    tree_ptr new_node = (tree_ptr) malloc(sizeof(tree_node));
    if (new_node == NULL)
        printf("Not enough space!");
    new_node -> data = num;
    new_node -> left = NULL;
    new_node -> right = NULL;
    node -> left = new_node; //creates left child
}

void insert_right(tree_ptr node, int num) {
    if (node -> right != NULL) {
        printf("This node already has a right child!");
        return;
    }
    tree_ptr new_node = (tree_ptr) malloc(sizeof(tree_node));
    if (new_node == NULL)
        printf("Not enough space!");
    new_node -> data = num;
    new_node -> left = NULL;
    new_node -> right = NULL;
    node -> right = new_node; //creates right child
}

void print_node(tree_ptr root) {
    if (root != NULL)
        printf("%d ", node_data(root));
}


void preorder(tree_ptr root) {
    if (root != NULL) {
        print_node(root);
        preorder(root -> left);
        preorder(root -> right); //called recursively for each sub-tree
    }
}

void inorder(tree_ptr root) {
    if (root != NULL) {
        inorder(root -> left);
        print_node(root);
        inorder(root -> right);
    }
}

void postorder(tree_ptr root) {
    if (root != NULL) {
        postorder(root -> left);
        postorder(root -> right);
        print_node(root);
    }
}

tree_ptr binaryTreeSearch(tree_ptr root, int key) {
    tree_ptr current = root;
    while (current != NULL) {
        if (current->data == key)
            return current;
        if (key < current->data)
            current = current -> left;
        else
            current = current -> right;
    }
    return NULL; //given this is a binary tree, every time the value can't be found, depending on if it is greater or less than the value of each node, we procceed to the right, or left sub-tree respectively, if not found, returns null
}

void binaryTreeInsert(tree_ptr *root, int key) {
    tree_ptr current;
    if (*root == NULL) {
        insert_root(root,key);
        return;
    }

    current = *root;
    while (1) {
        if (key == current->data) {
            printf("Cannot insert duplicates (Number %d already exists).\n", key);
            return;
        }
//comparisons for the correct insertion of the element, given its value, in the binary tree
        if (key < current->data) {
            if (current -> left == NULL) {
                insert_left(current,key);
                return;
            }
            else
                current = current -> left;
        }
        else {
            if (current -> right == NULL) {
                insert_right(current,key);
                return;
            }
            else
                current = current -> right; //inserts the elements in the binary tree, by doing the correct checks, and using the insert_root(), insert_left() and insert_right() functions

        }
    }

}

void destroy_tree(tree_ptr root) {
    if (root != NULL) {
        destroy_tree(root -> left);
        destroy_tree(root -> right);
        free(root); //destroys all the sub-trees and frees memory
    }
}

int height(tree_ptr root) {
    if (root == NULL)
        return -1;
    else {
        int left_height = height(root->left);
        int right_height = height(root->right);
        return 1 + (left_height > right_height ? left_height : right_height); //compares the heights of the sub-trees and returns the biggest + 1, because of the fact that the height is -1 if there is no tree
    }
}


