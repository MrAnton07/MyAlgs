#include "my_matrix.h"

int main(){
    int array[8][12] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    991, 919, 991, 991, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 991, 991, 1, 1, 1, 1, 1, 1,
    991, 991, 991, 991, 991, 991, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    };
    Map* map = (Map*)calloc(1, sizeof(Map));
    arr_to_2Dmap(*map, array, 12, 8);
    find_path_A_star(map, get_node(*map, 1, 1), get_node(*map, 7, 7));
    printf("Success!\n");
    return 0;
}