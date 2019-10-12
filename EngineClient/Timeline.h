#pragma once

class Timeline
{
public:
	virtual ~Timeline() = default;
	virtual int getTime() = 0;
};