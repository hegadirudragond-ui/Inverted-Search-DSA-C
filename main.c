/****************************************************************************************
* Name        : Rudragond Hegadi
* File Name   : main.c
* Date 		  : 07/12/2025
* Data        : File list, user menu choices
* Description : Driver function to manage menu, create, display, search, save, and update database.
****************************************************************************************/

#include "inverted_search.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// validate command line arguments
int main(int argc, char *argv[])
{
	/* Define the main function here */
	if (validate_arguments(argc, argv) == FAILURE)
	{     
		   return FAILURE;
	}
    printf("All valid .txt files processed.\n");
    //return SUCCESS;

	
    file_node *filelist = NULL;   // store file list

    // Build file list from command-line arguments
    for (int i = 1; i < argc; i++)
    {
        insert_file(&filelist, argv[i]);
    }

	int choice;
	int database_created = 0;
	 char word[50], file_name[50], save_file[50];
	do
	{
		printf("\n**********MENU**********\n");
		printf("1. Create data base.\n");
		printf("2. display data base.\n");
		printf("3. Search data base.\n");
		printf("4. save data base.\n");
		printf("5. Update data base.\n");
		printf("6. Exit.\n");

		printf("Enter the choice : ");
		scanf("%d",&choice);

		switch(choice)
		{
			case 1: 
			{
				if (database_created == 1)                                            //create database  function calling
				{
					printf("Database already created! Choose another option.\n");
				}
				else
				{
					create_database(filelist);
					database_created = 1;
					printf("Database created successfully!\n");
				}
				break;
				// if(create_database(filelist)==SUCCESS)
				// {
				// 	printf("1. Data base created Successfully.\n");
				// }
				// else
				// {
				// 	printf("Data base creation Failed.\n");
				// }
				// break;
			}
			case 2: 
			{
				if(display_database(filelist)==SUCCESS)                        //display database function calling
				{
					printf("2. Data base displayed Successfully.\n");
				}
				else
				{
					printf("Data base displaying Failed.\n");
				}
				break;
			}
			case 3:
			{
				char word[50];
    			printf("Enter the word to search : ");
    			scanf(" %49s", word);   
				if(search_database(word)==SUCCESS)                                // search data function calling
				{
					printf("3. Searching data base Successfully.\n");
				}
				else
				{
					printf("Searching data base Failed.\n");
				}
				break;
			}
			case 4:
			{
                printf("Enter file name to save database: ");                     //save function calling
                scanf("%s", save_file);
                if (save_database(save_file) == 0)
                    printf("Database saved successfully.\n");
                else
                    printf("Failed to save database.\n");
                break;
			}
			case 5:
			{
				char filename[50];                                                     //update choice
				printf("Enter filename to add: ");
				scanf(" %49s", filename);

				if (is_duplicate(head, filename))
				{
					printf("File already exists.\n");
				}
				else if (insert_file(&head, filename) == FAILURE)
				{
					printf("Failed to insert file.\n");
				}
				else if (create_database(head) == SUCCESS)
				{
					printf("Database updated with '%s'.\n", filename);
				}
				else
				{
					printf("Failed to update database.\n");
				}

				break;
			}
			case 6: 
			{
				printf("EXiting...\n");                              // exiting
				exit(0);
				break;
			}
			default : 
			{
				printf("Invalid Choice!...\n");
		
				break;
			}

		}

	} while (choice);
	return SUCCESS;
}

