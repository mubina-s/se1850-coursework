/*-----------------------------------------------------------------------------
- SE 185 Lab 07 - The DS4 Equalizer
- Developed for 185-Rursch by T.Tran and K.Wang
- Name: Mubina S.
- Section:1
- NetID:mubish
- Date: 3/25/2024
-
- This file provides the outline for your program
- Please implement the functions given by the prototypes below and
- complete the main function to make the program complete.
- You must implement the functions which are prototyped below exactly
- as they are requested.
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
- Includes
-----------------------------------------------------------------------------*/
// run with ./ds4rd-real.exe -d 054c:05c4 -D DS4_BT -t -g -b -j | ./lab7

#include <stdio.h>
#include <math.h>

/*-----------------------------------------------------------------------------
-								Defines
-----------------------------------------------------------------------------*/
#define PI 3.141592653589

/* NO GLOBAL VARIABLES ALLOWED */

/*-----------------------------------------------------------------------------
-								Prototypes
-----------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------
    PRE: Arguments must point to double variables or int variables as appropriate
    This function scans a line of DS4 data, and returns
    True when left button is pressed
    False Otherwise
    POST: it modifies its arguments to return values read from the input line.
------------------------------------------------------------------------------------*/
int read_input( int* time,
                double* g_x, double* g_y, double* g_z,
                int* button_T, int* button_C, int* button_X, int* button_S,
                int* l_joy_x, int* l_joy_y, int* r_joy_x, int* r_joy_y );

/*-----------------------------------------------------------------------------
    PRE: ~(-1.0) <= mag <= ~(1.0)
    This function scales the roll/pitch value to fit on the screen.
    Input should be capped at either -1.0 or 1.0 before the rest of your
    conversion.
    POST: -39 <= return value <= 39
-----------------------------------------------------------------------------*/
double scaleMagForScreen(double rad); // 

/*-----------------------------------------------------------------------------
    PRE: -128 <= mag <= 127
    This function scales the joystick value to fit on the screen.
    POST: -39 <= return value <= 39
-----------------------------------------------------------------------------*/
double scaleJoyForScreen(double rad);

/*----------------------------------------------------------------------------
    PRE: -39 <= number <= 39
    Uses print_chars to graph a number from -39 to 39 on the screen.
    You may assume that the screen is 80 characters wide.
----------------------------------------------------------------------------*/
void graph_line(double number);

/*-----------------------------------------------------------------------------
    PRE: num >= 0
    This function prints the character "use" to the screen "num" times
    This function is the ONLY place printf is allowed to be used
    POST: nothing is returned, but "use" has been printed "num" times
-----------------------------------------------------------------------------*/
void print_chars(double num, char use);


/*-----------------------------------------------------------------------------
-								Implementation
-----------------------------------------------------------------------------*/
int main()
{
    double x, y, z;                     /* Values of x, y, and z axis*/
    int t;                              /* Variable to hold the time value */
    int b_Up, b_Down, b_Left, b_Right;  /* Variables to hold the button statuses */
    int j_LX, j_LY, j_RX, j_RY;         /* Variables to hold the joystick statuses */
    int scaled_pitch, scaled_roll; 	    /* Value of the roll/pitch adjusted to fit screen display */
    int scaled_joy;                     /* Value of joystick adjusted to fit screen display */
	
    /* Put pre-loop preparation code here */
	
	int i;
	
    do
    {
	/* Scan a line of input */
	read_input(&t, &x, &y, &z, &b_Up, &b_Right, &b_Down, &b_Left, &j_LX, &j_LY, &j_RX, &j_RY);
	
	/* Calculate and scale for pitch AND roll AND joystick */	
	scaled_roll = scaleMagForScreen(x);
	scaled_pitch = scaleMagForScreen(y);
	scaled_joy = scaleJoyForScreen(j_LX);

	/* Switch between roll, pitch, and joystick with the up, down, and right button, respectivly */
		
	if (b_Up){
		i = 0;
	} else if (b_Down){
		i = 1;	
	} else if (b_Left){
		i = 2;	
	}
		
	/* Output your graph line */
	
	if(i == 0){
		graph_line(scaled_roll);
	} else if (i == 1){
		graph_line(scaled_pitch);
	} else if (i == 2){
		graph_line(scaled_joy);
	}

	fflush(stdout);

    } while (!b_Right); /* Modify to stop when left button is pressed */

    return 0;

}


int read_input( int* time, double* g_x, double* g_y, double* g_z,int* button_T, int* button_C, int* button_X, int* button_S,int* l_joy_x, int* l_joy_y, int* r_joy_x, int* r_joy_y ){
	
	scanf("%d, %lf, %lf, %lf, %d, %d, %d, %d, %d, %d, %d, %d", time, g_x, g_y, g_z, button_T, button_C, button_X, button_S , l_joy_x, l_joy_y, r_joy_x, r_joy_y);
	
	return *button_S;
}

/*-----------------------------------------------------------------------------
    PRE: ~(-1.0) <= mag <= ~(1.0)
    This function scales the roll/pitch value to fit on the screen.
    Input should be capped at either -1.0 or 1.0 before the rest of your
    conversion.
    POST: -39 <= return value <= 39
-----------------------------------------------------------------------------*/

double scaleMagForScreen(double rad){
	
	if (rad < -1.0){
		rad = -1.0;
	} else if (rad > 1.0){
		rad = 1.0;
	}
	
	double temp = rad * 39;
	
	return temp;
}

/*-----------------------------------------------------------------------------
    PRE: -128 <= mag <= 127
    This function scales the joystick value to fit on the screen.
    POST: -39 <= return value <= 39
	
-----------------------------------------------------------------------------*/

double scaleJoyForScreen(double rad){
	if( rad < -128.0){
		rad = -128.0;
	} else if (rad > 127.0){
		rad = 127.0;
	}
	
	double temp = rad / 127.0;
	
	temp = temp * 39;
	
	return -temp;
	
}

/*-----------------------------------------------------------------------------
    PRE: num >= 0
    This function prints the character "use" to the screen "num" times
    This function is the ONLY place printf is allowed to be used
    POST: nothing is returned, but "use" has been printed "num" times
-----------------------------------------------------------------------------*/

void print_chars(double num, char use){
	for( int a = 1; a <= num; a++){
		printf("%c", use);
	}
}

/*----------------------------------------------------------------------------
    PRE: -39 <= number <= 39
    Uses print_chars to graph a number from -39 to 39 on the screen.
    You may assume that the screen is 80 characters wide.
----------------------------------------------------------------------------*/
void graph_line(double number){
	if( number == 0.0){
		print_chars(40, ' ');
		print_chars(1, '0');
	} else if (number < 0.0 && number >= -39.0){
		print_chars(40, ' ');
	  print_chars(-number, 'R');
	} else if (number > 0.0 && number <= 39.0){
	  print_chars(40 - number, ' ');
	  print_chars(number, 'L');
	}
	printf("\n");
}