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
void print_edge(char *city);
void parse(Edge edges[]);
void run_kruskal(Edge edges[], Edge *min_tree);
char *subString (const char *input, int offset, int len, char *dest);
void sort(Edge list[], int length);
GHashTable *is_in_group(GPtrArray *groups, GString *city, int elements_in_groups);
//void hash_table_contains(gpointer data, gpointer user_data);





int main(int argc, char **argv)
{
    struct timeval start, end;
    gettimeofday(&start, 0);

    Edge *edges = malloc(8130 * sizeof (Edge)); // 8257 - 128 = 8129 edges
    parse(edges);

    sort(edges, 8128);

    /*for (int i = 0; i < 8130; ++i)
    {
        printf("%d: %s - %s \n",edges[i].weight, edges[i].city_a, edges[i].city_b );
    }
    */
    Edge *min_tree = malloc(129 * sizeof (Edge)); // 128 cities
    run_kruskal(edges, min_tree);
    gettimeofday(&end, 0);

    int weight = 0;
    for (int i = 0; i < 129; ++i)
    {
        weight += min_tree[i].weight;
        printf("%d: %s - %s \n", edges[i].weight, edges[i].city_a, edges[i].city_b );
    }
    printf("Total weight_ %d\n", weight);
    long elapsed = (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec
                   - start.tv_usec;
    printf("Time elapsed: %ld micro seconds ", elapsed);



    return 0;
}


gboolean remove_add(gpointer key, gpointer value, gpointer user_data)
{

    GHashTable *set = (GHashTable *) user_data;
    GString *k = (GString *) key;
    GString *v = (GString *) value;
    g_hash_table_add(user_data, key);


    //puts("removing");
    //puts(k-> str);

    gboolean t = TRUE;
    return t;
}


/*runs kruskal's algorithm on @param edges and stores
 a minimal spanning tree in @param min_tree*/
void run_kruskal(Edge edges[], Edge *min_tree)
{
    int result_size = 0;
    int elements_in_groups = 0;
    GPtrArray *groups = g_ptr_array_new();
    for (int i = 0; i < 8128; i++)
    {
        GString *city_a = g_string_new(edges[i].city_a);
        GString *city_b = g_string_new(edges[i].city_b);


        // Check if city A and B are already in a group
        GHashTable *group_A = is_in_group(groups, city_a, elements_in_groups);
        GHashTable *group_B = is_in_group(groups, city_b, elements_in_groups);




        if (group_A == NULL && group_B == NULL)
        {
            //puts("Adding");
            min_tree[result_size] = edges[i];
            result_size ++;
            GHashTable *new_group = g_hash_table_new(g_string_hash, g_string_equal);
            g_hash_table_add(new_group, city_a);
            g_hash_table_add(new_group, city_b);

            g_ptr_array_add(groups, new_group);
            elements_in_groups++;
        }
        else if (group_A == NULL && group_B != NULL)
        {
            min_tree[result_size] = edges[i];
            result_size ++;

            g_hash_table_add(group_B, city_a);
        }
        else if (group_A != NULL && group_B == NULL)
        {
            min_tree[result_size] = edges[i];
            result_size ++;
            g_hash_table_add(group_A, city_b);
        }
        else if (group_A != NULL && group_B != NULL)
        {


            //Might not work !=
            if (group_A != group_B)   // Both are in groups, and not the
            {
                // same =>
                // they should be added to the same group
                //puts("NOT SAME GROUP");
                g_hash_table_foreach_remove (group_B, remove_add, group_A);
                gboolean removed = g_ptr_array_remove(groups, group_B);
                elements_in_groups --;
                //puts("Not same");
                /*if (removed)
                {
                    puts("Group B removed from groups list");
                }
                */
                //groupA.addAll(groupB);
                //groups.remove(groupB);
                // kruskalResult.add(e);
                min_tree[result_size] = edges[i];
                result_size ++;
                if (g_hash_table_contains(group_A,  city_a) == g_hash_table_contains(group_B,  city_a))
                {
                    puts("Not samfdsgfhdshfghgfhfgdhfdge");
                }
                if (g_hash_table_contains(group_B,  city_b) == g_hash_table_contains(group_B,  city_b))
                {
                    puts("Not samgfhfdghfdfgdsghajndgjhsdfijgknlkfhe");
                    puts("----");
                }
            }
            else
            {
               if (g_hash_table_contains(group_A,  city_a) == g_hash_table_contains(group_A,  city_a))
                {
                    puts("Yes same");
                }
                if (g_hash_table_contains(group_B,  city_b) == g_hash_table_contains(group_A,  city_b))
                {
                    puts("Yes same");
                    puts("----");
                }
                //puts("BOTH THE SAME");
                
            }
        }
        //group_A

    }








}


GHashTable *is_in_group(GPtrArray *groups, GString *city, int elements)
{
    //puts("is_in_group called");
    GHashTable *temp_set = NULL;

    for (int i = 0; i < elements; i++)
    {

        temp_set = g_ptr_array_index(groups, i);
        //printf("Elements in set: %d\n", g_hash_table_size(temp_set));
        if (g_hash_table_contains(temp_set,  city) == TRUE)
        {
            //printf("Found: %s\n", city->str );
            return temp_set;

        }
    }
    //printf("City: %s not found\n", city-> str);
    return NULL;
}




int compare_edges(const void *a, const void *b)
{
    Edge *e1 = (Edge *)a;
    Edge *e2 = (Edge *)b;
    return e1 -> weight > e2->weight ? 1 : -1;
}
void sort(Edge list[], int length)
{
    qsort(list, length, sizeof(Edge), &compare_edges);
}
// Syracuse--"Springfield, MO" [1114]
void parse(Edge edges[])
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
            temp_copy = malloc(sizeof(char) * strlen(temp2) + 1);
            strcpy(temp_copy, temp2);
            edges[index].weight = atoi(temp_copy);
            temp_copy = malloc(sizeof(char) * strlen(temp1) + 1);
            strcpy(temp_copy, temp1);
            edges[index].city_a = temp_copy;
            temp_copy = malloc(sizeof(char) * strlen(temp3) + 1);
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
