#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include "executor.h"
#include "structs/list.h"
#include "menu.h"

List patients_list;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    while (1) {
        print_menu();
        MenuElement command = scan_command();
        executor(command, &patients_list);
    }

    return 0;
}