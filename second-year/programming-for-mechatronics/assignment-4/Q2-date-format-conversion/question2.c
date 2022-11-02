#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void DMY_MonthDY(char *buffer, const char *str);
void MonthDY_DMY(char *buffer, const char *str);



int main(){
char format1[12][11] = { "01/01/1970"
                       , "10/02/1763"
                       , "15/03/0044"
                       , "18/04/1982"
                       , "05/05/1789"
                       , "06/06/1944"
                       , "01/07/1867"
                       , "03/08/1492"
                       , "02/09/1945"
                       , "24/08/1917"
                       , "11/11/1918"
                       , "08/12/1980"
                       };
char format2[12][19] = { "January    1, 1970" // First Day of History (according to computers)
                       , "February  10, 1763" // France cedes Canada to England
                       , "March     15,   44" // Assassination of Julius Caesar
                       , "April     18, 1982" // Canada Achieves Sovereignty 
                       , "May        5, 1789" // French Revolution
                       , "June       6, 1944" // D-Day Landings of WWII
                       , "July       1, 1867" // Confederation of Canada
                       , "August     3, 1492" // Christopher Columbus Sets Sail for the Americas
                       , "September  2, 1945" // WWII Surrender of Japan
                       , "October   24, 1917" // October Revolution (Julian Calendar)
                       , "November  11, 1918" // WWI Armistice
                       , "December   8, 1980" // Murder of John Lennon
                       };
    
    char buffer1[12][11];
    char buffer2[12][19];
    
    printf ("-- DD\\MM\\YY to Month DD, YYYY\n");
    for (int i = 0; i < 12; i++) {
        printf("%s\n", format1[i]);
        DMY_MonthDY(buffer2[i], format1[i]);
        printf("-> \"%s\"\n", buffer2[i]);
    }
    
    
    printf ("\n\n-- Month DD, YYYY to DD\\MM\\YY\n");
    for (int i = 0; i < 12; i++) {
        printf("%s\n", format2[i]);
        MonthDY_DMY(buffer1[i], format2[i]);
        printf("-> \"%s\"\n", buffer1[i]);
    }
}

void DMY_MonthDY(char *buffer, const char *str) {
    char *months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    char *blanks[12] = {"  ", " ", "    ", "    ", "      ", "     ", "     ", "   ", "", "  ", " ", " "};
    int month;
    int b = str[3] - '0';
    int s = str[4] - '0';
    month = b*10+s-1;
    char *d = malloc(2*sizeof(char));
    char *y = malloc(4*sizeof(char));
    memcpy(d, str, 2);
    if (d[0] == '0')
        d[0] = ' ';
    for (int i = 0; i < 4; i++)
        y[i] = str[i+6];
    sprintf(buffer, "%s%s %s, %s", months[month], blanks[month], d, y);
}

void MonthDY_DMY(char *buffer, const char *str) {
    char *m = malloc(2*sizeof(char));
    char *d = malloc(2*sizeof(char));
    char *y = malloc(4*sizeof(char));
    if (str[0] == 'J') {
        if (str[1] == 'u') {
            if (str[2] == 'n')
                m = "06";
            else
                m = "07";
        } else
            m = "01";
    } else if (str[0] == 'M') {
        if (str[2] == 'r')
            m = "03";
        else
            m = "05";
    } else if (str[0] == 'A') {
        if (str[1] == 'p')
            m = "04";
        else
            m = "08";
    }
    else if (str[0] == 'F')
        m = "02";
    else if (str[0] == 'S')
        m = "09";
    else if (str[0] == 'O')
        m = "10";
    else if (str[0] == 'N')
        m = "11";
    else
        m = "12";
    d[0] = str[10];
    d[1] = str[11];
    if (d[0] == ' ')
        d[0] = '0';
    for (int i = 0; i < 4; i++) {
        y[i] = str[i+14];
        if (str[i+14] == ' ')
            y[i] = '0';
    }
    sprintf(buffer, "%s\\%s\\%s", d, m, y);
}

