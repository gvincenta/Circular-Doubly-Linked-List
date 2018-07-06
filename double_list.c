
/* circular doubly linked list, BST implementation
    * created by Gilbert Vincenta May 2018
        */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
typedef struct node node_t;
typedef int data_t;
struct node {
    data_t value;
    node_t *left;
    node_t *right;
    // left = previous, right = next
};


typedef struct {
    node_t *head;
    node_t *foot;
} list_t;

int cmp (void* a, void* b);
list_t *init_link();
void insert_at_foot (data_t data , list_t *link);
list_t *insert_at_head (data_t data, list_t *link);
void traverse (list_t *link, void (*action) (node_t *));
void echo (node_t *new);
void delete_head(list_t *link);
void delete_foot(list_t *link);
void delete_a_node (node_t *node);
void free_link (list_t *link);

int main (int argc, char* argv[]) {
    list_t *link;
    link = init_link();
    data_t new;
    while (scanf("%d",&new) == 1) {
        insert_at_head(new,link);
    }
    traverse(link, echo);
    free_link(link);
    return 0;
}

int cmp (void* a, void* b){
    return (* (data_t *) a ) - (* (data_t *) b);
}
void free_link (list_t *link){
    node_t *curr = link->head;
    node_t *oldhead;
    while (curr){
        oldhead = curr;
        curr = curr->right;
        free(oldhead);
        if (curr == link->head){
            break;
        }
    }
    /*all nodes freed*/
    free(link);
    /*link is gone*/
}

list_t *init_link(){
    list_t *link;
    link = (list_t *) malloc (sizeof(list_t));
    link->head = link->foot = NULL;
    return link;
}

void echo (node_t *new){
    printf("%d\n",new->value);
}

void insert_at_foot (data_t data , list_t *link){
    node_t *new;
    new = (node_t *) malloc(sizeof(node_t));
    new->value = data;
    new->right = link->head; // will point to NULL when it's empty
    new->left = link->foot;
    if (link->head == NULL && link->foot == NULL){
        link->head = link->foot = new;
        new->right = link->head;
        new->left = link->foot;
    }
    
    else {
        link->foot->right = new;
        link->foot = new;
        link->head->left = new;
    }
}


list_t *insert_at_head (data_t data, list_t *link){
    node_t *new;
    new = (node_t *) malloc(sizeof(node_t));
    new->value = data;
    new->left = link->foot; // will point to NULL when it's empty
    new->right = link->head;
    if (link->head == NULL && link->foot == NULL){
        link->head = link->foot = new;
        new->left = link->foot;
        new->right = link->head;
    }
    
    else {
        link->head->left = new;
        link->head = new;
        link->foot->right = new;
    }
    
    return link;
}

void traverse (list_t *link, void (*action) (node_t *)){
    node_t *curr = link->head;
    while (curr){
        action(curr);
        curr = curr->right;
        if (curr == link->head){
            /*already traversed the linked list once! */
            break;
        }
    }
}

void delete_foot(list_t *link){
    node_t *oldfoot = link->foot;
    link->foot = link->foot->left;
    link->foot->right = link->head;
    link->head->left = link->foot;
    free(oldfoot);
    oldfoot = NULL;
}

void delete_head(list_t *link){
    node_t *oldhead = link->head;
    link->head = link->head->right;
    link->foot->right = link->head;
    link->head->left = link->foot;
    free(oldhead);
    oldhead = NULL;
}

void delete_a_node (node_t *node){
    node->left->right = node->right;
    node->right->left = node->left;
    free(node);
    node = NULL;
}
