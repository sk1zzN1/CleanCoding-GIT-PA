#include <stdio.h>
#include <stdlib.h>


// Structura pentru nodul din lista de adiacență
typedef struct Node {
    int data;
    struct Node* next;
} Node;


// Structura pentru graf
typedef struct Graph {
    int v;         // număr de vârfuri
    int* visited;  // vector de vizitare
    Node** adjList;
} Graph;


// Stack simplu pentru DFS (opțional aici)
typedef struct Stack {
    int top;
    int capacity;
    int* array;
} Stack;


// Creează un nod
Node* create_node(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = v;
    newNode->next = NULL;
    return newNode;
}


// Creează graful
Graph* create_graph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->v = vertices;
    graph->adjList = (Node**)malloc(vertices * sizeof(Node*));
    graph->visited = (int*)calloc(vertices, sizeof(int));


    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
    }


    return graph;
}


// Adaugă muchie (neorientată)
void add_edge(Graph* graph, int src, int dest) {
    Node* newNode = create_node(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;


    newNode = create_node(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}


// DFS simplu pentru a verifica conexiunea
int dfs(Graph* graph, int src, int dest) {
    graph->visited[src] = 1;
    if (src == dest) return 1;


    Node* temp = graph->adjList[src];
    while (temp) {
        if (!graph->visited[temp->data]) {
            if (dfs(graph, temp->data, dest)) return 1;
        }
        temp = temp->next;
    }
    return 0;
}


// Resetează vectorul de vizitare
void reset_visited(Graph* graph) {
    for (int i = 0; i < graph->v; i++) {
        graph->visited[i] = 0;
    }
}


// Funcția principală pentru a verifica dacă există drum între două restaurante
void check_path(Graph* graph, int src, int dest) {
    reset_visited(graph);
    if (dfs(graph, src, dest)) {
        printf("Exista drum intre %d si %d.\n", src, dest);
    } else {
        printf("Nu exista drum intre %d si %d.\n", src, dest);
    }
}


int main() {
    int numVertices, numEdges;
    printf("Cate restaurante (noduri) sunt? ");
    scanf("%d", &numVertices);


    Graph* graph = create_graph(numVertices);


    printf("Cate legaturi (muchii) sunt? ");
    scanf("%d", &numEdges);


    printf("Introduceti perechi de noduri conectate (ex: 0 1):\n");
    for (int i = 0; i < numEdges; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        add_edge(graph, src, dest);
    }


    int q;
    printf("Cate perechi doriti sa verificati pentru drum direct? ");
    scanf("%d", &q);


    for (int i = 0; i < q; i++) {
        int from, to;
        printf("Verificare drum intre: ");
        scanf("%d %d", &from, &to);
        check_path(graph, from, to);
    }


    return 0;
}





