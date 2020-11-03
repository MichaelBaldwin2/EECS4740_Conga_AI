#pragma once

struct Move
{
	int x, y;
	int direction;
};

class Agent
{
public:
	std::string name;

public:
	virtual Move GetMove() = 0;
};


