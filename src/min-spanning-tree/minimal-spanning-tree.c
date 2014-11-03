#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <time.h>

#define min(a, b) (((a) < (b)) ? (a) : (b));


typedef struct
{
    int weight;
    char *city_a;
    char *city_b;
} Edge;

char *getcwd(char *buf, size_t size);
int compare_edges(char *city_a, char *city_b);
void print_edge(char *city);
void parse();
char *subString (const char *input, int offset, int len, char *dest);

Edge *edges;

int main(int argc, char **argv)
{
    edges = malloc(8130 * sizeof (Edge)); // 8257 - 128 = 8129 edges

    parse();
    for (int l = 0; l < 8128; l++)
    {
        puts(edges[l].city_a);
        puts(edges[l].city_b);
        printf("Weight: %d \n", edges[l].weight);

    }

    /*GList *list = NULL;
    list = g_list_append(list, "Hello world!");
    printf("The first item is '%s'\n", g_list_first(list)->data);
    */
    return 0;
}

// Syracuse--"Springfield, MO" [1114]
void parse()
{
    char working_directory[1024];
    if (getcwd(working_directory, sizeof(working_directory)) != NULL)
    {
        //fprintf(stdout, "Current working dir: %s\n", working_directory);
    }
    else
    {
        //perror("getcwd() error");
    }

    static const char filename[] = "/USA-highway-miles.in.txt";

    char *full_path;
    full_path = malloc(strlen(working_directory) + strlen(filename) + 1);
    full_path[0] = '\0';
    strcat(full_path, working_directory);
    strcat(full_path, filename);
    //printf("%s\n", full_path);

    FILE *file = fopen(full_path, "r");
    if (file != NULL)
    {

        char line[110]; /* or other suitable maximum line size */

        /*Skip until we see flag "TOKEN"*/
        while (fgets(line, sizeof line, file) != NULL
                && strstr(line, "TOKEN") == NULL)
        {


        }
        /* read the input */
        int index = 0;
        int letter_index = 0;
        char *temp1; //City A
        char *temp2; //Weight
        char *temp3; // City B

        while (fgets(line, sizeof line, file) != NULL
                && strstr(line, "EOF") == NULL)
        {

            line[strlen(line) - 2] = 0; // remove ' ] '
            temp1 = strtok(line, "[");
            temp2 = strtok(NULL, "["); //temp2 = weight
            if (line[strlen(line) - 2] == '"') //if "City" remove last ' " '
            {
                line[strlen(line) - 2] = '\0';
                temp1 = strtok(line, "--");
                temp3 = strtok(NULL, "--");
                temp3++;
            }
            else
            {
                line[strlen(line) - 1] = '\0';
                temp1 = strtok(line, "--");
                temp3 = strtok(NULL, "--");

            }
            if (temp1[0] == '"')
            {
                temp1++; //Increase pointer one, will point to the next char after ' " '
                line[strlen(line) - 1] = '\0'; // Changes second " ' " to \0
            }

            //We now need to make new copies of the pointers,
            //since those pointers all point to the same array, which will be modified next loop
            char *temp_copy;
            temp_copy = malloc(sizeof(char) * strlen(temp2));
            strcpy(temp_copy, temp2);
            edges[index].weight = atoi(temp_copy);
            temp_copy = malloc(sizeof(char) * strlen(temp1));
            strcpy(temp_copy, temp1);
            edges[index].city_a = temp_copy;
            temp_copy = malloc(sizeof(char) * strlen(temp3));
            strcpy(temp_copy, temp3);
            edges[index].city_b = temp_copy;
            index ++;


        }
        fclose(file);


    }
    else
    {
        perror(filename);
    }
}
