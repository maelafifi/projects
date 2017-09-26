/* sum_args_linked.c - sum args using a linked list */

#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct arg_node {
    struct list_elem elem;
    int value;
};


struct arg_node *arg_node_new(int value)
{
    struct arg_node *an;

    an = (struct arg_node *) malloc(sizeof(struct arg_node));
    if (an == NULL) {
        printf("arg_node_new(): Cannot malloc. Exiting.\n");
        exit(-1);
    }        
    an->value = value;
    
    return an;
}

    
void parse_args(int argc, char **argv, struct list *l)
{
    int i;
    struct arg_node *an;
    
    for (i = 0; i < argc; i++) {
        an = arg_node_new(atoi(argv[i]));
        list_push_back(l, &an->elem);
    }

    return;
}

int sum_args_list(struct list *l)
{
    struct list_elem *e;
    struct arg_node *an;
    int sum = 0;
    
    for (e = list_begin(l); e != list_end(l); e = list_next(e)) {
        an = list_entry(e, struct arg_node, elem);
        sum += an->value;
    }

    return sum;
}

int main(int argc, char **argv)
{
    struct list args_list;
    int sum;

    list_init(&args_list);
    
    parse_args(argc, argv, &args_list);

    sum = sum_args_list(&args_list);

    printf("%d\n", sum);
   
    return 0;
}

