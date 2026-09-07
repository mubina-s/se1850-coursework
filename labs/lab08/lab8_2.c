/*-----------------------------------------------------------------------------
-					  		SE 185 Lab 08
-             Developed for 185-Rursch by T.Tran and K.Wang
-	Name: Mubina S.
-	Section:1
-	NetID: mubish
-	Date: April 1, 2024 year
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
-								Includes
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include <ncurses/ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

/*-----------------------------------------------------------------------------
-								Defines
-----------------------------------------------------------------------------*/
//Mathmatical constants 
#define PI 3.14159

/* 	Screen geometry
    Use ROWS and COLUMNS for the screen height and width (set by system)
    MAXIMUMS */
#define COLUMNS 100
#define ROWS 80

/* 	Character definitions taken from the ASCII table */
#define AVATAR 'A'
#define WALL '*'
#define EMPTY_SPACE ' '

/*	Number of samples taken to form an moving average for the gyroscope data
    Feel free to tweak this. */
#define NUM_SAMPLES 10


/*-----------------------------------------------------------------------------
-								Static Data
-----------------------------------------------------------------------------*/
/* 2D character array which the maze is mapped into */
char MAZE[COLUMNS][ROWS];


/*-----------------------------------------------------------------------------
-								Prototypes
-----------------------------------------------------------------------------*/
/*	POST: Generates a random maze structure into MAZE[][]
    You will want to use the rand() function and maybe use the output %100.
    You will have to use the argument to the command line to determine how
    difficult the maze is (how many maze characters are on the screen). */
void generate_maze(int difficulty);

/*	PRE: MAZE[][] has been initialized by generate_maze()
    POST: Draws the maze to the screen */
void draw_maze(void);

/*	PRE: 0 < x < COLUMNS, 0 < y < ROWS, 0 < use < 255
    POST: Draws character use to the screen and position x,y */
void draw_character(int x, int y, char use);

/*	PRE: -1.0 < mag < 1.0
    POST: Returns tilt magnitude scaled to -1.0 -> 1.0
    You may want to reuse the roll function written in previous labs. */
double calc_roll(double mag);

/* 	Updates the buffer with the new_item and returns the computed
    moving average of the updated buffer */
double m_avg(double buffer[], int avg_size, double new_item);

