#ifndef LIST
#define LIST

typedef enum WorkType {
    PROSTHETICS = 1,
    FILLINGS,
    IMPLANTS,
    INSPECTION,
    EXTRACTION
} WorkType;

typedef struct PatientData {
    char name[150];
    unsigned card_number;
    WorkType type;
    unsigned cost;
    unsigned paid;
    unsigned debt;
} PatientData;

typedef struct ListNode {
    PatientData *data;
    struct ListNode *next;
} ListNode;

typedef struct List {
    ListNode *head;
} List;

#endif