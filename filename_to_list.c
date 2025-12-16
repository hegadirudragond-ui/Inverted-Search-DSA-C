#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "inverted_search.h"

file_node *head = NULL;
int is_duplicate(file_node *head, char *filename)        //checking duplicate file is present or not 
{
    while (head!=NULL)                                     // head is null or not
    {
        if (strcmp(head->file_name, filename) == 0)
            return 1;                                    // duplicate found
        head = head->link;                                //traverse head
    }
    return 0;  
}

int insert_file(file_node **head, char *filename)               //inserting to linked list for efficient 
{
    file_node *new_node = malloc(sizeof(file_node));             // memory allocating for new node
    if (new_node == NULL)
    {
        printf("Error: Memory allocation failed.\n");
        return 0;  // failure
    }

    strcpy(new_node->file_name, filename);                    
    new_node->link = *head;
    *head = new_node;

    return 1;  // success
}

int validate_arguments(int argc, char *argv[])                     //validating command line arguments
{
	/* Define the main function here */
	if(argc<2)                                                    // arguments must be greater than or equal to 2
	{
		printf("Error :  No input files.\n");
		return FAILURE;
	}

	int file_count=0;	
	for(int i=1;i<argc;i++)                                         
	{
		char *filename = argv[i];
		int len = strlen(filename);
		if(len<5 || strcmp(filename + len - 4, ".txt") !=0)                //file name must be end with .txt 
		{
			printf("Error : File %s is not valid .txt file.\n",filename);
			continue;
		}
		//open file in read mode
		FILE *fp = fopen(filename,"r");                                        //opening the file in read mode
		if(fp==NULL)
		{
			printf("Error : File %s cannot opened.\n",filename);
			continue;
		}
		//checking file is present and empty or not 
		fseek(fp,0,SEEK_END);                                                    //moving the file pointer to check whether the file is Empty or not
		if(ftell(fp)==0)
		{
			printf("Error : File %s is Empty.\n",filename);
			fclose(fp);
			continue;
		}	

		fclose(fp);

		// file is duplicate or not  if present skip and print error msg not duplicate store the file in linked list
		if (is_duplicate(head, filename))                                       
        {
            printf("Error : Duplicate file %s found. Skipping.\n", filename);
            continue;
        }
		insert_file(&head, filename);
        printf("File '%s' added to linked list.\n", filename);
        file_count++;
        printf("File '%s' validated successfully.\n", filename);
       
	}
		printf("Files Count : %d \n",file_count);
	return SUCCESS;
}
