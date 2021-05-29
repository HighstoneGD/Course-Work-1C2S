#include "structs/status.h"
#include "structs/list.h"

Status destructor(List *list);
Status push(List *list, PatientData *node);
Status remove_node(List *list, ListNode *client);
Status sort(List *list);
Status copy(PatientData *source, PatientData *destination);