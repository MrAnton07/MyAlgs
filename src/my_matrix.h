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
Node* find_path_A_star(Map* map, Node* start, Node* end);
bool not_in_explored(Node* node);
bool node_remove(Node** array, Node* node, const char* r_or_e);
bool node_add(Node** array, Node* node, const char* r_or_e);
Node*  find_best_adj(Node** reachable, Node* end);
Node* path(Node* node);
bool new_adjacent(Node** adjacents, Node* node, Map* map);

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
            // map.nodes[i*width+j] = *create_node(j, i, arr[i][j]);
            map.nodes[i*width+j].cost = arr[i][j];
            map.nodes[i*width+j].x = j;
            map.nodes[i*width+j].y = i;
            map.nodes[i*width+j].explored = false;
            map.nodes[i*width+j].reachable = false;
        }
    }
}

void print_map(Map* map){
    for(int i = 0; i<map->height; i++){
        for(int j = 0; j<map->width; j++){
            printf(" |X%dY%d| ", map->nodes[i*map->width+j].x, map->nodes[i*map->width+j].y);
        }
        printf("\n");
    }
}


Node* find_path_A_star(Map* map, Node* start, Node* end)
{
    int explored_elem = 0;
    int reachable_elem = 1;

    start->previous = nullptr;

	Node* reachable[REACHEBLE_BUFF_SIZE] = {start};//(Node**)calloc(REACHEBLE_BUFF_SIZE, sizeof(Node*));// [REACHEBLE_BUFF_SIZE] = {start};
	Node* explored[EXPLORED_BUFF_SIZE] = {};//(Node**)calloc(EXPLORED_BUFF_SIZE, sizeof(Node*));//[EXPLORED_BUFF_SIZE] = {};
    Node* adjacents[ADJACENTS_BUFF_SIZE] = {};//(Node**)calloc(ADJACENTS_BUFF_SIZE, sizeof(Node*)); //[ADJACENTS_BUFF_SIZE] = {};
    reachable[0] = start;
    printf("%d, %d\n", start->x, start->y);
    printf("%d, %d\n", end->x, end->y);
    printf("START\n");
    print_map(map);
	while(true){ // No reachable != [], КОСТЫЛЬ, ЧИСТО НА ОТЛАДКУ
        Node* node = nullptr;
		node = find_best_adj(reachable, end);
        if(node == start)
            printf("asfd");
        if(node == end)
            printf("OOOOOH\n");
        //tmp = node.previous
		if(node == end)
            //node->previous
            // free
            // free
            // free
			return path(node);
		node_remove(reachable, node, "r");
        // for (int i  = 0; i < REACHEBLE_BUFF_SIZE; i++){
        //     if (reachable[i] == start)
        //         printf("EAH\n");
        // }
		node_add(explored, node, "e");
        // for (int i  = 0; i < REACHEBLE_BUFF_SIZE; i++){
        //     if (explored[i] == start)
        //         printf("EAH1\n");
        // }
        // if (node->previous != nullptr)
        //     printf("EEES");
        new_adjacent(adjacents, node, map);
        //printf("%d, %d", node->x, node->y);
		for(int i = 0; i<ADJACENTS_BUFF_SIZE; i++){ //adj = adjacents[i]
            //printf("---%d IS %d, %d --- ", i, adjacents[i].x, adjacents[i].y);
			if((adjacents[i] != nullptr) && not_in_explored(adjacents[i])){ 
                //printf("1");
				node_add(reachable, adjacents[i], "r"); //
				//adjacents[i]->cost = node->cost+1;
                adjacents[i]->previous = node;
                //map.nodes[adjacents[i].y*map.width+adjacents[i].x].previous = node;
			}
			// if (adjacents[i] != nullptr && ((node->cost + 1) < adjacents[i]->cost)){
            //     //printf("2");
			// 	adjacents[i]->cost = node->cost + 1;
			// 	adjacents[i]->previous = node;
            //     //map.nodes[adjacents[i].y*map.width+adjacents[i].x].previous = node;
			// }

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

bool node_remove(Node** array, Node* node, const char* r_or_e)
{
    if(strcmp(r_or_e, "e") == 0){
        for(int i = 0; i < EXPLORED_BUFF_SIZE; i++){
            if(array[i] != nullptr){
                if(array[i]->explored == true){
                    if((array[i]->x == node->x)&&(array[i]->y == node->y)){ //Можно проверять равенство адресов
                        array[i]->explored = false;
                        // elem_counter--;
                        return true;
                    }
                }
            }
        }
    }

    else{
        for(int i = 0; i < REACHEBLE_BUFF_SIZE; i++){
            if(array[i] != nullptr){
                if(array[i]->reachable == true){
                    if((array[i]->x == node->x)&&(array[i]->y == node->y)){
                        array[i]->reachable = false;
                        // elem_counter--;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool node_add(Node** array, Node* node, const char* r_or_e)
{
    if(strcmp(r_or_e, "e") == 0){
        for(int i = 0; i < EXPLORED_BUFF_SIZE; i++){
            if(array[i] == nullptr){
                array[i] = node;
                array[i]->explored = true;
                return true;
            }                      ///////////////////////ПРИЧИНА ВСЕХ БЕД
            if(array[i]->explored == false){
                array[i] = node;
                array[i]->explored = true;
                return true;
            }
        }
    }

    else{
        for(int i = 0; i < REACHEBLE_BUFF_SIZE; i++){
            if(array[i] == nullptr){
                array[i] = node;
                array[i]->reachable = true;
                return true;
            }
            if(array[i]->reachable == false){
                array[i] = node;
                array[i]->reachable = true;
                //printf("GGGG");
                return true;
            }
        }
    }

    return false;
}

Node* find_best_adj(Node** reachable, Node* end) //ВОТ ТУТ ЛОГИЧЕСКАЯ ПРОБЛЕМА Node* node, 
{
	Node* node;
	int min = __INT_MAX__;
    int x = end->x;
    int y = end->y;
    printf("%d, %d", end->x, end->y);
    // int abs_coord = x + y;
	for (int i = 0; i < REACHEBLE_BUFF_SIZE; i++){ //CHANGE
        if(reachable[i] != nullptr){
            int cost_start_to_node = reachable[i]->cost;
            int cost_node_to_goal = abs((x+y)-(reachable[i]->x+reachable[i]->y));
            int total_cost = cost_node_to_goal+cost_start_to_node;
            if(reachable[i]->cost != 0){
                if (min >= total_cost){
                    printf("adsfasdfadfs%d, %dadsasdfafsd", reachable[i]->x, reachable[i]->y);
                    min = total_cost;
                    node = reachable[i];
                    // equal(node, &reachable[i]);                                 //??????????????????????????????????????
                }
            }
            // printf("sfddfssdf");
        }
	}
    printf("TOTALCOST: %d\n", min);
    // if(node == reachable[0])
    //     printf("asfd");
    // if(node == nullptr)
    //     printf("asfd");
	return node;
}

Node* path(Node* node)
{
	Node** full_path = (Node**)calloc(10, sizeof(Node*)); //MEMORY LEAK node->cost
    int tmp = 0;
    //OTLADKA
    char final[8][12] = {
        '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
        '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
        '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
        '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
        '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
        '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
        '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
        '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
    };
    //////////
	while(node != nullptr){
		full_path[tmp] = node;
        //printf("X: %d, Y: %d\n", node->x, node->y);
        final[node->y][node->x] = '@';
		node = node->previous;
        tmp++;
	}
    ////////////
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 12; j++){
            printf(" %c ", final[i][j]);
        }
        printf("\n");
    }
    ////////////
	return *full_path;
}

bool new_adjacent(Node** adjacents, Node* node, Map* map)
{
    if(node != nullptr){
        int x = node->x;
        int y = node->y;
        int w = map->width;
        int h = map->height;
        //adjacents = {};
        if(x+1 <= w-1)
            adjacents[1] = &(map->nodes[w*y + (x+1)]);
            // adjacents[1].previous = node;
            printf("%d, %d --- ", adjacents[1]->x, adjacents[1]->y);
        if(x-1 >= 0)
            adjacents[0] = &(map->nodes[w*y + (x-1)]);
            // adjacents[0].previous = node;
            printf("%d, %d ---", adjacents[0]->x, adjacents[0]->y);
        if(y+1 <= h-1)
            adjacents[2] = &(map->nodes[w*(y+1) + x]);
            // adjacents[2].previous = node;
            printf("%d, %d ---", adjacents[2]->x, adjacents[2]->y);
        if(y-1 >= 0)
            adjacents[3] = &(map->nodes[w*(y-1) + x]);
            // adjacents[3].previous = node;
            printf("%d, %d\n", adjacents[3]->x, adjacents[3]->y);
        return true;
    }
    return false;
}

#endif