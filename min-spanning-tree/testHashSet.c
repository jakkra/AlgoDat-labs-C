#include <glib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    GHashTable *hash_set = g_hash_table_new(g_string_hash, g_string_equal);
    
    GString *one = g_string_new("AAA");
    GString *two = g_string_new("BBB");
    GString *three = g_string_new("CCC");
    GString *one_same = g_string_new("AAA");

    g_hash_table_add(hash_set, one);
    g_hash_table_add(hash_set, two);
    g_hash_table_add(hash_set, three);
    printf("Size: %d\n", g_hash_table_size(hash_set));
    gboolean contains = g_hash_table_contains(hash_set, one_same);

    if (contains == TRUE)
    {

        puts("Contains");
    }
    else
    {
        puts("Doesn't contain");
    }

    GString *ptr = (GString*) g_hash_table_lookup(hash_set, one_same);
    printf("%s\n", ptr->str);
    return 0;
}