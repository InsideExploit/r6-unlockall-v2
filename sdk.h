#pragma once

#include <Windows.h>
#include <string>
#include <direct.h>
#include <fstream>
#include <iostream>

namespace sdk {
	bool IsKeyPressed(INT key);
	void Wait(INT time);
	std::string CurrentPath();

	void enabled(bool type);
	void disabled(bool type);

	void watermark();
}