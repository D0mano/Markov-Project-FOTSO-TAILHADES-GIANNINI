#ifndef TYPES_H
#define TYPES_H

typedef struct s_cell{
    struct s_cell* arrival;
    struct s_cell* next;
    int arrival_vertex;
    float probability;
} t_cell;

typedef t_cell* p_cell;

typedef struct s_list {
    t_cell* head;
}t_list;

typedef struct s_adjacency_list {
    int size;
    t_list* tab;
} t_adjacency_list;

typedef struct {
    int id;
    int num;
    int lowlink;
    int inStack;
} t_tarjan_vertex;

typedef struct s_class_cell {
    struct s_class_cell *next;
    t_tarjan_vertex vertex;
}t_class_cell;

typedef struct s_class_list {
    t_class_cell* head;
}t_class_list;

typedef struct {
    char name[10];
    t_class_list vertices;
    int size;
} t_class;

typedef struct s_partition_cell {
    struct s_partition_cell *next;
    t_class class;
} t_partition_cell;

typedef struct s_partition_list {
    struct s_partition_cell *head;
} t_partition_list;

typedef struct {
    t_partition_list classes;
    int size;
} t_partition;

typedef struct
{
    int from;
    int to;
} t_link;

typedef struct
{
    t_link *links;   // dynamically allocated array of t_link
    int log_size;    // number of valid links
} t_link_array;

#endif