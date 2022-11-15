#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>


#define MAX_LINES 100
#define MAX_LEN 1000

int charCounter(char data[MAX_LINES][MAX_LEN], int lineLengthArr[MAX_LINES], int lineCount);
int wordCounter(char data[MAX_LINES][MAX_LEN], int lineLengthArr[MAX_LINES], int lineCount);


void* routine() {
    printf("ABCDEFGHIJKLMNOPQRSTUVWXYZÆØÅ\n");
}

int main()
{
    //Multi_threading
    pthread_t t1, t2;
    pthread_create(&t1, NULL, &routine, NULL);
    pthread_create(&t2, NULL, &routine, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    //Declared ints
    int wordCount = 0;
    int charCount = 0;
    int lineCount = 0;

    //sets up a 2D array
    char data[MAX_LINES][MAX_LEN];

    /** Load file*/
    //makes it so we work in the right directory
    chdir(".."); //go one step back in directory

    //open text file
    FILE *file;
    file = fopen("tekst.txt", "r");

    //check if the file is loaded correctly
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    //reads the text file and adds it to the 2D array sorted by the current line.
    while (!feof(file) && !ferror(file))
        if (fgets(data[lineCount], MAX_LEN, file) != NULL)
            lineCount++;

    // Close the file when we are done working with it.
    fclose(file);

    /** length of current line stored in an array */
    int lineLengthArr[MAX_LINES];

    for (int i = 0 ; i < lineCount; i++) { //for each line
        for (int j = 0; j < MAX_LEN; j++) { //for each char

            if(data[i][j] == 0){
                lineLengthArr[i] = j; //add current char count to the line length array
                break;
            }
        }
        //printf("\nThis is the stored info in the line array %d",lineLengthArr[i]); // check if it is stored correctly
    }

    /** word counter */
    wordCount = wordCounter(data, lineLengthArr, lineCount);
    printf("\nThis is the current wordCount: %d",wordCount); //check for how it gets counted

    /** char counter */
        charCount = charCounter(data, lineLengthArr, lineCount);
        printf("\nThis is the current charCount: %d",charCount); //check for how it gets counted

    //prints the result in terminal from the 2D array
    for (int i = 0; i < lineCount; i++)
        printf("\n%s", data[i]);


    //observer thread that checks for everything is done and prints it all.

    return 0;
}

/** functions for the different commands */

int wordCounter(char data[MAX_LINES][MAX_LEN], int lineLengthArr[MAX_LINES], int lineCount){
    int wordCount = 0;
    for (int i = 0; i < lineCount; i++) { //for each line
        for (int j = 0; j < lineLengthArr[i] + 1; j++) { //for each char
            if (data[i][j] == 32 || data[i][j] == 0) { //checks for spacing and end of line
                wordCount++;
            }
        }
    }
    return wordCount;
}

int charCounter(char data[MAX_LINES][MAX_LEN], int lineLengthArr[MAX_LINES], int lineCount){
    int charCount = 0;
    for (int i = 0; i < lineCount; i++) { //for each line
        for (int j = 0; j < lineLengthArr[i] + 1; j++) { //for each char
            if (data[i][j] == 32) { //if you don't want to count for spaces as characters.
                charCount--; //counter balances the ++
            }
            charCount++;
        }
    }
    return charCount;
}