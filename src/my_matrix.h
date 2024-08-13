#ifndef MATRIX 
#define MATRIX

#include <stdlib.h>
#include <stdio.h>
#include <cstring>

#define REACHEBLE_BUFF_SIZE 256
#define EXPLORED_BUFF_SIZE 256
#define ADJACENTS_BUFF_SIZE 4

typedef struct Node{
    int cost;
    int x;
    int y;
    Node* previous;
    bool explored;
    bool reachable;
};

typedef struct Map{
    Node* nodes;
    int width;
    int height;
};

void equal(Node* node, const Node* origin);
Node* create_node(int x, int y, int cost);
Node* get_node(Map& map, int x, int y);
void arr_to_2Dmap(Map& map, int arr[][12], int width, int height); //KOSTIL DLYA OTLADKY
Node* find_path_A_star(Map& map, Node& start, Node& end);
bool not_in_explored(Node* node);
bool node_remove(Node* array, Node* node, const char* r_or_e);
bool node_add(Node* array, Node* node, const char* r_or_e);
Node* find_best_adj(Node* reachable, Node* end);
Node* path(Node* node);
bool new_adjacent(Node* adjacents, Node* node, Map* map);

void delete_map(Map& map); //Рекурсивно delete все ноды из nodes

void equal(Node* node, const Node* origin){
    node->cost = origin->cost;
    node->x = origin->x;
    node->y = origin->y;
    node->previous = origin->previous;
    node->explored = origin->explored;
    node->reachable = origin->reachable;
}

Node* create_node(int x, int y, int cost)
{
    Node* node = (Node*)calloc(1, sizeof(Node));
    node->cost = cost;
    node->x = x;
    node->y = y;
    node->explored = false;
    node->reachable = false;
    return node;
}

Node* get_node(Map& map, int x, int y)
{
    return &(map.nodes[(map.width*y)+x]);
}

void arr_to_2Dmap(Map& map, int arr[][12], int width, int height) //ТУТ КАКАЯ - ТО ПРОБЛЕМА
{
    map.width = width;
    map.height = height;
    map.nodes = (Node*)calloc(width*height, sizeof(Node)); //                    ТУТ УЖЕ ПРОИСХОДИТ ИНИЦИАЛИЗАЦИЯ СТРУКТУР, В ЦИКЛЕ НАМ НУЖНО ТОЛЬКО ПРИСВОИТЬ ЗНАЧЕНИЯ

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            map.nodes[i*width+j] = *create_node(j, i, arr[i][j]);
        }
    }
}


Node* find_path_A_star(Map& map, Node& start, Node& end)
{
    int explored_elem = 0;
    int reachable_elem = 1;

	Node reachable[REACHEBLE_BUFF_SIZE] = {start};
	Node explored[EXPLORED_BUFF_SIZE] = {};
    Node adjacents[ADJACENTS_BUFF_SIZE] = {};
    printf("%d, %d\n", start.x, start.y);
    printf("%d, %d\n", end.x, end.y);
    printf("START");
	while(true){ // No reachable != [], КОСТЫЛЬ, ЧИСТО НА ОТЛАДКУ
		Node* node = find_best_adj(reachable, &end);

		if((node->x == end.x)&&(node->y == end.y))
			return path(node);
		node_remove(reachable, node, "r");
		node_add(explored, node, "e");

        new_adjacent(adjacents, node, &map);
        //printf("%d, %d", node->x, node->y);
		for(int i = 0; i<ADJACENTS_BUFF_SIZE; i++){ //adj = adjacents[i]
            printf("---%d IS %d, %d --- ", i, adjacents[i].x, adjacents[i].y);
			if(not_in_explored(&adjacents[i])){ 
                //printf("1");
				node_add(reachable, &adjacents[i], "r"); //
				adjacents[i].cost = node->cost+1;
			}
			if ((node->cost + 1) < adjacents[i].cost){
                //printf("2");
				adjacents[i].cost = node->cost + 1;
				adjacents[i].previous = node;
			}

		}
	}
return NULL;
}

bool not_in_explored(Node* node)
{
    if(node->explored == false){
        node->explored = true;
        return true;
    }
    return false;
}

bool node_remove(Node* array, Node* node, const char* r_or_e)
{
    if(strcmp(r_or_e, "e") == 0){
        for(int i = 0; i < EXPLORED_BUFF_SIZE; i++){
            if(array[i].explored == true){
                if((array[i].x == node->x)&&(array[i].y == node->y)){
                    array[i].explored = false;
                    // elem_counter--;
                    return true;
                }
            }
        }
    }

    else{
        for(int i = 0; i < REACHEBLE_BUFF_SIZE; i++){
            if(array[i].reachable == true){
                if((array[i].x == node->x)&&(array[i].y == node->y)){
                    array[i].reachable = false;
                    // elem_counter--;
                    return true;
                }
            }
        }
    }
    return false;
}

bool node_add(Node* array, Node* node, const char* r_or_e)
{
    if(strcmp(r_or_e, "e") == 0){
        for(int i = 0; i < EXPLORED_BUFF_SIZE; i++){
            if(array[i].explored == false){
                equal(&array[i], node);
                return true;
            }
        }
    }

    else{
        for(int i = 0; i < REACHEBLE_BUFF_SIZE; i++){
            if(array[i].reachable == false){
                equal(&array[i], node);
                //printf("GGGG");
                return true;
            }
        }
    }

    return false;
}

Node* find_best_adj(Node* reachable, Node* end) //ВОТ ТУТ ЛОГИЧЕСКАЯ ПРОБЛЕМА
{
	Node* node;
	int min = __INT_MAX__;
    int x = end->x;
    int y = end->y;
    // printf("%d, %d", end->x, end->y);
    int abs_coord = x + y;
	for (int i = 0; i < REACHEBLE_BUFF_SIZE; i++){ //CHANGE
        if(reachable[i].cost != 0){
            int len = abs(abs_coord-(reachable[i].x+reachable[i].y));
            if (min > len){
                // printf("adsfasdfadfs%d, %dadsasdfafsd", reachable[i].x, reachable[i].y);
                min = len;
                node = &reachable[i];
                equal(node, &reachable[i]);                                 //??????????????????????????????????????
            }
        }
	}
    
	return node;
}

Node* path(Node* node)
{
	Node* full_path = (Node*)calloc(node->cost, sizeof(Node)); //MEMORY LEAK
    int tmp = 0;
	while(node != nullptr){
		equal(&full_path[tmp], node);
		node = node->previous;
        tmp++;
	}
	return full_path;
}

bool new_adjacent(Node* adjacents, Node* node, Map* map)
{
    int x = node->x;
    int y = node->y;
    int w = map->width;
    int h = map->height;
    //adjacents = {};
    if(x+1 <= w-1)
        adjacents[1] = map->nodes[w*y + (x+1)];
        // printf("%d, %d --- ", adjacents[1].x, adjacents[1].y);
    if(x-1 >= 0)
        adjacents[0] = map->nodes[w*y + (x-1)];
        // printf("%d, %d ---", adjacents[0].x, adjacents[0].y);
    if(y+1 <= h-1)
        adjacents[2] = map->nodes[w*(y+1) + x];
        // printf("%d, %d ---", adjacents[2].x, adjacents[2].y);
    if(y-1 >= 0)
        adjacents[3] = map->nodes[w*(y-1) + x];
        // printf("%d, %d\n", adjacents[3].x, adjacents[3].y);
    return true;
}

#endif