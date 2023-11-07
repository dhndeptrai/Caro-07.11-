#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#include<mmsystem.h>
#include <fstream>

using namespace std;

void CreateConsoleWindow(int pWidth, int pHeight) {
    HWND consoleWindow = GetConsoleWindow();
    RECT r;
    HANDLE hConsole;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 240);
    GetWindowRect(consoleWindow, &r);
    MoveWindow(consoleWindow, 0, 0, pWidth, pHeight, TRUE);
}
void FixConsoleWindow() {
    HWND consoleWindow = GetConsoleWindow();
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
    SetWindowLong(consoleWindow, GWL_STYLE, style);
}


void gotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void set_color(int color) {
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}
int b_color(std::string c, int k) {
    HANDLE hConsoleColor;
    hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsoleColor, k);
    std::cout << c;
    return 0;
}
/*
BOOL ShowScrollBar(
    HWND hWnd,
    int  wBar,
    BOOL bShow
);
void ShowScrollbar(BOOL Show)
{
    HWND hWnd = GetConsoleWindow();
    ShowScrollBar(hWnd, SB_BOTH, Show);
}
*/
void resizeConsole(int width, int height)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void ve_x_o(int n) //ve X va O
{
    gotoXY(70, 5); cout << "TURN: ";
    if (n == 0) {                                                           //vẽ biểu tượng X
        set_color(4);
        gotoXY(70, 6);  cout << " ,--,     ,--,";
        gotoXY(70, 7); cout << " |'. \\   / .`|";
        gotoXY(70, 8); cout << " ; \\ `\\ /' / ;";
        gotoXY(70, 9); cout << " `. \\  /  / .'";
        gotoXY(70, 10); cout << "  \\  \\/  / ./ ";
        gotoXY(70, 11); cout << "   \\  \\.'  /  ";
        gotoXY(70, 12); cout << "    \\  ;  ;    ";
        gotoXY(70, 13); cout << "   / \\  \\  \\   ";
        gotoXY(70, 14); cout << "  ;  /\\  \\  \\  ";
        gotoXY(70, 15); cout << "./__;  \\  ;  \\ ";
        gotoXY(70, 16); cout << "|   : / \\  \\  ;";
        gotoXY(70, 17); cout << ";   |/   \\  ' |";
        gotoXY(70, 18); cout << "`---'     `--` ";
    }
    else {                                                                  //vẽ biểu tượng O
        set_color(1);
        gotoXY(70, 6);  cout << "    ,----..    ";
        gotoXY(70, 7); cout << "   /   /   \\   ";
        gotoXY(70, 8); cout << "  /   .     :  ";
        gotoXY(70, 9); cout << " .   /   ;.  \\ ";
        gotoXY(70, 10); cout << ".   ;   /  ` ; ";
        gotoXY(70, 11); cout << ";   |  ; \\ ; | ";
        gotoXY(70, 12); cout << "|   :  | ; | ' ";
        gotoXY(70, 13); cout << ".   |  ' ' ' : ";
        gotoXY(70, 14); cout << "'   ;  \\; /  | ";
        gotoXY(70, 15); cout << " \\   \\  ',  /  ";
        gotoXY(70, 16); cout << "  ;   :    /   ";
        gotoXY(70, 17); cout << "   \\   \\ .'    ";
        gotoXY(70, 18); cout << "    `---`      ";
    }
}
bool win(int s[15][15], int x, int y) //xac dinh thang thua
{
    int c1 = 0, c2 = 0, h1 = 0, h2 = 0, ch1 = 0, ch2 = 0, cp1 = 0, cp2 = 0, temp = s[x][y];
    for (int i = 1; i < 5; i++) if (y - i >= 0 && s[x][y - i] == temp) c1++; else break;
    for (int i = 1; i < 5; i++) if (y + i < 15 && s[x][y + i] == temp) c2++; else break;
    for (int i = 1; i < 5; i++) if (x - i >= 0 && s[x - i][y] == temp) h1++; else break;
    for (int i = 1; i < 5; i++) if (y + i < 15 && s[x + i][y] == temp) h2++; else break;
    for (int i = 1; i < 5; i++) if (x - i >= 0 && y - i >= 0 && s[x - i][y - i] == temp) ch1++; else break;
    for (int i = 1; i < 5; i++) if (x + i < 15 && y + i < 15 && s[x + i][y + i] == temp) ch2++; else break;
    for (int i = 1; i < 5; i++) if (x + i < 15 && y - i >= 0 && s[x + i][y - i] == temp) cp1++; else break;
    for (int i = 1; i < 5; i++) if (x - i >= 0 && y + i < 15 && s[x - i][y + i] == temp) cp2++; else break;
    if (c1 + c2 >= 4 || h1 + h2 >= 4 || ch1 + ch2 >= 4 || cp1 + cp2 >= 4) return true;
    return false;
}
void Save_game(int s[15][15], bool current) //luu game
{
    ofstream input("D:\\codecpp\\input.txt", ios::app);
    ofstream output("D:\\codecpp\\output.txt", ios::app);
    if (current == true) {
        gotoXY(70, 24); cout << "Press name: ";
        string ten;
        cin >> ten; input << ten << "\n";
        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 15; j++) output << s[i][j] << " ";
            output << "\n";
        }
    }
    else {

    }
    input.close();
}
void Load_game(int n, int ss[15][15]) //tai game
{
    int s[150][15];
    ifstream output("D:\\codecpp\\output.txt");
    for (int i = 0; i < 15 * (n + 1); i++)
        for (int j = 0; j < 15; j++) output >> s[i][j];
    for (int i = 15 * n; i < 15 * n + 15; i++)
        for (int j = 0; j < 15; j++) ss[j][i - 15 * n] = s[i][j];
}
int f_load() //tuy chon tai game
{
    gotoXY(41, 15);
    int z = 0;
    ifstream input("D:\\codecpp\\input.txt");
    for (int i = 0; i < 10; i++) {
        string s;
        cout << "                            ";
        gotoXY(41, 15 + i * 2);
        input >> s; if (s.size() == 0) continue;
        z++;
        cout << i << ". "; cout << s;
        gotoXY(41, 17 + i * 2);
    }
    gotoXY(41, 13); cout << "Press from 0 to " << z - 1 << " to choose game.";
    char key = _getch();
    if (key >= 48 && key < 48 + z) return (key - 48);
    else return -1;
}

