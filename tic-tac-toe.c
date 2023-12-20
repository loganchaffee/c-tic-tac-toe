#include <stdio.h>
#include <stdlib.h>

void resetBoard();
void printBoard();
int getFreeSpaceCount();
void playerMove();
void computerMove();
char checkForWinner();

char board[3][3];
const char PLAYER = 'X';
const char COMPUTER_PLAYER = 'O';

int main() {
  char winner = ' ';

  resetBoard();

  while (winner == ' ' && getFreeSpaceCount() > 0) {
    printBoard();

    playerMove();

    winner = checkForWinner();
    if (winner != ' ') {
      break;
    }

    if (getFreeSpaceCount() == 0) {
      break;
    }

    computerMove();

    winner = checkForWinner();
    if (winner != ' ') {
      break;
    }
  }

  printBoard();

  // For some reason the winner is set to "" after printBoard is called
  // Get the winner again here
  winner = checkForWinner();

  if (winner == PLAYER) {
    printf("Game over. You win!\n");
  } else if (winner == COMPUTER_PLAYER) {
    printf("Game over. You lose.\n");
  } else {
    printf("Game over. Draw.\n");
  }

  return 0;
}

// Sets all spaces to ' '
void resetBoard() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      board[i][j] = ' ';
    }
  }
};

// Renders the baord to the terminal
void printBoard() {
  // Clear terminal
  system("clear");

  // Print to terminal
  printf("\n   1   2   3 ");
  printf("\nA  %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
  printf("\n  ---|---|---");
  printf("\nB  %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
  printf("\n  ---|---|---");
  printf("\nC  %c | %c | %c \n\n", board[2][0], board[2][1], board[2][2]);
}

// Counts and returns the number of free spaces on the board
int getFreeSpaceCount() {
  int count = 0;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i][j] == ' ') {
        count++;
      }
    }
  }

  return count;
};

void playerMove() {
  // The the players chosen space
  char input[2];
  printf("Enter a space: ");
  scanf("%s", input);

  // Get the x coordinate as a char a-c and convert it to a integer
  char xChar = input[0];
  int x;
  switch (xChar) {
  case 'A':
  case 'a':
    x = 0;
    break;
  case 'B':
  case 'b':
    x = 1;
    break;
  case 'C':
  case 'c':
    x = 2;
    break;
  default:
    // Check for invalid y space
    printf("Invalid space");
    playerMove();
  }

  // The the y cordinate and convert it to an integer and decrement it by 1
  char yChar = input[1];
  int y = atoi(&yChar);
  y--;

  // Check for invalid x space
  if (y > 2 || y < 0) {
    printf("Invalid space");
    playerMove();
    return;
  }

  if (board[x][y] == ' ') {
    board[x][y] = PLAYER;
  } else {
    printf("That space is already taken. ");
    playerMove();
    return;
  }
};

typedef struct {
  int row;
  int col;
} Coordinates;

