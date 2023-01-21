#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUFFER 1024

typedef struct KeyValue{
  char* key;
  char* val;
} KeyValue;

char* GetFile(char* filename){
  char* buffer = malloc(MAX_BUFFER * sizeof(char));
  memset(buffer, 0, MAX_BUFFER);

  FILE* file = fopen(filename, "r");

  fread(buffer, sizeof(char), MAX_BUFFER, file);

  return buffer;
}

KeyValue* parse(char* filename){
  char* bufferPointer = GetFile(filename);
  char buffer[MAX_BUFFER];

  KeyValue* keyValues = malloc(MAX_BUFFER * sizeof(KeyValue));
  memset(keyValues, 0, MAX_BUFFER);

  memset(buffer, 0, MAX_BUFFER);
  strcpy(buffer, bufferPointer);

  free(bufferPointer);

  // printf("%s\n===========\n", buffer);

  char currentChar = buffer[0];
  int index = 0;

  int isStarted = 0;
  int isComment = 0;

  int lowerIndex = 0;
  int upperIndex;

  char keyString[180];
  char valueString[180];

  while (currentChar != '\0'){
    if (!isComment && currentChar == '#'){
      isComment = 1;
    }

    if (isStarted){
      if (isComment && currentChar == '\n'){
        isComment = 0;
      }
      else if (currentChar == '-'){
        return keyValues;
      }
      else if (currentChar == ':'){
        upperIndex = index;

        // for (int j=lowerIndex; j<upperIndex; j++){
        //   strcat(keyString, currentChar);
        // }

        index++;
        currentChar = buffer[index];
        lowerIndex = index;

        while (currentChar != '\n'){
          index++;
          currentChar = buffer[index];
        }
        upperIndex = index;

        // for (int j=lowerIndex; j<upperIndex; j++){
        //   strcat(valueString, currentChar);
        // }

        printf("%s %s\n", keyString, valueString);
      }
      else if (currentChar == '\n'){
        lowerIndex = index + 1;
      }

    }
    else{
      if (currentChar == '-'){
        isStarted = 1;
      }
    }

    index++;
    currentChar = buffer[index];
  }
  printf("\n");
}

int main(){
  parse("test_file.qi");
  return 0;
}