int dogame(int s[15][15], bool cur, bool may) //thuc hien game
{
    set_color(0);
    //ShowScrollbar(0);
    gotoXY(0, 0);
    char key;
    int x = 22, y = 6;
    int xx = 0, oo = 0; //dem luot di
    bool check = true;
    gotoXY(70, 23); cout << "Press Space to play again.";
    gotoXY(70, 27); cout << "Press ESC 2 times to return to menu.";
    for (int i = 0; i < 15; i++) // tai thong tin game (neu la load game)
        for (int j = 0; j < 15; j++)
            if (s[i][j] == -1 || s[i][j] == 1) {
                if (s[i][j] == -1) oo++;
                if (s[i][j] == 1) xx++;
                check = !check;
            }
    gotoXY(70, 22); cout << "Press Backspace to save game and cancel";
    gotoXY(70, 2); cout << "Number of moves: ";
    gotoXY(70, 3); cout << "X: " << xx;
    gotoXY(70, 4); cout << "O: " << oo;
    while (1) { //bat dau choi
        if (xx + oo == 225) {
            gotoXY(0, 41); cout << "Draw";
            return 0;
        }
        if (check == true) {
            set_color(4);
            ve_x_o(0);
        }
        else {
            set_color(1);
            ve_x_o(1);
        }
        gotoXY(x, y);
        if (check == false && may == false) { //nuoc di cua may
            check = !check;
            while (1) {
                if (x < 76) {
                    gotoXY(x + 4, y); x += 4;
                }
                else { gotoXY(x - 4, y); x -= 4; }
                if (s[(x - 22) / 4][(y - 6) / 2] == 0) {
                    oo++;
                    gotoXY(70, 4); cout << "O: " << oo;
                    gotoXY(x, y);
                    cout << 'O'; s[(x - 22) / 4][(y - 6) / 2] = -1;
                    if (win(s, (x - 22) / 4, (y - 6) / 2) == true) {
                        gotoXY(70, 25); cout << "You lose.";
                        char keyy = _getch();
                        return -1;
                    }
                    break;
                }
                else {
                    if (y > 6) { gotoXY(x, y - 2); y -= 2; }
                    else { gotoXY(x, y + 2); y += 2; }
                    continue;
                }
            }
            continue;
        }
        key = _getch();
        if (key == 32) return 2;
        if (key == 8) { //luu game
            Save_game(s, cur); break;
        }
        if (key == 97 && x > 22) { gotoXY(x - 4, y); x -= 4; }
        if (key == 119 && y > 6) { gotoXY(x, y - 2); y -= 2; }
        if (key == 100 && x < 76) { gotoXY(x + 4, y); x += 4; }
        if (key == 115 && y < 34) { gotoXY(x, y + 2); y += 2; }
        if (key == 13 && s[(x - 22) / 4][(y - 6) / 2] == 0) {
            check = !check;
            if (check == false) {
                xx++;
                gotoXY(70, 3); cout << "X: " << xx;
                gotoXY(x, y);
                cout << 'X'; s[(x - 22) / 4][(y - 6) / 2] = 1;
                if (win(s, (x - 22) / 4, (y - 6) / 2) == true) { //xac dinh thang
                    gotoXY(70, 25); cout << "X win.";
                    char keyy = _getch();
                    return 1;
                }
            }
            else if (may == true) {
                oo++;
                gotoXY(70, 4); cout << "O: " << oo;
                gotoXY(x, y);
                cout << 'O'; s[(x - 22) / 4][(y - 6) / 2] = -1;
                if (win(s, (x - 22) / 4, (y - 6) / 2) == true) { //xac dinh thang
                    gotoXY(70, 25); cout << "O win.";
                    char keyy = _getch();
                    return -1;
                }
            }
        }
        if (key == 27) return 2; //thoat game
    }
}


