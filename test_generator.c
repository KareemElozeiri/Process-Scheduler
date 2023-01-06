#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define null 0

struct processData
{
    int arrivaltime;
    int priority;
    int runningtime;
    int memory_size;
    int id;
};

int main(int argc, char * argv[])
{
    FILE * pFile;
    pFile = fopen("processes.txt", "w");
    int no;
    struct processData pData;
    printf("Please enter the number of processes you want to generate: ");
    scanf("%d", &no);
    srand(time(null));
    //fprintf(pFile,"%d\n",no);
    int random_lower_bound = 1; // used for randoming processes sizes
    int random_upper_bound = 256; // used for randoming processes sizes
    int max_memory_size = 1024;
    int random_process_size;
    fprintf(pFile, "#id arrival runtime priority memsize\n");
    pData.arrivaltime = 1;
    for (int i = 1 ; i <= no ; i++)
    {
        random_process_size = (rand() % (random_upper_bound - random_lower_bound + 1)) + random_lower_bound;
        max_memory_size -= random_process_size;
        pData.id = i;
        pData.arrivaltime += rand() % (11); //processes arrives in order
        pData.runningtime = rand() % (30);
        pData.priority = rand() % (11);
        pData.memory_size = random_process_size;
        fprintf(pFile, "%d\t%d\t%d\t%d\t%d\n", pData.id, pData.arrivaltime, pData.runningtime, pData.priority, pData.memory_size);
    }
    fclose(pFile);
}
