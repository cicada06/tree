#include <stdio.h>

#include "bstree.h"
#include "print_btree.h"

int cmp(int *a, int *b)
{
    if(!a || !b) {
        return 0;
    }

    if(*a > *b) {
        return 1;
    } else if(*a < *b) {
        return -1;
    } else {
        return 0;
    }
}

int main(void)
{
    BSTreeNode *tree = NULL;

    insert_bstree(&tree, 4, cmp);
    insert_bstree(&tree, 2, cmp);
    insert_bstree(&tree, 6, cmp);
    insert_bstree(&tree, 1, cmp);
    insert_bstree(&tree, 3, cmp);
    insert_bstree(&tree, 5, cmp);
    insert_bstree(&tree, 7, cmp);

    print_ascii_tree(tree);

    destroy_bstree(*tree);

    return 0;
}