//Ve bang phu
void bangphu() {
    gotoXY(63, 0); printf("%c", char(201));
    for (int i = 1; i <= 50; i++) printf("%c", char(205));
    printf("%c", char(187));
    for (int j = 1; j <= 18; j++) {
        gotoXY(63, j); printf("%c", char(186));
        gotoXY(114, j); printf("%c", char(186));
    }
    gotoXY(63, 19); printf("%c", char(200));
    for (int i = 1; i <= 50; i++) printf("%c", char(205));
    printf("%c", char(188));

    gotoXY(63, 20); printf("%c", char(201));
    for (int i = 1; i <= 50; i++) printf("%c", char(205));
    printf("%c", char(187));
    for (int j = 21; j <= 29; j++) {
        gotoXY(63, j); printf("%c", char(186));
        gotoXY(114, j); printf("%c", char(186));
    }
    gotoXY(63, 30); printf("%c", char(200));
    for (int i = 1; i <= 50; i++) printf("%c", char(205));
    printf("%c", char(188));
}
void banggame() {
    set_color(0);
    //ve duong tren
    gotoXY(1, 0); printf("%c%c%c%c", char(201), char(205), char(205), char(205));
    gotoXY(1, 1); printf("%c", char(186));
    for (int i = 1; i <= 14; i++) {
        gotoXY(4 * i + 1, 0);
        printf("%c%c%c%c", char(203), char(205), char(205), char(205));
        gotoXY(4 * i + 1, 1);
        printf("%c", char(186));
    }
    gotoXY(61, 0); printf("%c", char(187));
    gotoXY(61, 1); printf("%c", char(186));
    Sleep(20);

    //ve duong giua
    for (int j = 2; j < 30; j = j + 2) {
        gotoXY(1, j); printf("%c%c%c%c", char(204), char(205), char(205), char(205));
        gotoXY(1, j + 1); printf("%c", char(186));
        for (int i = 1; i <= 14; i++) {
            gotoXY(4 * i + 1, j);
            printf("%c%c%c%c", char(206), char(205), char(205), char(205));
            gotoXY(4 * i + 1, j + 1);
            printf("%c", char(186));
        }
        gotoXY(61, j); printf("%c", char(185));
        gotoXY(61, j + 1); printf("%c", char(186));
        Sleep(20);
    }

    //ve duong duoi
    gotoXY(1, 30); printf("%c%c%c%c", char(200), char(205), char(205), char(205));
    for (int i = 1; i <= 14; i++) {
        gotoXY(4 * i + 1, 30);
        printf("%c%c%c%c", char(202), char(205), char(205), char(205));
    }
    gotoXY(61, 30); printf("%c", char(188));

    bangphu();
}


