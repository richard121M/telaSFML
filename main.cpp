#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

int main() {
    cout << "SFML 2.4.2" << endl;
    cout << "Programa esta rodando em ";
    #if defined(_WIN32)
        cout << "Windows" << endl;
    #elif defined(__linux__)
        cout << "Linux" << endl;
    #endif

    RenderWindow window(VideoMode(800, 600), "TELA SFML");
    CircleShape shape(120.f);
    shape.setFillColor(Color::Green);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
