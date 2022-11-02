#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

int isvowel(char p, char q);
float fkgrade(char str[]);


int main() {
    char plato[] = "He who is the real tyrant, whatever men may think, is the real slave, and is obliged to practise the greatest adulation and servility, and to be the flatterer of the vilest of mankind.  He has desires which he is utterly unable to satisfy, and has more wants than any one, and is truly poor, if you know how to inspect the whole soul of him: all his life long he is beset with fear and is full of convulsions and distractions, even as the State which he resembles: and surely the resemblance holds?";

    char aurelius[] = "Nothing pertains to human beings except what defines us as human.  No other things can be demanded of us.  They aren't proper to human nature, nor is it incomplete without them.  It follows that they are not our goal, or what helps us reach it -- the good.  If any of them were proper to us, it would be improper to disdain or resist it.  If the things themselves were good, it could hardly be good to give them up.  But in reality, the more we deny ourselves such things (and things like them) -- or are deprived of them involuntarily, even -- the better we become.";

    char descartes[] = "I suppose, accordingly, that all the things which I see are false (fictitious); I believe that none of those objects which my fallacious memory represents ever existed; I suppose that I possess no senses; I believe that body, figure, extension, motion, and place are merely fictions of my mind.  What is there, then, that can be esteemed true?  Perhaps this only, that there is absolutely nothing certain.";
    
    char empty[] = "";
    
    printf("Plato...\nexpected sentences = 2\ne  xpected words = 94\n  expected syllables = 135\n");
    float out = fkgrade(plato);
    printf("> Reading Level = %f\n", out);
    printf("Marcus Aurelius...\n  expected sentences = 7\n   expected words = 104\n    expected syllables = 153\n");
    out = fkgrade(aurelius);
    printf("> Reading Level = %f\n", out);
    printf("Rene Descartes...\n  expected sentences = 3\n   expected words = 67\n    expected syllables = 113\n");
    out = fkgrade(descartes);
    printf("> Reading Level = %f\n", out);
    
    out = fkgrade(empty);
    printf("> Reading Level = %f\n", out);
}

int isvowel(char p, char q) {
    char arr[10] = {'a','e','i','o','u','A','E','I','O','U'};
    int vowel = 0;
    for (int i = 0; i < 10; i++) {
        if (p == arr[i]) {
            for (int j = 0; j < 10; j++) {
                if (q == arr[j]) {
                    return 0;
                }
                else {
                    vowel++;
                }
            }
        }
    }
    return vowel;
}

float fkgrade(char str[]) {
    float syllables = 0;
    float words = 0;
    float sentences = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (isspace(str[i]) != 0) {
            if (isalpha(str[i+1]) != 0) {
                words++;
            }
            else if ((ispunct(str[i+1]) != 0) && (isalpha(str[i+2]) != 0)) {
                words++;
            }
        }
        else if (isvowel(str[i],str[i+1]) != 0) {
            syllables++;
        }
        else if ((str[i] == '.') || (str[i] == '!') || (str[i] == '?')) {
            sentences++;
        }
    }
    if ((isalpha(str[strlen(str)-1]) != 0) || (ispunct(str[strlen(str)-1]) != 0))
        words++;
    if ((words == 0) || (sentences == 0)) {
        return 0;
    }
    return 0.39*words/sentences+11.8*syllables/words-15.59;
}