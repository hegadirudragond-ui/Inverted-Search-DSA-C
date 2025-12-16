/***************************************************************************************************************************************************
* Name        : Rudragond Hegadi
* File Name   : search_database.c
* date		  : 07/12/2025
* Data        : char *word, hash_t hash_table[TOTAL_INDEX], main_node, Subnode
*Description    :Each word is now used to search in the linkedlist. The word has to be compared with
		:each word in the linked list. When found, the file details can be retrieved. Since the
		:linkedlist is in sorted order, the complexity of searching the word in the complete list
		:can be avoided. While string comparison, if the word in linkedlist is greater than the
		:word to be search, it shows the word doesn't exists in the list,
****************************************************************************************************************************************************/
#include "inverted_search.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

extern hash_t hash_table[TOTAL_INDEX];
//int search_database(char *word, word *indexlist, file_node* output_file)
int search_database(char *word)
{
		/* Definition here */
		if(word==NULL)
		{
			printf("Invalid input word.\n");
			return FAILURE;
		}
		
		for (int i = 0; word[i]; i++)
        word[i] = tolower(word[i]);

		printf("Searching database...\n");
		//checking index
		int index;
		 if (isupper(word[0]))             //1st letter is captail
		 {
       		 index = word[0] - 'A';
		 }
    	else if(islower(word[0]))			 //1st letter is small
		{
        	index = word[0] - 'a';
		}
   		 else									//extra character
		 {
      		  index = 26;
		 }

		main_node *mtemp = hash_table[index].link;        //take main temp
		while(mtemp!=NULL)
		{
			
			// if (strcmp(mtemp->word, word) == 0)
			if (strcasecmp(mtemp->word, word) == 0)
			{
				// FOUND
				printf("\n--------------------------------------\n");
				printf("WORD        : %s\n", word);
				printf("FILE COUNT  : %d\n", mtemp->file_count);
				printf("--------------------------------------\n");

				Subnode *sub = mtemp->slink;
				while (sub != NULL)
				{
					printf("FILE : %-15s  COUNT : %d\n",
						sub->file_name, sub->word_count);
						sub = sub->link;
				}

				printf("--------------------------------------\n\n");
				return SUCCESS;
			}
		

        // Optimization: break if list is sorted and word passed alphabetically
        if (strcmp(mtemp->word, word) > 0)
            break;

        mtemp = mtemp->mlink;                              //traverse
		}

    printf("Word '%s' not found in database.\n", word);
    return FAILURE;

}

