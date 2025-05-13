#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100

// Structure for an adjacency list node
typedef struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
} AdjListNode;

// Adjacency list
typedef struct AdjList {
    AdjListNode* head;
} AdjList;

// Graph with array of adjacency lists
typedef struct Graph {
    int V;
    AdjList* array;
} Graph;

// Min Heap Node
typedef struct MinHeapNode {
    int v;
    int dist;
} MinHeapNode;

// Min Heap
typedef struct MinHeap {
    int size;
    int capacity;
    int* pos; // position of vertex in the heap
    MinHeapNode** array;
} MinHeap;

// Create new adjacency list node
AdjListNode* newAdjListNode(int dest, int weight) {
    AdjListNode* node = (AdjListNode*)malloc(sizeof(AdjListNode));
    node->dest = dest;
    node->weight = weight;
    node->next = NULL;
    return node;
}

// Create a graph with V vertices
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));
    for (int i = 0; i < V; i++)
        graph->array[i].head = NULL;
    return graph;
}

// Add edge to graph
void addEdge(Graph* graph, int src, int dest, int weight) {
    AdjListNode* node = newAdjListNode(dest, weight);
    node->next = graph->array[src].head;
    graph->array[src].head = node;

    // Undirected graph: add reverse edge
    node = newAdjListNode(src, weight);
    node->next = graph->array[dest].head;
    graph->array[dest].head = node;
}

// Create a MinHeapNode
MinHeapNode* newMinHeapNode(int v, int dist) {
    MinHeapNode* node = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    node->v = v;
    node->dist = dist;
    return node;
}

// Create a MinHeap
MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->pos = (int*)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    heap->array = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*));
    return heap;
}

// Swap two heap nodes
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// Heapify at index i
void minHeapify(MinHeap* heap, int i) {
    int smallest = i, left = 2*i + 1, right = 2*i + 2;
    if (left < heap->size && heap->array[left]->dist < heap->array[smallest]->dist)
        smallest = left;
    if (right < heap->size && heap->array[right]->dist < heap->array[smallest]->dist)
        smallest = right;

    if (smallest != i) {
        MinHeapNode* smallestNode = heap->array[smallest];
        MinHeapNode* currentNode = heap->array[i];

        // Update pos[]
        heap->pos[smallestNode->v] = i;
        heap->pos[currentNode->v] = smallest;

        swapMinHeapNode(&heap->array[smallest], &heap->array[i]);
        minHeapify(heap, smallest);
    }
}

// Check if heap is empty
int isEmpty(MinHeap* heap) {
    return heap->size == 0;
}

// Extract minimum node
MinHeapNode* extractMin(MinHeap* heap) {
    if (isEmpty(heap))
        return NULL;

    MinHeapNode* root = heap->array[0];
    MinHeapNode* last = heap->array[heap->size - 1];
    heap->array[0] = last;

    heap->pos[root->v] = heap->size - 1;
    heap->pos[last->v] = 0;

    --heap->size;
    minHeapify(heap, 0);

    return root;
}

// Decrease distance of a vertex
void decreaseKey(MinHeap* heap, int v, int dist) {
    int i = heap->pos[v];
    heap->array[i]->dist = dist;

    while (i && heap->array[i]->dist < heap->array[(i - 1)/2]->dist) {
        heap->pos[heap->array[i]->v] = (i - 1)/2;
        heap->pos[heap->array[(i - 1)/2]->v] = i;
        swapMinHeapNode(&heap->array[i], &heap->array[(i - 1)/2]);
        i = (i - 1)/2;
    }
}

// Check if a vertex is in the heap
int isInMinHeap(MinHeap *heap, int v) {
    return heap->pos[v] < heap->size;
}

// Dijkstra’s algorithm
void dijkstra(Graph* graph, int src) {
    int V = graph->V;
    int dist[V];

    MinHeap* heap = createMinHeap(V);

    for (int v = 0; v < V; v++) {
        dist[v] = INT_MAX;
        heap->array[v] = newMinHeapNode(v, dist[v]);
        heap->pos[v] = v;
    }

    heap->array[src] = newMinHeapNode(src, 0);
    heap->pos[src] = src;
    dist[src] = 0;
    decreaseKey(heap, src, 0);

    heap->size = V;

    while (!isEmpty(heap)) {
        MinHeapNode* minNode = extractMin(heap);
        int u = minNode->v;

        AdjListNode* curr = graph->array[u].head;
        while (curr != NULL) {
            int v = curr->dest;

            if (isInMinHeap(heap, v) && dist[u] != INT_MAX &&
                curr->weight + dist[u] < dist[v]) {
                dist[v] = dist[u] + curr->weight;
                decreaseKey(heap, v, dist[v]);
            }
            curr = curr->next;
        }
    }

    printf("Vertex \tDistance from Source %d\n", src);
    for (int i = 0; i < V; i++)
        printf("%d \t%d\n", i, dist[i]);
}

// ---------- MAIN ----------
int main() {
    int V, E, src, u, v, w;

    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    Graph* graph = createGraph(V);

    printf("Enter %d edges (src dest weight):\n", E);
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &u, &v, &w);
        addEdge(graph, u, v, w);
    }

    printf("Enter source vertex: ");
    scanf("%d", &src);

    dijkstra(graph, src);

    return 0;
}