void delay(int delay, int t0, int t, double x, double y, double z);
/*
gcc -o lab8_2 lab8_2.c -lncurses
./ds4rd.exe -d 054c:05c4 -D DS4_USB -t -g | ./lab8_2
*/
/*-----------------------------------------------------------------------------
-								Implementation
-----------------------------------------------------------------------------*/
/*	Main - Run with './ds4rd-real.exe -t -g -b' piped into STDIN */
void main(int argc, char* argv[])
{	
	double x[NUM_SAMPLES], y[NUM_SAMPLES], z[NUM_SAMPLES];
	double new_x, new_y, new_z;
	double avg_x, avg_y, avg_z;
	int t, t0, difficulty, lose, q, p;
	int row = 0;
	int	col = COLUMNS / 2;
	int a = 0, b = 0;
	
	sscanf(argv[1], "%d", &difficulty );
	
  if (argc != 2)
  {
      printw("You must enter the difficulty level on the command line.");
      refresh();
      return;
  }
  
  else
  {
    /* 	Setup screen for Ncurses
        The initscr functionis used to setup the Ncurses environment
        The refreash function needs to be called to refresh the outputs
        to the screen */
    initscr();
    refresh();

    /* WEEK 2 Generate the Maze */
	generate_maze(difficulty);
	draw_maze();
    /* Read gyroscope data and fill the buffer before continuing */
	    for(int i = 0; i < NUM_SAMPLES; i++)
    {
        scanf("%d, %lf, %lf, %lf", &t,  &new_x, &new_y, &new_z);
        x[i] = new_x;
    }
    /* Event loop */
	draw_character(col, row, AVATAR);
    do
    {	
        /* Read data, update average */
		scanf("%d, %lf, %lf, %lf", &t, &new_x, &new_y, &new_z);
		t0 = t;
        avg_x = m_avg(x, NUM_SAMPLES, new_x);
		
        /* Is it time to move?  if so, then move avatar */
		
		if (MAZE[col][row+1] != WALL){
			scanf("%d, %lf, %lf, %lf", &t, &new_x, &new_y, &new_z);
			avg_x = m_avg(x, NUM_SAMPLES, new_x);
			if ((avg_x < -0.1) && (MAZE[col+1][row+1] != WALL)){
				delay(500 ,t0, t, new_x, new_y, new_z);
				draw_character(col, row, EMPTY_SPACE);
				col += 1, row += 1;
				draw_character(col, row, AVATAR);
			} else if ((avg_x > 0.1) && (MAZE[col-1][row+1] != WALL)){
				delay(500 ,t0, t, new_x, new_y, new_z);
				draw_character(col, row, EMPTY_SPACE);
				col -= 1, row += 1;
				draw_character(col, row, AVATAR);
			} else {
				delay(500 ,t0, t, new_x, new_y, new_z);
				draw_character(col, row, EMPTY_SPACE);
				row += 1;
				draw_character(col, row, AVATAR);
			}
		} else if (MAZE[col][row+1] == WALL){
			if ((MAZE[col+1][row] == WALL) && (MAZE[col-1][row] == WALL)){
				delay(500, t0, t, new_x, new_y, new_z);
				draw_character(col, row, EMPTY_SPACE);
				draw_character(col, row, AVATAR);
				delay(1000 ,t0, t, new_x, new_y, new_z);
				lose = 1;
				break;
			} else if((MAZE[col+1][row] != WALL) || (MAZE[col-1][row] != WALL)){
					int i = 0, j = 0;
					while (MAZE[col+i][row] != WALL){
						if (MAZE[col+i][row+1] != WALL){
							lose = 0;
							break;
						} else if (MAZE[col+i][row+1] == WALL){
							while (MAZE[col-j][row] != WALL){
								if (MAZE[col-j][row+1] != WALL){
									lose = 0;
									break;
								} else if (MAZE[col-j][row+1] == WALL){
									lose = 2;
								}
								j += 1;
							}
						}
						i += 1;
					}
					if (lose == 2){
					delay(500, t0, t, new_x, new_y, new_z);
					draw_character(col, row, EMPTY_SPACE);
					draw_character(col, row, AVATAR);
					delay(1000 ,t0, t, new_x, new_y, new_z);
					lose = 2;
					break;
					} else if (lose != 2){
						scanf("%d, %lf, %lf, %lf", &t, &new_x, &new_y, &new_z);
						avg_x = m_avg(x, NUM_SAMPLES, new_x);
						if ((avg_x < -0.1) && (MAZE[col+1][row] != WALL)){
							delay(500 ,t0, t, new_x, new_y, new_z);
							draw_character(col, row, EMPTY_SPACE);
							col += 1;
							draw_character(col, row, AVATAR);
						} else if ((avg_x > 0.1) && (MAZE[col-1][row] != WALL)){
							delay(500 ,t0, t, new_x, new_y, new_z);
							draw_character(col, row, EMPTY_SPACE);
							col -= 1;
							draw_character(col, row, AVATAR);
						} else {
							delay(500 ,t0, t, new_x, new_y, new_z);
							draw_character(col, row, EMPTY_SPACE);
							draw_character(col, row, AVATAR);
						}
					}
			}
		}
				
					
			

		
    } while(row < ROWS); // Change this to end game at right time

    /* Print the win message */
	
    /* This function is used to cleanup the Ncurses environment.
    Without it, the characters printed to the screen will persist
    even after the progam terminates */
    endwin();
	
	}
	
	if (lose == 2){
		printf("There is no chance you can win this!\nGAME OVER! YOU LOST!\n");
	} else if (lose == 1){
		printf("You have nowhere to move!\nGAME OVER! YOU LOST!\n");
	} else if (lose == 0){
		printf("YOU WIN!\n");
	}
}


double m_avg(double buffer[], int avg_size, double new_item)
{
	double sum_items = 0;
	
	for(int i = 0; i < avg_size - 1; i++){
		buffer[i] = buffer[i+1];
	}
	
	buffer[avg_size-1] = new_item;
	
	for (int j = 0; j < avg_size; j++){
		sum_items = buffer[j] + sum_items;
	}
	
	sum_items = sum_items / avg_size;
	
    return sum_items;	
}


/* 	PRE: 0 < x < COLUMNS, 0 < y < ROWS, 0 < use < 255
    POST: Draws character use to the screen and position x,y
    THIS CODE FUNCTIONS FOR PLACING THE AVATAR AS PROVIDED.
    DO NOT NEED TO CHANGE THIS FUNCTION. */
void draw_character(int x, int y, char use)
{
    mvaddch(y,x,use);
    refresh();
}

void generate_maze(int difficulty){
	srand(time(NULL));
	for (int i = 1; i < ROWS; i++){
		MAZE[0][i] = WALL, MAZE[99][i] = WALL;
		for (int j = 0; j < difficulty; j++){
			MAZE[rand() % 100][i] = WALL;
		}
	}
}

void draw_maze(void){
	for (int i = 1; i < ROWS; i++){
		for (int j = 0; j < COLUMNS; j++){
			if(MAZE[j][i] == WALL){
				draw_character(j, i, WALL);
			}
		}
	}
}

void delay(int delay, int t0, int t, double x, double y, double z){
	scanf("%d, %lf, %lf, %lf", &t, &x, &y, &z);
		while (delay > (t - t0)){
			scanf("%d, %lf, %lf, %lf", &t, &x, &y, &z);
		}
}