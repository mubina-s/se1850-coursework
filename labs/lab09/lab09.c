// Lab 09 DS4Talker 
// gcc -o lab09 lab09.c -lncurses		./ds4rd-real.exe -d 054c:05c4 -D DS4_BT -t -b -j -bt | ./lab09 wordslist-1.txt

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#define WORDLENGTH 11
#define MAXWORDS 100
#define DEBUGM 1   // Set this to 0 to disable debug output

// To make the X button work multiple times. It stores the sentence variations.
struct sentence_record{
	char sentence[80];
};

// Reads words from the file into WL and trims the whitespace off of the end
// DO NOT MODIFY THIS FUNCTION
int read_words(char* WL[MAXWORDS], char* file_name);

// modifies str to trim white space off the right side
// DO NOT MODIFY THIS FUNCTION
void trimws(char* str);

void ClearSentence(void);

int main(int argc, char* argv[]) {
	char* wordlist[MAXWORDS], *selectedWord[MAXWORDS];
	char Capital[WORDLENGTH], FirstElement[WORDLENGTH];
	int wordcount, i;
	int row = 0, col = 0, row0, col0, row1, col1;
	int t0, t, Triangle, Circle, Cross, Square, R3, L3, Options, Share, R2, L2, R1, L1, LJoyX, LJoyY, RJoyX, RJoyY;
	int Cap = 0, num = 0, words = 1000;
	struct sentence_record curr[1000];

	wordcount = read_words(wordlist, argv[1]);
	// First word was changing randomly when it was entering the while loop so I tried to store it somewhere else.
	strcpy(FirstElement, wordlist[0]);
	for (int p = 0; FirstElement[p] != '\0'; p++){
		if ((FirstElement[p] >= 97) && (FirstElement[p] <= 122)){
			FirstElement[num] = FirstElement[p];
			FirstElement[p] = '\0';
			num += 1;
		}
	}
	//read_words fills the wordlist array and then returns the number of words.
	
	initscr();

	if (DEBUGM){
		printf("Read %d words from %s \n", wordcount, argv[1]);
		for (i = 0; i < wordcount; i++, row++){
			
			if (i % 20 == 0 && i != 0){
				col += 20, row = 0;
			}
		//I moved the rest of the words 20 columns right every 20 words to achieve a better format.
			
			mvprintw(row, col, "%20s", wordlist[i]);
			refresh();
		}

		// "i" is not a local variable in the for loop so I will be able to use it in the rest of the code.
		printf("\n");
	}
	
	// most of your code goes here. Do not forget to include the ncurses library
	strcpy(curr[words].sentence, "\0");
	col += 10;
	mvprintw(row, col, "%c", '>');
	refresh();
	do{	
		while (Triangle != 0 || Circle != 0 || Cross != 0 || Square != 0 || R3 != 0 || L3 != 0){
			scanf("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d", &t, &Triangle, &Circle, &Cross, &Square, &R3, &L3, &Options, &Share, &R2, &L2, &R1, &L1, &LJoyX, &LJoyY, &RJoyX, &RJoyY);
		}
		scanf("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d", &t, &Triangle, &Circle, &Cross, &Square, &R3, &L3, &Options, &Share, &R2, &L2, &R1, &L1, &LJoyX, &LJoyY, &RJoyX, &RJoyY);
		t0 = t, row0 = row, col0 = col;
	
		if (((LJoyX > 27 && LJoyX <= 127) || (RJoyX > 27 && RJoyX <= 127)) && (col + 20 < 80)){
			col += 20, i += 20;
		} else if (((LJoyX < -28 && LJoyX >= -128) || (RJoyX < -28 && RJoyX >= -128)) && (col - 20 > 0)){
			col -= 20, i -= 20;
		} else if (((LJoyY > 27 && LJoyY <= 127) || (RJoyY > 27 && RJoyY <= 127)) && (row + 1 < 20)){
			row += 1, i += 1;
		} else if (((LJoyY < -28 && LJoyY >= -128) || (RJoyY < -28 && RJoyY >= -128)) && (row - 1 >= 0)){
			row -= 1, i -= 1;
		}
		// I updated the value of "i" each time the cursor moves. 
		// It will not get unreasonable value because I also added a border in the if statements.
		// Since there are only 20 words in a column, I added or subtract 20 when it moves along the row.
		// And when it moves along the column it will decrease or increase one unit.
		
		while (125 > (t - t0)){
			scanf("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d", &t, &Triangle, &Circle, &Cross, &Square, &R3, &L3, &Options, &Share, &R2, &L2, &R1, &L1, &LJoyX, &LJoyY, &RJoyX, &RJoyY);
		}
		
		mvprintw(row0, col0, "%c", ' ');
		refresh();
		mvprintw(row, col, "%c", '>');
		refresh();
		
		if (i != 0){
		selectedWord[i] = wordlist[i]; // selectedWord points to wordlist.
		} else if (i == 0){
		strcpy(selectedWord[i], FirstElement); // To fix the random value of the first word.
		}
		
		if (Triangle == 1){
			words -= 1;
			strcpy(curr[words].sentence, curr[words+1].sentence);
			strcat(curr[words].sentence, " ");
			if (Cap == 1){
				strcpy(Capital, selectedWord[i]);
				if ((Capital[0] >= 97) && (Capital[0] <= 122)){
					Capital[0] = Capital[0] - 32;
				}
				strcat(curr[words].sentence, Capital);
				Cap = 0;
			} else if (Cap == 0){
				strcat(curr[words].sentence, selectedWord[i]);
			}
			mvprintw(30, 0, "%s", curr[words].sentence);
			refresh();
		} else if (Circle == 1){
			Cap = 1;
		} else if (Cross  == 1 && (words < 1000)){
			words += 1;
			ClearSentence();
			mvprintw(30, 0, "%s", curr[words].sentence);
			refresh();
		} else if (Square == 1){
			words -= 1;
			strcpy(curr[words].sentence, curr[words+1].sentence);
			if (Cap == 1){
				strcpy(Capital, selectedWord[i]);
				if ((Capital[0] >= 97) && (Capital[0] <= 122)){
					Capital[0] = Capital[0] - 32;
				}
				strcat(curr[words].sentence, Capital);
				Cap = 0;
			} else if (Cap == 0){
				strcat(curr[words].sentence, selectedWord[i]);
			}
			mvprintw(30, 0, "%s", curr[words].sentence);
			refresh();
		} else if (R3 == 1 || L3 == 1){
			words = 1000;
			strcpy(curr[words].sentence, "\0");
			ClearSentence();
			mvprintw(30, 0, "%s", curr[words].sentence);
			refresh();
		} 	
		
	} while(1);
	
	return 0;
}

// DO NOT MODIFY THIS FUNCTION!
void trimws(char* str){
	int length = strlen(str);
	int x;
	if (length == 0) return;
	x = length - 1;
	while (isspace(str[x]) && (x >= 0)) {
		str[x] = '\0';
		x -= 1;
	}
}

// DO NOT MODIFY THIS FUNCTION!
int read_words(char* WL[MAXWORDS], char* file_name){
	int numread = 0;
	char line[WORDLENGTH];
	char *p;
	FILE* fp = fopen(file_name, "r");
	while (!feof(fp)) {
		p = fgets(line, WORDLENGTH, fp);
		if (p != NULL) 
		{
			trimws(line);
			WL[numread] = (char *)malloc(strlen(line) + 1);
			strcpy(WL[numread], line);
			numread++;
		}
	}
	fclose(fp);
	return numread;
}

// Clears the screen.

void ClearSentence(void){
	for (int j = 30; j < 80; j++){
		for ( int k = 0; k < 80; k++){
			mvprintw(j, k, "%c", ' ');
		}
	}
}