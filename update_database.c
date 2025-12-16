/****************************************************************************************
* Name        : Rudragond Hegadi
* File Name   : update_database.c
* Date        : 07/12/2025
* Data        : file_node *head, char filename[50], hash_t hash_table[TOTAL_INDEX], main_node, Subnode
* Description : Updates the database by adding new files and updating word counts.
****************************************************************************************/
#include "inverted_search.h"
#include <stdio.h>
#include <ctype.h>

extern hash_t hash_table[TOTAL_INDEX];                            // index size

int update_database(file_node *filelist)
{
    printf("\n********** DATABASE **********\n");

    for (int i = 0; i < TOTAL_INDEX; i++)
    {
        main_node *mtemp = hash_table[i].link;                    
        while (mtemp != NULL)                                      //main node 
        {
            printf("\nWORD        : %s\n", mtemp->word);
            printf("FILE COUNT 	  : %d\n", mtemp->file_count);
            printf("--------------------------------------\n");

            Subnode *sub = mtemp->slink;                                 //subnode traversing
            while (sub != NULL)                                        // subnode update 
            {
                printf("FILE : %-15s  COUNT : %d\n",sub->file_name, sub->word_count);
				sub = sub->link;
            }
            printf("--------------------------------------\n");
            mtemp = mtemp->mlink;                                       // traversing 
        }
    }

    printf("\n********** END OF DATABASE **********\n");
    return SUCCESS;
}



