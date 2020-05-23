#ifndef _TGT_CONSOLE_UI_UTILS
#define _TGT_CONSOLE_UI_UTILS

namespace ConUI
{
	//The box property masks.
	enum BoxProperty
	{
		HEADER = 1,
		FOOTER = 2
	};

	//Draws a line with a starting character, middle characters and last character for a specified width.
	void DrawLine(char first, char between, char last, int width);

	//Draws a hollow rectangle, optionally with header or footer.
	//typeMask = BoxProprty masks
	void DrawBox(int x, int y, int width, int height, int typeMask, int ldIntervalMs);

	//Draws a hollow rectangle for value input.
	void DrawInputBox(int x, int y, int width, int height);

	/*
		Clears a box and it's contents.

		Xa = Horizontal position of the upper left corner
		Ya = Vertical position of the upper left corner
		Xb = Horizontal position of the lower right corner
		Yb = Vertical position of the lower right corner
		ldIntervalMs = Delay between line deletion
	*/
	void ClearBox(int Xa, int Ya, int Xb, int Yb, int ldIntervalMs);
}

#endif // !_TGT_CONSOLE_UI_UTILS
