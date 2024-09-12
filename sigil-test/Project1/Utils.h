#pragma once

struct Vector2
{
	float x;
	float y;
};

const int screenWidth = 800;
const int screenHalfWidth = screenWidth / 2;
const int screenHeight = 600;
const int screenHalfHeight = screenHeight / 2;

//First it'll do a random from 0 to "max", then it'll sum "add" to the result.
int GetRandomNum(int max, int add);