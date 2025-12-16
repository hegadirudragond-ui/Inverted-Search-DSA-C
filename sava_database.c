/****************************************************************************************
* Name        : Rudragond Hegadi
* File Name   : save_database.c
* Date        : 07/12/2025
* Data        : hash_t hash_table[TOTAL_INDEX], FILE *fp, main_node, Subnode
* Description : Saves the current database to a file for later use.
****************************************************************************************/

#include "inverted_search.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern hash_t hash_table[TOTAL_INDEX];                                       // 3hash table

// Function to save database to a file
int save_database(const char *output_file)
{
    FILE *fp = fopen(output_file, "w");                                             // Open file for writing
    if (fp == NULL) 
    {                                                                           // Check if file opened successfully
        printf("Cannot open file %s\n", output_file);
        return -1;
    }

                                                                                        
    for (int i = 0; i < TOTAL_INDEX; i++)                                              // Loop over all hash table entries
     {
        main_node *wordNode = hash_table[i].link;

        while (wordNode != NULL)
         {                                                                                  // Loop over words
            fprintf(fp, "%s %d: ", wordNode->word, wordNode->file_count);               // Write word and count

            Subnode *fileNode = wordNode->slink;

            while (fileNode != NULL) 
            {                                                                           // Loop over files for this word
                fprintf(fp, "%s %d", fileNode->file_name, fileNode->word_count);            // Write file info
                fileNode = fileNode->link;
                if (fileNode != NULL)
                {
                    fprintf(fp, ", ");                                              // Separate files with comma
                }
            }

            fprintf(fp, "\n");                                                   // New line after each word
            wordNode = wordNode->mlink;                                         // Move to next word
        }
    }

    fclose(fp);                                                                 // Close the file
    printf("Database saved to %s\n", output_file);
    return 0;
}
