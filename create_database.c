/***************************************************************************************************************************************************
*Name           :Rudragond Hegadi
*Date           :07/12/2025
*File           :create_database.c
*Title          :To create the database
*Description    :The list of the files can be provided by storing all the file names in another file, FileList the names of the files which 
		:are to be documented are provided by this file. When a file is added or removed, FileList is changed accordingly.
		:So read the file names and start indexing.
****************************************************************************************************************************************************/
#include "inverted_search.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define TOTAL_INDEX 27  // 26 letters + 1 for non-alphabetic

hash_t hash_table[TOTAL_INDEX] = {0};  // Declare hash table variable

int create_database(file_node *filelist)
{
	/* Definition here */
	printf("\n");
	//printf("Creating data base started...\n");
	//check filelist is  null or not
	if(filelist==NULL)
	{
		return FAILURE;
	}

	file_node *temp = filelist;
	
	while(temp!=NULL)
	{
		FILE *fp =fopen(temp->file_name,"r");
		if(fp==NULL)
		{
			printf("Error : File %s cannot open.\n",temp->file_name);
			temp = temp->link;
			continue;
		}
		
		
		char word[50];
		while(fscanf(fp,"%s",word)!=EOF)
		{
			int index;

			if(isupper(word[0]))
			{
				 index= word[0] - 65;
			} 
			else if(islower(word[0]))
			{
				index = word[0] - 97;
			}
			else
			{
				index = 26;
			}
			
  	main_node *mtemp = hash_table[index].link;
    main_node *mprev = NULL;
    int word_found = 0;

    // Search for word in main_node list
    while (mtemp != NULL)
    {
        if (strcmp(mtemp->word, word) == 0)
        {
            word_found = 1;
            break;
        }
        mprev = mtemp;
        mtemp = mtemp->mlink;
    }

    // Word not found -> create new main_node
    if (!word_found)
    {
        mtemp = (main_node *)malloc(sizeof(main_node));
        strcpy(mtemp->word, word);
        mtemp->file_count = 1;
        mtemp->slink = NULL;
        mtemp->mlink = NULL;

        if (!mprev)
            hash_table[index].link = mtemp;
        else
            mprev->mlink = mtemp;

        // Add first subnode for this file
        Subnode *sub = (Subnode *)malloc(sizeof(Subnode));
        strcpy(sub->file_name, temp->file_name);
        sub->word_count = 1;
        sub->link = NULL;
        mtemp->slink = sub;

        // Print debug
        // printf("Word: %-12s | File: %-15s | Count: %d | Index: %d\n", word, temp->file_name, sub->word_count, index);
    }
    else
    {
        // Word found -> search for this file in subnode list
        Subnode *stemp = mtemp->slink;
        Subnode *sprev = NULL;
        int file_found = 0;

        while (stemp != NULL)
        {
            if (strcmp(stemp->file_name, temp->file_name) == 0)
            {
                stemp->word_count++;  // Increment word count
                file_found = 1;

                // Print debug
                // printf("Word: %-12s | File: %-15s | Count: %d | Index: %d\n", word, temp->file_name, stemp->word_count, index);
                break;
            }
            sprev = stemp;
            stemp = stemp->link;
        }

        // File not found -> add new subnode
        if (!file_found)
        {
            Subnode *sub = (Subnode *)malloc(sizeof(Subnode));
            strcpy(sub->file_name, temp->file_name);
            sub->word_count = 1;
            sub->link = NULL;

            if (sprev)
                sprev->link = sub;

            mtemp->file_count++;

            // Print debug
            // printf("Word: %-12s | File: %-15s | Count: %d | Index: %d\n", word, temp->file_name, sub->word_count, index);
        }
    
	}
}
		 fclose(fp);
        temp = temp->link;  // Move to next file
	}
	return SUCCESS;
}







// void insert_to_database(char *word, char *filename, int index)
// {
//     main_node *curr_word = hash_table[index];
//     main_node *prev_word = NULL;
//     int word_found_flag = 0;
//     int file_found_flag = 0;

//     // Check if word exists in this index
//     while (curr_word != NULL)
//     {
//         if (strcmp(curr_word->word, word) == 0)
//         {
//             word_found_flag = 1;
//             break;
//         }
//         prev_word = curr_word;
//         curr_word = curr_word->mlink;
//     }

//     // If word not found, create a new main_node
//     if (!word_found_flag)
//     {
//         curr_word = (main_node *)malloc(sizeof(main_node));
//         strcpy(curr_word->word, word);
//         curr_word->file_count = 0;
//         curr_word->slink = NULL;
//         curr_word->mlink = NULL;

//         if (!prev_word)
//             hash_table[index] = curr_word; // first word in this bucket
//         else
//             prev_word->mlink = curr_word;
//     }

//     // Check if file already linked
//     Subnode *curr_file = curr_word->slink;
//     while (curr_file != NULL)
//     {
//         if (strcmp(curr_file->file_name, filename) == 0)
//         {
//             curr_file->word_count++;
//             file_found_flag = 1;
//             break;
//         }
//         curr_file = curr_file->link;
//     }

//     // If file not found, add new Subnode
//     if (!file_found_flag)
//     {
//         Subnode *new_file = (Subnode *)malloc(sizeof(Subnode));
//         strcpy(new_file->file_name, filename);
//         new_file->word_count = 1;
//         new_file->link = curr_word->slink;
//         curr_word->slink = new_file;
//         curr_word->file_count++;
//     }

//     // Debug print (optional)
//     printf("Inserted Word: %-12s | File: %-15s | Index: %d\n", word, filename, index);
// }