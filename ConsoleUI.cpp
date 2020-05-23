#include "ConsoleUI.h"
#include "ConsoleUtils.h"

#include <iostream>
#include <chrono>
#include <thread>

using namespace std::this_thread;     // sleep_for, sleep_until

namespace ConUI
{
	void DrawLine(char first, char between, char last, int width)
	{
		std::cout << first;
		for(int i = 0; i < width - 2; i++)
			std::cout << between;
		std::cout << last;
	}

	void DrawBox(int x, int y, int width, int height, int typeMask, int ldIntervalMs)
	{
		std::chrono::milliseconds timespan(ldIntervalMs);

		ConUtls::GotoXY(x, y);
		DrawLine(201, 205, 187, width);
		sleep_for(timespan);

		bool hasHeader = typeMask & BoxProperty::HEADER;
		bool hasFooter = typeMask & BoxProperty::FOOTER;

		int heightShfit = 2;
		if (hasHeader)
		{
			ConUtls::GotoXY(x, y + 1);
			DrawLine(186, ' ', 186, width);
			sleep_for(timespan);
			ConUtls::GotoXY(x, y + 2);
			DrawLine(204, 205, 185, width);
			heightShfit += 2;
		}
		if (hasFooter)
			heightShfit += 2;

		for (int i = 1; i <= height - heightShfit; i++)
		{
			ConUtls::GotoXY(x, y + i + (hasHeader ? 2 : 0));
			DrawLine(186, ' ', 186, width);
			sleep_for(timespan);
		}

		if (hasFooter)
		{
			ConUtls::GotoXY(x, y + height - 3);
			DrawLine(204, 205, 185, width);
			sleep_for(timespan);
			ConUtls::GotoXY(x, y + height - 2);
			DrawLine(186, ' ', 186, width);
			sleep_for(timespan);
		}

		ConUtls::GotoXY(x, y + height - 1);
		DrawLine(200, 205, 188, width);
	}

	void DrawInputBox(int x, int y, int width, int height)
	{
		ConUtls::GotoXY(x, y);
		DrawLine(218, 196, 191, width);
		for (int i = 1; i <= height - 2; i++)
		{
			ConUtls::GotoXY(x, y + i);
			DrawLine(179, ' ', 179, width);
		}
		ConUtls::GotoXY(x, y + height - 1);
		DrawLine(192, 196, 217, width);
	}

	void ClearBox(int Xa, int Ya, int Xb, int Yb, int ldIntervalMs)
	{
		std::chrono::milliseconds timespan(ldIntervalMs);

		int Xd = Xb - Xa; //Calculate box width
		int Yd = Yb - Ya; //Calculate box height
		for (int i = Yd; i >= 0; i--) //For each line of the rectangle to be cleaned starting with the last
		{
			ConUtls::GotoXY(Xa, Ya + i); //Go to the first column and the row (row - number of clean rows)
			for (int j = 0; j <= Xd; j++) //For the length of each line
				std::cout << ' '; //Clear character at position
			sleep_for(timespan); //Esperar o tempo especificado depois de limpar a linha até passar à próxima
		}
	}
}
