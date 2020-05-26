#include "level.h"

#include <stdlib.h>
#include <assert.h>

level *level_new(int size_x, int size_y){
    // Ask memory for the level struct
    //ASIGNACION DIANAMICA PARA UNA VARIABLE TIPO LEVEL(OSEA EL NIVEL EN SI)
    level *lvl = malloc(sizeof(level));

    // Set the size
    //A LOS VALORES DEL STRUCT DE LEVEL SE LE ASIGNAN TAMAÑOS(CON LA FLECHITAS)
    lvl->size_x = size_x;
    lvl->size_y = size_y;

    // Ask memory for the cell* array
    //FILAS
    lvl->cells  = malloc(lvl->size_y * sizeof(char *));

    // Ask memory for each row
    //COLUMNA
    for(int y=0; y<lvl->size_y; y++){
        lvl->cells[y] = malloc(lvl->size_x * sizeof(char));
    }

    // Initialize level
    //RECORRE LA MATRIZ, A CADA VALOR SE LE INICIA CON UN PUNTO
    for(int y=0; y<lvl->size_y; y++){
        for(int x=0; x<lvl->size_x; x++){
            lvl->cells[y][x] = '.';
        }
    }

    // Retreieve level's pointer
    return lvl;
}

int level_get(const level *lvl, int x, int y){
    // For cells outside the matrix:
    if(x<0) return '#';
    if(y<0) return '#';
    if(x>=lvl->size_x) return '#';
    if(y>=lvl->size_y) return '#';
    // Regular cells
    return lvl->cells[y][x];
}

//PASO EL NIVEL PARA LLENARLO CON COSAS
void level_fill_random(level *lvl, int wall_size){
    // Check that the wall_size is smaller than the level
    //ESTA COSA ES COMO UN IF
    assert(wall_size<lvl->size_x);
    assert(wall_size<lvl->size_y);
    // Compute a good number of walls so that up to 1/10 of the level is filled
    int n_walls = lvl->size_x*lvl->size_y/wall_size/10;
    // Add each of the walls
    for(int i=0; i<n_walls; i++){
        int vert = rand()%2; // vertical or horizontal? 0 o 1
        if(vert){
            // Initial wall position
            int wx = rand()%(lvl->size_x);
            int wy = rand()%(lvl->size_y-wall_size);
            // Iterate to place wall vertically
            for(int k=0; k<wall_size; k++){
                lvl->cells[wy+k][wx] = '#';
            }
        }else{
            // Initial wall position
            int wx = rand()%(lvl->size_x-wall_size);
            int wy = rand()%(lvl->size_y);
            // Iterate to place wall horizontally
            //CONSTRUYE EL MURO
            for(int k=0;k<wall_size;k++){
                lvl->cells[wy][wx+k] = '#';
            }
        }
    }
}

// Free level memory
void level_free(level *lvl){
    // Free each row first
    for(int y=0;y<lvl->size_y;y++){
        free(lvl->cells[y]);
    }
    // Free char* array
    free(lvl->cells);
    // Free the level
    free(lvl);
}