void computerMove() {

  // check cpu win horizontally
  for (int i = 0; i < 3; i++) {
    char currentRow[3] = {board[i][0], board[i][1], board[i][2]};
    int playerRowSpaceCount = 0;
    int cpuRowSpaceCount = 0;
    int winningColumn;
    for (int j = 0; j < 3; j++) {
      if (currentRow[j] == PLAYER) {
        playerRowSpaceCount++;
      }
      if (currentRow[j] == COMPUTER_PLAYER) {
        cpuRowSpaceCount++;
      }
      if (currentRow[j] == ' ') {
        winningColumn = j;
      }
    }
    if (cpuRowSpaceCount == 2 && playerRowSpaceCount == 0) {
      board[i][winningColumn] = COMPUTER_PLAYER;
      return;
    }
  }
  // Check for a possible player win horizontally
  for (int i = 0; i < 3; i++) {
    char currentRow[3] = {board[i][0], board[i][1], board[i][2]};
    int playerRowSpaceCount = 0;
    int cpuRowSpaceCount = 0;
    int winningColumn;
    for (int j = 0; j < 3; j++) {
      if (currentRow[j] == PLAYER) {
        playerRowSpaceCount++;
      }
      if (currentRow[j] == COMPUTER_PLAYER) {
        cpuRowSpaceCount++;
      }
      if (currentRow[j] == ' ') {
        winningColumn = j;
      }
    }
    if (playerRowSpaceCount == 2 && cpuRowSpaceCount == 0) {
      board[i][winningColumn] = COMPUTER_PLAYER;
      return;
    }
  }

  // Check for a possible cpu win vertically
  for (int i = 0; i < 3; i++) {
    char currentColumn[3] = {board[0][i], board[1][i], board[2][i]};
    int playerRowSpaceCount = 0;
    int cpuRowSpaceCount = 0;
    int winningRow;
    for (int j = 0; j < 3; j++) {
      if (currentColumn[j] == PLAYER) {
        playerRowSpaceCount++;
      }
      if (currentColumn[j] == COMPUTER_PLAYER) {
        cpuRowSpaceCount++;
      }
      if (currentColumn[j] == ' ') {
        winningRow = j;
      }
    }
    if (cpuRowSpaceCount == 2 && playerRowSpaceCount == 0) {
      board[winningRow][i] = COMPUTER_PLAYER;
      return;
    }
  }
  // Check for a possible player win vertically
  for (int i = 0; i < 3; i++) {
    char currentColumn[3] = {board[0][i], board[1][i], board[2][i]};
    int playerRowSpaceCount = 0;
    int cpuRowSpaceCount = 0;
    int winningRow;
    for (int j = 0; j < 3; j++) {
      if (currentColumn[j] == PLAYER) {
        playerRowSpaceCount++;
      }
      if (currentColumn[j] == COMPUTER_PLAYER) {
        cpuRowSpaceCount++;
      }
      if (currentColumn[j] == ' ') {
        winningRow = j;
      }
    }
    if (playerRowSpaceCount == 2 && cpuRowSpaceCount == 0) {
      board[winningRow][i] = COMPUTER_PLAYER;
      return;
    }
  }

  // check cpu win
  {
    int i = 0;
    int j = 0;
    int playerRowSpaceCount = 0;
    int cpuRowSpaceCount = 0;
    while (i < 3) {
      int winningRow;
      int winningColumn;
      if (board[i][j] == PLAYER) {
        playerRowSpaceCount++;
      }
      if (board[i][j] == COMPUTER_PLAYER) {
        cpuRowSpaceCount++;
      }
      if (board[i][j] == ' ') {
        winningRow = i;
        winningColumn = j;
      }
      i++;
      j++;
      if (i >= 3) {
        if (cpuRowSpaceCount == 2 && playerRowSpaceCount == 0) {
          board[winningRow][winningColumn] = COMPUTER_PLAYER;
          return;
        }
      }
    }
  }
  // Check for possible player win diagonally
  {

    int i = 0;
    int j = 0;
    int playerRowSpaceCount = 0;
    int cpuRowSpaceCount = 0;
    while (i < 3) {
      int winningRow;
      int winningColumn;
      if (board[i][j] == PLAYER) {
        playerRowSpaceCount++;
      }
      if (board[i][j] == COMPUTER_PLAYER) {
        cpuRowSpaceCount++;
      }
      if (board[i][j] == ' ') {
        winningRow = i;
        winningColumn = j;
      }
      i++;
      j++;
      if (i >= 3) {
        if (playerRowSpaceCount == 2 && cpuRowSpaceCount == 0) {
          board[winningRow][winningColumn] = COMPUTER_PLAYER;
          return;
        }
      }
    }
  }

  // check cpu win diagonally
  {
    int playerRowSpaceCount = 0;
    int cpuRowSpaceCount = 0;
    int i = 0;
    int j = 2;
    while (i < 3) {
      int winningRow;
      int winningColumn;
      if (board[i][j] == PLAYER) {
        playerRowSpaceCount++;
      }
      if (board[i][j] == COMPUTER_PLAYER) {
        cpuRowSpaceCount++;
      }
      if (board[i][j] == ' ') {
        winningRow = i;
        winningColumn = j;
      }
      i++;
      j--;
      if (i >= 3) {
        if (cpuRowSpaceCount == 2 && playerRowSpaceCount == 0) {
          board[winningRow][winningColumn] = COMPUTER_PLAYER;
          return;
        }
      }
    }
  }

  // check player win diagonally
  {
    int playerRowSpaceCount = 0;
    int cpuRowSpaceCount = 0;
    int i = 0;
    int j = 2;
    while (i < 3) {
      int winningRow;
      int winningColumn;
      if (board[i][j] == PLAYER) {
        playerRowSpaceCount++;
      }
      if (board[i][j] == COMPUTER_PLAYER) {
        cpuRowSpaceCount++;
      }
      if (board[i][j] == ' ') {
        winningRow = i;
        winningColumn = j;
      }
      i++;
      j--;
      if (i >= 3) {
        if (playerRowSpaceCount == 2 && cpuRowSpaceCount == 0) {
          board[winningRow][winningColumn] = COMPUTER_PLAYER;
          return;
        }
      }
    }
  }

  // If we've made it this far there is no winning. Just pick randomly
  int row = 0;
  int col = 0;
  do {
    row = rand() % 3;
    col = rand() % 3;
  } while (board[row][col] != ' ');

  board[row][col] = COMPUTER_PLAYER;
};

// Returns character of winner or space if no winner
char checkForWinner() {
  char w = ' ';

  // Check rows and columns
  for (int i = 0; i < 3; i++) {
    if (board[i][0] == board[i][1] && board[i][1] == board[i][2] &&
        board[i][0] != ' ') {
      w = board[i][0]; // Winner in the current row
    }

    if (board[0][i] == board[1][i] && board[1][i] == board[2][i] &&
        board[0][i] != ' ') {
      w = board[0][i]; // Winner in the current column
    }
  }

  // Check diagonals
  if (board[0][0] == board[1][1] && board[1][1] == board[2][2] &&
      board[0][0] != ' ') {
    w = board[0][0]; // Winner in the main diagonal
  }

  if (board[0][2] == board[1][1] && board[1][1] == board[2][0] &&
      board[0][2] != ' ') {
    w = board[0][2]; // Winner in the other diagonal
  }

  return w; // No winner yet
};
