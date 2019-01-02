// search_functions.c
// <STUDENT: Shuhao Lai, Slai16.>

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "search_functions.h"

/* 
 * Given a filename and a MAX_SIZExMAX_SIZE grid to fill, this function 
 * populates the grid and returns n, the actual grid dimension. 
 * If filename_to_read_from can't be opened, this function returns -1.
 * If the file contains an invalid grid, this function returns -2.
 */
int populate_grid(char grid[][MAX_SIZE], char filename_to_read_from[])
{
	FILE* txt_file = fopen(filename_to_read_from, "r");
	if (txt_file == NULL) //Don't forget to make print in main.
		return -1;
	char letter;
	int len_of_first_r = -1, r = 0, c = 0, previous_c;
	while (fscanf(txt_file, "%c", &letter) == 1)
	{
		if (isspace(letter))
		{
		  if(c == 0 && letter == '\n')
		    break;
			if (len_of_first_r == -1)
				len_of_first_r = c;
			else if (len_of_first_r != c)
			{
			  //printf("Invalid grid.\n");
				fclose(txt_file);
				return -2;
			}
			r++;
			previous_c = c;
			c = 0;
			continue;
		}
		if (c == 10 || c == MAX_SIZE)
		{
		  //printf("Invalid grid.\n");
			fclose(txt_file);
			return -2;
		}
		grid[r][c] = tolower(letter);
		c++; //Represents the number of letters in the columns of grid
	}
	if (r == 0 || r != previous_c)
	{
	  //printf("Invalid grid.\n");
		fclose(txt_file);
		return -2;
	}
	fclose(txt_file);
	return r;
}

/* 
 * Looks for word in grid only reading from left to right. Returns number of times word was found in grid using this method.
 */
int find_right(char grid[][MAX_SIZE], int n, char word[], FILE *write_to)
{
	int word_len = strlen(word);
	int found_count = 0;
	for (int r = 0; r < n; r++)
	{
		for (int c = 0; c <= (n - word_len); c++)
		{
			if (grid[r][c] == tolower(word[0]))
			{
				int found = 1;
				for (int grid_index = c + 1, word_index = 1;
						word_index < word_len; grid_index++, word_index++)
				{
					if (grid[r][grid_index] != tolower(word[word_index]))
					{
						found = 0;
						break;
					}
				}
				if (found)
				{
					fprintf(write_to, "%s %d %d %c\n", word, r, c, 'R');
					//c = c + word_len - 1;
					found_count++;
				}
			}
		}
	}
	return found_count;
}

/* 
 * Looks for word in grid only reading from left to right; however, word is reversed. Returns number of times word was found in grid using this method.
 */
int find_left(char grid[][MAX_SIZE], int n, char word[], FILE *write_to)
{
	int word_len = strlen(word);
	char reversed_word[word_len + 1];
	for (int i = 0, reverse_index = word_len - 1; i < word_len;
			i++, reverse_index--)
		reversed_word[i] = word[reverse_index];
	reversed_word[word_len] = '\0';

	int found_count = 0;
	for (int r = 0; r < n; r++)
	{
		for (int c = 0; c <= (n - word_len); c++)
		{
			if (grid[r][c] == tolower(reversed_word[0]))
			{
				int found = 1;
				for (int grid_index = c + 1, word_index = 1;
						word_index < word_len; grid_index++, word_index++)
				{
					if (grid[r][grid_index]
							!= tolower(reversed_word[word_index]))
					{
						found = 0;
						break;
					}
				}
				if (found)
				{
					fprintf(write_to, "%s %d %d %c\n", word, r,
							c + word_len - 1, 'L');
					//c = c + word_len - 1;
					found_count++;
				}
			}
		}
	}
	return found_count;
}

/* 
 *Finds word in grid by starting from top and finding down. returns the number of times the word has been found.
 */
int find_down(char grid[][MAX_SIZE], int n, char word[], FILE *write_to)
{
	int word_len = strlen(word);
	int found_count = 0;
	for (int c = 0; c < n; c++)
	{
		for (int r = 0; r <= (n - word_len); r++)
		{
			if (grid[r][c] == tolower(word[0]))
			{
				int found = 1;
				for (int grid_index = r + 1, word_index = 1;
						word_index < word_len; grid_index++, word_index++)
				{
					if (grid[grid_index][c] != tolower(word[word_index]))
					{
						found = 0;
						break;
					}
				}
				if (found)
				{
					fprintf(write_to, "%s %d %d %c\n", word, r, c, 'D');
					//r = r + word_len - 1;
					found_count++;
				}
			}
		}
	}
	return found_count;
}

/* 
 *Finds word in grid by starting from top and finding down; however, word is reveresed. returns the number of times the word has been found.
 */
int find_up(char grid[][MAX_SIZE], int n, char word[], FILE *write_to)
{
	int word_len = strlen(word);
	char reversed_word[word_len + 1];
	for (int i = 0, reverse_index = word_len - 1; i < word_len;
			i++, reverse_index--)
		reversed_word[i] = word[reverse_index];
	reversed_word[word_len] = '\0';

	int found_count = 0;
	for (int c = 0; c < n; c++)
	{
		for (int r = 0; r <= (n - word_len); r++)
		{
			if (grid[r][c] == tolower(reversed_word[0]))
			{
				int found = 1;
				for (int grid_index = r + 1, word_index = 1;
						word_index < word_len; grid_index++, word_index++)
				{
					if (grid[grid_index][c]
							!= tolower(reversed_word[word_index]))
					{
						found = 0;
						break;
					}
				}
				if (found)
				{
					fprintf(write_to, "%s %d %d %c\n", word, r + word_len - 1,
							c, 'U');
					//r = r + word_len - 1;
					found_count++;
				}
			}
		}
	}
	return found_count;
}

/* 
 *Looks for a word in a grid in all directions (excluding diagonal). Returns the number of times the word was found.
 */
int find_all(char grid[][MAX_SIZE], int n, char word[], FILE *write_to)
{
  if(strlen(word) > (unsigned)n)
    return 0;
	int found = 0;
	found += find_right(grid, n, word, write_to);
	found += find_left(grid, n, word, write_to);
	found += find_down(grid, n, word, write_to);
	found += find_up(grid, n, word, write_to);
	return found;
}

/*
 * Reads lhs and rhs character by character until either reaches eof.
 * Returns true if the files can be read and the two files match
 * character by character. Returns false if two files either can't be
 * opened or don't match. The definition of this function is provided 
 * for you.
 */
int file_eq(char lhs_name[], char rhs_name[])
{
	FILE* lhs = fopen(lhs_name, "r");
	FILE* rhs = fopen(rhs_name, "r");

	// don't compare if we can't open the files
	if (lhs == NULL || rhs == NULL)
		return 0;

	int match = 1;
	// read until both of the files are done or there is a mismatch
	while (!feof(lhs) || !feof(rhs))
	{
		if (feof(lhs) ||                      // lhs done first
				feof(rhs) ||                  // rhs done first
				(fgetc(lhs) != fgetc(rhs)))
		{ // chars don't match
			match = 0;
			break;
		}
	}
	fclose(lhs);
	fclose(rhs);
	return match;
}

