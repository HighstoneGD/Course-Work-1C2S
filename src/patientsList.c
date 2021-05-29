#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "patientsList.h"
#include "menu.h"

Status destructor(List *list) {
    if (!list)
        return NULL_POINTER;

    ListNode *tmp;
    while (!list -> head) {
        tmp = list -> head -> next;
        free(list -> head);
        list -> head = tmp;
    }
    return OK;
}

Status push(List *list, PatientData *data) {
    if (!list || !data)
        return NULL_POINTER;

    ListNode *cur = list -> head;
    while (cur) {
        if (!strcmp(cur -> data -> name, data -> name) || cur -> data -> card_number == data -> card_number) 
            return ELEMENT_ALREADY_EXISTS;
        cur = cur -> next;
    }
    ListNode *tmp = (ListNode *) malloc(sizeof(ListNode));
    tmp -> data = data;
    tmp -> next = list -> head;
    list -> head = tmp;
    return OK;
}

Status remove_node(List *list, ListNode *client) {
    if (!list || !client)
        return NULL_POINTER;
    
    if (!list -> head)
        return NO_ELEMENTS;
    
    ListNode *cur = list -> head;

    if (cur == client) {
        list -> head = cur -> next;
        free(cur);
        return OK;
    }
        
    while (cur -> next) {
        if (cur -> next == client) {
            ListNode *target = cur -> next;
            cur -> next = target -> next;
            free(target);
            return OK;
        }
            
        cur = cur -> next;
    }

    return ELEMENT_NOT_FOUND;
}

Status sort(List *list) {
    if (!list)
        return NULL_POINTER;
    
    unsigned size = 0;
    ListNode *cur = list -> head;
    while (cur) {
        size++;
        cur = cur -> next;
    }

    for (unsigned i = 0; i < size; i++) {
        cur = list -> head;

        while (cur -> next) {
            if (cur -> data -> debt < cur -> next -> data -> debt) {
                PatientData *temp = cur -> data;
                cur -> data = cur -> next -> data;
                cur -> next -> data = temp;
            }

            cur = cur -> next;
        }
    }

    return OK;
}

Status copy(PatientData *source, PatientData *destination) {
    if (!source || !destination)
        return NULL_POINTER;
    strcpy(destination -> name, source -> name);
    destination -> card_number = source -> card_number;
    destination -> type = source -> type;
    destination -> cost = source -> cost;
    destination -> paid = source -> paid;
    destination -> debt = source -> debt;
    return OK;
}