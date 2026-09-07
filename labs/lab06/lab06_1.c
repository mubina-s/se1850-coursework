/*----------------------------------------------------------------------------
-		                    SE 185: Lab 06 - Bop-It!	    	             -
-	Name: 		Mubina Sadriddinova												 -
- 	Section:			1												 -
-	NetID:		mubish@iastate.edu											     -
-	Date:	03.02.2024												 -
-----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
-								Includes									 -
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*----------------------------------------------------------------------------
-	                            Prototypes                                   -
-----------------------------------------------------------------------------*/
void Bop_ItGame(int t, int triangle, int circle, int cross, int square);

/*----------------------------------------------------------------------------
-	                            Notes                                        -
-----------------------------------------------------------------------------*/
// Compile with gcc lab06_1.c -o lab06_1
// Run with ./ds4rd-real.exe -d 054c:05c4 -D DS4_BT -t -b | ./lab06_1.exe

/*----------------------------------------------------------------------------
-								Implementation								 -
-----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    srand(time(NULL)); // for a random game each time.
	
	int t, triangle, circle, cross, square;

	printf("This is a Bop-It Game!\n");
	printf("Please press the Circle Button to begin!\n\n");
	
	while (1){
		scanf("%d, %d, %d, %d, %d", &t, &triangle, &circle, &cross, &square);
	
		if (circle == 1){
			while (triangle == 1 || circle == 1 || cross == 1 || square == 1){ // to rundomize the buttons 
				scanf("%d, %d, %d, %d, %d", &t, &triangle, &circle, &cross, &square);
			}
			Bop_ItGame(t, triangle, circle, cross, square);
		}	
	}
	
    return 0;
}


void Bop_ItGame(int t, int triangle, int circle, int cross, int square){
		
		int limit[25];
		for (int i = 0; i < 25; i++){
			limit[i] = 2500 - (i * 100);
		}

		for (int n = 0; n < 25; n++){
		scanf("%d, %d, %d, %d, %d", &t, &triangle, &circle, &cross, &square);
		int t0 = t;
		int num = rand()% 4;
		
		//for randomized buttons to be pressed used while and for functions here 
			if (num == 0){
				printf("Press the triangle button!\nYou have %d milliseconds to respond!\n\n", limit[n]);
					while (triangle == 1 || circle == 1 || cross == 1 || square == 1){
						scanf("%d, %d, %d, %d, %d", &t, &triangle, &circle, &cross, &square);
					}				
				while (limit[n] > (t - t0)){
				scanf("%d, %d, %d, %d, %d", &t, &triangle, &circle, &cross, &square);
				if (triangle == 1){
					break;
				} else if (circle == 1 || cross == 1 || square == 1){
				printf("Wrong button! :(\nYou lose!\nYou made it through %d rounds!\n", n);
					exit(0);
				}
				}
				if (limit[n] < (t - t0)){
				printf("You ran out of time. :(\nThanks for playing!\nYou made it through %d rounds!\n", n);
					exit(0);
				}	
			} else if (num == 1){
				printf("Press the circle button!\nYou have %d milliseconds to respond!\n\n", limit[n]);
					while (triangle == 1 || circle == 1 || cross == 1 || square == 1){
						scanf("%d, %d, %d, %d, %d", &t, &triangle, &circle, &cross, &square);
					}				
				while (limit[n] > (t - t0)){
				scanf("%d, %d, %d, %d, %d", &t, &triangle, &circle, &cross, &square);
				if (circle == 1){
					break;
				} else if (triangle == 1 || cross == 1 || square == 1){
				printf("Wrong button! :(\nYou lose!\nYou made it through %d rounds!\n", n);
					exit(0);
				}
				}				
				if (limit[n] < (t - t0)){
				printf("You ran out of time. :(\nThanks for playing!\nYou made it through %d rounds!\n", n);
					exit(0);
				}	
			} else if (num == 2){
				printf("Press the cross button!\nYou have %d milliseconds to respond!\n\n", limit[n]);
					while (triangle == 1 || circle == 1 || cross == 1 || square == 1){
						scanf("%d, %d, %d, %d, %d", &t, &triangle, &circle, &cross, &square);
					}				
				while (limit[n] > (t - t0)){
				scanf("%d, %d, %d, %d, %d", &t, &triangle, &circle, &cross, &square);
				if (cross == 1){
					break;
				} else if (triangle == 1 || circle == 1 || square == 1){
				printf("Wrong button! :(\nYou lose!\nYou made it through %d rounds!\n", n);
				exit(0);
				}
				}				
				if (limit[n] < (t - t0)){
				printf("You ran out of time. :(\nThanks for playing!\nYou made it through %d rounds!\n", n);
					exit(0);
				}	
			} else if (num == 3){
				printf("Press the square button!\nYou have %d milliseconds to respond!\n\n", limit[n]);
					while (triangle == 1 || circle == 1 || cross == 1 || square == 1){
						scanf("%d, %d, %d, %d, %d", &t, &triangle, &circle, &cross, &square);
					}				
				while (limit[n] > (t - t0)){
					scanf("%d, %d, %d, %d, %d", &t, &triangle, &circle, &cross, &square);
					if (square == 1){
						break;
					} else if (triangle == 1 || circle == 1 || cross == 1){
					printf("Wrong button! :(\nYou lose!\nYou made it through %d rounds!\n", n);
						exit(0);
					}
					}
				if (limit[n] < (t - t0)){
				printf("You ran out of time. :(\nThanks for playing!\nYou made it through %d rounds!\n", n);
					exit(0);
				}
			}
		}
}