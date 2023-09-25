#include "bst.h"
#include <stdlib.h>
#include <stdio.h>

bst_node_t* bst_create(item_t value) {
    bst_node_t* node = malloc(sizeof(bst_node_t));
    node->value = value;
    return node;
}

bst_node_t* bst_insert(bst_node_t* root, item_t value) {
    if (root == NULL) {
        return bst_create(value);
    } else if (value < root->value) {
        root->left = bst_insert(root->left, value);
    } else if (value >= root->value) {
        root->right = bst_insert(root->right, value);
    }

    return root;
}

bool bst_search(bst_node_t* root, item_t value) {
    return true;
}

void bst_print_inorder(bst_node_t* root) {
    if (root == NULL) {
        return;
    }

    bst_print_inorder(root->left);
    printf("%d ", root->value);
    bst_print_inorder(root->right);
}

void bst_print_preorder(bst_node_t* root) {
    if (root == NULL) {
        return;
    }

    printf("%d ", root->value);
    bst_print_preorder(root->right);
    bst_print_preorder(root->left);
}

void bst_print_posorder(bst_node_t* root) {
    if (root == NULL) {
        return;
    }

    bst_print_posorder(root->right);
    bst_print_posorder(root->left);
    printf("%d ", root->value);
}

void bst_destroy(bst_node_t* root) {
    if (root == NULL) {
        return;
    }

    bst_destroy(root->left);
    bst_destroy(root->right);
    free(root);
}

bst_node_t* bst_find_successor(bst_node_t* root) {
    if (root->left == NULL) {
        return root;
    }

    return bst_find_successor(root->left);
}

bst_node_t* bst_remove(bst_node_t* root, item_t value) {
    if (root == NULL) {
        return NULL;
    }

    if (value < root->value) {
        root->left = bst_remove(root->left, value);
    } else if (value > root->value) {
        root->right = bst_remove(root->right, value);
    } else {
        if (root->left == NULL) {
            bst_node_t* child = root->right;
            free(root);
            return child;
        } else if (root->right == NULL) {
            bst_node_t* child = root->left;
            free(root);
            return child;
        }

       bst_node_t* successor = bst_find_successor(root->right);

       root->value = successor->value;
       root->right = bst_remove(root->right, successor);
    }
}
