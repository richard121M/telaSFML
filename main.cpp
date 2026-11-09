#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace sf;
using namespace std;

int main() {
    cout << "Programa esta rodando em ";
    #if defined(_WIN32)
        cout << "Windows" << endl;
    #elif defined(__linux__)
        cout << "Linux" << endl;
    #endif

    // criando a tela
    RenderWindow window(VideoMode(850, 600), "TELA SFML");
    // ==================

    // criando um circulo
    CircleShape circulo(32); // declarando e definido o raio //
    circulo.setFillColor(Color::Green); // definido a cor //
    circulo.setPosition(0,0); // definindo a posicao //
    // ==================

    // criando um quadrado
    RectangleShape quadrado({64, 64}); // declarando o quadrado e definido o seu tamanho //
    quadrado.setFillColor(Color::Blue); // definindo a cor //
    quadrado.setPosition(64,0); // definido a posicao //
    // ==================//

    // criando um quadrado
    RectangleShape retangulo({128, 64}); // declarando o retangulo e definido o seu tamanho //
    retangulo.setFillColor(Color::Magenta); // definindo a cor //
    retangulo.setPosition(128,0); // definido a posicao //
    // ==================

    // criando um quadrado
    // nao existe no sfml uma funcao para criar um triangulo //
    // porem e possivel crialo atraves do ConvexShape //
    ConvexShape triangulo; // declarando o triangulo//
    triangulo.setPointCount(3); // definindo o numero de pontos //
    triangulo.setPoint(0, {32,0}); // a possicao do ponto 0 //
    triangulo.setPoint(1, {0,64}); // a possicao do ponto 1 //
    triangulo.setPoint(2, {64,64}); // a possicao do ponto 2 //
    triangulo.setFillColor(Color::Red); // definindo a cor //
    triangulo.setPosition(256,0); // definido a posicao do pivo do poligono //
    // ==================

    // criando bola que gira //
    float angulo = 0.0;
    float velocidadeAngular = 0.05;
    float moduloVetor = 4.0;
    CircleShape circulog(32); // declarando e definido o raio //
    circulog.setFillColor(Color::Yellow); // definido a cor //
    circulog.setPosition(350,250); // definindo a posicao //
    // ==================

    // definindo o frames por segundo do programa //
    window.setFramerateLimit(60);
    while (window.isOpen()) {

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(circulo); // desenhado o circulo na tela //
        window.draw(quadrado); // desenhando o quadrado na tela //
        window.draw(retangulo); // desenhando o retangulo na tela //
        window.draw(triangulo); // desenhando o retangulo na tela //
        window.draw(circulog); // desenhando o retangulo na tela //
        angulo += velocidadeAngular;
        circulog.move(cos(angulo)*moduloVetor,sin(angulo)*moduloVetor);
        window.display();
    }

    return 0;
}
