#include "bst.h"
#include "stdlib.h"

int main() {
    bst_node_t* root = NULL;

    root = bst_insert(root, 5);
    root = bst_insert(root, 3);
    root = bst_insert(root, 8);
    root = bst_insert(root, 1);
    root = bst_insert(root, 4);
    root = bst_insert(root, 7);

    bst_print_inorder(root);
    printf("\n");
    bst_print_preorder(root);
    printf("\n");
    bst_print_posorder(root);
    printf("\n");

    bst_destroy(root);

    return 0;
}