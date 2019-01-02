// test_search_functions.c
// <STUDENT: Shuhao Lai, Slai16>

#include <stdio.h>
#include <assert.h>
#include "search_functions.h"

/* 
 * Declarations for tester functions whose definitions appear below.
 * (You will need to fill in the function definition details, at the
 * end of this file, and add comments to each one.) 
 * Additionally, for each helper function you elect to add to the 
 * provided search_functions.h, you will need to supply a corresponding
 * tester function in this file.  Add a declaration for it here, its
 * definition below, and a call to it where indicated in main.
 */
void test_file_eq();      // This one is already fully defined below.
void test_populate_grid();
void test_find_right();
void test_find_left();
void test_find_down();
void test_find_up();
void test_find_all();

/*
 * Main method which calls all test functions.
 */
int main()
{
	printf("Testing file_eq...\n");
	test_file_eq();
	printf("Passed file_eq test.\n\n");

	printf("Running search_functions tests...\n");
	test_populate_grid();
	test_find_right();
	test_find_left();
	test_find_down();
	test_find_up();
	test_find_all();

	// You may add calls to additional test functions here.

	printf("Passed search_functions tests!!!\n");
}

/*
 * Test file_eq on same file, files with same contents, files with
 * different contents and a file that doesn't exist.
 * Relies on files test1.txt, test2.txt, test3.txt being present.
 */
void test_file_eq()
{
	FILE* fptr = fopen("test1.txt", "w");
	fprintf(fptr, "this\nis\na test\n");
	fclose(fptr);

	fptr = fopen("test2.txt", "w");
	fprintf(fptr, "this\nis\na different test\n");
	fclose(fptr);

	fptr = fopen("test3.txt", "w");
	fprintf(fptr, "this\nis\na test\n");
	fclose(fptr);

	assert(file_eq("test1.txt", "test1.txt"));
	assert(file_eq("test2.txt", "test2.txt"));
	assert(!file_eq("test2.txt", "test1.txt"));
	assert(!file_eq("test1.txt", "test2.txt"));
	assert(file_eq("test3.txt", "test3.txt"));
	assert(file_eq("test1.txt", "test3.txt"));
	assert(file_eq("test3.txt", "test1.txt"));
	assert(!file_eq("test2.txt", "test3.txt"));
	assert(!file_eq("test3.txt", "test2.txt"));
	assert(!file_eq("", ""));  // can't open file
}

void test_populate_grid()
{
	char grid1[MAX_SIZE][MAX_SIZE];
	assert(populate_grid(grid1, "Small_Grid.txt") == 4);

	char grid2[MAX_SIZE][MAX_SIZE];
	assert(populate_grid(grid2, "Different_C_And_R.txt") == -2);

	char grid3[MAX_SIZE][MAX_SIZE];
	assert(populate_grid(grid3, "Exceed_MAX_SIZE.txt") == -2);

	char grid4[MAX_SIZE][MAX_SIZE];
	assert(populate_grid(grid4, "Empty_Grid.txt") == -2);

	char grid5[MAX_SIZE][MAX_SIZE];
	assert(populate_grid(grid5, "Max_R_and_C.txt") == 10);

	char grid6[MAX_SIZE][MAX_SIZE];
	assert(populate_grid(grid6, "More_After_Newline_Grid.txt") == 4);

	char grid7[MAX_SIZE][MAX_SIZE];
	assert(populate_grid(grid7, "One_By_One_Grid.txt") == 1);

	//Checks file that can't be opened.
	char grid8[MAX_SIZE][MAX_SIZE];
	assert(populate_grid(grid8, "") == -1);

}

