/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			bst.cpp
 * Author(s):		Peter Bauer
 * Due Date:		May 31, 2017
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include <stdio.h>
#include "bst.h"
#include <stdlib.h>
#include "general.h"
#define MAXL 50

struct Node{
  int data;
   Bst left_subtree;
   Bst right_subtree;
};

Bst new_bst(){
   Bst _head = 0;
   return _head;
}
void delete_bst(Bst bst){
  if(bst == 0)return;
  delete_bst(bst->left_subtree);
  delete_bst(bst->right_subtree);
  sfree(bst);
}

int get_depth(Bst bst){
  if(bst == 0)return 0;
  int depth = get_depth(bst->left_subtree)+1;
  int r = get_depth(bst->right_subtree)+1;
  return  r>depth ? r:depth;
}

void add(Bst* bst, int value){
  Bst &aka = *bst;
  if(aka == 0){
    aka = (Bst)malloc(sizeof(struct Node));
    aka->data = value;
    aka->left_subtree =0;
    aka->right_subtree =0;
  }
  else if(value <= aka->data){
      add(&aka->left_subtree, value);
  }
  else{
      add(&aka->right_subtree,value);
  }
}

int root_value(Bst bst){
  return bst==0?0:bst->data;
}

Bst left_subtree(Bst root){
  return root == 0?0:root->left_subtree;
}

Bst right_subtree(Bst root){
  return root == 0?0:root->right_subtree;
}

int traverse_pre_order(Bst bst, int *elements, int start){
    if(bst == 0)return 0;
    int count = 0;
    elements[start] = bst->data;
    count += traverse_pre_order(bst->left_subtree, elements, start+1);
    count+= traverse_pre_order(bst->right_subtree, elements, start+count+1);
    return count+1;
}

int traverse_in_order(Bst bst, int *elements, int start){
    if(bst == 0)return 0;
    int count = 0;
    count += traverse_in_order(bst->left_subtree, elements, start);
    elements[start+count] = bst->data;
    count+= traverse_in_order(bst->right_subtree, elements, start+count+1);
    return count+1;
}

int traverse_post_order(Bst bst, int *elements, int start){
    if(bst == 0)return 0;
    int count = 0;
    count += traverse_post_order(bst->left_subtree, elements, start);
    count += traverse_post_order(bst->right_subtree, elements, start+count);
    elements[start+count] = bst->data;
    return count+1;
}

bool are_equal(Bst bst1, Bst bst2){
  if(bst1 == bst2)return true;
  if(bst1 != 0 && bst2 != 0){
    int arr1[MAXL];
    int length = traverse_pre_order(bst1, arr1, 0);
    int arr2[MAXL];
    int length2 = traverse_pre_order(bst2, arr2, 0);
    if(length == length2){
      bool x = true;
      for (int i = 0; i < length; i++) {
        if(arr1[i]!= arr2[i])x = false;
      }
      return x;
    }
  }
  return false;
}

void most_left_longest_branch(Bst bst, Bst* branch){
    if(bst == 0)return;
    add(branch, bst->data);
    get_depth(bst->left_subtree) >= get_depth(bst->right_subtree) ? most_left_longest_branch(bst->left_subtree, branch):most_left_longest_branch(bst->right_subtree, branch);
}

int get_number_of_subtrees(Bst bst){
    if(bst == 0)return -1;
return get_number_of_subtrees(bst->left_subtree) +1+ get_number_of_subtrees(bst->right_subtree)+1;
}
