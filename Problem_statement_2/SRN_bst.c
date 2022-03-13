// Name:
// SRN: 
#include "bst.h"
#include <stdlib.h>
#include <stdio.h>

/*
 ** Do not use global variables.
 ** Mark any functions that you declare in this file that are not in the header as static
 ** Do not use static variables
 ** All occurences of count_ptr indicate that the number of comparison
 ** operations need to be stored in the location pointed by it
 ** The implementation can assume it is initialized to 0.
*/

// Initializes the root of the bst
void init_bst(bst_t *bst)
{   
    bst->root=NULL;
}

// Inserts element key into the Binary search tree
// Stores the number of comparisons at the location
// pointed by count_ptr
static node_t* insert_into_bst(node_t *root,int key,int *count_ptr){
	if(root==NULL){
		node_t *temp=(node_t*)malloc(sizeof(node_t));
		temp->left=NULL;
		temp->right=NULL;
		temp->key=key;
		return temp;
	}
	if(++*count_ptr && key<=root->key){
		root->left=insert_into_bst(root->left,key,count_ptr);
	}else if(++*count_ptr && key>root->key){
		root->right=insert_into_bst(root->right,key,count_ptr);
	}
}
void insert(bst_t *tree, int key, int *count_ptr)
{
    tree->root=insert_into_bst(tree->root,key,count_ptr);
    // node_t *temp,*curr,*prev;
    // temp=(node_t*)malloc(sizeof(node_t));
	// temp->key=key;
	// temp->left=temp->right=NULL;
    // (*count_ptr)++;
    // if(tree->root==NULL){    
    //     tree->root=temp;
    //     //printf("%d : ",tree->root->key);
    // }
    // else{
    //     curr=tree->root;      
    //     prev=NULL;
    //     (*count_ptr)++;
    //     while(curr!=NULL){
           
    //         (*count_ptr)++;
    //         prev=curr;
    //         (*count_ptr)++;
    //         if(key<curr->key)
    //             curr=curr->left;
    //         else 
    //             curr=curr->right;
	//     }
    //     (*count_ptr)++;
    //     if(key<prev->key){
    //         prev->left=temp;
    //         //printf("%d : ",prev->left->key);
    //         //*count_ptr++;
    //     }
    //     else {
    //         prev->right=temp;
    //         //printf("%d : ",prev->right->key);
    //         //*count_ptr++;
    //         (*count_ptr)++;
    //     }
    // }
}

// Delete key from the BST
// Replaces node with in-order successor
static node_t* delete_from_bst(node_t *root,int key,int* count_ptr){
	if(root!=NULL){

		if(++*count_ptr && key<root->key){
			root->left=delete_from_bst(root->left,key,count_ptr);
		}else if(++*count_ptr && key>root->key){
			root->right=delete_from_bst(root->right,key,count_ptr);
		}else{

			node_t *temp;
			if(++*count_ptr && root->left==NULL){
				temp=root->right;
				free(root);

			}else if(++*count_ptr && root->right==NULL){
				temp=root->left;
				free(root);

			}else{
				node_t *pr=root->right;
				while(++*count_ptr && pr->left!=NULL){
					pr=pr->left;
				}
				root->key=pr->key;
				root->right=delete_from_bst(root->right,pr->key,count_ptr);
				temp=root;
			}
			return temp;
		}

	}
	return root;
}
void delete_element(bst_t *tree, int key, int *count_ptr)
{
    tree->root=delete_from_bst(tree->root,key,count_ptr);
    // node_t *temp = tree->root, *parent = NULL, *grandchild = NULL, *inorder_suc = NULL;
    // // Search for a given node in a tree
    // (*count_ptr)++;
    // while (temp != NULL && temp->key != key) {

    //     // if value is greater than root node
    //     (*count_ptr)++;
    //     if (key > temp->key) {
    //         (*count_ptr)--;
    //         parent = temp;
    //         temp = temp->right;
    //     }

    //     // if value is less than root node
    //     else if (key < temp->key) {
    //         parent = temp;
    //         temp = temp->left;
    //     }
    //     (*count_ptr)++;
    // }

    // // value not found in tree
    // (*count_ptr)++;
    // if (temp == NULL) {
    //     (*count_ptr)--;
    //     (*count_ptr)--;
    //     return;
    // }

    // // temp has only one child (right)
    // else if (temp->left == NULL) {
    //     (*count_ptr)--;
    //     grandchild = temp->right;
    // }

    // // temp has only one child (left)
    // else if (temp->right == NULL) {
    //     (*count_ptr)++;
    //     grandchild = temp->left;
    // }
        
    // // temp has two children nodes
    // else {
    //     // Find the inorder successor (next number in ascending 
    //     // order). It will be the min of the right subtree
    //     inorder_suc = temp->right;
    //     (*count_ptr)++;
    //     while (inorder_suc->left != NULL) {
    //         (*count_ptr)++;
    //         inorder_suc = inorder_suc->left;
    //     }
    //     (*count_ptr)++;
    //     (*count_ptr)++;
    //     // Once found, the left subtree of temp gets assigned 
    //     // to the inorder successor of temp

    //     inorder_suc->left = temp->left;

    //     // grandchild becomes temp->right
    //     grandchild = temp->right;
    // }

    // // Attach grandchild

    // // If root node is being deleted
    // (*count_ptr)++;
    // (*count_ptr)++;
    // (*count_ptr)++;
    // if (parent == NULL) {
    //     (*count_ptr)--;
    //     (*count_ptr)--;
    //     tree->root = grandchild;
    // }
    // else if (temp == parent->right) {
    //     (*count_ptr)--;
    //     parent->right = grandchild;
    // }
    // else if (temp == parent->left) {
    //     parent->left = grandchild;
    // }
    
    // // Delete temp
    // free(temp);

    
}
static int search_node(node_t *node,int key,int *count_ptr)
{
    (*count_ptr)++;
    if(node==NULL) return -1;
    (*count_ptr)++;
    if(node->key==key){
        return key;
    }
    (*count_ptr)++;
    if(key<node->key){
        return search_node(node->left,key,count_ptr);
    }else{
        return search_node(node->right,key,count_ptr);
    }
}
// Searches for the element key in the bst
// Returns the element if found, else -1
int search(const bst_t *tree, int key, int *count_ptr)
{
    (*count_ptr)++;
    if(tree->root==NULL){
        return -1;
    }
    return search_node(tree->root,key,count_ptr);
}
static int find_max_node(node_t *node,int *count_ptr){
    (*count_ptr)++;
    if (node->right == NULL) {
        return node->key;
    }
    return find_max_node(node->right,count_ptr);
}
// Returns the maximum element in the BST
int find_max(const bst_t *tree, int *count_ptr)
{
    (*count_ptr)++;
    if (tree->root == NULL) {
        return -1;
    }
    return find_max_node(tree->root,count_ptr);
}
static void clear_nodes(node_t *curr){
    if(curr==NULL)return;
    clear_nodes(curr->left);
    clear_nodes(curr->right);
    //printf("Deleting node : %d",curr->key);
    free(curr);
}
// Deletes all the elements of the bst
void free_bst(bst_t *bst) 
{
    if(bst->root==NULL) return;
    clear_nodes(bst->root);
}

// Deletes all the elements if the bst and ensures it can be used again
void clear_bst(bst_t *bst)
{
    if(bst->root==NULL) return;
    clear_nodes(bst->root);
    init_bst(bst);
}
