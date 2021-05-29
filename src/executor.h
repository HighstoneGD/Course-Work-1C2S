#include "structs/menuElement.h"
#include "structs/list.h"
#include "structs/status.h"

void executor(MenuElement command, List *patients_list);
void add_client(List *patients_list);
void remove_client(List *patients_list);
void modify_client(List *patients_list);
void get_client(List *patients_list);
void print_all(List *patients_list);
void print_debtors(List *patients_list);
void remove_debtless(List *patients_list);
void sort_debt(List *patients_list);
unsigned get_method(unsigned amount);
void print_error(Status status);
void sync_debt(PatientData *data);
FILE * open_file(char method[3]);
Status write_from_console(PatientData **result);
Status get_element_by_name(List *list, char name[], ListNode **result);
Status write_to_console(PatientData *data);