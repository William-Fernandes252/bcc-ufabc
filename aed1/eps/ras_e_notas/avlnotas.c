#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef enum rotation { SD, SE, DD, DE, NN } rotation;

typedef struct balance_op_report_t {
   rotation tipo_rotacao;
   int ra_no_desbalanceado;
   int x;
   int y;
   int z;
} balance_op_report_t;

void balance_op_report_print(balance_op_report_t* report) {
    if (report == NULL || report->tipo_rotacao == NN) {
        puts("[Ja esta balanceado]");
        return;
    }

    char rotation_codes[4][3] = {"SD\0", "SE\0", "DD\0", "DE\0"};

    printf("[No desbalanceado: %d]\n", report->ra_no_desbalanceado);
    printf("[Rotacao: %s]\n", rotation_codes[report->tipo_rotacao]);
    printf("[x=%d y=%d z=%d]\n", report->x, report->y, report->z);
}

typedef struct search_op_report_t {
    int comparison_count;
    int score;
} search_op_report_t;

void search_op_report_print(search_op_report_t* report) {
    printf("C=%d Nota=%d\n", report->comparison_count, report->score);
}

typedef struct avl_node_t {
    int nota;
    int ra;
    struct avl_node_t* left;
    struct avl_node_t* right;
    int height;
} avl_node_t;

int maximum(int a, int b) {
    if (a > b) {
        return a;
    }

    return b;
}

int avl_height(avl_node_t* root) {
    if (root == NULL) {
        return 0;
    }
    
    return root->height;
}

void avl_destroy(avl_node_t* root) {
    if (root != NULL) {
        avl_destroy(root->left);
        avl_destroy(root->right);
        free(root);
    }
}

avl_node_t* avl_create_node(int nota, int ra) {
    avl_node_t* node = malloc(sizeof(avl_node_t));

    node->nota = nota;
    node->ra = ra;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return node;
}

int avl_balance_factor(avl_node_t* root) {
    if (root == NULL) {
        return 0;
    }
    
    return avl_height(root->left) - avl_height(root->right);
}

void avl_update_height(avl_node_t* root) {
    if (root != NULL) {
        root->height = 1 + maximum(avl_height(root->left), avl_height(root->right));
    }
}

avl_node_t* avl_rotate_left(avl_node_t* root) {
    avl_node_t* pivot = root->right;

    root->right = pivot->left;
    pivot->left = root;

    avl_update_height(root);
    avl_update_height(pivot);

    return pivot;
}

avl_node_t* avl_rotate_right(avl_node_t* root) {
    avl_node_t* pivot = root->left;

    root->left = pivot->right;
    pivot->right = root;

    avl_update_height(root);
    avl_update_height(pivot);

    return pivot;
}

avl_node_t* avl_rebalance(avl_node_t* root, balance_op_report_t* report) {
    if (root != NULL) {
        int bf = avl_balance_factor(root);
        int bf_r = avl_balance_factor(root->right);
        int bf_l = avl_balance_factor(root->left);

        if (bf < -1 || bf > 1) {
            report->ra_no_desbalanceado = root->ra; 
            if (bf < -1 && bf_r <= 0) {
                report->tipo_rotacao = SE;
                report->x = root->ra;
                report->y = root->right->ra;
                report->z = root->right->right->ra;
                root = avl_rotate_left(root);
            } else if (bf > 1 && bf_l >= 0) {
                report->tipo_rotacao = SD;
                report->z = root->ra;
                report->y = root->left->ra;
                report->x = root->left->left->ra;
                root = avl_rotate_right(root);
            } else if (bf < -1 && bf_r > 0) {
                report->tipo_rotacao = DD;
                report->z = root->ra;
                report->x = root->left->ra;
                report->y = root->left->right->ra;
                root->right = avl_rotate_right(root->right);
                root = avl_rotate_left(root);
            } else if (bf > 1 && bf_l < 0) {
                report->tipo_rotacao = DE;
                report->x = root->ra;
                report->z = root->right->ra;
                report->y = root->right->left->ra;
                root->left = avl_rotate_left(root->left);
                root = avl_rotate_right(root);
            }
        }

        avl_update_height(root);
    }

    return root;
}

