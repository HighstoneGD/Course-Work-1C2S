#include <stdio.h>
#include "menu.h"

#define ITEMS_AMOUNT 10
#define ITEM_MAX_LENGTH 110
#define MENU_WIDTH 70

char menu_items[ITEMS_AMOUNT][ITEM_MAX_LENGTH] = {
    "Вибір дії",
    "1. Додати клієнта до списку",
    "2. Видалити клієнта зі списку",
    "3. Корегувати дані клієнта",
    "4. Вивести список повністю",
    "5. Вивести довідку клієнта",
    "6. Вивести довідку про боржників",
    "7. Видалити записи клієнтів, які не мають заборгованості",
    "8. Сортувати записи за сумою заборгованості",
    "0. Вихід з програми",
};

void print_line() {
    printf("\n");
    for (unsigned i = 0; i < MENU_WIDTH; i++)
        printf("-");
}

void print_menu() {
    printf("\n");
    print_line();
    printf("\n\t%s", menu_items[0]);
    print_line();
    
    for (int i = 1; i < ITEMS_AMOUNT; i++)
        printf("\n\t%s", menu_items[i]);
    
    print_line();
    printf("\n");
}

MenuElement scan_command() {
    printf("\nВведіть номер команди: ");
    unsigned command;
    scanf("%u", &command);
    return command <= ITEMS_AMOUNT ? command : 10;
}

void press_to_continue() {
    printf("\nНатисніть Enter щоб продовжити... ");
    getchar();
    while (getchar() != '\n') {}
}