#ifndef MENU_ELEMENT
#define MENU_ELEMENT

extern char types[5][60];

typedef enum MenuElement {
    EXIT,
    ADD_CLIENT,
    REMOVE_CLIENT,
    MODIFY_CLIENT,
    PRINT_ALL,
    PRINT_CLIENT,
    PRINT_DEBTORS,
    REMOVE_DEBTLESS,
    SORT_BY_DEBT,
} MenuElement;

#endif