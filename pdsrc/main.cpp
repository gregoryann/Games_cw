#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;



int main() {
	
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}