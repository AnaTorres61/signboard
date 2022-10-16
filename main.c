#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define TEXT_LENGTH 100
#define TEXT_DISPLAY_LENGTH 300
#define DISPLAY_LENGTH 8

char displayLine[TEXT_DISPLAY_LENGTH];
char letterLine[TEXT_DISPLAY_LENGTH];

void printDisplayLetter(char *segments, int lineIndex, int letterIndex, int origin) {
  char activeSegments[4];

  switch (lineIndex) {
    case 0:
      sprintf(activeSegments, " %c ", segments[0] == '1' ? '-' : ' ');
      break;
    case 1:
      sprintf(activeSegments, "%c %c", segments[5] == '1' ? '|' : ' ', segments[1] == '1' ? '|' : ' ');
      break;
    case 2:
      sprintf(activeSegments, " %c ", segments[6] == '1' ? '-' : ' ');
      break;
    case 3:
      sprintf(activeSegments, "%c %c", segments[4] == '1' ? '|' : ' ', segments[2] == '1' ? '|' : ' ');
      break;
    case 4:
      sprintf(activeSegments, " %c ", segments[3] == '1' ? '-' : ' ');
  }

  if (letterIndex != origin)
    strcat(displayLine, " ");
  
  strcat(displayLine, activeSegments);
}

void getLetterSegments(char letter, int lineIndex, int letterIndex, int origin) {
  char letterSegments[8];

  switch (letter) {
    case 'A':
      sprintf(letterSegments, "1110111");
      break;
    case 'B':
      sprintf(letterSegments, "0011111");
      break;
    case 'C':
      sprintf(letterSegments, "1001110");
      break;
    case 'D':
      sprintf(letterSegments, "0111101");
      break;
    case 'E':
      sprintf(letterSegments, "1001111");
      break;
    case 'F':
      sprintf(letterSegments, "1000111");
      break;
    case 'G':
      sprintf(letterSegments, "1011110");
      break;
    case 'H':
      sprintf(letterSegments, "0010111");
      break;
    case 'I':
      sprintf(letterSegments, "0000110");
      break;
    case 'J':
      sprintf(letterSegments, "0111100");
      break;
    case 'K':
      sprintf(letterSegments, "1010111");
      break;
    case 'L':
      sprintf(letterSegments, "0001110");
      break;
    case 'M':
      sprintf(letterSegments, "1010100");
      break;
    case 'N':
      sprintf(letterSegments, "1110110");
      break;
    case 'O':
      sprintf(letterSegments, "1111110");
      break;
    case 'P':
      sprintf(letterSegments, "1100111");
      break;
    case 'Q':
      sprintf(letterSegments, "1110011");
      break;
    case 'R':
      sprintf(letterSegments, "1100110");
      break;
    case 'S':
      sprintf(letterSegments, "1011011");
      break;
    case 'T':
      sprintf(letterSegments, "0001111");
      break;
    case 'U':
      sprintf(letterSegments, "0111110");
      break;
    case 'V':
      sprintf(letterSegments, "0111010");
      break;
    case 'W':
      sprintf(letterSegments, "0101010");
      break;
    case 'X':
      sprintf(letterSegments, "0110111");
      break;
    case 'Y':
      sprintf(letterSegments, "0111011");
      break;
    case 'Z':
      sprintf(letterSegments, "1101001");
      break;
    case ' ':
      sprintf(letterSegments, "0000000");
      break;
    case '0':
      sprintf(letterSegments, "1111110");
      break;
    case '1':
      sprintf(letterSegments, "0110000");
      break;
    case '2':
      sprintf(letterSegments, "1101101");
      break;
    case '3':
      sprintf(letterSegments, "1111001");
      break;
    case '4':
      sprintf(letterSegments, "0110011");
      break;
    case '5':
      sprintf(letterSegments, "1011011");
      break;
    case '6':
      sprintf(letterSegments, "1011111");
      break;
    case '7':
      sprintf(letterSegments, "1110000");
      break;
    case '8':
      sprintf(letterSegments, "1111111");
      break;
    case '9':
      sprintf(letterSegments, "1111011");
      break;
    case '"':
      sprintf(letterSegments, "0100010");
      break;
    case 39: // Special case: single quote (')
      sprintf(letterSegments, "0000010");
      break;
    case ',':
      sprintf(letterSegments, "0011000");
      break;
    case '-':
      sprintf(letterSegments, "0000001");
      break;
    case ':':
      sprintf(letterSegments, "0001001");
      break;
    case '=':
      sprintf(letterSegments, "1000001");
      break;
    case '<':
      sprintf(letterSegments, "1000011");
      break;
    case '>':
      sprintf(letterSegments, "1100001");
      break;
    default:
      sprintf(letterSegments, "0110111");
  }

  printDisplayLetter(&letterSegments, lineIndex, letterIndex, origin);
}

void printSignLetters(char *text, int origin, int destination) {
  system("clear");
  strcpy(letterLine, "");
  for (int lineIndex = 0; lineIndex < 5; lineIndex++) {
    strcpy(displayLine, "");
    
    for (int letterIndex = origin; letterIndex < destination; letterIndex++) {
      // Show characters above display
      /*
      if (lineIndex == 0) {
        char letter[5];
        sprintf(letter, " %c  ", toupper(text[letterIndex]));
        strcat(letterLine, letter);
      }
      */

      getLetterSegments(toupper(text[letterIndex]), lineIndex, letterIndex, origin);
    }

    if (lineIndex == 0)
      printf("%s\n", letterLine);
    
    printf("%s\n", displayLine);
  }
}

void displayMove(char *text) {
  while (1) {
    for (int origin = 0, destination = DISPLAY_LENGTH; origin < strlen(text); origin++) {
      printSignLetters(text, origin, destination);
      sleep(2);
      if (destination < (strlen(text)))
        destination++;
    }
    
    system("clear");
    char copy[DISPLAY_LENGTH];
    for (int right = DISPLAY_LENGTH - 1; right > 0; right--) {
      for (int left = 0, leftOriginal = 0; left < DISPLAY_LENGTH; left++) {
        if (left >= right) {
          copy[left] = text[leftOriginal];
          leftOriginal++;
        } else {
          copy[left] = ' ';
        }
      }
      printSignLetters(copy, 0, DISPLAY_LENGTH);
      sleep(2);
    }
  }
}

void printDisplay(char *text) {
  if (strlen(text) > DISPLAY_LENGTH)
    displayMove(text);
  else
    printSignLetters(text, 0, strlen(text));
}

void main() {
  char userText[TEXT_LENGTH];

  printf("> Digite um texto para ser exibido no letreiro digital: ");
  scanf(" %[^\n]s", userText);

  printDisplay(&userText);
}
