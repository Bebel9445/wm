/*

wm version 2.3 : Add IS2, PZIV ausf. H and Maus

wm version 2.2 : Add Katyusha and FT17

wm version 2.1 : Add Leclerc MBT

wm version 2.0 : Add various options

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
int add_leclerc(int x);
int add_katyusha(int x);
int add_ft17(int x);
int add_is2(int x);
int add_pzivh(int x);
int add_maus(int x);
void option(char *str);
int my_mvaddstr(int y, int x, char *str);

int kv2 = 0;
int leclerc = 0;
int katyusha = 0;
int ft17 = 0;
int is2 = 0;
int pzivh = 0;
int maus = 0;
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
    extern int kv2, leclerc, katyusha, disco, blitz, escape;
    while (*str != '\0')
    {
        switch (*str)
        {
            case 'K': kv2 = 1; break;
            case 'L': leclerc = 1; break;
            case 'B': katyusha = 1; break;
            case 'F': ft17 = 1; break;
            case 'I': is2 = 1; break;
            case 'P': pzivh = 1; break;
            case 'M': maus = 1; break;
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
        else if (leclerc) {
            if(add_leclerc(x) == ERR) break;
        }
        else if (katyusha) {
            if(add_katyusha(x) == ERR) break;
        }
        else if (ft17) {
            if(add_ft17(x) == ERR) break;
        }
        else if (is2) {
            if(add_is2(x) == ERR) break;
        }
        else if (pzivh) {
            if(add_pzivh(x) == ERR) break;
        }
        else if (maus) {
            if(add_maus(x) == ERR) break;
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



int add_leclerc(int x) {
    static char* leclerc[LECLERCHEIGHT + 1] = {
        LECLERC_1, LECLERC_2, LECLERC_3, LECLERC_4, LECLERC_5, LECLERC_6,
        LECLERC_7, LECLERC_8, LECLERC_9, LECLERC_10, LECLERC_11,
        LECLERC_12, LECLERC_13, LECLERC_14, LECLERC_15, LECLERC_16,
        LECLERC_17, LECLERC_18, LECLERC_19, LECLERC_20, LECLERC_21,
        LECLERC_22, LECLERC_23, LECLERC_24, LECLERC_25, LECLERC_26,
        LECLERCDEL
    };
    int y, i;
    if (x < - LECLERCLENGTH) return ERR;
    y = LINES / 2 - 5;

    for(i = 0; i <= LECLERCHEIGHT; ++i) {
        my_mvaddstr(y + i, x, leclerc[i]);
    }
    add_smoke(y + 10, x + 175);

    return OK;
}

int add_katyusha(int x) {
    static char* katyusha[KATYUSHAHEIGHT + 1] = {
        KATYUSHA_1, KATYUSHA_2, KATYUSHA_3, KATYUSHA_4, KATYUSHA_5, KATYUSHA_6,
        KATYUSHA_7, KATYUSHA_8, KATYUSHA_9, KATYUSHA_10, KATYUSHA_11,
        KATYUSHA_12, KATYUSHA_13, KATYUSHA_14, KATYUSHA_15, KATYUSHA_16,
        KATYUSHA_17, KATYUSHA_18, KATYUSHA_19, KATYUSHA_20, KATYUSHA_21,
        KATYUSHA_22, KATYUSHA_23, KATYUSHA_24, KATYUSHA_25, KATYUSHA_26,
        KATYUSHA_27, KATYUSHA_28, KATYUSHA_29, KATYUSHA_30, KATYUSHA_31,
        KATYUSHA_32, KATYUSHA_33, KATYUSHA_34, KATYUSHA_35, KATYUSHA_36,
        KATYUSHA_37, KATYUSHA_38, KATYUSHA_39, KATYUSHA_40, KATYUSHA_41,
        KATYUSHADEL
    };
    int y, i;
    if (x < - KATYUSHALENGTH) return ERR;
    y = LINES / 2 - 20;

    for(i = 0; i <= KATYUSHAHEIGHT; ++i) {
        my_mvaddstr(y + i, x, katyusha[i]);
    }
    add_smoke(y + 28, x + 145);

    return OK;
}

int add_ft17(int x) {
    static char* ft17[FT17HEIGHT + 1] = {
        FT17_1, FT17_2, FT17_3, FT17_4, FT17_5, FT17_6,
        FT17_7, FT17_8, FT17_9, FT17_10, FT17_11,
        FT17_12, FT17_13, FT17_14, FT17_15, FT17_16,
        FT17_17, FT17_18, FT17_19, FT17_20, FT17_21,
        FT17_22, FT17_23, FT17_24, FT17_25, FT17_26,
        FT17_27, FT17_28, FT17_29, FT17_30, FT17_31,
        FT17_32, FT17_33, FT17_34, FT17_35, FT17_36,
        FT17_37, FT17_38, FT17_39, FT17_40,
        FT17DEL
    };
    int y, i;
    if (x < - FT17LENGTH) return ERR;
    y = LINES / 2 - 20;

    for(i = 0; i <= FT17HEIGHT; ++i) {
        my_mvaddstr(y + i, x, ft17[i]);
    }
    add_smoke(y + 18, x + 140);

    return OK;
}

int add_is2(int x) {
    static char* is2[IS2HEIGHT + 1] = {
        IS2_1, IS2_2, IS2_3, IS2_4, IS2_5, IS2_6,
        IS2_7, IS2_8, IS2_9, IS2_10, IS2_11,
        IS2_12, IS2_13, IS2_14, IS2_15, IS2_16,
        IS2_17, IS2_18, IS2_19, IS2_20, IS2_21,
        IS2_22, IS2_23, IS2_24, IS2_25, IS2_26,
        IS2_27, IS2_28, IS2_29, IS2_30, IS2_31,
        IS2_32, IS2_33, IS2_34, IS2_35, IS2_36,
        IS2_37, IS2_38, IS2_39, IS2_40,
        IS2DEL
    };
    int y, i;
    if (x < - IS2LENGTH) return ERR;
    y = LINES / 2 - 20;

    for(i = 0; i <= IS2HEIGHT; ++i) {
        my_mvaddstr(y + i, x, is2[i]);
    }
    add_smoke(y + 17, x + 195);

    return OK;
}

int add_pzivh(int x) {
    static char* pzivh[PZIVHHEIGHT + 1] = {
        PZIVH_1, PZIVH_2, PZIVH_3, PZIVH_4, PZIVH_5, PZIVH_6,
        PZIVH_7, PZIVH_8, PZIVH_9, PZIVH_10, PZIVH_11,
        PZIVH_12, PZIVH_13, PZIVH_14, PZIVH_15, PZIVH_16,
        PZIVH_17, PZIVH_18, PZIVH_19, PZIVH_20, PZIVH_21,
        PZIVH_22, PZIVH_23, PZIVH_24, PZIVH_25, PZIVH_26,
        PZIVH_27, PZIVH_28, PZIVH_29, PZIVH_30, PZIVH_31,
        PZIVH_32, PZIVH_33, PZIVH_34, PZIVH_35, PZIVH_36,
        PZIVH_37, PZIVH_38, PZIVH_39, PZIVH_40, PZIVH_41,
        PZIVHDEL
    };

    int y, i;
    if (x < - PZIVHLENGTH)  return ERR;
    y = LINES / 2 - 20;

    for(i = 0; i <= PZIVHHEIGHT; ++i) {
        my_mvaddstr(y + i, x, pzivh[i]);
    }
    add_smoke(y + 19, x + 190);

    return OK;
}

int add_maus(int x) {
    static char* maus[MAUSHEIGHT + 1] = {
        MAUS_1, MAUS_2, MAUS_3, MAUS_4, MAUS_5, MAUS_6,
        MAUS_7, MAUS_8, MAUS_9, MAUS_10, MAUS_11,
        MAUS_12, MAUS_13, MAUS_14, MAUS_15, MAUS_16,
        MAUS_17, MAUS_18, MAUS_19, MAUS_20, MAUS_21,
        MAUS_22, MAUS_23, MAUS_24, MAUS_25, MAUS_26,
        MAUS_27, MAUS_28, MAUS_29, MAUS_30, MAUS_31,
        MAUS_32, MAUS_33, MAUS_34, MAUS_35, MAUS_36,
        MAUS_37, MAUS_38, MAUS_39, MAUS_40, MAUS_41,
        MAUSDEL
    };
    int y, i;
    if (x < - MAUSLENGTH) return ERR;
    y = LINES / 2 - 20;

    for(i = 0; i <= MAUSHEIGHT; ++i) {
        my_mvaddstr(y + i, x, maus[i]);
    }
    add_smoke(y + 20, x + 200);

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