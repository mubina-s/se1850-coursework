/*----------------------------------------------------------------------------
- SE 185: Lab 03 - Introduction to the DS4 and Functions -
- Name:Mubina
-
- Section:1
-
- NetID:mubish
-
- Date:02.12.2024
-
-----------------------------------------------------------------------------*/

#include <stdio.h>
#include <math.h>

double magnitude(double x, double y, double z);
int minutes (int t);
int seconds (int t);
int milliseconds (int t);

int main(int argc, char *argv[]) {
	int t;
double ax, ay, az;
while (1)
{
scanf("%d, %lf, %lf, %lf", &t, &ax, &ay, &az);

printf("Echoing output: %8.3d, %7.4lf, %7.4lf, %7.4lf\n", t/1000, ax, ay, az);

printf("At %d ms, the acceleration's magnitude was: %lf\n", t,
magnitude(ax, ay, az));


printf("At %d minutes, %d seconds, and %d milliseconds it was: %lf\n",
minutes(t), seconds(t), milliseconds(t), magnitude(ax, ay, az));

}
return 0;
}


int minutes (int t) {
int minutes = ((t/60000));
return minutes; 
}
int seconds (int t){
	int seconds= ((t/1000)%60);
	return seconds;
}
int milliseconds (int t){
	int milliseconds=(t%1000);
return milliseconds;
}

/**
* Calculates and returns the magnitude of three given values.
*
* @param x - The x-axis scanned values from the DS4 controller.
* @param y - The y-axis scanned values from the DS4 controller.
* @param z - The z-axis scanned values from the DS4 controller.
* @return - The magnitude of the given values.
*/
double magnitude(double x, double y, double z)
{ double magnitude= (pow(x,2.0)+ pow (y,2.0)+ pow(z, 2.0));
 return sqrt( magnitude);
}