#include <stdbool.h>

typedef int item_t;

typedef struct bst_node_t {
    item_t value;
    struct bst_node_t* left;
    struct bst_node_t* right;
} bst_node_t;

bst_node_t* bst_create(item_t value);
void bst_destroy(bst_node_t* root);
bst_node_t* bst_insert(bst_node_t* root, item_t value);
bool bst_search(bst_node_t* root, item_t value);
void bst_print_inorder(bst_node_t* root);
void bst_print_preorder(bst_node_t* root);
void bst_print_posorder(bst_node_t* root);
bst_node_t* bst_remove(bst_node_t* root, item_t value);