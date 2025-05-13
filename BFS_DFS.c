#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100
#define HASH_SIZE 11

// ------------------- Graph Section -------------------

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjLists;
    bool* visited;
} Graph;

// Queue for BFS
int queue[MAX], front = 0, rear = 0;

void enqueue(int value) { queue[rear++] = value; }
int dequeue() { return queue[front++]; }
bool isQueueEmpty() { return front == rear; }

// Stack for DFS
int stack[MAX];
int top = -1;

void push(int value) { stack[++top] = value; }
int pop() { return stack[top--]; }
bool isStackEmpty() { return top == -1; }

Node* createNode(int v) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(Node*));
    graph->visited = malloc(vertices * sizeof(bool));
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = false;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void bfs(Graph* graph, int startVertex) {
    for (int i = 0; i < graph->numVertices; i++) graph->visited[i] = false;
    front = rear = 0;
    graph->visited[startVertex] = true;
    enqueue(startVertex);

    printf("BFS Traversal: ");
    while (!isQueueEmpty()) {
        int current = dequeue();
        printf("%d ", current);
        Node* temp = graph->adjLists[current];
        while (temp) {
            int adj = temp->vertex;
            if (!graph->visited[adj]) {
                graph->visited[adj] = true;
                enqueue(adj);
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

void dfs(Graph* graph, int startVertex) {
    for (int i = 0; i < graph->numVertices; i++) graph->visited[i] = false;
    top = -1;
    push(startVertex);

    printf("DFS Traversal: ");
    while (!isStackEmpty()) {
        int current = pop();
        if (!graph->visited[current]) {
            graph->visited[current] = true;
            printf("%d ", current);
            Node* temp = graph->adjLists[current];
            while (temp) {
                if (!graph->visited[temp->vertex]) push(temp->vertex);
                temp = temp->next;
            }
        }
    }
    printf("\n");
}

// ------------------- Hashing with Linear Probing -------------------

int slotsPerIndex = 2;  // default
int hashTable[HASH_SIZE][4]; // max 4 slots per index

void initHashTable() {
    for (int i = 0; i < HASH_SIZE; i++)
        for (int j = 0; j < 4; j++)
            hashTable[i][j] = -1;
}

void insertHash(int key) {
    int index = key % HASH_SIZE;
    int startIndex = index;
    while (1) {
        for (int i = 0; i < slotsPerIndex; i++) {
            if (hashTable[index][i] == -1) {
                hashTable[index][i] = key;
                printf("Inserted %d at index %d, slot %d\n", key, index, i);
                return;
            }
        }
        index = (index + 1) % HASH_SIZE;
        if (index == startIndex) {
            printf("Hash table is full!\n");
            return;
        }
    }
}

void displayHash() {
    printf("Hash Table (Mod 11, %d-slot Linear Probing):\n", slotsPerIndex);
    for (int i = 0; i < HASH_SIZE; i++) {
        printf("[%2d]: ", i);
        for (int j = 0; j < slotsPerIndex; j++) {
            if (hashTable[i][j] != -1)
                printf("%d ", hashTable[i][j]);
            else
                printf("- ");
        }
        printf("\n");
    }
}

// ------------------- Main Menu -------------------

int main() {
    int choice;
    Graph* graph = NULL;
    int vertices, edges, u, v, start;

    initHashTable();  // Initialize hashing table

    do {
        printf("\n--- Menu ---\n");
        printf("1. Create Graph (Enter Vertices and Edges)\n");
        printf("2. BFS Traversal\n");
        printf("3. DFS Traversal\n");
        printf("4. Set Hashing Slot Size (2/3/4)\n");
        printf("5. Insert into Hash Table\n");
        printf("6. Display Hash Table\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter number of vertices: ");
                scanf("%d", &vertices);
                graph = createGraph(vertices);
                printf("Enter number of edges: ");
                scanf("%d", &edges);
                printf("Enter %d edges (u v):\n", edges);
                for (int i = 0; i < edges; i++) {
                    scanf("%d %d", &u, &v);
                    addEdge(graph, u, v);
                }
                printf("Graph created with %d vertices and %d edges.\n", vertices, edges);
                break;
            case 2:
                if (!graph) {
                    printf("Create a graph first!\n");
                    break;
                }
                printf("Enter start vertex for BFS: ");
                scanf("%d", &start);
                bfs(graph, start);
                break;
            case 3:
                if (!graph) {
                    printf("Create a graph first!\n");
                    break;
                }
                printf("Enter start vertex for DFS: ");
                scanf("%d", &start);
                dfs(graph, start);
                break;
            case 4:
                printf("Enter slot size per index (2, 3, or 4): ");
                scanf("%d", &slotsPerIndex);
                if (slotsPerIndex < 2 || slotsPerIndex > 4) {
                    printf("Invalid slot size! Setting to default (2).\n");
                    slotsPerIndex = 2;
                }
                initHashTable();  // clear table when changing slots
                break;
            case 5:
                printf("Enter key to insert into hash table: ");
                scanf("%d", &u);
                insertHash(u);
                break;
            case 6:
                displayHash();
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 0);

    return 0;
}
