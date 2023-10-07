#include "struct.h"
#include "global.h"
#include "include.h"
#include "define.h"

void precompute_distance_to_edge()
{
    for (int file = 0; file < 8; file++) {
        for (int rank = 0; rank < 8; rank++) {

            int num_north = 7 - rank;
            int num_south = rank;
            int num_west = file;
            int num_east = 7 - file;

            int square_index = rank * 8 + file;

            precomputed_values.distances[square_index].north = num_north;
            precomputed_values.distances[square_index].south = num_south;
            precomputed_values.distances[square_index].east = num_east;
            precomputed_values.distances[square_index].west = num_west;
            precomputed_values.distances[square_index].north_west = MIN(num_north, num_west);
            precomputed_values.distances[square_index].north_east = MIN(num_north, num_east);
            precomputed_values.distances[square_index].south_west = MIN(num_south, num_west);
            precomputed_values.distances[square_index].south_east = MIN(num_south, num_east);


        }
    }
}