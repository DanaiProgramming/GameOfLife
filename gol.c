#include "gol_display.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>


struct state {bool OldState; bool NewState;};
typedef struct state state;

enum { Hgrid=30, Wgrid=30, Hrec=20, Wrec=20}; //Height and Width of the grid (array), Height and Width each cell (rectangle)

struct game{
    state grid[Hgrid][Wgrid];
};
typedef struct game game;




//Fill the grid with random alive and dead cells (0/1)
void fillGrid(game *g){

    for (int i=0; i<Hgrid; i++){
        for (int j=0; j<Wgrid; j++){
            g->grid[i][j].OldState = rand()%2;
        }
    }
}

//Color and display the cells (alive or dead)
void printGrid(game *g, display *d){

    for (int i=0; i<Hgrid; i++){
        for (int j=0; j<Wgrid; j++){

            if  (g->grid[i][j].OldState==1)
                colorCell(d, i*Hrec, j*Wrec, 1); //Color the cell Black - Alive

            else if  (g->grid[i][j].OldState==0)
                colorCell(d, i*Hrec, j*Wrec, 0); //Color the cell White - Dead

        }
    }
}

//Update the old state of the cells to be ready for the next generation states
void update(game *g){
    for (int i=0; i<Hgrid; i++){
        for (int j=0; j<Wgrid; j++){
            g->grid[i][j].OldState = g->grid[i][j].NewState;
        }
    }
}

//Define the next state of the cells (next generation) according to the number of neighbors around it
void NextState(int row, int col, int LiveNeighbors, game *g){

    if (LiveNeighbors<2 || LiveNeighbors>3){ //UNDERPOPULATION | OVERPOPULATION
        g->grid[row][col].NewState=0;
    }
    else if (LiveNeighbors==3){             //CREATION
        g->grid[row][col].NewState=1;
    }
    else{                                   //LiveNeighbors=2 or 3 -> keeps its state
        g->grid[row][col].NewState=g->grid[row][col].OldState;
    }
}


//Count the alive neighbors around the current cell
int compareCells(int row, int col, game *g){
    //compare all the 8 cells (max) neighboring the current cell (if not at the edges outliine)
    //NEIGHBORS:  row-1 col-1 | row-1 col | row-1 col+1 | row col-1 | row col+1 | row+1 col-1 | row+1 col | row+1 col+1 |

    int LiveNeighbors=0;
    for (int i=row-1; i<=row+1; i++){
        for (int j=col-1; j<=col+1; j++){

            if (i>=0 && i<Hgrid){     //if current cell is on the edge or the outline of grid
                if (j>=0 && j<Wgrid){ //

                    if (i!=row || j!=col){ //don't compare the current cell
                        if (g->grid[i][j].OldState==1)
                            LiveNeighbors+=1;
                    }
                }
            }
        }
    }
    return LiveNeighbors;
}

//Run the main functions of the program
void runGOL(game *g){

  int LiveNeighbors;
  for (int i=0; i<Hgrid; i++){
      for (int j=0; j<Wgrid; j++){

          LiveNeighbors=compareCells(i,j,g);
          NextState(i,j,LiveNeighbors,g);
      }
  }
}


//==================================TESTING=====================================
//Test CompareCells function
void testCompareCells(game *g){

    g->grid[1][1].OldState=1; g->grid[1][2].OldState=1; g->grid[1][3].OldState=1;
    g->grid[2][1].OldState=1; g->grid[2][3].OldState=1; g->grid[3][1].OldState=1;
    g->grid[3][2].OldState=1; g->grid[3][3].OldState=1;
    assert(compareCells(2, 2, g) == 8);

    g->grid[1][1].OldState=0; g->grid[1][2].OldState=0; g->grid[1][3].OldState=0;
    g->grid[2][1].OldState=1; g->grid[2][3].OldState=0; g->grid[3][1].OldState=1;
    g->grid[3][2].OldState=0; g->grid[3][3].OldState=0;
    assert(compareCells(2, 2, g) == 2);

    g->grid[1][1].OldState=0; g->grid[1][2].OldState=1; g->grid[1][3].OldState=0;
    g->grid[2][1].OldState=1; g->grid[2][3].OldState=1; g->grid[3][1].OldState=1;
    g->grid[3][2].OldState=0; g->grid[3][3].OldState=1;
    assert(compareCells(2, 2, g) == 5);
}

//Test NextState function
void testNextState(game *g){

    g->grid[2][2].OldState=1;
    NextState(2, 2, 0, g); //<2
    assert((g->grid[2][2].NewState) == 0);

    g->grid[2][2].OldState=1;
    NextState(2, 2, 2, g); //2
    assert(g->grid[2][2].NewState == 1);

    g->grid[2][2].OldState=1;
    NextState(2, 2, 3, g); //3
    assert(g->grid[2][2].NewState == 1);

    g->grid[2][2].OldState=1;
    NextState(2 ,2 , 6, g); //>3
    assert(g->grid[2][2].NewState == 0);

    g->grid[2][2].OldState=0;
    NextState( 2, 2, 3, g); //3
    assert(g->grid[2][2].NewState == 1);
}
//==============================================================================



int main(int n, char *args[]) {

    if (n==2){ //Only for Testing

        if (strcmp(args[1], "test") == 0 ){
            game *g = malloc(sizeof(game));
            testNextState(g);
            testCompareCells(g);
            printf("All tests pass\n");
        }
        else printf("Write 'test' to do the testing\n");
    }

    else if (n==1){ //Run game of life normally

      srand(time(NULL));

      display *d= newDisplay("Game Of Life", Wgrid*Wrec , Hgrid*Hrec );
      game *g = malloc(sizeof(game));

      fillGrid(g);
      printGrid(g,d);
      show(d);

      while(true){
          runGOL(g);
          printGrid(g,d);
          pause(d,100);
          update(g);
          show(d);

          //key(d);
      }
      free(d);
      free(g);
    }

    return 0;
}
