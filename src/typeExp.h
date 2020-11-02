#include <stdio.h>
#define MAX_LEN 50


typedef enum{integer = 0, real = 0, boolean = 0, rect_Arr=1, jagged_Arr=2}type;

typedef struct
{
    char var_name[MAX_LEN];
    type var_n;
    char arr_type[MAX_LEN];
    union
    {
        struct
        {
            char type[MAX_LEN];
        }primitive;

        struct
        {
            char type[MAX_LEN];
            int dimensions;
            int* low;
            int* high;
            char basicElementType[] = "integer";

        }rect;

       struct
        {
           char type[MAX_LEN];
           int dimensions;
           int low, high;
           int* size;
           int** values;
           char* basicElementType = "integer";

        }jagged;


    }typeExpression;

}typeCell;

typedef struct link
{
    typeCell t;
    struct link* next;

}LINK ;

typedef struct
{
    LINK* head;
    LINK* tail;
}typex_table;



