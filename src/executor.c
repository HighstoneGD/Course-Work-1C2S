#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "executor.h"
#include "patientsList.h"
#include "menu.h"

char types[5][60] = {
    "������������",
    "�����������",
    "�����������",
    "��������� �����",
    "��������� ����"
};

void executor(MenuElement command, List *patients_list) {
    switch(command) {
        case EXIT:
            destructor(patients_list);
            printf("\n������ �������� ��������.");
            exit(0);
            break;
        case ADD_CLIENT:
            add_client(patients_list);
            break;
        case REMOVE_CLIENT:
            remove_client(patients_list);
            break;
        case MODIFY_CLIENT:
            modify_client(patients_list);
            break;
        case PRINT_ALL:
            print_all(patients_list);
            break;
        case PRINT_CLIENT:
            get_client(patients_list);
            break;
        case PRINT_DEBTORS:
            print_debtors(patients_list);
            break;
        case REMOVE_DEBTLESS:
            remove_debtless(patients_list);
            break;
        case SORT_BY_DEBT:
            sort_debt(patients_list);
            break;
        default:
            printf("\n������� �����: ������� �� ����. ��������� �� ���");
    }
}

void add_client(List *patients_list) {
    printf("\n��������� �������� �� ������.\n1. ����� �������\n2. ����� ����\n������ ����� �����: ");
    
    PatientData *data = malloc(sizeof(PatientData));
    Status status;

    if (get_method(2) == 1) {
        status = write_from_console(&data);
        print_error(status);

        if (status != OK)
            return;

        status = push(patients_list, data);

        print_error(status);

        if (status == OK)
            printf("\n�������� ������ ������.");

    } else {
        FILE *f = open_file("rb");

        if (!f) {
            print_error(FILE_NOT_FOUND);
            return;
        }

        while (1) {
            fread(data, sizeof(PatientData), 1, f);

            if (feof(f))
                break;
            
            status = push(patients_list, data);

            print_error(status);
            if (status == OK)
                printf("\n�������� ������ ������.");   
        }

        fclose(f);
    }

    press_to_continue();
}

void remove_client(List *patients_list) {
    printf("\n�������� ���������� ��� �볺���. ������ ��'�: ");
    char name[150];
    getchar();
    gets(name);

    ListNode *client;
    Status status = get_element_by_name(patients_list, name, &client);
    remove_node(patients_list, client);

    if (status == OK)
        printf("\n�������� ������ ��������.");

    print_error(status);
    press_to_continue();
}

void modify_client(List *patients_list) {
    printf("\n������ ���������� ��� �볺���.");
    char name[150];
    printf("\n������ ��'�:\n");
    getchar();
    gets(name);
    ListNode *client;
    Status status = get_element_by_name(patients_list, name, &client);

    if (status != OK)
        return print_error(status);

    PatientData *old_client_data = malloc(sizeof(PatientData));
    PatientData *new_client_data = malloc(sizeof(PatientData));

    copy(client -> data, old_client_data);
    copy(client -> data, new_client_data);

    status = remove_node(patients_list, client);

    if (status != OK)
        return print_error(NULL_POINTER);
    
    write_to_console(new_client_data);

    while (1) {
        printf("\n\n1. ��'�\n2. ����� ������\n3. ��� ������\n4. ֳ�� ������\n5. ��������\n6. �������� ��� � �����\n������� ����, ��� ������� ������: ");
        unsigned field = get_method(6);

        if (field != 6)
            printf("\n������ ���� ��������: ");

        switch (field) {
            case 1:
                getchar();
                gets(new_client_data -> name);
                break;
            case 2:
                scanf("%u", &(new_client_data -> card_number));
                break;
            case 3:
                printf("\n���� ����:");
                for (int i = 0; i < 5; i++)
                    printf("\n%d. %s", i + 1, types[i]);
                printf("\n������ ���: ");
                unsigned type = get_method(5);
                new_client_data -> type = type;
                break;
            case 4:
                scanf("%u", &(new_client_data -> cost));
                sync_debt(new_client_data);
                break;
            case 5:
                scanf("%u", &(new_client_data -> paid));
                sync_debt(new_client_data);
                break;
            case 6:
                status = push(patients_list, new_client_data);
                print_error(status);
                if (status != OK) {
                    status = push(patients_list, old_client_data);
                    print_error(status);
                    printf("\n������� �������, ���� ��� �� ���� �����.\n");
                }

                press_to_continue();
                return;
        }
    }

}

void get_client(List *patients_list) {
    printf("\n������� ���������� ��� �볺���.");
    char name[150];
    printf("\n������ ��'�: ");
    getchar();
    gets(name);
    ListNode *client;
    Status status = get_element_by_name(patients_list, name, &client);

    if (status != OK) {
        print_error(status);
        press_to_continue();
        return;
    }

    printf("\n1. ����� �������\n2. � ����\n������ ����� ������: ");
        
    if (get_method(2) == 1) {
        Status status1 = write_to_console(client -> data);
        print_error(status1);
        print_line();
    } else {
        FILE *f = open_file("ab");

        if (!f) {
            print_error(FILE_NOT_FOUND);
            press_to_continue();
            return;
        }

        fwrite(client, sizeof(PatientData), 1, f);
        fclose(f);
    }

    press_to_continue();
}