avl_node_t* avl_insert(avl_node_t* root, int nota, int ra, balance_op_report_t* report) {
    report->tipo_rotacao = NN;
    if (root == NULL) {
        return avl_create_node(nota, ra);
    }

    if (ra < root->ra) {
        root->left = avl_insert(root->left, nota, ra, report);
    } else if (ra > root->ra) {
        root->right = avl_insert(root->right, nota, ra, report);
    } else {
        return root;
    }
    avl_update_height(root);

    return avl_rebalance(root, report);
}

avl_node_t* avl_find_min(avl_node_t* root) {
    if (root->left == NULL) {
        return root;
    }

    return avl_find_min(root->left);
}

avl_node_t* avl_remove(avl_node_t* root, int ra, bool* removed, balance_op_report_t* report) {
    if (root == NULL) {
        return NULL;
    }
    if (ra < root->ra) {
        root->left = avl_remove(root->left, ra, removed, report);
    } else if (ra > root->ra) {
        root->right = avl_remove(root->right, ra, removed, report);
    } else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        if (root->right == NULL) {
            avl_node_t* child = root->left;

            free(root);
            *removed = true;

            return child;
        }
        if (root->left == NULL) {
            avl_node_t* child = root->right;

            free(root);
            *removed = true;

            return child;
        }
        avl_node_t* min_child = avl_find_min(root->right);

        root->ra = min_child->ra;
        root->nota = min_child->nota;
        root->right = avl_remove(root->right, min_child->ra, removed, report);
    }

    avl_update_height(root);

    return avl_rebalance(root, report);
}

avl_node_t* avl_search(avl_node_t* root, int ra, search_op_report_t* report) {

    report->comparison_count += 1;
    if (root->ra == ra) {
        report->score = root->nota;
        return root;
    }

    if (root == NULL) {
        return root;
    }

    report->comparison_count += 1;
    if (ra < root->ra) {
        return avl_search(root->left, ra, report);
    } else {
        return avl_search(root->right, ra, report);
    }
}

void avl_print_postorder(avl_node_t* node) {
    if (node == NULL) {
        return;
    }

    avl_print_postorder(node->left);
    avl_print_postorder(node->right);
    printf("%d ", node->ra);
}

void avl_print_postorder_list(avl_node_t* root) {
    if (root == NULL) {
        printf("[]");
        return;
    }

    printf("[");
    avl_print_postorder(root);
    printf("]\n");
}

#define MAX_COMMAND_SIZE 20

typedef struct {
    char cmd;
    int arg1;
    int arg2;
} command;

void process_command(const char* input, command* cmd) {
    char* token;
    char* rest = (char*) input;
    int i = 0;
    while ((token = strtok_r(rest, " ", &rest))) {
        if (i == 0) {
            cmd->cmd = token[0];
        } else if (i == 1) {
            cmd->arg1 = atoi(token);
        } else if (i == 2) {
            cmd->arg2 = atoi(token);
        }
        i += 1;
    }
}

int main(int argc, char const *argv[]) {
    avl_node_t* root = NULL, * search_result;
    balance_op_report_t balance_report;
    search_op_report_t search_report;

    command comando = {0, 0, 0};
    char input[MAX_COMMAND_SIZE];
    while (true) {
        fgets(input, sizeof(input), stdin);

        process_command(input, &comando);
        if (comando.cmd == 'I') {
            root = avl_insert(root, comando.arg2, comando.arg1, &balance_report);
            balance_op_report_print(&balance_report);
        } else if (comando.cmd == 'R') {
            root = avl_remove(root, comando.arg1, false, &balance_report);
            balance_op_report_print(&balance_report);
        } else if (comando.cmd == 'B') {
            search_report.comparison_count = 0;
            search_report.score = 0;
            search_result = avl_search(root, comando.arg1, &search_report);
            if (search_result == NULL) search_report.score = -1;
            search_op_report_print(&search_report);
        } else if (comando.cmd == 'A') {
            printf("A=%d\n", avl_height(root) - 1);
        } else if (comando.cmd == 'P') {
            avl_print_postorder_list(root);
            avl_destroy(root);
            break;
        } else {
            printf("Comando inválido.\n");
            break;
        }
    }

    return 0;
}
