/***************************************************************************************************************************************************
* Name        : Rudragond Hegadi
* date        : 07/12/2025
* File Name   : display_database.c
* Data        : hash_t hash_table[TOTAL_INDEX], main_node, Subnode, file occurrences, word counts
*Title          :To display  the results.
*Description    :When all the words are searched the ouput list is formed. In this the file with max count
		:(representing maximum word match ) can be selected and displayed. For advanced searched,
		:(weighage of words stored in database linkedlist) can also be used. So the results will be more
		:accurate.
****************************************************************************************************************************************************/
#include "inverted_search.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern hash_t hash_table[26]; // Hash table for 26 letters

int display_database(file_node *filelist)
{
    printf("\n************** DISPLAY DATABASE **************\n"); // Header

    printf("Index  | Word        | File count  | File/s\n"); // Table header
    printf("------------------------------------------------------\n"); // Divider

    for (int i = 0; i < 26; i++) // Loop over hash table for 26 letters
    {
        main_node *mtemp = hash_table[i].link; // Get first word node
        if (mtemp == NULL)                      // Skip if empty
            continue;

        while (mtemp != NULL)                    // Loop over words in this index
        {
            printf("[%d]   [ %-15s] %d file/s: ", i, mtemp->word, mtemp->file_count); // Print word info

            Subnode *stemp = mtemp->slink;      // Get first file node
            while (stemp != NULL)               // Loop over files for this word
            {
                printf("File : %-10s %d", stemp->file_name, stemp->word_count); // Print file info
                stemp = stemp->link;            // Move to next file
                if (stemp != NULL)
                    printf(", ");               // Comma between files
            }

            printf("\n");                        // New line after files
            mtemp = mtemp->mlink;                // Move to next word
        }
    }

    printf("**********************************************\n\n"); // Footer
    return SUCCESS; // Return success
}
