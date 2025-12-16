/****************************************************************************************
* Name        : Rudragond Hegadi
* File Name   : inverted_search.h
* Date        : 07/12/2025
* Data        : Structure definitions (main_node, Subnode, file_node, hash_t), macros, function declarations
* Description : Header file containing definitions and declarations for database operations.
****************************************************************************************/


#ifndef INVERTED_SEARCH_H
#define INVERTED_SEARCH_H
#define TOTAL_INDEX 27  

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//macros
#define SUCCESS 0
#define FAILURE -1

extern int database_created;

typedef struct sub                       //structure for subnode
{
    int word_count;
    char file_name[50];
    struct sub *link;

}Subnode;

typedef struct main                         //structure for mainnode
{
    int file_count;
    char word[50];
    Subnode *slink;
   struct main *mlink;

}main_node;

typedef struct hash                          //structure for hashtable
{
    int index;
    main_node *link;

}hash_t;

typedef struct file                           //structure for filenode or linkedlist            
{
    char file_name[50];
    struct file *link;

}file_node;

extern file_node *head;

// own defined functions prototypes
int validate_arguments(int argc, char *argv[]);
int is_duplicate(file_node *head, char *filename);
int insert_file(file_node **head, char *filename);




// main functions calling prototypes
int create_database(file_node *filelist);
int display_database(file_node *filelist);
int save_database(const char *output_file);
int search_database(char *word);
int update_database(file_node *filelist);

#endif
