#include "list.h"
#include <stdio.h>

int main(void){
    struct cellule *p = NULL;
    
    head_push(&p, 100);
    head_push(&p, 2);
    head_push(&p, 10);
    head_push(&p, 42);
    
    print_list(p);
    
    head_pop(&p);
    head_pop(&p);
    
    print_list(p);
    
    free_list(&p);
    
    return 0;
}
