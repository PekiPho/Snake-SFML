#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Grid
{
private:
	Sprite* sprite;
	Texture& texture;
	Vector2i velicina;
	RenderWindow& window;
	bool mapa[100][100];

public:

	Grid(Vector2i vel, Texture& text,RenderWindow& win) :texture(text), velicina(vel),window(win) {

	}

	void Init() {
		sprite = new Sprite(texture);
		sprite->setScale({ 0.5,0.5 });

		//cout << velicina.x << " " << velicina.y << endl;
		for (int i = 0; i < velicina.x; i++) {
			for (int j = 0; j < velicina.y; j++) {
				mapa[i][j] = rand() % 2;
			}
		}
	}

	void Draw() {
		
		for (int i = 0; i < velicina.x; i++) {
			for (int j = 0; j < velicina.y; j++) {
				sprite->setPosition({ i * 16.0f,j * 16.0f });
				sprite->setTextureRect(IntRect({ 128,mapa[i][j] * 32 }, { 32,32 }));

				window.draw(*sprite);
			}
		}

		
	}

	void Restart(Vector2i v) {
		velicina.x = v.x;
		velicina.y = v.y;

		Init();
	}
};

