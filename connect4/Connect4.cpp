#include <iostream>
#include <random>
#include "Connect4.h"

Connect4::Connect4() {
	this->fillGrid();

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(1, 2);
	this->player = dist(rng);
}
Connect4::Connect4(bool youStart) {
	this->fillGrid();
	this->player = youStart ? 1 : 2;
}

void Connect4::fillGrid()
{
	this->grid = new int* [P4_SIZE_X];
	for (int i = 0; i < P4_SIZE_X; i++) {
		this->grid[i] = new int[P4_SIZE_Y];
		for (int j = 0; j < P4_SIZE_Y; j++) {
			this->grid[i][j] = 0;
		}
	}
}
bool Connect4::verifToken(int x, int y, int token)
{
	for (int i = 0; i < 4; i++) {
		if (this->consecutiveTokens(x, y, this->directions[i][0][0], this->directions[i][0][1]) + this->consecutiveTokens(x, y, this->directions[i][1][0], this->directions[i][1][1]) + (this->getToken(x, y) == token ? 1 : 0) >= 4)
			return true;
	}
	return false;
}
int Connect4::consecutiveTokens(int x, int y, int sensX, int sensY)
{
	int count = 0;
	int cooPointX = x;
	int cooPointY = y;
	int nextCooPointX = x + sensX;
	int nextCooPointY = y + sensY;
	while (this->tokenInGrid(nextCooPointX, nextCooPointY) && this->getToken(cooPointX, cooPointY) == this->getToken(nextCooPointX, nextCooPointY)) {
		count++;
		cooPointX = cooPointX + sensX;
		cooPointY = cooPointY + sensY;
		nextCooPointX = cooPointX + sensX;
		nextCooPointY = cooPointY + sensY;
	}
	return count;
}
bool Connect4::tokenInGrid(int x, int y)
{
	return x >= 0 && y >= 0 && x < P4_SIZE_X && y < P4_SIZE_X;
}


int** Connect4::getGrid()
{
	return this->grid;
}
int Connect4::getPlayer()
{
	return this->player;
}
int Connect4::getToken(int x, int y)
{
	return this->grid[x][y];
}
bool Connect4::columnFilled(int column)
{
	return this->grid[column][P4_SIZE_Y - 1] != 0;
}
int Connect4::columnTokenCount(int column)
{
	int tokenCount = 0;
	for (int i = 0; i < P4_SIZE_Y - 1; i++)
	{
		if (this->grid[column][i] != 0)
		{
			tokenCount++;
		}
	}
	std::cout << "-->" << tokenCount << std::endl;
	return tokenCount;
}
bool Connect4::gridFilled()
{
	for (int i = 0; i < P4_SIZE_X; i++) {
		if (!this->columnFilled(i))
			return false;
	}
	return true;
}
void Connect4::showGrid()
{
	for (int j = 1; j < P4_SIZE_X * 4 + 2; j++) {
		std::cout << "-";
	}
	std::cout << std::endl;
	for (int j = P4_SIZE_Y - 1; j >= 0; j--) {
		std::cout << "|";
		for (int i = 0; i < P4_SIZE_X; i++) {
			char token = ' ';
			if (this->grid[i][j] == 1)
				token = 'X';
			else if (this->grid[i][j] == 2)
				token = 'O';
			std::cout << " " << token << " |";
		}
		std::cout << std::endl;
		for (int j = 1; j < P4_SIZE_X * 4 + 2; j++) {
			std::cout << "-";
		}
		std::cout << std::endl;
	}
}
bool Connect4::addToken(int column)
{
	int tokenHeight = 0;
	while (this->grid[column][tokenHeight] != 0 && tokenHeight < P4_SIZE_Y - 1) {
		tokenHeight++;
	}
	this->grid[column][tokenHeight] = this->player;
	return this->verifToken(column, tokenHeight, this->player);
}
void Connect4::next()
{
	this->player = 3 - this->player;
}