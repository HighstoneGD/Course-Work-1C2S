#include <stdio.h>
#include "menu.h"

#define ITEMS_AMOUNT 10
#define ITEM_MAX_LENGTH 110
#define MENU_WIDTH 70

char menu_items[ITEMS_AMOUNT][ITEM_MAX_LENGTH] = {
    "���� 䳿",
    "1. ������ �볺��� �� ������",
    "2. �������� �볺��� � ������",
    "3. ���������� ��� �볺���",
    "4. ������� ������ �������",
    "5. ������� ������ �볺���",
    "6. ������� ������ ��� ��������",
    "7. �������� ������ �볺���, �� �� ����� �������������",
    "8. ��������� ������ �� ����� �������������",
    "0. ����� � ��������",
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
    printf("\n������ ����� �������: ");
    unsigned command;
    scanf("%u", &command);
    return command <= ITEMS_AMOUNT ? command : 10;
}

void press_to_continue() {
    printf("\n�������� Enter ��� ����������... ");
    getchar();
    while (getchar() != '\n') {}
}