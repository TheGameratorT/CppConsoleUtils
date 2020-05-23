#ifndef _TGT_CONSOLE_UTILS_H
#define _TGT_CONSOLE_UTILS_H

#include <string>

#include <windows.h>

namespace ConUtls
{
  enum TextColor
  {
    Black,
    Blue,
    Green,
    Cyan,
    Red,
    Magenta,
    Brown,
    LightGray,
    DarkGray,
    LightBlue,
    LightGreen,
    LightCyan,
    LightRed,
    LightMagenta,
    Yellow,
    White
  };

  void SetColor(int bgcolor, int txtcolor, HANDLE hStdOut = nullptr);

  void SetTextColor(int color, HANDLE hStdOut = nullptr);

  void SetTextBackground(int color, HANDLE hStdOut = nullptr);

  void GotoXY(int x, int y, HANDLE hStdOut = nullptr);

  void ClearScr(HANDLE hStdOut = nullptr);

  void SetShowCursor(bool showFlag, HANDLE hStdOut = nullptr);

  std::string GetLineWithLimit(int width, std::string defaultString, bool acceptEmpty, bool* escaped = nullptr);

  int GetLineWithLimit(int width, int defaultNumber, bool allowZero, bool* escaped = nullptr);
}

#endif // !_TGT_CONSOLE_UTILS_H

