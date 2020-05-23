#include "ConsoleUtils.h"

#include <conio.h>
#include <iostream>

namespace ConUtls
{
  void SetColor(int bgcolor, int txtcolor, HANDLE hStdOut)
  {
    if (!hStdOut)
      hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    WORD wColor = ((bgcolor & 0xF) << 4) + (txtcolor & 0x0F);
    SetConsoleTextAttribute(hStdOut, wColor);
  }

  void SetTextColor(int color, HANDLE hStdOut)
  {
    if(!hStdOut)
      hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
      SetColor((csbi.wAttributes >> 4) & 0xF, color, hStdOut);
  }

  void SetTextBackground(int color, HANDLE hStdOut)
  {
    if (!hStdOut)
      hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
      SetColor(color, csbi.wAttributes & 0xF, hStdOut);
  }

  void GotoXY(int x, int y, HANDLE hStdOut)
  {
    if (!hStdOut)
      hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(
      hStdOut,
      coord
    );
  }

  void ClearScr(HANDLE hStdOut)
  {
    if(!hStdOut)
      hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD coordScreen = { 0, 0 };    /* here's where we'll home the
                                        cursor */
    BOOL bSuccess;
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */
    DWORD dwConSize;                 /* number of character cells in
                                        the current buffer */

                                        /* get the number of character cells in the current buffer */

    bSuccess = GetConsoleScreenBufferInfo(hStdOut, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    /* fill the entire screen with blanks */

    bSuccess = FillConsoleOutputCharacter(hStdOut, (TCHAR)' ',
      dwConSize, coordScreen, &cCharsWritten);

    /* get the current text attribute */

    bSuccess = GetConsoleScreenBufferInfo(hStdOut, &csbi);

    /* now set the buffer's attributes accordingly */

    bSuccess = FillConsoleOutputAttribute(hStdOut, csbi.wAttributes,
      dwConSize, coordScreen, &cCharsWritten);

    /* put the cursor at (0, 0) */

    bSuccess = SetConsoleCursorPosition(hStdOut, coordScreen);
    return;
  }

  void SetShowCursor(bool showFlag, HANDLE hStdOut)
  {
    if(!hStdOut)
      hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(hStdOut, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(hStdOut, &cursorInfo);
  }

  std::string GetLineWithLimit(int width, std::string defaultString, bool acceptEmpty, bool* escaped)
  {
    char key;
    std::string result = defaultString;
    std::cout << defaultString;

    bool canExit;

    do
    {
      key = _getch();

      if (key != 0 && key != -32)
      {
        if (key == 8) //Backspace
        {
          if (result.length() > 0)
          {
            result.pop_back();
            std::cout << "\b \b";
          }
        }
        else if (key == 27 && escaped) //Escape
        {
          *escaped = true;
          return result;
        }
        else if (key != 13) //Any key that isn't ENTER
        {
          if (result.length() < width)
          {
            result.push_back(key);
            std::cout << key;
          }
        }
      }
      else
      {
        _getch();
      }

      canExit = (key == 13 && (result.length() > 0 || acceptEmpty));

    } while (!canExit);

    if(escaped)
      *escaped = false;
    return result;
  }

  int GetLineWithLimit(int width, int defaultNumber, bool allowZero, bool* escaped)
  {
    char key;
    std::string str = std::to_string(defaultNumber);
    std::cout << defaultNumber;

    bool canExit;
    int result;

    do
    {
      key = _getch();

      if (key != 0 && key != -32)
      {
        if (key == 8) //Backspace
        {
          if (str.length() > 0)
          {
            str.pop_back();
            std::cout << "\b \b";
          }
        }
        else if (key == 27 && escaped) //Escape
        {
          *escaped = true;
          return 0;
        }
        else if (key != 13) //Any key that isn't ENTER
        {
          if ((key > 47) && (key < 58))
          {
            if (str.length() < width)
            {
              str.push_back(key);
              std::cout << key;
            }
          }
        }
      }
      else
      {
        _getch();
      }

      if (str.length() > 0)
        result = std::stoi(str);
      else
        result = 0;

      canExit = (key == 13 && ((result != 0) || allowZero));

    } while (!canExit);

    if (escaped)
      *escaped = false;
    return result;
  }
}