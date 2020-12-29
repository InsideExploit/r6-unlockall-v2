#include "sdk.h"

bool sdk::IsKeyPressed(INT key) {
	if (GetAsyncKeyState(key)) {
		return true;
	}
	else {
		return false;
	}
}

void sdk::Wait(INT time) {
	Sleep(time);
}

std::string sdk::CurrentPath()
{
	char* cwd = _getcwd(0, 0);
	std::string directory(cwd);
	std::free(cwd);
	return directory;
}

void sdk::enabled(bool type) {

	while (type) {
		std::cout << "\n[+] enabled";
		sdk::Wait(300);
		type = false;
	}
}

void sdk::disabled(bool type) {

	while (type) {
		std::cout << "\n[+] disabled";
		sdk::Wait(300);
		type = false;
	}
}

void sdk::watermark() {
	SetConsoleTitleA("Coded by InsideExploit [UC] | Release of 29/12/2020");

	std::cout << R"(
  _    _ _   _ _      ____   _____ _  __           _      _      
 | |  | | \ | | |    / __ \ / ____| |/ /     /\   | |    | |     
 | |  | |  \| | |   | |  | | |    | ' /     /  \  | |    | |     
 | |  | | . ` | |   | |  | | |    |  <     / /\ \ | |    | |     
 | |__| | |\  | |___| |__| | |____| . \   / ____ \| |____| |____ 
  \____/|_| \_|______\____/ \_____|_|\_\ /_/    \_\______|______|
                                                                 
                                                                 
)";
}