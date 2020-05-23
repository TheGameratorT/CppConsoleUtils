#ifndef _TGT_CONSOLE_UTILS_H
#define _TGT_CONSOLE_UTILS_H

#include <string>

#include <windows.h>

namespace ConUtls
{
  //Colors that can be used by the console.
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

  //Sets the background and text color for the next text to be written.
  void SetColor(int bgcolor, int txtcolor, HANDLE hStdOut = nullptr);

  //Sets the text color and keeps previous background color for the next text to be written.
  void SetTextColor(int color, HANDLE hStdOut = nullptr);

  //Sets the background color and keeps previous text color for the next text to be written.
  void SetTextBackground(int color, HANDLE hStdOut = nullptr);

  //Goes to a X, Y coordinate in the console.
  void GotoXY(int x, int y, HANDLE hStdOut = nullptr);

  //Clears the console.
  void ClearScr(HANDLE hStdOut = nullptr);

  //Sets if the text cursor is displayed or not.
  void SetShowCursor(bool showFlag, HANDLE hStdOut = nullptr);

  //Reads a string with a max input size.
  std::string GetLineWithLimit(int width, std::string defaultString, bool acceptEmpty, bool* escaped = nullptr);

  //Reads an integer with a max input size.
  int GetLineWithLimit(int width, int defaultNumber, bool allowZero, bool* escaped = nullptr);
}

#endif // !_TGT_CONSOLE_UTILS_H