int Start_game(int& kq, int n, bool may) //khoi dong game
{
    CreateConsoleWindow(1200, 700);
    FixConsoleWindow();
    int s[15][15] = {};
    system("cls");
    banggame();
    if (n > -1) { //tai game (neu co)
        Load_game(n, s);
        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 15; j++) {
                gotoXY(22 + j * 4, i * 2 + 6);
                if (s[i][j] == 1) {
                    set_color(4);
                    cout << "X";
                }
                else if (s[i][j] == -1) {
                    set_color(1);
                    cout << "O";
                }
                else cout << " ";
            }
            cout << "\n";
        }
    }
    int ss[15][15];
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15; j++) ss[j][i] = s[i][j];
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15; j++) s[i][j] = ss[i][j];
    while (1) { //vong lap choi game
        kq = dogame(s, true, may);
        gotoXY(70, 28); cout << "Press Enter to play again.";
        char key = _getch();
        if (key == 13 || key == 32) {
            n = -1;
            for (int i = 0; i < 15; i++)
                for (int j = 0; j < 15; j++) s[i][j] = 0;
            system("cls");
            banggame();
            continue;
        }
        else if (key == 27) return kq;
    }
}

int blink_text(int x, int y, std::string(c)) {
    for (int i = 0; i < 5; i++) {
        gotoXY(x, y);
        b_color(c, 78);
        Sleep(50);
        gotoXY(x, y);
        b_color(c, 73);
        Sleep(50);
        b_color("", 240);
    }
    return 0;
}

void dongchuchinh() {
    set_color(4);
    printf("\n               _/_/_/_/_/_/_/_/_ \n");
    printf("            _/_/_/_/_/_/_/_/_/_/_ \n");
    printf("           _/_/_/             _/_/\n");
    printf("          _/_/_/           _/_/_/"); set_color(1); printf("              _/_/_/_/_/_/"); set_color(2); printf("     _/_/_/    _/_/_/_/_/_/"); set_color(6); printf("        _/_/_/_/_/_/_/\n"); set_color(4);
    printf("         _/_/_/"); set_color(1); printf("                        _/_/_/_/_/_/_/_/_/"); set_color(2); printf("        _/_/  _/_/_/_/_/_/_/"); set_color(6); printf("    _/_/_/_/_/_/_/_/_/_/_/\n"); set_color(4);
    printf("        _/_/_/"); set_color(1); printf("                     _/_/           _/_/_/"); set_color(2); printf("        _/_/_/_/_/           "); set_color(6); printf("_/_/_/               _/_/_/\n"); set_color(4);
    printf("       _/_/_/"); set_color(1); printf("                   _/_/               _/_/"); set_color(2); printf("        _/_/_/_/            "); set_color(6); printf("_/_/_/                  _/_/_/\n"); set_color(4);
    printf("      _/_/_/"); set_color(1); printf("                   _/_/               _/_/"); set_color(2); printf("        _/_/_/              "); set_color(6); printf("_/_/_/                  _/_/_/\n"); set_color(4);
    printf("     _/_/_/"); set_color(1); printf("                   _/_/               _/_/"); set_color(2); printf("        _/_/                "); set_color(6); printf("_/_/_/                  _/_/_/\n"); set_color(4);
    printf("    _/_/_/"); set_color(1); printf("                   _/_/               _/_/"); set_color(2); printf("        _/_/                "); set_color(6); printf("_/_/_/                  _/_/_/\n"); set_color(4);
    printf("   _/_/_/         _/_/_/"); set_color(1); printf("    _/_/_/           _/_/_/"); set_color(2); printf("        _/_/                "); set_color(6); printf("_/_/_/                  _/_/_/\n"); set_color(4);
    printf("   _/_/_/_/_/_/_/_/_/_/"); set_color(1); printf("      _/_/_/_/_/_/_/_/_/_/_/"); set_color(2); printf("       _/_/                  "); set_color(6); printf("_/_/_/_/_/_/_/_/_/_/_/_/_/\n"); set_color(4);
    printf("    _/_/_/_/_/_/_/_/_/"); set_color(1); printf("        _/_/_/_/_/_/_/_/_/_/_/_/"); set_color(2); printf("   _/_/                    "); set_color(6); printf("_/_/_/_/_/_/_/_/_/_/_/\n"); set_color(4);
}

