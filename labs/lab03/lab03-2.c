/*----------------------------------------------------------------------------
- SE 185: Lab 03 - Introduction to the DS4 and Functions -
- Name:Mubina
-
- Section:1
-
- NetID:mubish
-
- Date:02.06.2024
-
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>

int numButtons (int button1, int button2, int button3, int button4);
int main(int argc, char *argv[])
{ int button1, button2, button3, button4;

while (1)
{
	scanf("%d, %d, %d, %d", &button1, &button2, &button3, &button4);
printf("The number of button pessed :%d\n", numButtons(button1, button2, button3, button4));
}
return 0;
}
int numButtons(int button1, int button2, int button3, int button4){
	int numButtons=(button1+button2+button3+button4);
	return numButtons;
}

