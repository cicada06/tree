#ifndef __PRINT_BTREE_H__
#define __PRINT_BTREE_H__

#include "bstree.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef BSTreeNode Tree;

#if 0
struct Tree 
{
  Tree * left, * right;
  int value;
};
#endif

void print_ascii_tree(Tree * t);

#ifdef __cplusplus
}
#endif

#endif