void line_up(int x, int y, int w) {
    for (int i = x; i <= x + w; i++) {
        gotoXY(i, y);
        printf("%c", char(196));
    }
    gotoXY(x, y); printf("%c", char(218));
    gotoXY(x + w, y); printf("%c", char(191));
    gotoXY(x, y + 1); printf("%c", char(179));
    gotoXY(x + w, y + 1); printf("%c", char(179));
}
void line_bot(int x, int y, int w) {
    for (int i = x; i <= x + w; i++) {
        gotoXY(i, y);
        printf("%c", char(196));
    }
    gotoXY(x, y); printf("%c", char(195));
    gotoXY(x + w, y); printf("%c", char(180));
    gotoXY(x, y + 1); printf("%c", char(179));
    gotoXY(x + w, y + 1); printf("%c", char(179));
}
void line_down(int x, int y, int w) {
    for (int i = x; i <= x + w; i++) {
        gotoXY(i, y);
        printf("%c", char(196));
    }
    gotoXY(x, y); printf("%c", char(192));
    gotoXY(x + w, y); printf("%c", char(217));
}

void bangchon() {
    line_up(43, 15, 30);
    line_bot(43, 17, 30);
    line_bot(43, 19, 30);
    line_bot(43, 21, 30);
    line_bot(43, 23, 30);
    line_bot(43, 25, 30);
    line_bot(43, 27, 30);
    line_down(43, 29, 30);
}


//MỤC 4. SOUND
int a_th = 1;


//MỤC 5. HELP
void _help() {
    system("cls");
    printf("\n\n\n\t\t\t\t\t\t  CONTROL:");
    printf("\n\n\t\tUsing 'W', 'A', 'S', 'D' button to go up, left, down, right;\n\t\t press Enter to play");
    printf("\n\n\n\t\t\t\t\t\tINSTRUCTION:\n");
    printf("\n\n\t\t1. Caro is a 2-player game. Players alternate turns marking an X or O on an\n\t\t empty square on the board. The X player go first\n");
    printf("\n\t\t2. The winner is the first player to form an unbroken line of five marks of\n\t\t their color horizontally, vertically, or diagonally.\n");
    printf("\n\t\t3. If the board is completely filled and no one can make a line of 5 Xs or\n\t\t Os, then the game ends in a draw\n");
    printf("\n\n\t\tHAVE FUN!");
    printf("\n\n\n\n\n\t\t\t\t\t\t\t\t(Press any key to go back)");
    _getch();
}

void _about() {
    system("cls");
    printf("\n\n\n\n\n\t\t\t\t\t\tGROUP 7 - 23TNT1:");
    printf("\n\n\n\t\t\t\tStudent 1: 23122010_Nguyen Nhat Minh (Leader)");
    printf("\n\n\t\t\t\tStudent 2: 23122005_Le Hai Dang");
    printf("\n\n\t\t\t\tStudent 3: 23122011_Doan Hai Nam");
    printf("\n\n\t\t\t\tStudent 4: 23122027_Vo Ngoc Hieu");
    printf("\n\n\t\t\t\tInstructor: Mr. Truong Toan Thinh");
    _getch();
}

