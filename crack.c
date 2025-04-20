#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

#if __has_include("fileutil.h")
#include "fileutil.h"
#endif

#define PASS_LEN 50     // Maximum length any password will be.
#define HASH_LEN 33     // Length of hash plus one for null.

//checks the alphabetical order
int alphabetic(const void * a, const void * b)
{
    char ** aa = (char **)a;
    char ** bb = (char **)b;

    return strcmp(*aa, *bb);
}

/*Searches for an exact string match
char * exactstringSearchAA(char *target, char **lines, int size)
{
	int count = 0;
	while(size != count)
	{
		if(strcmp(lines[count], target) == 0)
		{
			return lines[count];
		}
		count++;
	}
	return NULL;
}
*/

//Binary Search
int strsearch(const void *key, const void *elem)
{
    return strcmp(*(char **)key, *(char **)elem);
}

//Main Function
int main(int argc, char *argv[])
{
    //exit if parameters are invalid
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dictionary_file\n", argv[0]);
        exit(1);
    }

    // TODO: Read the hashes file into an array.
    //   Use either a 2D array or an array of arrays.
    //   Use the loadFile function from fileutil.c
    //   Uncomment the appropriate statement.
    int size;
    //char (*hashes)[HASH_LEN] = loadFile(argv[1], &size);
    char **hashes = loadFileAA(argv[1], &size);
    
    // CHALLENGE1: Sort the hashes using qsort.
    qsort(hashes, size, sizeof(char *), alphabetic);
    // TODO
    // Open the password file for reading.
    FILE *in = fopen(argv[2], "r");
    char line[PASS_LEN];
    int count = 0;

    // TODO
    // For each password, hash it, then use the array search
    while(fgets(line, sizeof(line), in))
    {
        //Trim newline character
        for (int i = 0; line[i] != '\0'; i++)
        {
            if (line[i] == '\n')
            {
                line[i] = '\0';
                break;
            }
        } 
        char *createdHash = md5(line, strlen(line));
        // Uses binary search to find a matching hash
        char **foundHash = bsearch(&createdHash, hashes, size, sizeof(char *), strsearch);
        // If you find it, display the password and the hash.
        if (foundHash != NULL)
        {
            printf("%s - %s\n", *foundHash, line);
            // Keep track of how many hashes were found.
            count++;
        }
    }
    // CHALLENGE1: Use binary search instead of linear search.

    // TODO
    // When done with the file:
    //   Close the file
    fclose(in);
    //   Display the number of hashes found.
    printf("Hashes Found: %d\n", count);
    //   Free up memory.
    freeAA(hashes, size);
}

//clang crack.c fileutil.c md5.c -l crypto