void print_grid(char grid[][MAX_SIZE], int n)
{
	for (int r = 0; r < n; r++)
	{
		for (int c = 0; c < n; c++)
		{
			printf("%c", grid[r][c]);
		}
		printf("\n");
	}
}
void test_find_right()
{
	char word1[] = "pop";
	char grid1[MAX_SIZE][MAX_SIZE];
	int size1 = populate_grid(grid1, "Two_Found_Grid.txt");
	//print_grid(grid, size);
	FILE* output1 = fopen("Found2_Output_Right.txt", "w");
	int found1 = find_right(grid1, size1, word1, output1);
	assert(found1 == 2);
	fclose(output1);
	assert(
			file_eq("Found2_Output_Right.txt",
					"Desired_Found2_Output_Right.txt"));

	//Second test

	char word2[] = "abcd";
	char grid2[MAX_SIZE][MAX_SIZE];
	int size2 = populate_grid(grid2, "One_Found_On_Edge_Grid.txt");
	//print_grid(grid, size);
	FILE* output2 = fopen("Edge_Find_Output_R.txt", "w");
	int found2 = find_right(grid2, size2, word2, output2);
	assert(found2 == 1);
	fclose(output2);
	assert(file_eq("Edge_Find_Output_R.txt", "Desired_Edge_Find_Output_R.txt"));

	//Third test
	char word3[] = "a";
	char grid3[MAX_SIZE][MAX_SIZE];
	int size3 = populate_grid(grid3, "One_By_One_Grid.txt");
	//print_grid(grid, size);
	FILE* output3 = fopen("One_By_One_Output_R.txt", "w");
	int found3 = find_right(grid3, size3, word3, output3);
	assert(found3 == 1);
	fclose(output3);
	assert(
			file_eq("One_By_One_Output_R.txt",
					"Desired_Found_Output_1x1_R.txt"));
}

void test_find_left()
{
	char word1[] = "pop";
	char grid1[MAX_SIZE][MAX_SIZE];
	int size1 = populate_grid(grid1, "Two_Found_Grid.txt");
	//print_grid(grid, size);
	FILE* output1 = fopen("Found2_Output_Left.txt", "w");
	int found1 = find_left(grid1, size1, word1, output1);
	assert(found1 == 2);
	fclose(output1);
	assert(file_eq("Found2_Output_Left.txt", "Desired_Found2_Output_Left.txt"));

	//Second test

	char word2[] = "abcd";
	char grid2[MAX_SIZE][MAX_SIZE];
	int size2 = populate_grid(grid2, "One_Found_On_Edge_Grid.txt");
	//print_grid(grid, size);
	FILE* output2 = fopen("Edge_Find_Output_L.txt", "w");
	int found2 = find_left(grid2, size2, word2, output2);
	assert(found2 == 1);
	fclose(output2);
	assert(file_eq("Edge_Find_Output_L.txt", "Desired_Edge_Find_Output_L.txt"));

	//Third test
	char word3[] = "a";
	char grid3[MAX_SIZE][MAX_SIZE];
	int size3 = populate_grid(grid3, "One_By_One_Grid.txt");
	//print_grid(grid, size);
	FILE* output3 = fopen("One_By_One_Output_L.txt", "w");
	int found3 = find_left(grid3, size3, word3, output3);
	assert(found3 == 1);
	fclose(output3);
	assert(
			file_eq("One_By_One_Output_L.txt",
					"Desired_Found_Output_1x1_L.txt"));
}

void test_find_down()
{
	char word1[] = "pop";
	char grid1[MAX_SIZE][MAX_SIZE];
	int size1 = populate_grid(grid1, "Two_Found_Grid.txt");
	//print_grid(grid, size);
	FILE* output1 = fopen("Found2_Output_Down.txt", "w");
	int found1 = find_down(grid1, size1, word1, output1);
	assert(found1 == 2);
	fclose(output1);
	assert(file_eq("Found2_Output_Down.txt", "Desired_Found2_Output_Down.txt"));

	//Second test

	char word2[] = "abcd";
	char grid2[MAX_SIZE][MAX_SIZE];
	int size2 = populate_grid(grid2, "One_Found_On_Edge_Grid.txt");
	//print_grid(grid, size);
	FILE* output2 = fopen("Edge_Find_Output_D.txt", "w");
	int found2 = find_down(grid2, size2, word2, output2);
	assert(found2 == 1);
	fclose(output2);
	assert(file_eq("Edge_Find_Output_D.txt", "Desired_Edge_Find_Output_D.txt"));

	//Third test
	char word3[] = "a";
	char grid3[MAX_SIZE][MAX_SIZE];
	int size3 = populate_grid(grid3, "One_By_One_Grid.txt");
	//print_grid(grid, size);
	FILE* output3 = fopen("One_By_One_Output_D.txt", "w");
	int found3 = find_down(grid3, size3, word3, output3);
	assert(found3 == 1);
	fclose(output3);
	assert(
			file_eq("One_By_One_Output_D.txt",
					"Desired_Found_Output_1x1_D.txt"));
}

