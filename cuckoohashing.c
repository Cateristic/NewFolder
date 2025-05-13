#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 11     // Size of each table
#define MAX_LOOP 20       // Prevent infinite loop

int table1[TABLE_SIZE];
int table2[TABLE_SIZE];

// Initialize both tables with -1 (indicating empty)
void initTables() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table1[i] = -1;
        table2[i] = -1;
    }
}

// Hash functions
int hash1(int key) {
    return key % TABLE_SIZE;
}

int hash2(int key) {
    return (key / TABLE_SIZE) % TABLE_SIZE;
}

// Insert using cuckoo hashing
int cuckooInsert(int key) {
    int count = 0;
    int pos, temp;

    while (count < MAX_LOOP) {
        // Try to place in table1
        pos = hash1(key);
        if (table1[pos] == -1) {
            table1[pos] = key;
            return 1;
        }

        // Kick out existing key
        temp = table1[pos];
        table1[pos] = key;
        key = temp;

        // Try to place in table2
        pos = hash2(key);
        if (table2[pos] == -1) {
            table2[pos] = key;
            return 1;
        }

        // Kick out again
        temp = table2[pos];
        table2[pos] = key;
        key = temp;

        count++;
    }

    // Failed after too many displacements
    printf("Cycle detected or table overflow. Rehashing needed!\n");
    return 0;
}

void displayTables() {
    printf("\nTable 1:\n");
    for (int i = 0; i < TABLE_SIZE; i++)
        printf("[%2d]: %d\n", i, table1[i]);

    printf("\nTable 2:\n");
    for (int i = 0; i < TABLE_SIZE; i++)
        printf("[%2d]: %d\n", i, table2[i]);
}

int main() {
    int n, key;
    initTables();

    printf("Enter number of keys to insert: ");
    scanf("%d", &n);

    printf("Enter %d keys:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &key);
        cuckooInsert(key);
    }

    displayTables();
    return 0;
}
