#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "bstree.h"

static BSTreeNode* create_bstree_node(Type value, BSTreeNode *parent, BSTreeNode *left, BSTreeNode *right)
{
    BSTreeNode *p;

    p = (BSTreeNode *)malloc(sizeof(BSTreeNode));
    if(!p) {
        return NULL;
    }

    p->value = value;
    p->left = left;
    p->right = right;
    p->parent = parent;

    return p;
}

int preorder_bstree(BSTreeNode *tree, int (*action)(BSTreeNode *))
{
    if(tree == NULL) {
        return 0;
    }

    action(tree);
    preorder_bstree(tree->left, action);
    preorder_bstree(tree->right, action);

    return 0;
}

int inorder_bstree(BSTreeNode *tree, int (*action)(BSTreeNode *))
{
    if(tree == NULL) {
        return 0;
    }

    inorder_bstree(tree->left, action);
    action(tree);
    inorder_bstree(tree->right, action);

    return 0;
}

int postorder_bstree(BSTreeNode *tree, int (*action)(BSTreeNode *))
{
    if(tree == NULL) {
        return 0;
    }

    postorder_bstree(tree->left, action);
    postorder_bstree(tree->right, action);
    action(tree);

    return 0;
}

int bstree_height(BSTreeNode *tree)
{
    int h = 0, hl = 0, hr = 0;

    if(!tree) {
        return 0;
    }

    hl = bstree_height(tree->left);
    hr = bstree_height(tree->right);

    if(hl > hr) {
        h = hl + 1;
    } else {
        h = hr + 1;
    }

    return h;
}

