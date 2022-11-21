#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


#define MAX_LINES 1000
#define MAX_LEN 1000

int charCounter(char data[MAX_LINES][MAX_LEN], int lineLengthArr[MAX_LINES], int lineCount);
int wordCounter(char data[MAX_LINES][MAX_LEN], int lineLengthArr[MAX_LINES], int lineCount);

//sets up a 2D array
char data[MAX_LINES][MAX_LEN];
int lineLengthArr[MAX_LINES];
int lineCount = 0;

FILE *fp;

pthread_mutex_t lock;


void *wordCountThread(void *args) {

    pthread_mutex_lock(&lock);

    int wordCount = 0;
    for (int i = 0; i < lineCount; i++) { //for each line
        for (int j = 0; j < lineLengthArr[i] + 1; j++) { //for each char
            if (data[i][j] == 32 || data[i][j] == 0) { //checks for spacing and end of line
                wordCount++;
            }
        }
    }
    printf("Number of words %d \n", wordCount);

    fprintf(fp, "Number of words %d \n", wordCount);


    pthread_mutex_unlock(&lock);

    return NULL;

}

void *numberOfSentences(void *args) {

    pthread_mutex_lock(&lock);

    int sentenceCount = 0;
    for (int i = 0; i < lineCount; i++) { //for each line
        for (int j = 0; j < lineLengthArr[i] + 1; j++) { //for each char
            if (data[i][j] == 46) { //checks for spacing and end of line
                sentenceCount++;
            }
        }
    }
    printf("Number of sentences %d \n", sentenceCount);

    fprintf(fp, "Number of sentences %d \n", sentenceCount);


    pthread_mutex_unlock(&lock);

    return NULL;

}

void *charCountThread(void *arg) {

    pthread_mutex_lock(&lock);

    int charCount = 0;
    for (int i = 0; i < lineCount; i++) { //for each line
        for (int j = 0; j < lineLengthArr[i] + 1; j++) { //for each char
            if (data[i][j] == 32) { //if you don't want to count for spaces as characters.
                charCount--; //counter balances the ++
            }
            charCount++;
        }
    }
    printf("Number of chars %d \n", charCount);

    fprintf(fp, "Number of chars %d \n", charCount);

    pthread_mutex_unlock(&lock);

    return NULL;

}

int main()
{

    /** Load file*/
    //makes it so we work in the right directory
    chdir(".."); //go one step back in directory

    //open text file
    FILE *file;
    file = fopen("tekst1.txt", "r");

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


    for (int i = 0 ; i < lineCount; i++) { //for each line
        for (int j = 0; j < MAX_LEN; j++) { //for each char

            if(data[i][j] == 0){
                lineLengthArr[i] = j; //add current char count to the line length array
                break;
            }
        }
        //printf("\nThis is the stored info in the line array %d",lineLengthArr[i]); // check if it is stored correctly
    }

    //Updating counters to count from data file.



    //prints the result in terminal from the 2D array
    //for (int i = 0; i < lineCount; i++) {
    //    printf("%s\n", data[i]);
    //}

    // file
    fp = fopen("output.txt", "w");

    //Multi_threading
    pthread_t thread1, thread2, thread3; // creating separate threads.

    //pthread_t *pthreads[] = {&tid0}; //array containing all threads

    pthread_create(&thread1, NULL, wordCountThread, NULL);
    pthread_create(&thread2, NULL, charCountThread, NULL);
    pthread_create(&thread3, NULL, numberOfSentences, NULL);



    /**
     * joins finished threads into main program, for all threads
     */
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    fclose(fp);

    //print staement computing what the threads have processed.

    return 0;
}