void print_all(List *patients_list) {
    printf("������ �볺���.\n1. ����� �������\n2. � ����\n������ ����� ������: ");
    unsigned method = get_method(2);
    FILE *f;

    if (method == 2) {
        f = open_file("ab");
        if (!f) {
            print_error(FILE_NOT_FOUND);
            return;
        }
    }

    ListNode *cur = patients_list -> head;
    
    if (!cur) {
        print_error(NO_ELEMENTS);
        print_line();
        return;
    }

    while (cur) {
        method == 1 ? write_to_console(cur -> data) : fwrite(cur -> data, sizeof(PatientData), 1, f);
        cur = cur -> next;
    }

    if (method == 1)
        print_line();
    else
        fclose(f);

    press_to_continue();
}

void print_debtors(List *patients_list) {
    printf("\n������ ��������.\n1. ��� ���� \n2. ���� �����\n������ �� ���� ������ ���������� ��������: ");
    unsigned empty = 1, method = get_method(2);
    ListNode *cur = patients_list -> head;

    while (cur) {
        if (cur -> data -> debt) {
            empty = 0;
            print_line();
            method == 1 ? 
                printf("\n%s: %s", cur -> data -> name, types[cur -> data -> type]) : 
                printf("\n%s: %u ���.", cur -> data -> name, cur -> data -> debt);
        }
        cur = cur -> next;
    }

    if (empty)
        print_error(NO_ELEMENTS);

    print_line();
    press_to_continue();
}

void remove_debtless(List *patients_list) {
    printf("��������� ��� ������ ��� ��������������.\n");
    ListNode *cur = patients_list -> head;

    while (cur) {
        if (!cur -> data -> debt) {
            ListNode *debtless = cur;
            cur = cur -> next;
            Status status = remove_node(patients_list, debtless);
            print_error(status);
            if (status == OK)
                printf("\n�������� ������ ��������.");
        } else {
            cur = cur -> next;
        }
    }

    press_to_continue();
}

void sort_debt(List *patients_list) {
    printf("���������� ��� ������ �� ���������� ��������������...");
    Status status = sort(patients_list);

    print_error(status);
    if (status == OK)
        printf("\n�������� ������ ������������.\n");
    
    press_to_continue();
}

unsigned get_method(unsigned amount) {
    unsigned method;
    while (1) {
        method = scan_unsigned();
        if (!method || method > amount)
            printf("�������� ��������. ��������� �� ���: ");
        else
            return method;
    }
}

void sync_debt(PatientData *data) {
    data -> debt = data -> paid < data -> cost ? data -> cost - data -> paid : 0;
    printf("\n�������������� ��������� %d ���.", data -> debt);
}

void print_error(Status status) {
    switch(status) {
        case OK:
            break;
        case NULL_POINTER:
            printf("\n������� � ����� ��������.");
            break;
        case INPUT_ERROR:
            printf("\n�� ������� �������� ����������: ������������ ������ �����.");
            break;
        case ELEMENT_ALREADY_EXISTS:
            printf("\n������� � ����� ��'�� ��� ������� ������ ��� ����.");
            break;
        case NO_ELEMENTS:
            printf("\n������ ������...");
            break;
        case ELEMENT_NOT_FOUND:
            printf("\n������ �������� ����.");
            break;
        case FILE_NOT_FOUND:
            printf("\n���� � ����� ��'�� �� ���������.");
            break;
        default:
            printf("\n������� �������.");
    }
}

FILE * open_file(char method[3]) {
    printf("\n������ ����� ����� (��� ����������): ");
    char name[100];
    scanf("%s", name);
    strcat(name, ".bin");
    FILE *f = fopen(name, method);
    return f;
}

Status write_from_console(PatientData **result) {
    if (!result)
        return NULL_POINTER;
    
    printf("\n���� �����:");
    printf("\n������ ��'� ��/��� ������� ��������: ");
    getchar();
    gets((*result) -> name);
    printf("\n������ ����� ������ ��������: ");
    (*result) -> card_number = scan_unsigned();
    printf("\n���� ����:");
    for (int i = 0; i < 5; i++)
        printf("\n%d. %s", i + 1, types[i]);
    printf("\n������ ��� ������: ");
    unsigned type = get_method(5);
    (*result) -> type = type;
    printf("\n������ ������� �������� ������ (� ���): ");
    (*result) -> cost = scan_unsigned();
    printf("\n������ �������� ���� (� ���): ");
    (*result) -> paid = scan_unsigned();
    sync_debt(*result);
    return OK;
}

Status get_element_by_name(List *list, char name[], ListNode **result) {
    if (!list || !result)
        return NULL_POINTER;
    
    ListNode *cur = list -> head;
    while (cur) {
        if (!strcmp(cur -> data -> name, name)) {
            *result = cur;
            return OK;
        }
        cur = cur -> next;
    }
    return ELEMENT_NOT_FOUND;
}

Status write_to_console(PatientData *data) {
    if (!data)
        return NULL_POINTER;
    print_line();
    printf("\n��'�: %s", data -> name);
    printf("\n����� ������: %d", data -> card_number);
    printf("\n��� ������: %s", types[data -> type]);
    printf("\n������� ������: %d ���", data -> cost);
    printf("\n��������: %d ���", data -> paid);
    printf("\n��������������: %d ���", data -> debt);
    return OK;
}