#if 0
//int level_bstree(BSTreeNode *tree, int (*action)(BSTreeNode *))
int level_bstree(BSTreeNode *tree, int pos)
{
    int i;
    int tree_height = bstree_height(tree);
    
    if(!tree) {
        return -1;
    }

    for(i = 0; i < ((int)pow(2,tree_height)-1)/2-1; i++) {
        printf(" ");
    }
    printf("%d", tree->value);
    
    struct queue q;

    init_queue(&q);
    push(q, 

    printf("\n");
}
#endif

// recursive
BSTreeNode* search_bstree(BSTreeNode *tree, int (*cmp)(Type*, Type *), Type* pvalue)
{
    int ret;
    BSTreeNode *pNode = tree;

    if(tree == NULL) {
        return NULL;
    }

    ret = cmp(pvalue, &pNode->value);
    if(ret == 0) {
        return pNode;
    } else if(ret < 0) {
        pNode = search_bstree(tree->left, cmp, pvalue);
    } else {
        pNode = search_bstree(tree->right, cmp, pvalue);
    }

    return pNode; 
}

BSTreeNode *iterative_search_bstree(BSTreeNode *tree, int (*cmp)(Type*, Type*), Type* pvalue)
{
    int ret;
    BSTreeNode *pNode = tree;
    
    while(pNode != NULL) {
        ret = cmp(pvalue, &pNode->value);
        if(ret == 0) {
            break;
        } else if(ret < 0) {
            pNode = pNode->left;
        } else {
            pNode = pNode->right;
        }
    }

    return pNode; 
}

// 最大节点最多有一颗左树，不可能有右子树
BSTreeNode *bstree_maximum(BSTreeNode *tree)
{
    BSTreeNode *pNode = tree;

    if(pNode != NULL) {
        while(pNode->right) {
            pNode = pNode->right;
        }
    }

    return pNode;
}

// 最小节点最多有一颗右树，不可能有左子树
BSTreeNode *bstree_minimum(BSTreeNode *tree)
{
    BSTreeNode *pNode = tree;

    if(pNode != NULL) {
        while(pNode->left) {
            pNode = pNode->left;
        }
    }

    return pNode;
}

// 前驱节点可能有双子树, 除非该节点有左子树
BSTreeNode *bstree_predecessor(BSTreeNode *pNode)
{
    BSTreeNode *rslt;

    if(!pNode) {
        return NULL;
    }

    if(pNode->left) {
        rslt = bstree_maximum(pNode->left);        
    } else {
        // 从祖先节点中查找前驱(当前节点位于祖先节点的右子树)
        while(pNode->parent) {
            // 如果节点是左节点，继续向上找
            if(pNode == pNode->parent->left) {
                pNode = pNode->parent;
            } else {
                break;
            }
        }
        rslt = pNode->parent;
    }

    return rslt;
}

// 前驱节点可能有双子树, 除非该节点有右子树
BSTreeNode *bstree_successor(BSTreeNode *pNode)
{
    BSTreeNode *rslt;

    if(!pNode) {
        return NULL;
    }

    if(pNode->right) {
        rslt = bstree_minimum(pNode->right);        
    } else {
        // 从祖先节点中查找前驱(当前节点位于祖先节点的左子树)
        while(pNode->parent) {
            // 如果节点是右节点，继续向上找
            if(pNode == pNode->parent->right) {
                pNode = pNode->parent;
            } else {
                break;
            }
        }
        rslt = pNode->parent;
    }

    return rslt;
}

// 节点插入后是"叶子"节点
int bstree_insert(BSTreeNode **tree, BSTreeNode *z, int (*cmp)(Type*, Type*))
{
    int ret;
    BSTreeNode **t = tree;
    BSTreeNode *p = NULL;

    if(!z) {
        return -1;
    }

    while(*t) {
        p = *t;
        ret = cmp(&(z->value), &(*t)->value);
        if(ret < 0) {
            t = &(*t)->left;
        } else if (ret > 0) {
            t = &(*t)->right;
        } else {
            return 0;
        }
    }
    *t = z;
    z->parent = p; 

    return 0;
}

int insert_bstree(BSTreeNode **tree, Type key, int (*cmp)(Type*, Type*))
{
    BSTreeNode *z;

    if ((z=create_bstree_node(key, NULL, NULL, NULL)) == NULL)
        return -1;

    return bstree_insert(tree, z, cmp);
}

int bstree_delete(BSTreeNode **tree, BSTreeNode *z, int (*cmp)(Type*, Type*))
{
    if(!z || (!tree) || !(*tree)) {
        return -1;
    }

    if(z->parent) {
        bstree_insert(&(z->parent), z->right, cmp);
        bstree_insert(&(z->parent), z->left, cmp);
    } else if(z->left){
        *tree = z->left;
        bstree_insert(&(z->left), z->right, cmp);
    } else {
        *tree = z->right; 
    }

    return 0;
}

// 关键：删除的节点最多只有一颗子树
int bstree_delete_iterative(BSTreeNode **tree, BSTreeNode *z)
{
    BSTreeNode *del_node_child, *del_node;

    if(!tree || !z) {
        return -1;
    }

    // del_node is the node that has one child at most
    // del_node最多只有一颗子树，
    // 删除del_node仅需将del_node->child和del_node->parent连起来
    if(!z->left || !z->right) {
        del_node = z;
    } else {
        // del_node是z右子树min
        // z有右子树，则del_node必然是最多有一个右子树
        // 前驱也可以
        del_node = bstree_successor(z);
    }

    if(del_node->left) {
        // del_node的右子树为NULL, del_node是z
        // 假设z具有左右子树，则del_node是右子树的min(min不可能有left)
        del_node_child = del_node->left;
    } else {
        del_node_child = del_node->right;
    }

    if(del_node_child) {
        del_node_child->parent = del_node->parent; 
    }

    if(del_node->parent == NULL) {
       *tree = del_node_child; 
    } else if(del_node->parent->left == del_node) {
        del_node->parent->left = del_node_child;
    } else {
        del_node->parent->right = del_node_child;
    }

    if(del_node != z) {
        z->value = del_node->value;
    }

    free(del_node);

    return 0;
}

int delete_bstree(BSTreeNode **tree, Type key, int (*cmp)(Type*, Type *))
{
    BSTreeNode *z; 
    int ret = 0;

    z = search_bstree(*tree, cmp, &key);
    if (z != NULL)
        ret = bstree_delete(tree, z, cmp);

    return ret;
}

int destroy_node(BSTreeNode *node)
{
    free(node);

    return 0;
}

void destroy_bstree(BSTreeNode tree)
{
#if 0
    if (tree==NULL)
        return ;

    // 后序遍历
    if (tree->left != NULL)
        destroy_bstree(tree->left);
    if (tree->right != NULL)
        destroy_bstree(tree->right);

    free(tree);
#endif

#if 0
    postorder_bstree(&tree, destroy_node);
#endif

    BSTreeNode *p, *c;

    c = &tree;
    while(c) {
        if(c->left) {
            c = c->left;
        } else if(c->right) {
            c = c->right;
        } else {
            p = c->parent;
            printf("delete: %d\n", c->value);
            free(c);
            if(!p) {
                break;
            } else {
                if(p->left == c) {
                    p->left = NULL;
                    if(p->right) {
                        c = p->right;
                    } else {
                        c = p;
                    }
                } else {
                    p->right = NULL;
                    c = p;
                }
            }
        }
    }
}
