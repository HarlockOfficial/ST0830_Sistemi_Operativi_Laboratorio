#ifndef LISTLIB_LIST_H
#define LISTLIB_LIST_H
typedef struct list_t{
    int val;
    struct list_t *next;
} list;

int is_empty(list* lst);
list* empty_list();
list* add(list* lst, int val);
int contains(list* lst, int val);
#endif //LISTLIB_LIST_H
