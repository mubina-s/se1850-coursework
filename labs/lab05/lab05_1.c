/*----------------------------------------------------------------------------
-		         SE 185: Lab 05 - Conditionals (What's up?)	    	         -
-	Name: Mubina														 -
- 	Section: 1														 -
-	NetID: mubish													     -
-	Date: 02/21/2024														 -
-----------------------------------------------------------------------------*/


#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int close_to(double tolerance, double point, double value);

double magnitude(double ax, double ay, double az);

int orientation(double gx, double gy, double gz);


// Compile with gcc lab05_1.c -o lab05_1
// Run with ./ds4rd-real.exe -d 054c:05c4 -D DS4_BT -a -g -b | ./lab05_1

/*----------------------------------------------------------------------------
-								Implementation								 -
-----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    int triangle, circle, x_button, square;
    double ax, ay, az, gx, gy, gz;

    while (1)
    {
        scanf("%lf, %lf, %lf, %lf, %lf, %lf, %d, %d, %d, %d",
		&ax, &ay, &az, &gx, &gy, &gz, &triangle, &circle, &x_button, &square);
		
		if (triangle == 1){	
		exit(0);
		} else { 
		
				orientation(gx, gy, gz);
		}
		
		
        /* printf for observing values scanned in from ds4rd.exe,
         * be sure to comment or remove in final program */
        //printf("Echoing output: %lf, %lf, %lf, %lf, %lf, %lf, %d, %d, %d, %d \n",
        //ax, ay, az, gx, gy, gz, triangle, circle, x_button, square);
		
        /* It would be wise (mainly save time) if you copy your code to calculate
         * the magnitude from lab03-1.c. You will also need to copy your
         * prototypes and functions to the appropriate sections in this program. */
        //printf("The acceleration's current magnitude is: %lf\n", magnitude(ax, ay, az));
    }

    return 0;
}

/* Put your functions here, and be sure to put prototypes above. */

double magnitude(double ax, double ay, double az){
	double magnitude = sqrt(pow(ax, 2.0) + pow(ay, 2.0) + pow(az, 2.0));
	return magnitude;
}

int close_to(double tolerance, double point, double value){
	if (value <= (point + tolerance) && value >= (point - tolerance)){
		return 1; // to print orientation only 1 time
	} else {
		return 0;
	}
}

int orientation(double gx, double gy, double gz){ //used for finding the orientation
	int temp1, temp2;
	int triangle, circle, x_button, square;
    double ax, ay, az;
	scanf("%lf, %lf, %lf, %lf, %lf, %lf, %d, %d, %d, %d",
	&ax, &ay, &az, &gx, &gy, &gz, &triangle, &circle, &x_button, &square);
	
	while (close_to(0.025, 0, (magnitude(ax, ay, az))) == 1){
		
		scanf("%lf, %lf, %lf, %lf, %lf, %lf, %d, %d, %d, %d",
		&ax, &ay, &az, &gx, &gy, &gz, &triangle, &circle, &x_button, &square);

	if ((close_to(0.25, 1, gx)) == 1){
		printf("LEFT\n");
		while ((close_to(0.25, 1, gx)) != 0){
		scanf("%lf, %lf, %lf, %lf, %lf, %lf, %d, %d, %d, %d",
		&ax, &ay, &az, &gx, &gy, &gz, &triangle, &circle, &x_button, &square);
		}
	} else if ((close_to(0.25, -1, gx)) == 1){
		printf("RIGHT\n");
		while ((close_to(0.25, -1, gx)) != 0){
		scanf("%lf, %lf, %lf, %lf, %lf, %lf, %d, %d, %d, %d",
		&ax, &ay, &az, &gx, &gy, &gz, &triangle, &circle, &x_button, &square);
		}
	} else if ((close_to(0.25, 1, gy)) == 1){
		printf("TOP\n");
		while ((close_to(0.25, 1, gy)) != 0){
		scanf("%lf, %lf, %lf, %lf, %lf, %lf, %d, %d, %d, %d",
		&ax, &ay, &az, &gx, &gy, &gz, &triangle, &circle, &x_button, &square);
		}
	} else if ((close_to(0.25, -1, gy)) == 1){
		printf("BOTTOM\n");
		while ((close_to(0.25, -1, gy)) != 0){
		scanf("%lf, %lf, %lf, %lf, %lf, %lf, %d, %d, %d, %d",
		&ax, &ay, &az, &gx, &gy, &gz, &triangle, &circle, &x_button, &square);
		}
	} else if ((close_to(0.25, 1, gz)) == 1){
		printf("BACK\n");
		while ((close_to(0.25, 1, gz)) != 0){
		scanf("%lf, %lf, %lf, %lf, %lf, %lf, %d, %d, %d, %d",
		&ax, &ay, &az, &gx, &gy, &gz, &triangle, &circle, &x_button, &square);
		}
	} else if ((close_to(0.25, -1, gz)) == 1){
		printf("FRONT\n");
		while ((close_to(0.25, -1, gz)) != 0){
		scanf("%lf, %lf, %lf, %lf, %lf, %lf, %d, %d, %d, %d",
		&ax, &ay, &az, &gx, &gy, &gz, &triangle, &circle, &x_button, &square);
		}
	} 
	}
}