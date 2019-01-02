// word_search.c
// <STUDENT: Shuhao Lai, Slai16>

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "search_functions.h"

/*
 * This is the HW3 main function that performs a word search.
 */
int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		printf("Please enter a command line argument.\n");
		return 1;
	}
	char grid_file_name[strlen(argv[1]) + 1];
	strcpy(grid_file_name, argv[1]);
	char grid[MAX_SIZE][MAX_SIZE];
	int size = populate_grid(grid, grid_file_name), count = 0;
	if(size == -1){
	  printf("Grid file failed to open.\n");
	  return -1;
	}
	else if(size == -2){
	  printf("Invalid grid.\n");
	  return -2;
	}
	char word[size * 4 + 10], letter;

	//printf("Input word(s) please.\n");
	//FILE* output = fopen("Official_Output.txt", "w");

	while (scanf("%c", &letter) == 1)
	{
		if (isspace(letter))
		{
			word[count] = '\0';
			int found_count = find_all(grid, size, word, stdout);
			if (!found_count)
				printf("%s - Not Found\n", word);
			count = 0;
			continue;
		}
		word[count] = letter;
		count++;
	}
	word[count] = '\0';
	if(strlen(word) > 0){
	  int found_count = find_all(grid, size, word, stdout);
	  if( !found_count)
	    printf("%s - Not Found\n", word);
	}else 
	//fclose(output);
	return 0;
}

