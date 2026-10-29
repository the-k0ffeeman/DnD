#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<Windows.h>

#include"Battle.h"

using namespace std;

bool RemoveConsoleScrollback() // source: ChatGPT
{
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO info{};
    if (!GetConsoleScreenBufferInfo(output, &info))
        return false;

    SHORT rows = info.srWindow.Bottom - info.srWindow.Top + 1;
    SHORT columns = info.srWindow.Right - info.srWindow.Left + 1;

    // Put the visible window at the top of the buffer.
    SMALL_RECT window{ 0, 0, columns - 1, rows - 1 };
    if (!SetConsoleWindowInfo(output, TRUE, &window))
        return false;

    // Keep the cursor inside the smaller buffer.
    COORD cursor{ 0, 0 };
    SetConsoleCursorPosition(output, cursor);

    // Keep the buffer's width, but make its height match the visible rows.
    COORD buffer{ info.dwSize.X, rows };
    return SetConsoleScreenBufferSize(output, buffer) != 0;
}

int main()
{
    // Source - https://stackoverflow.com/a/36983796
    // Posted by RED SOFT ADAIR, modified by community. See post 'Timeline' for change history
    // Retrieved 2026-10-28, License - CC BY-SA 4.0

    HWND hwnd = GetConsoleWindow();
    RECT rect = { 50, 20, 700, 1000 };
    MoveWindow(hwnd, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, TRUE);
    if (!RemoveConsoleScrollback())
    {
        cout << "Could not resize console buffer: " << GetLastError() << "\n";
    }

    SetConsoleTitleA("DnD Style Combat");
    srand(time(0));

    Battle battle(3, 5);
    battle.game();

    return 0;
}