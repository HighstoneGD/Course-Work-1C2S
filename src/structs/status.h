#ifndef STATUS
#define STATUS

typedef enum Status {
    OK,
    NULL_POINTER,
    FILE_NOT_FOUND,
    ELEMENT_ALREADY_EXISTS,
    INPUT_ERROR,
    ELEMENT_NOT_FOUND,
    NO_ELEMENTS
} Status;

#endif