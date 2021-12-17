#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct ll_node {
    struct ll_node* prev;
    struct ll_node* next;
    void* data;
};

struct ll_list {
    struct ll_node* header;
    int len;
};

struct ll_iter {
    struct ll_node * current;
    struct ll_list * list;
};

void ll_init (struct ll_list* list) {
    list->header = malloc(sizeof(*list->header));
    list->header->prev = list->header;
    list->header->next = list->header;
    list->header->data = NULL;
    list->len = 0;
}

void ll_iter (struct ll_list* list, struct ll_iter* iter) {
    iter->current = list->header;
    iter->list = list;
}

bool ll_has_next (struct ll_iter* iter) {
    return iter->current->next != iter->list->header;
}

void* ll_next (struct ll_iter* iter) {
    iter->current = iter->current->next;
    return iter->current->data;
}

void ll_insert(struct ll_iter *iter, void *data) {
    struct ll_node *new_node = malloc(sizeof(*new_node));
    new_node->data = data;
    new_node->prev = iter->current;
    new_node->next = new_node->prev->next;
    new_node->prev->next = new_node;
    new_node->next->prev = new_node;
    iter->list->len += 1;
}

/**
 * @brief Remove the previous element in the list
 * 
 * @param iter The list iterator to remove from
 * @return int -1 if tried to remove header, 1 if success
 */
int ll_remove(struct ll_iter* iter) {
    if (iter->current == iter->list->header) return -1;

    struct ll_node* node = iter->current;
    iter->current = node->prev;

    node->prev->next = node->next;
    node->next->prev = node->prev;

    free(node);
    iter->list->len--;
    return 1;
}

void print_list(struct ll_list* list) {
    struct ll_iter iter;
    ll_iter(list, &iter);
    int i = 0;
    while (ll_has_next(&iter)) {
        char *data = ll_next(&iter);
        printf("Element %i: %s\n", i++, data);
    }
}

int main() {
    struct ll_list list;
    ll_init(&list);

    struct ll_iter iter;
    ll_iter(&list, &iter);

    ll_insert(&iter, "Hello, World!");
    ll_next(&iter);
    ll_insert(&iter, "This is a list!");
    ll_next(&iter);

    print_list(&list);

    ll_remove(&iter);

    print_list(&list);

    return 0;
}