void test_find_up()
{
	char word1[] = "pop";
	char grid1[MAX_SIZE][MAX_SIZE];
	int size1 = populate_grid(grid1, "Two_Found_Grid.txt");
	//print_grid(grid, size);
	FILE* output1 = fopen("Found2_Output_Up.txt", "w");
	int found1 = find_up(grid1, size1, word1, output1);
	assert(found1 == 2);
	fclose(output1);
	assert(file_eq("Found2_Output_Up.txt", "Desired_Found2_Output_Up.txt"));

	//Second test

	char word2[] = "abcd";
	char grid2[MAX_SIZE][MAX_SIZE];
	int size2 = populate_grid(grid2, "One_Found_On_Edge_Grid.txt");
	//print_grid(grid, size);
	FILE* output2 = fopen("Edge_Find_Output_U.txt", "w");
	int found2 = find_up(grid2, size2, word2, output2);
	assert(found2 == 1);
	fclose(output2);
	assert(file_eq("Edge_Find_Output_U.txt", "Desired_Edge_Find_Output_U.txt"));

	//Third test
	char word3[] = "a";
	char grid3[MAX_SIZE][MAX_SIZE];
	int size3 = populate_grid(grid3, "One_By_One_Grid.txt");
	//print_grid(grid, size);
	FILE* output3 = fopen("One_By_One_Output_U.txt", "w");
	int found3 = find_up(grid3, size3, word3, output3);
	assert(found3 == 1);
	fclose(output3);
	assert(
			file_eq("One_By_One_Output_U.txt",
					"Desired_Found_Output_1x1_U.txt"));
}

void test_find_all()
{
	char word1[] = "pop";
	char grid1[MAX_SIZE][MAX_SIZE];
	int size1 = populate_grid(grid1, "Two_Found_Grid.txt");
	FILE* output1 = fopen("Found2_Output_All.txt", "w");
	int found1 = find_all(grid1, size1, word1, output1);
	assert(found1 == 8);
	fclose(output1);
	assert(file_eq("Found2_Output_All.txt", "Desired_Found2_Output_All.txt"));

	//Second test

	char word2[] = "abcd";
	char grid2[MAX_SIZE][MAX_SIZE];
	int size2 = populate_grid(grid2, "One_Found_On_Edge_Grid.txt");
	FILE* output2 = fopen("Edge_Find_Output_All.txt", "w");
	int found2 = find_all(grid2, size2, word2, output2);
	assert(found2 == 4);
	fclose(output2);
	assert(
			file_eq("Edge_Find_Output_All.txt",
					"Desired_Edge_Find_Output_All.txt"));
	//Third test
	char word3[] = "a";
	char grid3[MAX_SIZE][MAX_SIZE];
	int size3 = populate_grid(grid3, "One_By_One_Grid.txt");
	FILE* output3 = fopen("One_By_One_Output_All.txt", "w");
	int found3 = find_all(grid3, size3, word3, output3);
	assert(found3 == 4);
	fclose(output3);
	assert(
			file_eq("One_By_One_Output_All.txt",
					"Desired_Found_Output_1x1_All.txt"));

	//Fourth test
	char word4[] = "b"; //Will find nothing
	char grid4[MAX_SIZE][MAX_SIZE];
	int size4 = populate_grid(grid4, "One_By_One_Grid.txt");
	FILE* output4 = fopen("One_By_One_No_Output_All.txt", "w");
	int found4 = find_all(grid4, size4, word4, output4);
	assert(found4 == 0);
	fclose(output4);
	assert(
			file_eq("One_By_One_No_Output_All.txt",
					"Desired_No_Found_Output_1x1_All.txt"));
}

