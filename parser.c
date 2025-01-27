
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_LINES   1000   // max lines we might store
#define MAX_LENGTH  1024   // max length for each line

static bool id_seen_before(int window_id, int *id_array, int size) {
    for (int i = 0; i < size; i++) {
        if (id_array[i] == window_id) {
            return true;
        }
    }
    return false;
}

// The main function that finds the last 3 unique windows
void top_used_windows(char *top_names[3], int top_ids[3]) {
    FILE *file = fopen("/usr/local/bin/focus_events.txt", "r");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    char  *lines[MAX_LINES];
    int    line_count = 0;

    while (line_count < MAX_LINES) {
        char buffer[MAX_LENGTH];
        if (!fgets(buffer, sizeof(buffer), file)) {
            break; 
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        lines[line_count] = strdup(buffer);
        line_count++;
    }
    fclose(file);

    int found_count = 0; 

    for (int i = line_count - 1; i >= 0 && found_count < 3; i--) {

        char *name_ptr = strstr(lines[i], "Window Name:");
        char *id_ptr   = strstr(lines[i], "Window ID:");
        if (!name_ptr || !id_ptr) {
            continue;
        }

        name_ptr += strlen("Window Name:");
        while (isspace((unsigned char)*name_ptr)) {
            name_ptr++;
        }

        
        char *end_of_name = strchr(name_ptr, ',');
        if (end_of_name) {
            *end_of_name = '\0'; 
        }

        char *dash = strchr(name_ptr, '-');
        if (dash) {
            *dash = '\0'; 
        }

        for (int k = strlen(name_ptr) - 1; k >= 0 && isspace((unsigned char)name_ptr[k]); k--) {
            name_ptr[k] = '\0';
        }

        id_ptr += strlen("Window ID:");
        while (isspace((unsigned char)*id_ptr)) {
            id_ptr++;
        }

        char *end_of_id = strchr(id_ptr, ',');
        if (end_of_id) {
            *end_of_id = '\0';
        }
        int window_id = atoi(id_ptr);

        if (!id_seen_before(window_id, top_ids, found_count)) {
            // This is a new window ID
            top_ids[found_count]   = window_id;
            top_names[found_count] = strdup(name_ptr);
            found_count++;
        }
    }

    for (int i = found_count; i < 3; i++) {
        top_ids[i] = 0;
        top_names[i] = NULL;
    }

    printf("=== Last %d Unique Windows ===\n", found_count);
    for (int i = 0; i < found_count; i++) {
        printf("#%d -> ID: %d, Name: '%s'\n", 
               i+1, top_ids[i], top_names[i] ? top_names[i] : "(null)");
    }

    for (int i = 0; i < line_count; i++) {
        free(lines[i]);
    }
}


