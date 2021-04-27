#include <stddef.h>
#include <stdlib.h>
#include "list.h"

list *allocate_node(int val);

list* empty_list(){
    return NULL;
}

int is_empty(list* lst){
    return lst == NULL;
}

list *add(list* lst, int val){
    if (is_empty(lst)){
        return allocate_node(val);
    }
    list *out = lst;
    while(lst->next != NULL){
        lst = lst->next;
    }
    lst->next = allocate_node(val);
    return out;
}

int contains(list *lst, int val){
    while(lst != NULL){
        if(lst->val==val){
            return 1;
        }
        lst = lst->next;
    }
    return 0;
}

list *allocate_node(int val) {
    list *node = malloc(sizeof(list));
    node->val=val;
    node->next=NULL;
    return node;
}
