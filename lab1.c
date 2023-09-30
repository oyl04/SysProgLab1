#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int BufferSize = 30, NumVowels = 5;

const char Vowels [] = {'A', 'a', 'E', 'e', 'I', 'i', 'O', 'o', 'U', 'u'};

int cnt = 0;

bool isVowel(const char c){
    for (int i = 0; i < NumVowels * 2; ++i){
        if (Vowels[i] == c) return true;
    }
    return false;
}

bool isLetter (const char c){
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')){
        return true;
    }
    else return false;
}

bool isUniqueWord(const char* word, char** words){
    for (int i = 0; i < cnt; ++i){
        if (strlen(word) != strlen(words[i])) continue;
        else if (strcasecmp(word, words[i]) == 0) return false;
    }
    return true;
}

int main()
{

    FILE *file = fopen("in.txt", "r");

    if (file == NULL) {
        printf("Failed to open the file.");
        return -1;
    }

    char c;

    int cntVowels = 0, cntConsonant = 0, numWords = 16;

    char **words = (char **)malloc(16 * sizeof(char *));

    char buffer[BufferSize + 1];

    while (c=fgetc(file)){

        if (isLetter(c) && cntVowels + cntConsonant >= 30){
            printf("A buffer overflow. The current word: %s... The word will be ignored.\n", buffer);
            while (isLetter(c=getc(file))){}
            cntVowels = 0;
            cntConsonant = 0;
            buffer[0] = '\0';
        }

        else if (isLetter(c)){
            buffer[cntVowels + cntConsonant] = c;
            cntVowels += isVowel(c);
            cntConsonant += !isVowel(c);
        }

        else if (cntVowels + cntConsonant > 0 && cntVowels > cntConsonant){
            buffer[cntVowels + cntConsonant] = '\0';
            if (isUniqueWord(buffer, words)){
            printf("%s\n", buffer);
            words[cnt] = (char *)malloc(cntVowels + cntConsonant + 1);
            strcpy(words[cnt], buffer);
            cnt++;
            if (cnt == numWords) {
                numWords *= 2;
                words = (char **)realloc(words, numWords * sizeof(char *));
            }
            }
            cntConsonant = 0;
            cntVowels = 0;
        }

        else {
            cntConsonant = 0;
            cntVowels = 0;
        }
        if (c == EOF) break;
    }

    for (int i = 0; i < cnt; ++i) free(words[i]);

    free(words);

    fclose(file);
    return 0;
}
