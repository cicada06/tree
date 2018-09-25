#ifndef __BSTREE_H__
#define __BSTREE_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef int Type;

typedef struct _BSTreeNode {
    Type value;
    struct _BSTreeNode *left;
    struct _BSTreeNode *right;
    struct _BSTreeNode *parent;
}BSTreeNode;

int insert_bstree(BSTreeNode **tree, Type key, int (*cmp)(Type*, Type*));
void destroy_bstree(BSTreeNode tree);

#define CONTINUE_TRAVEL (0)
#define EXIT_TRAVEL (1)

#ifdef __cplusplus
}
#endif

#endif
