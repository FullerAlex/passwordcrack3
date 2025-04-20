#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileutil.h"

// DIRECTIONS
// Choose whether you are doing the 2D array or
// the array of arrays.
// For the 2D array,
//    implement loadFile2D, substringSearch2D, and free2D.
// For the array of arrays, 
//    implement loadFileAA, substringSearchAA, and freeAA.

//Global Constants
const int CAPACITY_START = 20;
const int CAP_INCREMENT = 10;

// Load the text file from the given filename.
// Return a pointer to the array of strings.
// Sets the value of size to be the number of valid
// entries in the array (not the total array length).
char ** loadFileAA(char *filename, int *size)
{
	FILE *in = fopen(filename, "r");
	if (!in)
	{
	    perror("Can't open file");
	    exit(1);
	}
	
	// TODO
	// Allocate memory for an array of strings (arr).
	char ** arr = malloc(CAPACITY_START * sizeof(char *));
	int capacity = CAPACITY_START;

	char line[999];
	int count = 0;

	// Read the file line by line.
	while(fgets(line, sizeof(line), in))
	{

    	//   Trim newline.
		for (int i = 0; line[i] != '\0'; i++)
        {
            if (line[i] == '\n')
            {
                line[i] = '\0';
                break;
            }
        }

		//   Expand array if necessary (realloc).
		if(count == capacity)
		{
			capacity += CAP_INCREMENT;
        	arr = realloc(arr, capacity * sizeof(char *));
		}

		//   Allocate memory for the string (str).
		arr[count] = malloc(strlen(line) + 1);

		//   Copy each line into the string (use strcpy).
		strcpy(arr[count], line);
		count++;

		//   Attach the string to the large array (assignment =).
		//arr[count] = malloc(strlen(line));
	}
	// Close the file.
	fclose(in);
	// The size should be the number of entries in the array.
	*size = count;
	
	// Return pointer to the array of strings.
	return arr;
}

// Search the array for the target string.
// Return the found string or NULL if not found.
char * substringSearchAA(char *target, char **lines, int size)
{
	int count = 0;
	while(size != count)
	{
		if(strstr(lines[count], target))
		{
			return lines[count];
		}
		count++;
	}
	return NULL;
}

// Free the memory used by the array
void freeAA(char ** arr, int size)
{
	int count = 0;
	while(size != count)
	{
		free(arr[count]);
		count++;
	}
}



/*
char (*loadFile2D(char *filename, int *size))[COLS]
{
	FILE *in = fopen(filename, "r");
	if (!in)
	{
	    perror("Can't open file");
	    exit(1);
	}
	
	// TODO
	// Allocate memory for an 2D array, using COLS as the width.
	// Read the file line by line into a buffer.
    //   Trim newline.
	//   Expand array if necessary (realloc).
	//   Copy each line from the buffer into the array (use strcpy).
    // Close the file.
	
	// The size should be the number of entries in the array.
	*size = 0;
	
	// Return pointer to the array.
	return NULL;
}
*/


/*
char * substringSearch2D(char *target, char (*lines)[COLS], int size)
{
    
    return NULL;
}
*/


/*
void free2D(char (*arr)[COLS])
{

}
*/