#include <curses.h>
#include <signal.h>
#include <unistd.h>
#include "wm.h"

void add_smoke(int y, int x);
int add_pzvitii(int x);
void option(char *str);
int my_mvaddstr(int y, int x, char *str);

// int pzvitii = 0;

int my_mvaddstr(int y, int x, char *str)
{
    for ( ; x < 0; ++x, ++str)
        if (*str == '\0')  return ERR;
    for ( ; *str != '\0'; ++x, ++str)
        if (mvaddch(y, x, *str) == ERR)  return ERR;
    return OK;
}

/* no options for now

void option(char *str) 
{
    while (*str != '\0') {
        switch (*str++) {
            default: break;
        }
    }
}
*/

int main(int argc, char *argv[])
{
    int x;// i;

    /*
    for (i = 1; i < argc; ++i) {
        if (*argv[i] == '-') {
            option(argv[i] + 1);
        }
    }
    */
   
    initscr(); // initialize the window
    signal(SIGINT, SIG_IGN); // ignore SIGINT (ctrl-c)
    signal(SIGTSTP, SIG_IGN); // ignore SIGTSTP (ctrl-z)
    noecho(); // do not echo input characters
    curs_set(0); // make cursor invisible
    nodelay(stdscr, TRUE); // make getch non-blocking
    leaveok(stdscr, TRUE); // cursor position does not matter
    scrollok(stdscr, FALSE); // do not scroll the window

    for (x = COLS - 1; ; --x) {
        if (add_pzvitii(x) == ERR) break;
        
        getch();
        refresh();
        usleep(40000);
    }
    mvcur(0, COLS - 1, LINES - 1, 0);
    endwin();
    return 0;
}

int add_pzvitii(int x) {
    static char* pzvitii[PZVITIIHEIGHT + 1] = {
        PZVITII1, PZVITII2, PZVITII3, PZVITII4, PZVITII5, PZVITII6,
        PZVITII7, PZVITII8, PZVITII9, PZVITII10, PZVITII11, PZVITII12,
        PZVITII13, PZVITII14, PZVITII15, PZVITII16, PZVITII17, PZVITII18,
        PZVITII19, PZVITII20, PZVITII21, PZVITII22, PZVITII23, PZVITII24,
        PZVITII25, PZVITII26, PZVITII27, PZVITII28, PZVITII29, PZVITII30,
        PZVITII31, PZVITII32, PZVITII33, PZVITII34, PZVITII35, PZVITII36,
        PZVITII37, PZVITII38, PZVITII39, PZVITII40, PZVITIIDEL
    };

    int y, i;
    if (x < - PZVITIILENGTH)  return ERR;
    y = LINES / 2 - 20;

    for(i = 0; i <= PZVITIIHEIGHT; ++i) {
        my_mvaddstr(y + i, x, pzvitii[i]);
    }
    add_smoke(y + 14, x + 242);

    return OK;
}

void add_smoke(int y, int x)
#define SMOKEPTNS 16
{
    static struct smokes {
        int y, x;
        int ptrn, kind;
    } S[1000];
    static int sum = 0;
    static char *Smoke[2][SMOKEPTNS]
        = {{"(   )", "(    )", "(    )", "(   )", "(  )",
            "(  )" , "( )"   , "( )"   , "()"   , "()"  ,
            "O"    , "O"     , "O"     , "O"    , "O"   ,
            " "                                          },
           {"(@@@)", "(@@@@)", "(@@@@)", "(@@@)", "(@@)",
            "(@@)" , "(@)"   , "(@)"   , "@@"   , "@@"  ,
            "@"    , "@"     , "@"     , "@"    , "@"   ,
            " "                                          }};
    static char *Eraser[SMOKEPTNS]
        =  {"     ", "      ", "      ", "     ", "    ",
            "    " , "   "   , "   "   , "  "   , "  "  ,
            " "    , " "     , " "     , " "    , " "   ,
            " "                                          };
    static int dy[SMOKEPTNS] = { 2,  1, 1, 1, 0, 0, 0, 0, 0, 0,
                                 0,  0, 0, 0, 0, 0             };
    static int dx[SMOKEPTNS] = {-2, -1, 0, 1, 1, 1, 1, 1, 2, 2,
                                 2,  2, 2, 3, 3, 3             };
    int i;

    if (x % 4 == 0) {
        for (i = 0; i < sum; ++i) {
            my_mvaddstr(S[i].y, S[i].x, Eraser[S[i].ptrn]);
            S[i].y    -= dy[S[i].ptrn];
            S[i].x    += dx[S[i].ptrn];
            S[i].ptrn += (S[i].ptrn < SMOKEPTNS - 1) ? 1 : 0;
            my_mvaddstr(S[i].y, S[i].x, Smoke[S[i].kind][S[i].ptrn]);
        }
        my_mvaddstr(y, x, Smoke[sum % 2][0]);
        S[sum].y = y;    S[sum].x = x;
        S[sum].ptrn = 0; S[sum].kind = sum % 2;
        sum ++;
    }
}