// Name: ABHINAV GUNTI
// SRN: PES1UG20CS008
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

// Initialize the root of binary search tree
void init_bst(bst_t *bst){   //at first,the root is assigned to NULL since there are no elements
    bst->root=NULL;
}

static node_t* insert_nodes(node_t *root,int key,int *count_ptr){
	if(root==NULL){     //if root is null, this node becomes the root
        ++*count_ptr;       //increments count_ptr because of if(root==NULL) comparision
		node_t *curr;  
        curr=(node_t*)malloc(sizeof(node_t));   //dynamically allocating memory using malloc of size node_t
        curr->key=key;
        //we initialize the left and right subtree of the node to NULL
		curr->left=curr->right=NULL;
        //since its the first node being inserted,this node is the root of the tree
        //thus we return this node
		return curr;
	}
    //if node being inserted is not the last element
	if(++*count_ptr && key<=root->key){     //incrementing count_ptr whenever comparision is the basic operation
        //if key is lesser than the node we move to the left subtree
        
		root->left=insert_nodes(root->left,key,count_ptr);  
	}else if(++*count_ptr && key>root->key){    //we increment the count_ptr pointer inside the if statement itself
        //if key is greater than the node we move to the right subtree
    
		root->right=insert_nodes(root->right,key,count_ptr);
	}
}
//to insert elements into the binary tree and the pointer variable holds the number of comparisions made
void insert(bst_t *tree, int key, int *count_ptr)
{
    //calling helper function insert_nodes()
    //which inserts the node into the binary search tree recursively 
    //passing root of the tree as an argument to the function

    tree->root=insert_nodes(tree->root,key,count_ptr);
}

//deletes the given key from the binary search tree and replaces with inorder_sucessor
static node_t* delete_node(node_t *curr,int key,int* count_ptr){
	if(curr!=NULL){ //root should not be equal to NULL
		if(++*count_ptr && key<curr->key){  //we increment the count_ptr pointer value since a comaprision was made
            //we move to left subtree of the node
			curr->left=delete_node(curr->left,key,count_ptr);
		}else if(++*count_ptr && key>curr->key){//we increment the count_ptr pointer value since a comaprision was made
            //we move to right subtree of the node
			curr->right=delete_node(curr->right,key,count_ptr);
		}else{
			node_t *node;
			if(++*count_ptr && curr->left==NULL){//increemenyting pointer
				node=curr->right;
				free(curr);//freeing node

			}else if(++*count_ptr && curr->right==NULL){
				node=curr->left;
				free(curr);//freeing node

			}else{
				node_t *pres=curr->right;
				while(++*count_ptr && pres->left!=NULL){//incrementing pointer
					pres=pres->left;
				}
				curr->key=pres->key;
				curr->right=delete_node(curr->right,pres->key,count_ptr);
				node=curr;
                ++*count_ptr;
			}
			return node;
		}
	}
	return curr;
}
void delete_element(bst_t *tree, int key, int *count_ptr)
{
    tree->root=delete_node(tree->root,key,count_ptr);//calling the helper function
}
//search_node is a helper function which recursively finds the desired node
static int search_node(node_t *node,int key,int *count_ptr)
{
    (*count_ptr)=(*count_ptr)+3;//adding 3 because of 3 comaprision statements
    if(node==NULL) {
        (*count_ptr)=(*count_ptr)-2;    //subtracting 2 because bottom 2 comparisions are never executed
        //if node not found it returns -1
        return -1;
    }   
    //if node is found
    if(node->key==key){
        (*count_ptr)--;//subtracting 1 because bottom comparision is never excecuted
        return key;
    }//to move to tree's subtrees
    if(key<node->key){
        //left sub tree
        return search_node(node->left,key,count_ptr);
    }else{
        //right sub tree
        return search_node(node->right,key,count_ptr);
    }
}
// Searches for the element key in the bst
// Returns the element if found, else -1
int search(const bst_t *tree, int key, int *count_ptr)
{
    (*count_ptr)++; //for tree->root==NULL comparison
    if(tree->root==NULL){
        //returns -1 if tree is empty
        return -1;  
    }
    return search_node(tree->root,key,count_ptr);//calling helper function
}
//helper function to find max node
static int max_node(node_t *node,int *count_ptr){
    (*count_ptr)++; //for node->right==NULL comparison
    if (node->right == NULL) {      //if equal to NULL, the max elemet is found
        return node->key;
    }
    return max_node(node->right,count_ptr);
}
// Returns the maximum element in the BST
int find_max(const bst_t *tree, int *count_ptr)
{
    //we find the max element by moving to the leftmost subtree recursively
    (*count_ptr)++;     //for tree->root==NULL comparison
    if (tree->root == NULL) {//if tree->root==NULL then the tee is empty i.e tree->root points to NULL
        return -1;      //returning -1 because elements dont exist
    }
    return max_node(tree->root,count_ptr);//we call the max_node helper function which finds the max element recursively
}
static void kill_nodes(node_t *curr){
    if(curr==NULL)return;
    kill_nodes(curr->left);
    kill_nodes(curr->right);
    //printf("Deleting node : %d",curr->key);
    free(curr);
}
// Deletes all the elements of the bst
void free_bst(bst_t *bst) 
{
    if(bst->root==NULL){return;}//exit the function if the bst is empty
    //calling the init_bst function
    kill_nodes(bst->root);//we dont call init_bst and thus the tree cannot be used again
}

// Deletes all the elements if the bst and ensures it can be used again
void clear_bst(bst_t *bst)
{
    if(bst->root==NULL){return;}//exit the function if the bst is empty
    //calling the helper function to delete and deallocate moemory of the nodes in bst
    kill_nodes(bst->root);
    //calling the init_bst function
    init_bst(bst);//since we need to resuse the tree, its important to initialize the variable to NULL again
}
// Name: ABHINAV GUNTI
// SRN: PES1UG20CS008