#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


#define MAX_LINES 100
#define MAX_LEN 1000

int charCounter(char data[MAX_LINES][MAX_LEN], int lineLengthArr[MAX_LINES], int lineCount);
int wordCounter(char data[MAX_LINES][MAX_LEN], int lineLengthArr[MAX_LINES], int lineCount);

/**
 * struct containing integer data for our threads,
 */
typedef struct thread_data {
    int a;
    int b;
    int result;


} thread_data;

/**
 * the thread itself, with pointers to the data struct.
 * @param arg
 * @return
 */
void *myThread(void *arg) {
    thread_data *tdata=(thread_data *)arg;
    int a=tdata->a;
    int b=tdata->b;
    int result=a+b;
    tdata->result=result;

    sleep(1);
    printf("\n\nPrinting words and characters from thread\n");
    sleep(1);
    printf("Words: %d Characters: %d",a,b);
    sleep(1);
    printf("\nTo make sure we sleep for 3 to add words and characters in total.");
    sleep(3);
    printf("\n%d",result);
    sleep(1);
    printf("\nAYOOOO!!");

    pthread_exit(NULL);
}

void *myThread2(void *arg) {
    thread_data *tdata=(thread_data *)arg;
    int a=tdata->a;
    int b=tdata->b;
    int result=a+b;
    tdata->result=result;

    printf("\nThis is second thread speaking");
    printf("\nWe have the same data see %d %d %d",a,b,result);
    sleep(7);
    printf("\nLol you thought i was done, I'm Still...");
    sleep(2);
    printf("\nhere. \nit's i threat 2.");
    sleep(1);
    printf("\nHow could you forgeeeeeeeetzzzz.");
    sleep(3);
    printf("\nBBBBBBBBBBBBBZZZZZZzzzzzzzz<<<<<<<");
    sleep(4);
    printf("\nThread 2 is DEAD!, my condolences.");

    pthread_exit(NULL);
}


int main()
{
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

    //Updating counters to count from data file.
    wordCount = wordCounter(data, lineLengthArr, lineCount);
    charCount = charCounter(data, lineLengthArr, lineCount);


    //prints the result in terminal from the 2D array
    for (int i = 0; i < lineCount; i++) {
        printf("\n%s", data[i], "\n");
    }

    //Multi_threading
    pthread_t tid0, tid1; // creating separate threads.
    thread_data tdata; // creating an object of our thread data.

    tdata.a = wordCount; //assigning an integer value for thread data a, as wordCount.
    tdata.b = charCount; //assigning an integer value for thread data b, as charCount.

    //pthread_t *pthreads[] = {&tid0}; //array containing all threads

    pthread_create(&tid0, NULL, &myThread, (void*)&tdata);
    pthread_create(&tid1, NULL, &myThread2, (void*)&tdata);//starts tid0 in calling process


    /**
     * joins finished threads into main program, for all threads
     */
    pthread_join(tid0,NULL);
    pthread_join(tid1,NULL);


    //print staement computing what the threads have processed.

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
