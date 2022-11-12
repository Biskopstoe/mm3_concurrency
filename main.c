#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>


#define MAX_LINES 100
#define MAX_LEN 1000

int charCounter();

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

    //makes it so we work in the right directory
    chdir("..");

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

    //prints the result in terminal from the 2D array
    for (int i = 0; i < lineCount; i++)
        printf("%s", data[i]);

    //prints results of functions
    int x1 = charCounter();
    printf(x1);

    //observer thread that checks for everything is done and prints it all.

    return 0;
}

/*
int wordCount(int data[M][N],lineCount){
//look after space " "
    int wordCount = 0;

    int i, j;
    for (i = 0; i < M; i++)
      for (j = 0; j < N; j++)
        wordCount++;

    return wordCount;
}
 */


int charCounter(){

    int nc = 0;
    for(int i; i<5;i++)
    {
        do
            ++nc;
        while (getchar() != '\n');
        printf("Character count is:%d\n", nc - 1);
        nc = 0;
    }
    return nc;

}