#include "memory.h"
#include "json.h"
#include "sdk.h"

using json = nlohmann::json;
json config;
std::string configPath = sdk::CurrentPath() + "\\config.json";

void create_config() {
	std::cout << "[+] making the config file, just wait...";
	sdk::Wait(300);

	config["version"] = 4.0;
	config["enable"] = 112;
	config["disable"] = 113;

	std::ofstream configurationOut;
	configurationOut.open(configPath);
	configurationOut << config;
	configurationOut.close();

	sdk::Wait(1500);

	_exit(false);
}

int main()
{
	sdk::watermark();

	std::ifstream configurationIn(configPath);
	if (!configurationIn) {
		create_config();
	}

	configurationIn >> config;

	float version = config["version"];
	int enable = config["enable"];
	int disable = config["disable"];

	if (version < 4.0 || version > 4.0) {
		std::cout << "[+] detected older version, creating new config...";
		configurationIn.close();
		system("del -R config.json");
		sdk::Wait(300);
		std::cout << std::endl;
		create_config();
		sdk::Wait(500);
		_exit(false);
	}

	memory::pid = memory::get_processid("RainbowSix.exe"); if (!memory::pid) return false;
	memory::module = memory::get_module(memory::pid, "RainbowSix.exe");
	memory::base = memory::get_base(memory::module); if (!memory::base) return false;
	memory::base_size = memory::module.modBaseSize;
	memory::handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, memory::pid);

	std::cout << "[+] pid -> " << memory::pid << "\n[+] base ->" << std::hex << memory::base << "\n[+] base size -> " << std::hex << memory::base_size << "\n[+] handle -> "  << memory::handle << std::endl << std::endl;

	while (!sdk::IsKeyPressed(VK_END)) {
	
		sdk::Wait(1);

		if (sdk::IsKeyPressed(enable)) {
			uint8_t rax[] = { 0x48, 0xB8, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x48, 0x8B, 0x32, 0x48, 0x85 };
			uint8_t ret[] = { 0xC3 };
			WriteProcessMemory(memory::handle, (LPVOID)(memory::base + 0x192220), rax, sizeof(rax), NULL);
			WriteProcessMemory(memory::handle, (LPVOID)(memory::base + 0x192220), ret, sizeof(ret), NULL);

			sdk::enabled(true);
		}
		else if (sdk::IsKeyPressed(disable)) {
			uint8_t rax[] = { 0x41, 0x57, 0x41, 0x56, 0x56, 0x57, 0x53, 0x48, 0x83, 0xEC, 0x20, 0x48, 0x8B, 0x32, 0x48, 0x85 };
			WriteProcessMemory(memory::handle, (LPVOID)(memory::base + 0x192220), rax, sizeof(rax), NULL);

			sdk::disabled(true);
		}

	}
}
