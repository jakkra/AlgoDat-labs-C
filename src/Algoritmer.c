/*
 ============================================================================
 Name        : Algoritmer.c
 Author      : Jakob Krantz
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <time.h>
#include "linkedlist.h"

#define min(a, b) (((a) < (b)) ? (a) : (b));

char *getcwd(char *buf, size_t size);
int ford_fulceson(int source, int destination);
int bfs(int source, int destination);
void bfsCut(int source, int goal);
void show_graph();
void parse();

int number_of_nodes = 55;
double points[280][3];
int graph[55][55];
int parent[55];
int visited[55]; // 1 = true, 0 = false
int residualGraph[55][55];

int main(int argc, char const *argv[]) {
	struct timeval start, end;
	gettimeofday(&start, 0);

	parse();
	//show_graph();
	int max_flow = ford_fulceson(0, 54);
	gettimeofday(&end, 0);
	long elapsed = (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec
			- start.tv_usec;
	printf("Time elapsed: %ld micro seconds ", elapsed);
	printf("\nMax flow = %d\n", max_flow);

	//bfsCut(0, 54);

	return 0;
}

int ford_fulceson(int source, int destination) {
	int u, v = 0;
	int max_flow = 0;
	int path_flow = 0;
	for (int source_vertex = 0; source_vertex < number_of_nodes;
			source_vertex++) {
		for (int destination_vertex = 0; destination_vertex < number_of_nodes;
				destination_vertex++) {
			residualGraph[source_vertex][destination_vertex] =
					graph[source_vertex][destination_vertex];
		}
	}

	while (bfs(source, destination)) {
		//puts("Stuck");
		path_flow = 99999;
		for (v = destination; v != source; v = parent[v]) {
			u = parent[v];
			path_flow = min(path_flow, residualGraph[u][v])
			;
		}
		for (v = destination; v != source; v = parent[v]) {
			u = parent[v];
			residualGraph[u][v] -= path_flow;
			residualGraph[v][u] += path_flow;
		}
		max_flow += path_flow;
		//printf("Max_Flow%d\n", max_flow);
	}

	return max_flow;

}

void show_graph() {
	for (int row = 0; row < number_of_nodes; ++row) {
		for (int col = 0; col < number_of_nodes; ++col) {
			printf(" %d", graph[row][col]);
		}
		puts("");
	}
}

void bfsCut(int source, int goal) {
	int element;
	for (int vertex = 0; vertex < number_of_nodes; vertex++) {
		parent[vertex] = -1;
		visited[vertex] = 0;
	}
	add_end(source);
	parent[source] = -1;
	visited[source] = 1;
	while (!is_empty()) {

		element = remove_first();
		for (int index = 0; index < number_of_nodes; index++) {

			if (residualGraph[element][index] > 0 && !visited[index]) {
				parent[index] = element;
				add_end(index);
				visited[index] = 1;
			}
		}
	}
	/*for (int i = 0; i < number_of_nodes; i++) {
	 for (int j = 0; j < number_of_nodes; j++) {
	 if (visited[i] && !visited[j] && (graph[i][j] > 0)) {
	 puts(i + " " + j + " " + graph[i][j]);
	 }
	 }

	 }
	 */
}

int bfs(int source, int goal) {

	int path_found = 0;
	int element = 0;

	for (int vertex = 0; vertex < number_of_nodes; vertex++) {
		parent[vertex] = -1;
		visited[vertex] = 0;

	}

	add_end(source);
	parent[source] = -1;
	visited[source] = 1;

	while (!is_empty()) {
		element = remove_first();
		for (int index = 0; index < number_of_nodes; index++) {
			if (residualGraph[element][index] > 0 && !visited[index]) {
				parent[index] = element;
				add_end(index);
				visited[index] = 1;

			}
		}
	}
	if (visited[goal]) {
		path_found = 1;
	}

	return path_found;

}

void parse() {
	char working_directory[1024];
	if (getcwd(working_directory, sizeof(working_directory)) != NULL) {
		//fprintf(stdout, "Current working dir: %s\n", working_directory);
	} else {
		//perror("getcwd() error");
	}

	static const char filename[] = "/rail.txt";

	char *full_path;
	full_path = malloc(strlen(working_directory) + strlen(filename) + 1);
	full_path[0] = '\0';
	strcat(full_path, working_directory);
	strcat(full_path, filename);
	//printf("%s\n", full_path);

	FILE *file = fopen(full_path, "r");
	if (file != NULL) {

		char line[128]; /* or other suitable maximum line size */

		/*Skip until we see flag "DESTINATIONS"*/
		while (fgets(line, sizeof line, file) != NULL
				&& strstr(line, "DESTINATIONS") == NULL) {
		}
		/* read the input */
		char *splitted_value;
		while (fgets(line, sizeof line, file) != NULL
				&& strstr(line, "EOF") == NULL) {

			int column = atoi(splitted_value = strtok(line, " "));
			int row = atoi(splitted_value = strtok(NULL, " "));
			int weight =
					atoi(splitted_value = strtok(NULL, " ")) != -1 ?
							atoi(splitted_value) : 1000;
			graph[column][row] = weight;
			graph[row][column] = weight;

		}
		fclose(file);
	} else {
		perror(filename);
	}
}
