#ifndef EDITOR_H
#define EDITOR_H

#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _GNU_SOURCE

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/ioctl.h>
#include <time.h>
#include <sys/types.h>
#include <ctype.h>

#define NOTAVIM_VERSION "0.0.1"
#define NOTAVIM_TAB_STOP 8 
#define NOTAVIM_QUIT_TIMES 3
#define HL_HIGHTLIGHT_NUMBERS (1<<0)
#define HL_HIGHTLIGHT_STRINGS (1<<1)

#define CTRL_KEY(k) ((k) & 0x1f)

#define ABUF_INIT {NULL, 0}

struct editorSyntax {
    char *filetype;
    char **filematch;
    char **keywords;
    char *singleline_comment_start;
    char *multiline_comment_start;
    char *multiline_comment_end;
    int flags;
};


struct abuf{
    char *b;
    int len;
};

enum editorKey {
    BACKSPACE = 127,
    ARROW_LEFT = 1000,
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN,
    DEL_KEY,
    HOME_KEY,
    END_KEY,
    PAGE_UP,
    PAGE_DOWN
};

typedef struct erow {
    int idx;
    int size;
    int rsize;
    char *chars;
    char *render;
    unsigned char *hl;
    int hl_open_comment;
} erow;

struct editorConfig {
    int cx, cy;
    int rx;
    int rowoff;
    int coloff;
    int screenrows;
    int screencols;
    int numrows;
    erow *row;
    int dirty;
    char *filename;
    char statusmsg[80];
    time_t statusmsg_time;
    struct editorSyntax *syntax;
    struct termios orig_termios;
};

extern struct editorConfig E;

enum editorHighlight {
    HL_NORMAL = 0,
    HL_COMMENT,
    HL_MLCOMMENT,
    HL_KEYWORD1,
    HL_KEYWORD2,
    HL_STRING,
    HL_NUMBER,
    HL_MATCH
};



void die(const char* s);
void disableRawMode(void);
void enableRawMode(void);
int editorReadKey(void);
int getCursorPosition(int* rows, int* cols);
int getWindowSize(int* rows, int* cols);
void editorUpdateSyntax(erow *row);
int editorSyntaxToColor(int hl);
void editorSelectSyntaxHighlight(void);
int editorRowCxToRx(erow *row, int cx);
int editorRowRxToCx(erow *row, int rx);
void editorUpdateRow(erow *row);
void editorInsertRow(int at, char* s, size_t len);
void editorFreeRow(erow *row);
void editorDelRow(int at);
void editorRowInsertChar(erow *row, int at, int c);
void editorRowAppendString(erow *row, char *s, size_t len);
void editorRowDelChar(erow *row, int at);
void editorInsertChar(int c);
void editorInsertNewLine(void);
void editorDelChar(void);
char *editorRowsToString(int *buflen);
void editorOpen(char *filename);
void editorSave(void);
void editorFindCallback(char *query, int key);
void editorFind(void);
void abAppend(struct abuf *ab, const char *s, int len);
void abFree(struct abuf *ab);
void editorScroll(void);
void editorDrawRows(struct abuf *ab);
void editorDrawStatusBar(struct abuf *ab);
void editorDrawMessageBar(struct abuf *ab);
void editorRefreshScreen(void);
void editorSetStatusMessage(const char *fmt, ...);
char *editorPrompt(char* prompt, void(*callback)(char*, int));
void editorMoveCursor(int key);
void editorProcessKeypress(void);
void initEditor(void);

#endif
