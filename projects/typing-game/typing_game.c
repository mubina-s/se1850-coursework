#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define BOARD_WIDTH 60
#define BOARD_HEIGHT 10
#define MAX_WORDS 100
#define INITIAL_DELAY 1000

char board[BOARD_HEIGHT][BOARD_WIDTH];
char words[MAX_WORDS][50];
int numWords;

// Function to read words from file into an array
void readWordsFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        exit(1);
    }

    numWords = 0;
    while (fgets(words[numWords], sizeof(words[numWords]), file) != NULL) {
        words[numWords][strcspn(words[numWords], "\n")] = '\0'; // Remove newline
        numWords++;
        if (numWords >= MAX_WORDS) {
            break; // Reached maximum words
        }
    }

    fclose(file);
}

// Function to add a word to the board at a random x position on the top row
void addWordToBoard(const char *word) {
    int wordLength = strlen(word);
    int startX = rand() % (BOARD_WIDTH - wordLength + 1); // Random start position

    // Place the word on the top row of the board
    for (int i = 0; i < wordLength; i++) {
        board[0][startX + i] = word[i];
    }
}

// Function to move every word down one row on the board
void moveWordsDown() {
    for (int row = BOARD_HEIGHT - 1; row > 0; row--) {
        for (int col = 0; col < BOARD_WIDTH; col++) {
            board[row][col] = board[row - 1][col];
        }
    }
    // Clear the top row after moving words down
    memset(board[0], ' ', BOARD_WIDTH);
}

// Function to display the game board
void displayBoard() {
    system("clear"); // Clear the terminal

    printf("Welcome to the Typing Game!\n");
    printf("Type the words as they reach the bottom.\n\n");

    for (int row = 0; row < BOARD_HEIGHT; row++) {
        for (int col = 0; col < BOARD_WIDTH; col++) {
            putchar(board[row][col]);
        }
        putchar('\n');
    }
}

// Function to check if a word is on the board
int isWordOnBoard(const char *word) {
    for (int row = 0; row < BOARD_HEIGHT; row++) {
        for (int col = 0; col < BOARD_WIDTH; col++) {
            if (strncmp(&board[row][col], word, strlen(word)) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    srand(time(NULL)); // Seed the random number generator
    readWordsFromFile("wordList.txt"); // Read words from file

    memset(board, ' ', sizeof(board)); // Initialize the game board

    printf("Hello, this is a typing game. You will need to type the words as they appear.\n");
    printf("Would you like to play or add a word?\n");

    char choice;
    printf("You currently have %d words that can be used. (p/w)\n", numWords);
    scanf(" %c", &choice);

    if (choice == 'w') {
        // Add a word to the text file
        char newWord[50];
        printf("What word would you like to add? ");
        scanf("%s", newWord);

        FILE *file = fopen("wordList.txt", "a");
        if (file == NULL) {
            fprintf(stderr, "Error opening file for appending.\n");
            return 1;
        }

        fprintf(file, "%s\n", newWord);
        fclose(file);

        printf("Word added successfully!\n");
        return 0;
    } else if (choice != 'p') {
        printf("Invalid choice. Exiting...\n");
        return 1;
    }

    printf("What would you like your minimum word length to be? ");
    int min_length;
    scanf("%d", &min_length);

    //printf("Press Enter to start the game...\n");
    //getchar(); // Wait for Enter key
   // getchar(); // Consume the newline character

    int delay = INITIAL_DELAY;
    int timeSinceLastInput = 0;
    int score = 0;
    time_t startTime = time(NULL);

    while (1) {
        displayBoard(); // Display the game board

        int numNewWords = timeSinceLastInput / 1000; // Number of new words based on time delay

        for (int i = 0; i < numNewWords; i++) {
            if (numWords > 0) {
                addWordToBoard(words[rand() % numWords]); // Add a random word to the board
            }
        }

        moveWordsDown(); // Move every word down one row

        char userInput[50];
        scanf("%s", userInput);

        if (isWordOnBoard(userInput)) {
            // Word typed correctly, remove it from the board
            for (int row = 0; row < BOARD_HEIGHT; row++) {
                for (int col = 0; col < BOARD_WIDTH; col++) {
                    if (strncmp(&board[row][col], userInput, strlen(userInput)) == 0) {
                        memset(&board[row][col], ' ', strlen(userInput));
                        score += strlen(userInput); // Increase score
                    }
                }
            }
        }

        // Check if any word has reached the bottom of the board
                for (int col = 0; col < BOARD_WIDTH; col++) {
            if (board[BOARD_HEIGHT - 1][col] != ' ') {
                printf("Game over! A word has reached the bottom of the board.\n");
                break;
            }
        }

        // Adjust delay and time since last input
        delay -= 50; // Decrease delay over time
        if (delay < 100) {
            delay = 100; // Minimum delay
        }
        timeSinceLastInput += delay;

        // Sleep for a short interval to control game speed
        usleep(100000); // Sleep for 0.1 seconds (100,000 microseconds)
    }

    // Calculate game duration
    time_t endTime = time(NULL);
    int gameDuration = (int)(endTime - startTime);

    printf("Game over! Your score: %d\n", score);
    printf("Time played: %d seconds\n", gameDuration);

    return 0;
}
