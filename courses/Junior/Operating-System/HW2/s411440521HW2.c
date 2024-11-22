#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define NUM_COLUMNS 4
#define MAX_ROWS 1000

// Macro for error handling
#define CHECK_ALLOC(ptr) if (!(ptr)) { perror("Memory allocation failed"); goto finally; }
#define CHECK_FILE(fp, filename) if (!(fp)) { fprintf(stderr, "Failed to open %s\n", filename); goto finally; }

typedef struct {
    int *data;
    int size;
    long sum;
} ThreadData;

typedef struct {
    ThreadData *thread_data;
    int row_count;
    int *merged_data;
} MergeData;

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Sort and sum each column
void *sort_and_sum(void *arg) {
    ThreadData *td = (ThreadData *)arg;

    // Sort the column data
    qsort(td->data, td->size, sizeof(int), compare);

    // Calculate the sum
    td->sum = 0;
    for (int i = 0; i < td->size; i++) {
        td->sum += td->data[i];
    }

    pthread_exit(NULL);
}

// Merge all column data
void *merge_columns(void *arg) {
    MergeData *md = (MergeData *)arg;
    int *merged_data = md->merged_data;
    ThreadData *thread_data = md->thread_data;

    int index = 0;
    for (int i = 0; i < NUM_COLUMNS; i++) {
        memcpy(merged_data + index, thread_data[i].data, md->row_count * sizeof(int));
        index += md->row_count;
    }

    // Sort the merged data
    qsort(merged_data, NUM_COLUMNS * md->row_count, sizeof(int), compare);

    pthread_exit(NULL);
}

int main() {
    char input_filename[100], output_filename[100];
    FILE *input_file, *output_file;
    printf("Input File: ");
    scanf("%s", input_filename);

    // Open input file
    input_file = fopen(input_filename, "r");
    CHECK_FILE(input_file);

    // Read input data
    int data[MAX_ROWS][NUM_COLUMNS];
    int row_count = 0;
    while (row_count < MAX_ROWS && fscanf(input_file, "%d,%d,%d,%d\n",
           &data[row_count][0], &data[row_count][1],
           &data[row_count][2], &data[row_count][3]) == NUM_COLUMNS) {
        row_count++;
    }
    fclose(input_file);

    // Get target file name and handle existing files
    while (1) {
        printf("Output File: ");
        scanf("%s", output_filename);

        // Check if source and target are the same
        if (strcmp(input_filename, output_filename) == 0) {
            printf("Source and target cannot be the same!\n");
            continue;
        }

        FILE *output_file = fopen(output_filename, "r");
        if (output_file) {
            fclose(output_file);
            printf("File exists. (a) Enter new name (b) Overwrite (c) Quit\n");
            char option;
            scanf(" %c", &option);
            if (option == 'a') continue;
            if (option == 'c') return 0;
        }
        break;
    }

    // Clear previous content of output file
    output_file = fopen(output_filename, "w");
    fclose(output_file);

    // Create threads for sorting and summing columns
    pthread_t threads[NUM_COLUMNS];
    ThreadData thread_data[NUM_COLUMNS];
    for (int col = 0; col < NUM_COLUMNS; col++) {
        thread_data[col].size = row_count;
        thread_data[col].data = malloc(row_count * sizeof(int));

        CHECK_ALLOC(thread_data[col].data);

        for (int row = 0; row < row_count; row++)
            thread_data[col].data[row] = data[row][col];

        pthread_create(&threads[col], NULL, sort_and_sum, &thread_data[col]);
    }

    // Open output file
    output_file = fopen(output_filename, "a");
    CHECK_FILE(output_file, output_filename);

    // Join threads and write sorted column and sum to output file
    for (int col = 0; col < NUM_COLUMNS; col++) {
        pthread_join(threads[col], NULL);

        fprintf(output_file, "Thread %d: ", col + 1);
        for (int row = 0; row < row_count; row++) {
            fprintf(output_file, "%d", thread_data[col].data[row]);
            if (row != row_count - 1) fprintf(output_file, ", ");
        }
        fprintf(output_file, "\nsum %d: %ld\n", col + 1, thread_data[col].sum);
    }
    fclose(output_file);

    // Merge all column data
    int *merged_data = malloc(NUM_COLUMNS * row_count * sizeof(int));
    CHECK_ALLOC(merged_data);

    // Create a thread for merging
    pthread_t merge_thread;
    MergeData merge_data = {thread_data, row_count, merged_data};
    pthread_create(&merge_thread, NULL, merge_columns, &merge_data);

    // Wait for the merge thread to finish
    pthread_join(merge_thread, NULL);

    // Write merged results to the output file
    output_file = fopen(output_filename, "a");
    CHECK_FILE(output_file, output_filename);

    fprintf(output_file, "=================================================\n");
    for (int i = 0; i < NUM_COLUMNS * row_count; i++) {
        fprintf(output_file, "%d", merged_data[i]);
        if ((i + 1) % 40 == 0) fprintf(output_file, "\n");
        else if (i != NUM_COLUMNS * row_count - 1) fprintf(output_file, ", ");
    }
    fprintf(output_file, "\n");
    fclose(output_file);

finally:
    // Free allocated memory
    free(merged_data);
    for (int col = 0; col < NUM_COLUMNS; col++)
        free(thread_data[col].data);

    return 0;
}