int cn = 1;
void text_with_bg() {
    if (cn == 1) {
        gotoXY(44, 16); b_color(">>>  PLAYER VS COMPUTER   <<<", 78);
    }
    if (cn != 1) {
        gotoXY(44, 16); b_color("     PLAYER VS COMPUTER      ", 240);
    }
    if (cn == 2) {
        gotoXY(44, 18); b_color(">>>   PLAYER VS PLAYER    <<<", 78);
    }
    if (cn != 2) {
        gotoXY(44, 18); b_color("      PLAYER VS PLAYER       ", 240);
    }
    if (cn == 3) {
        gotoXY(44, 20); b_color(">>>       LOAD GAME       <<<", 78);
    }
    if (cn != 3) {
        gotoXY(44, 20); b_color("          LOAD GAME          ", 240);
    }
    if (cn == 4) {
        switch (a_th) {
        case 0:
            gotoXY(44, 22); b_color(">>>      SOUND: OFF       <<<", 78);
            break;
        case 1:
            gotoXY(44, 22); b_color(">>>      SOUND:  ON       <<<", 78);
            break;
        }
    }
    if (cn != 4) {
        switch (a_th) {
        case 0:
            gotoXY(44, 22); b_color("         SOUND: OFF          ", 240);
            break;
        case 1:
            gotoXY(44, 22); b_color("         SOUND:  ON          ", 240);
            break;
        }
    }
    if (cn == 5) {
        gotoXY(44, 24); b_color(">>>          HELP         <<<", 78);
    }
    if (cn != 5) {
        gotoXY(44, 24); b_color("             HELP            ", 240);
    }
    if (cn == 6) {
        gotoXY(44, 26); b_color(">>>         ABOUT         <<<", 78);
    }
    if (cn != 6) {
        gotoXY(44, 26); b_color("            ABOUT            ", 240);
    }

    if (cn == 7) {
        gotoXY(44, 28); b_color(">>>          EXIT         <<<", 78);
    }
    if (cn != 7) {
        gotoXY(44, 28); b_color("             EXIT            ", 240);
    }

}

void menu() {
    int kq, temp;
    system("cls");
    dongchuchinh();
    bangchon();
    text_with_bg();
    int t = _getch();
    if (t == 13) {				//nhan enter
        switch (cn) {
        case 1:
            blink_text(49, 16, "PLAYER VS COMPUTER");
            kq = 2;
            system("cls");
            kq = Start_game(kq, -1, false);
            break;
        case 2:
            blink_text(50, 18, "PLAYER VS PLAYER");
            kq = 2;
            system("cls");
            kq = Start_game(kq, -1, true);
            break;
        case 3:
            blink_text(54, 20, "LOAD GAME");
            temp = f_load();
            if (temp == -1) break;
            kq = Start_game(kq, temp, true);
            break;
        case 4:
            switch (a_th) {
            case 0:
                blink_text(53, 22, "SOUND: OFF");
                a_th = 1;

                break;
            case 1:
                blink_text(53, 22, "SOUND:  ON");
                a_th = 0;

                break;
            }
            break;
        case 5:
            blink_text(57, 24, "HELP");
            _help();
            break;
        case 6:
            blink_text(56, 26, "ABOUT");
            _about();
            break;
        case 7:
            blink_text(57, 28, "EXIT");
            printf("\n\n________________");
            exit(0);
            break;
        }
    }
    else if (t == 80) {			//mui ten xuong
        cn++;
    }
    else if (t == 72) {			//mui ten len
        cn--;
    }
    if (cn == 8) {
        cn = 1;
    }
    else if (cn == 0) {
        cn = 7;
    }
}

int main() {
    CreateConsoleWindow(1200, 700);
    FixConsoleWindow();
    while (1) {
        menu();
    }
    return 0;
}


/* set_color(0);
    char s = 205;
    char c = 215;
    for (int i = 0; i <= 36; i++)
    {
        for (int j = 0; j <= 36; j++)
        {
            if (i < 4) printf(" ");
            else if ((i == 4 || i == 36) && (j >= 20 && j <= 34)) cout << s << s << s << s;
            else if ((i == 4 || i == 36) && (j == 35)) cout << s;
            else if ((j == 19 || j == 36) && (i >= 4 && i <= 36)) cout << c;
            else if (j < 20) printf(" ");
            else if (i % 2 == 1 && j < 35)  printf("%c%c%c%c", 197, 196, 196, 196);
            else if (i % 2 == 0 && j < 35) printf("%c   ", 179);
            else if (i % 2 == 1 && j == 35) printf("%c", 197);
            else if (i % 2 == 0 && j == 35) printf("%c", 179);
        }
        printf("\n");
    }
    for (int i = 0; i < 22; i++) {
        gotoXY(89, 4 + i); cout << c; for (int i = 0; i < 43; i++) cout << " ";
        cout << c << "\n";
    }
    gotoXY(90, 4); for (int i = 0; i < 43; i++) cout << s;
    gotoXY(90, 15); for (int i = 0; i < 43; i++) cout << '_';
    gotoXY(90, 25); for (int i = 0; i < 43; i++) cout << s;*/