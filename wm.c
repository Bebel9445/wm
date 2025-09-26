/*

wm version 2.0 : add various options

wm version 1.0 : wm runs in terminal and shows ASCII art

*/

#include <curses.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include "wm.h"

void add_smoke(int y, int x);
int add_pzvitii(int x);
int add_kv2(int x);
void option(char *str);
int my_mvaddstr(int y, int x, char *str);

int kv2 = 0;
int disco = 0;
int blitz = 1;
int escape = 1;

int my_mvaddstr(int y, int x, char *str)
{
    for ( ; x < 0; ++x, ++str)
        if (*str == '\0')  return ERR;
    for ( ; *str != '\0'; ++x, ++str)
        if (mvaddch(y, x, *str) == ERR)  return ERR;
    return OK;
}

void option(char *str) 
{
    extern int kv2;
    while (*str != '\0')
    {
        switch (*str)
        {
            case 'K': kv2 = 1; break;
            case 'd': disco = 1; break;
            case 'b': blitz = 4; break;
            case 'e': escape = 0; break;
            default: break;
        }
        str++;
    }
    
}


int main(int argc, char *argv[])
{
    int x, i;

    for (i = 1; i < argc; ++i) {
        if (*argv[i] == '-') {
            option(argv[i] + 1);
        }
    }
   
    initscr(); // initialize the window
    if (disco == 1) {
        start_color();
        init_pair(4, COLOR_RED, COLOR_BLACK);
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(1, COLOR_CYAN, COLOR_BLACK);
    }
    if (escape) {
        signal(SIGINT, SIG_IGN); // ignore SIGINT (ctrl-c)
        signal(SIGTSTP, SIG_IGN); // ignore SIGTSTP (ctrl-z)
    }
    noecho(); // do not echo input characters
    curs_set(0); // make cursor invisible
    nodelay(stdscr, TRUE); // make getch non-blocking
    leaveok(stdscr, TRUE); // cursor position does not matter
    scrollok(stdscr, FALSE); // do not scroll the window

    for (x = COLS - 1; ; --x) {
        if (kv2) {
            if (add_kv2(x) == ERR) break;
        }
        else if (add_pzvitii(x) == ERR) break;    
        
        getch();
        refresh();
        usleep(40000 / blitz);
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

int add_kv2(int x) {
    static char* kv2[KV2HEIGHT + 1] = {
        KV2_1, KV2_2, KV2_3, KV2_4, KV2_5, KV2_6,
        KV2_7, KV2_8, KV2_9, KV2_10, KV2_11,
        KV2_12, KV2_13, KV2_14, KV2_15, KV2_16,
        KV2_17, KV2_18, KV2_19, KV2_20, KV2_21,
        KV2_22, KV2_23, KV2_24, KV2_25, KV2_26,
        KV2_27, KV2_28, KV2_29, KV2_30, KV2_31,
        KV2_32, KV2_33, KV2_34, KV2_35, KV2_36,
        KV2_37, KV2_38, KV2_39, KV2_40, KV2_41,
        KV2DEL
    };
    int y, i;
    if (x < - KV2LENGTH)  return ERR;
    y = LINES / 2 - 20;

    for(i = 0; i <= KV2HEIGHT; ++i) {
        my_mvaddstr(y + i, x, kv2[i]);
    }
    add_smoke(y + 20, x + 120);

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

    if (disco && (x + INT_MAX/2) % 4 == 2)
        attron(COLOR_PAIR((x + INT_MAX/2) / 16 % 4 + 1));

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