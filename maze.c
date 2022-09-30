#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
  int i, j, rows, cols;
  char a;
  FILE *reader = fopen(fileName, "r");
  fscanf(reader, "%d %d", &cols, &rows);
  maze_t *newmaze = malloc(sizeof(maze_t));                          
  newmaze -> height = rows;
  newmaze -> width = cols;
  newmaze -> cells = (char **)malloc(rows * sizeof(char *));         
    for (i = 0; i < rows; i++){
      newmaze -> cells[i] = (char *)malloc(cols * sizeof(char));
    }
    for (i = 0; i < rows; i++){
      for (j = 0; j < cols; j++){
        a = fgetc(reader);                                                  
        if (a != '\n')
          newmaze -> cells[i][j] = a;
        else                                                               
        j--;   
        if (j >= 0){                                                        
          if (newmaze -> cells[i][j] == START){                     
            newmaze -> startRow = i;
            newmaze -> startColumn = j;
          }
          if (newmaze -> cells[i][j] == END){                           
            newmaze -> endRow = i;
            newmaze -> endColumn = j;
          }
        }
      }
    }
    fclose(reader);                                                         

    return newmaze;

}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.

  int i;
  for (i = 0; i < maze -> height; i++){
      free(maze -> cells[i]);
    }
  free(maze -> cells);
  free(maze);
  maze = NULL;

}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
  int i,j;
printf("%d %d\n", maze -> width, maze -> height);
    for (i = 0; i < maze -> height; i++){
      for (j = 0; j < maze -> width; j++){
        printf("%c", maze -> cells[i][j]);
      }
      printf("\n");
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
    
if (col < 0 || col >= maze -> width || row < 0 || row >= maze -> height){
      return 0;
    }
    if (maze -> cells[row][col] == WALL || maze -> cells[row][col] == PATH || maze -> cells[row][col] == VISITED){
      return 0;
    }
    if (col == maze -> endColumn && row == maze -> endRow){
      maze -> cells[maze -> startRow][maze -> startColumn] = START;
      return 1;
    }
    if (maze -> cells[row][col] != END){
      maze -> cells[row][col] = PATH;
    }
    if (solveMazeDFS(maze, col - 1, row)){
      return 1;
    }
    if (solveMazeDFS(maze, col, row - 1)){
      return 1;
    }
    if (solveMazeDFS(maze, col + 1, row)){
      return 1;
    }
    if (solveMazeDFS(maze, col, row + 1)){
      return 1;
    }
    if (maze -> cells[row][col] != START && maze -> cells[row][col] != END){
      maze -> cells[row][col] = VISITED;
    }

    return 0;

}
