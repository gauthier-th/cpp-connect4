#pragma once

#define P4_SIZE_X 7
#define P4_SIZE_Y 6

class Connect4
{
private:
	int** grid;
	int player = 1;
	int directions[4][2][2] = {
		{
			{ 1, 0 },
			{ -1, 0 }
		},
		{
			{ 0, 1 },
			{ 0, -1 }
		},
		{
			{ 1, 1 },
			{ -1, -1 }
		},
		{
			{ 1,-1 },
			{ -1, 1 }
		}
	};
	void fillGrid();
	bool verifToken(int x, int y, int token);
	int consecutiveTokens(int x, int y, int dirX, int dirY);
	bool tokenInGrid(int x, int y);
public:
	static const int SIZE_X = P4_SIZE_X;
	static const int SIZE_Y = P4_SIZE_Y;
	Connect4();
	Connect4(bool youStart);
	int getPlayer();
	int getToken(int x, int y);
	int** getGrid();
	bool columnFilled(int column);
	int columnTokenCount(int column);
	bool gridFilled();
	void showGrid();
	bool addToken(int column);
	void next();
};

