#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include<mmsystem.h>
#include <fstream>
#include<string>
#pragma comment(lib,"winmm.lib")
using namespace std;

#define CONSOLE_WIDTH 1280
#define CONSOLE_HEIGHT 720
//Keyboard
#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_LEFT 75
#define ARROW_RIGHT 77
#define KEY_ENTER 13
#define SPACE 32
#define KEY_ESC 27

struct _BufferInfo {
    int col;
    int row;
};
void menu();
void Start_game(int& kq, int n, bool may);
void End_game();
void Save_game(int s[15][15], bool current);
bool win(int s[15][15], int x, int y);
void SET_COLOR(int color)
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}
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
void HideCursor(bool visible)
{
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = visible;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}
void SetColor(int color)
{
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
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


void Ancontro() {
    CONSOLE_CURSOR_INFO Info;
    Info.bVisible = FALSE;
    Info.dwSize = 20;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
void Hiencontro()
{
    CONSOLE_CURSOR_INFO Info;
    Info.bVisible = TRUE;
    Info.dwSize = 20;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}


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
void resizeConsole(int width, int height)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, height, TRUE);
}
_BufferInfo GetConsoleSize()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    _BufferInfo bf = { columns, rows };
    return bf;
}
int a_th;
void _sound() {
    if (a_th == 1) PlaySound(TEXT("01.-Main-Menu.wav"), NULL, SND_ASYNC | SND_LOOP);
    else if (a_th == 2) PlaySound(TEXT("win.wav"), NULL, SND_ASYNC);
    else if (a_th == 3) PlaySound(TEXT("lose.wav"), NULL, SND_ASYNC);
    else if (a_th == 4)PlaySound(TEXT("draw.wav"), NULL, SND_ASYNC);
    else if (a_th == 5)PlaySound(TEXT("ingame.wav"), NULL, SND_ASYNC);
    else PlaySound(NULL, NULL, SND_ASYNC);
}
vector<string> ReadFile(string filename)
{
    std::fstream textFile;
    textFile.open(filename.c_str(), std::fstream::in);
    string line;
    std::vector<std::string> line1;
    while (getline(textFile, line))
        line1.push_back(line);
    textFile.close();
    return line1;
}
void DrawBox(int color, int width, int height, int x, int y, int delay)
{
    SetColor(color);
    gotoXY(x, y);

    for (int i = 0; i < width; i++)
    {
        cout << " ";
    }
    for (int i = 1; i <= height; i++)
    {
        Sleep(delay);
        gotoXY(x, y + i);
        cout << " ";
        SetColor(14 * 16 + 14);
        for (int j = 0; j < width - 2; j++)
        {
            cout << " ";
        }
        SetColor(color);
        cout << " ";
        SetColor(8 * 16 + 2);
        cout << " ";
        SetColor(color);
    }
    SetColor(color);
    gotoXY(x, y + height + 1);
    Sleep(delay);
    for (int i = 0; i < width; i++)
    {
        cout << " ";
    }
    SetColor(8 * 16 + 2);
    cout << " ";
    for (int i = 1; i <= width; i++)
    {
        gotoXY(x + i, y + height + 2);
        cout << " ";
    }
    SetColor(240);
}
void PrintText(string text, int color, int x, int y)
{
    gotoXY(x, y);
    SetColor(color);
    cout << text;
    SetColor(240);
}
void DrawFromFile(string filename, int color, int x, int y)
{
    int tempY = y;
    vector<string> line1 = ReadFile(filename);

    if (filename == "XWin.txt" || filename == "OWin.txt" || filename == "Draw.txt" || filename == "PWin.txt" || filename == "PLose.txt")
    {
        int turn = 0;
        while (1)
        {
            turn = turn % 4;
            for (int i = 0; i < line1.size() / 4; i++)
                PrintText(line1[i + 9 * turn], color + turn % 15, x, y++);
            y = tempY;
            Sleep(500);
            turn++;
            gotoXY(0, y);
            PrintText("Press any key to skip...", 240, x + 40, y + 10);
            if (_kbhit())
            {
                int kb = _getch();
                system("cls");
                break;
            };
        }
    }
    else
    {
        for (int i = 0; i < line1.size(); i++)
        {
            PrintText(line1[i], color, x, y);
            y++;
        }
    }
}
void YesNoHighlight(int k)
{
    _BufferInfo bf = GetConsoleSize();
    switch (k)
    {
    case 1:
        DrawFromFile("Yes.txt", 7 * 16 + 12, (bf.col - 60) / 2, (bf.row - 20));
        DrawFromFile("No.txt", 14 * 16 + 0, (bf.col + 15) / 2, (bf.row - 20));
        break;
    case 2:
        DrawFromFile("Yes.txt", 14 * 16 + 0, (bf.col - 60) / 2, (bf.row - 20));
        DrawFromFile("No.txt", 7 * 16 + 12, (bf.col + 15) / 2, (bf.row - 20));
        break;
    }
}
int AskContinueAction()
{
    _BufferInfo bf = GetConsoleSize();
    DrawFromFile("Yes.txt", 7 * 16 + 12, (bf.col - 60) / 2, (bf.row - 20));
    fflush(stdin);
    int k = 1;
    do
    {
        int cmd = toupper(_getch());
        if ((cmd == 'D' || cmd == ARROW_RIGHT) && k < 2)
        {
            k++;
            YesNoHighlight(k);
        }
        else if ((cmd == 'A' || cmd == ARROW_LEFT) && k > 1)
        {
            k--;
            YesNoHighlight(k);
        }
        else if (cmd == KEY_ENTER)
        {
            return k;
            break;
        }
    } while (1);
}
int AskContinueBox(bool may)
{
    int kq = 0;
    _BufferInfo bf = GetConsoleSize();
    DrawBox(16, 100, 20, (bf.col - 100) / 2, (bf.row - 20) / 2, 50);

    DrawFromFile("Continue.txt", 14 * 16 + 5, (bf.col - 80) / 2, (bf.row - 28));
    DrawFromFile("Yes.txt", 14 * 16 + 0, (bf.col - 60) / 2, (bf.row - 20));
    DrawFromFile("No.txt", 14 * 16 + 0, (bf.col + 15) / 2, (bf.row - 20));
    int Action = AskContinueAction();
    if (Action == 1) {
        a_th = 5*(a_th!=0);
        _sound();
        system("cls");
        HideCursor(true);
        return 1;
    }
    else if (Action == 2) {
        a_th = 1 * (a_th != 0);
        _sound();
        system("cls");
        HideCursor(true);
        return 0;
    }
}
int End_game(int kq, bool may)
{

    int a;
    _BufferInfo bf = GetConsoleSize();
    HideCursor(false);
    switch (kq)
    {
    case 1:
        a_th = 2 * (a_th != 0);
        _sound();
        system("cls");
        DrawFromFile("XWin.txt", 240, bf.col / 2 - 30, bf.row / 2 - 10);
        a = AskContinueBox(may);
        break;
    case 0:
        a_th = 4 * (a_th != 0);
        _sound();
        system("cls");
        DrawFromFile("Draw.txt", 240, bf.col / 2 - 30, bf.row / 2 - 10);
        a = AskContinueBox(may);
        break;
    case -1:
        a_th = 3 * (a_th != 0);
        _sound();
        system("cls");
        DrawFromFile("OWin.txt", 240, bf.col / 2 - 30, bf.row / 2 - 10);
        a = AskContinueBox(may);
        break;
    case 2:
        a_th = 2 * (a_th != 0);
        _sound();
        system("cls");
        DrawFromFile("PWin.txt", 240, bf.col / 2 - 30, bf.row / 2 - 10);
        a = AskContinueBox(may);
        break;
    case -2:
        a_th = 3 * (a_th != 0);
        _sound();
        system("cls");
        DrawFromFile("PLose.txt", 240, bf.col / 2 - 30, bf.row / 2 - 10);
        a = AskContinueBox(may);
        break;
    default:
        break;
    }
    HideCursor(true);
    return a;
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
void Save_game(vector<int> v, bool current) //luu game
{
    fstream input("input.txt", ios::app);
    fstream output("output.txt", ios::app);
    if (current == true) {
        gotoXY(70, 24); cout << "Press name: ";
        string ten;
        getline(cin, ten); input << ten << "\n";
        for (int i = 0; i < v.size(); i++) {
            output << v[i] << " ";
        }
        output << 100 << "\n";
    }
    input.close();
    a_th = 1*(a_th!=0);
    _sound();
}
void Load_game(int n, vector<int>& v) //tai game
{
    fstream output("output.txt");
    for (int i = 0; i < n; i++) output.ignore(1000, '\n');
    int i;
    while (1) {
        output >> i;
        if (i == 100) return;
        v.push_back(i);
    }
    a_th = 5*(a_th!=0);
    _sound();
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
void xoagame(int n)
{
    vector<string> v, v2;
    fstream input("input.txt");
    fstream output("output.txt");
    for (int i = 0; i < 10; i++) {
        string s, t;
        getline(input, s);
        getline(output, t);
        if (s.empty() == 0) v.push_back(s);
        if (t.empty() == 0) v2.push_back(t);
    }
    input.close(); output.close();
    v.erase(v.begin() + n);
    v2.erase(v2.begin() + n);
    fstream input2("input.txt", ios::out);
    fstream output2("output.txt", ios::out);
    for (int i = 0; i < v.size(); i++) {
        input2 << v[i] << "\n";
        output2 << v2[i] << "\n";
    }
    input2.close(); output2.close();
}
int f_load() //tuy chon tai game
{
    system("cls");
    int z = 0;
    ifstream input("input.txt");
    for (int i = 0; i < 10; i++) {
        string s;
        line_up(35, 2, 40);
        for (int j = 4; j <= 20; j += 2) line_bot(35, j, 40);
        line_down(35, 22, 40);
        gotoXY(41, 3 + i * 2);
        getline(input, s); if (s.size() == 0) break;
        z++;
        cout << i << ". "; cout << s;
        gotoXY(41, 5 + i * 2);
    }
    gotoXY(41, 1); cout << "Press from 0 to " << z - 1 << " to choose game.";
    gotoXY(41, 24); cout << " Press F to delete game.";
    char key = _getch();
    if (key >= 48 && key < 48 + z) return (key - 48);
    else if (key == 70 || key == 102) {
        cout << "Press from 0 to " << z - 1 << " to choose game to delete: ";
        char key = _getch();
        if (key >= 48 && key < 48 + z) xoagame(key - 48);
        gotoXY(41, 25); cout << "Game " << key - 48 << " has been deleted!";
        Sleep(1000); system("cls");
        return -1;
    }
    else {
        system("cls");
        return -1;
    }
}
void nhapnhay(int s[15][15])
{
    int x = 0;
    while (x < 5) {
        for (int i = 0; i < 15; i++)
            for (int j = 0; j < 15; j++) if (win(s, i, j) == true) {
                gotoXY(i * 4 + 3, j * 2 + 1); cout << " ";
            }
        Sleep(100);
        for (int i = 0; i < 15; i++)
            for (int j = 0; j < 15; j++) if (win(s, i, j) == true) {
                if (s[i][j] == 1) {
                    gotoXY(i * 4 + 3, j * 2 + 1);
                    set_color(4); cout << "X";
                }
                else if (s[i][j] == -1) {
                    gotoXY(i * 4 + 3, j * 2 + 1);
                    set_color(1); cout << "O";
                }
            }
        Sleep(100);
        x++;
    }
}
void load_to(vector<int>& v, bool& check, int s[15][15], int& xx, int& oo)
{
    if (v.size() > 0) {
        if (v[2] == -1) check = !check;
        for (int i = 0; i < v.size(); i += 3) {
            if (v[i + 2] == 1) {
                gotoXY(v[i], v[i + 1]);
                set_color(4); cout << "X";
                s[(v[i] - 3) / 4][(v[i + 1] - 1) / 2] = 1;
                xx++;
            }
            else {
                gotoXY(v[i], v[i + 1]);
                set_color(1); cout << "O";
                s[(v[i] - 3) / 4][(v[i + 1] - 1) / 2] = -1;
                oo++;
            }
            check = !check;
            Sleep(200);
        }
    }
}
int dogame(vector<int> v, bool cur, bool may) //thuc hien game
{
    set_color(0);
    //ShowScrollbar(0);
    gotoXY(1, 1);
    char key;
    int s[15][15] = {};
    int x = 3, y = 1;
    int xx = 0, oo = 0; //dem luot di
    bool check = cur;
    load_to(v, check, s, xx, oo);
    gotoXY(70, 22); cout << "Press Backspace to save game and cancel";
    gotoXY(70, 2); cout << "Number of moves: ";
    gotoXY(70, 3); cout << "X: " << xx;
    gotoXY(70, 4); cout << "O: " << oo;
    while (1) { //bat dau choi
        if (xx + oo == 225)  return 0;
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
                if (s[(x - 3) / 4][(y - 1) / 2] == 0) {
                    oo++;
                    v.push_back(x); v.push_back(y); v.push_back(-1);
                    gotoXY(70, 4); cout << "O: " << oo;
                    gotoXY(x, y);
                    cout << 'O'; s[(x - 3) / 4][(y - 1) / 2] = -1;
                    if (win(s, (x - 3) / 4, (y - 1) / 2) == true) {
                        nhapnhay(s);
                        return -2;
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
        if (key == 32) return 2; //choi lai
        if (key == 8) { //luu game
            Save_game(v, true); return 3;
        }
        if ((key == 97 || key == 65) && x > 3) { gotoXY(x - 4, y); x -= 4; }
        if ((key == 119 || key == 87) && y > 1) { gotoXY(x, y - 2); y -= 2; }
        if ((key == 100 || key == 68) && x < 59) { gotoXY(x + 4, y); x += 4; }
        if ((key == 115 || key == 83) && y < 29) { gotoXY(x, y + 2); y += 2; }
        if (key == 13 && s[(x - 3) / 4][(y - 1) / 2] == 0) {
            check = !check;
            if (check == false) { //nuoc di cua X
                xx++;
                v.push_back(x); v.push_back(y); v.push_back(1);
                gotoXY(70, 3); cout << "X: " << xx;
                gotoXY(x, y);
                cout << 'X'; s[(x - 3) / 4][(y - 1) / 2] = 1;
                if (win(s, (x - 3) / 4, (y - 1) / 2) == true) { //xac dinh thang
                    nhapnhay(s);
                    return 1;
                }
            }
            else if (may == true) { // nuoc di cua O
                oo++;
                v.push_back(x); v.push_back(y); v.push_back(-1);
                gotoXY(70, 4); cout << "O: " << oo;
                gotoXY(x, y);
                cout << 'O'; s[(x - 3) / 4][(y - 1) / 2] = -1;
                if (win(s, (x - 3) / 4, (y - 1) / 2) == true) { //xac dinh thang
                    nhapnhay(s);
                    return -1;
                }
            }
        }
        if (key == 27) return 4; //thoat game
    }
}

//Ve bang phu
void bangphu() {
    gotoXY(63, 0); printf("%c", char(201));
    for (int i = 1; i <= 50; i++) printf("%c", char(205));
    printf("%c", char(187));
    Sleep(10);
    for (int j = 1; j <= 18; j++) {
        gotoXY(63, j); printf("%c", char(186));
        gotoXY(114, j); printf("%c", char(186));
        Sleep(10);
    }
    gotoXY(63, 19); printf("%c", char(200));
    for (int i = 1; i <= 50; i++) printf("%c", char(205));
    printf("%c", char(188));
    Sleep(10);

    gotoXY(63, 20); printf("%c", char(201));
    for (int i = 1; i <= 50; i++) printf("%c", char(205));
    printf("%c", char(187));
    Sleep(10);
    for (int j = 21; j <= 29; j++) {
        gotoXY(63, j); printf("%c", char(186));
        gotoXY(114, j); printf("%c", char(186));
        Sleep(10);
    }
    gotoXY(63, 30); printf("%c", char(200));
    for (int i = 1; i <= 50; i++) printf("%c", char(205));
    printf("%c", char(188));
    Sleep(10);
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

void Start_game(int& kq, int n, bool may) //khoi dong game
{
    a_th = 5 * (a_th != 0);
    _sound();
    FixConsoleWindow();
    vector<int> v;
    int x = 0, o = 0;
    bool cur = true;
    if (n > -1)  //tai game (neu co)
        Load_game(n, v);
    gotoXY(90, 1);
    while (1) { //vong lap choi game
        system("cls");
        banggame();
        gotoXY(90, 5); cout << "Player X win: " << x; //dem so lan X win
        gotoXY(90, 7); cout << "Player O win: " << o; //dem so lan O win
        gotoXY(70, 23); cout << "Press Space to play again.";
        gotoXY(70, 27); cout << "Press ESC to return to menu.";
        kq = dogame(v, cur, may);
        if (kq == 1) x++;
        else if (kq < 0) o++;
        if (kq == 2) {
            v.clear(); continue;
        }
        if (kq == 3 || kq == 4) {
            system("cls");
            break;
        }
        int a = End_game(kq, may);
        if (a == 1) {
            n = -1; cur = !cur;
            v.clear();
            continue;
        }
        else break;
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
    gotoXY(0, 0);
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

//MỤC 5. HELP
void _help() {
    system("cls");
    printf("\n\n\n\t\t\t\t\t\t  CONTROL:");
    printf("\n\n\t\tUsing 'W', 'A', 'S', 'D' button to go up, left, down, right;\n\t\t press Enter to play");
    printf("\n\n\t\tTurn on English keyboard to play");
    printf("\n\n\n\t\t\t\t\t\tINSTRUCTION:\n");
    printf("\n\n\t\t1. Caro is a 2-player game. Players alternate turns marking an X or O on an\n\t\t empty square on the board. The X player go first\n");
    printf("\n\t\t2. The winner is the first player to form an unbroken line of five marks of\n\t\t their color horizontally, vertically, or diagonally.\n");
    printf("\n\t\t3. If the board is completely filled and no one can make a line of 5 Xs or\n\t\t Os, then the game ends in a draw\n");
    printf("\n\n\t\tHAVE FUN!");
    printf("\n\n\n\n\n\t\t\t\t\t\t\t\t(Press any key to go back)");
    _getch();
    system("cls");
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
    system("cls");
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
        HANDLE hConsoleColor;
        hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsoleColor, 240);
    }
    if (cn != 7) {
        gotoXY(44, 28); b_color("             EXIT            ", 240);
    }

}

void menu() {
    int kq, temp;
    text_with_bg();
    dongchuchinh();
    bangchon();
    Ancontro();
    int t = _getch();
    if (t == 13) {				//nhan enter
        Hiencontro();
        switch (cn) {
        case 1:
            blink_text(49, 16, "PLAYER VS COMPUTER");
            kq = 2;
            system("cls");
            Start_game(kq, -1, false);
            break;
        case 2:
            blink_text(50, 18, "PLAYER VS PLAYER");
            kq = 2;
            system("cls");
            Start_game(kq, -1, true);
            break;
        case 3:
            blink_text(54, 20, "LOAD GAME");
            temp = f_load();
            if (temp == -1) break;
            Start_game(kq, temp, true);
            break;
        case 4:
            switch (a_th) {
            case 0:
                blink_text(53, 22, "SOUND: OFF");
                a_th = 1;
                _sound();
                break;
            case 1:
                blink_text(53, 22, "SOUND:  ON");
                a_th = 0;
                _sound();
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
    SetConsoleTitle(L"Game Caro");
    CreateConsoleWindow(1100, 700);
    FixConsoleWindow();
    a_th = 1;
    _sound();
    while (1) {
        menu();
    }
    return 0;
}
