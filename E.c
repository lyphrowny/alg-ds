#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node* left;
    struct Node* right;
    int val;
    int len;
} Node_t;

int ntol(int number) {
    int len;
    if (len = (number <= 0))
        number = ~number + 1;

    while (number) {
        number /= 10;
        len++;
    }
    return len;
}

Node_t* newNode(Node_t* node, int val) {
    node = (Node_t*) malloc(sizeof(Node_t));
    node->left = NULL;
    node->right = NULL;
    node->val = val;
    node->len = 0;
    return node;
}

void fixLen(Node_t* node) {
    int len = 0;
    if (node->right != NULL)
        len += node->right->len + ntol(node->right->val);
    if (node->left != NULL)
        len += node->left->len + ntol(node->left->val);
    node->len = len;
}

Node_t* insertNode(Node_t* node, int val) {
    if (node == NULL)
        return newNode(node, val);

    if (val > node->val)
        node->right = insertNode(node->right, val);
    else if (val < node->val)
        node->left = insertNode(node->left, val);
    fixLen(node);
    return node;
}

Node_t* findMin(Node_t* node) {
    while (node != NULL && node->left != NULL)
        node = node->left;
    return node;
}

Node_t* deleteNode(Node_t* node, int val) {
    if (node == NULL)
        return NULL;

    if (val > node->val)
        node->right = deleteNode(node->right, val);
    else if (val < node->val)
        node->left = deleteNode(node->left, val);
    else {
        if (node->left == NULL || node->right == NULL) {
            Node_t* tmp = node->right == NULL ? node->left : node->right;
            free(node);
            return tmp;
        }
        Node_t* tmp = findMin(node->right);
        node->val = tmp->val;
        node->right = deleteNode(node->right, tmp->val);
    }
    fixLen(node);
    return node;
}

Node_t* findNode(Node_t* node, int val) {
    if (node == NULL || node->val == val)
        return node;
    else if (val > node->val)
        return findNode(node->right, val);
    return findNode(node->left, val);
}

void freeTree(Node_t* node) {
    if (node != NULL) {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}

int main() {

    Node_t* root = NULL;
    int c = getchar(), number;

    while (c != EOF) {
        scanf("%d", &number);
        switch (c) {
            case 'a':
                root = insertNode(root, number);
                break;
            case 'f':
                printf(findNode(root, number) == NULL ? "no\n" : "yes\n");
                break;
            case 'r':
                root = deleteNode(root, number);
                break;
            default:
                freeTree(root);
                return 0;
        }

        if ((c = getchar()) == '\n')
            c = getchar();
    }
    freeTree(root);

    return 0;
}