#include "core.h"
#include "window.h"

using namespace GeoFrame;

int main() {
	Init();
	Window window(1500, 750, "Test window");
	while (true) {
		if (window.IsClosed()) { break; }
		else { ; }

		glfwPollEvents();
		window.Swap();
	}

	Terminate();
	
	return 0;
}