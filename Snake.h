#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

class Snake
{
private:
	RenderWindow& window;
	Texture& texture;
	Sprite* sprite;

	Vector2i velicina;
	Vector2i niz[100];
	Vector2i fruit;

	int length;


	char nizT[100];
	char previous;

	bool left;
	bool right;
	bool up;
	bool down;

	bool start;

public:
	Snake(RenderWindow& window,Texture& texture,Vector2i vel):window(window),texture(texture),velicina(vel) {
		for (int i = 0; i < 100; i++) {
			niz[i].x = -1;
			niz[i].y = -1;
		}
	}

	void Init() {
		sprite = new Sprite(texture);
		sprite->setScale({ 0.5f,0.5f });

		SetControl(true, false, false, false);
		start = false;

		length = 4;
		previous = 'S';
		for (int i = 0; i < 4; i++) {
			niz[i].x = velicina.x/2;
			niz[i].y = velicina.y/2 -3 + i;
			nizT[i] = rand() % 4;
			
		}

		GenerateFruit();
	}

	void Draw() {
		
		int i = 0;
		while (niz[i].x != -1) {
			sprite->setPosition({ niz[i].x * 16.0f,niz[i].y * 16.0f });

			if (i == 0) {
				sprite->setTextureRect(IntRect({ 64,0 }, { 32,32 }));

			}
			else {
				
				sprite->setTextureRect(IntRect({ nizT[i]*32,32}, {32,32}));
			}
			window.draw(*sprite);
			i++;
		}

		sprite->setPosition({ fruit.x * 16.0f,fruit.y * 16.0f });
		sprite->setTextureRect(IntRect({ 96,0 }, { 32,32 }));

		window.draw(*sprite);
		
	}

	void Update() {

		if (start) {
			Pomeri();

			if (up)
				niz[0].y += -1;
			if (down)
				niz[0].y += 1;
			if (right)
				niz[0].x += 1;
			if (left)
				niz[0].x += -1;

			int i = 1;
			while (niz[i].x != -1) {
				if (CheckCollision(niz[0], niz[i]))
					start = false;
				i++;
			}

			if (niz[0].x >= velicina.x || niz[0].x < 0 || niz[0].y >= velicina.y || niz[0].y < 0)
				start = false;

			if (CheckCollision(fruit, niz[0])) {
				niz[length].x = -2;
				length++;

				GenerateFruit();
			}
			
		}
	}

	void RenderInput() {
		if (!start && Keyboard::isKeyPressed(Keyboard::Scan::Space))
			start = true;
		if (start) {

			if (Keyboard::isKeyPressed(Keyboard::Scan::W) && previous != 'S') {
				SetControl(true, false, false, false);
				previous = 'W';
			}
			if (Keyboard::isKeyPressed(Keyboard::Scan::S) && previous != 'W') {
				SetControl(false, false, true, false);
				previous = 'S';
			}
			if (Keyboard::isKeyPressed(Keyboard::Scan::D) && previous != 'A') {
				SetControl(false, false, false, true);
				previous = 'D';
			}
			if (Keyboard::isKeyPressed(Keyboard::Scan::A) && previous != 'D') {
				SetControl(false, true, false, false);
				previous = 'A';
			}
		}
		
	}

	bool CheckCollision(Vector2i& one,Vector2i& two) {
		if (one.x==two.x && one.y  == two.y) {
			return true;
		}

		return false;
	}

	void GenerateFruit() {

		bool fax;
		int x;
		int y;

		do {
			fax = true;


			x = rand() % velicina.x;
			y = rand() % velicina.y;

			for (int i = 0; i < velicina.x; i++) {
				if (niz[i].x == x) {
					for (int j = 0; j < velicina.y; j++) {
						if (niz[i].y == y) {
							fax = false;
						}
					}
				}
			}

		} while (!fax);

		fruit.x = x;
		fruit.y = y;
		//cout << fruit.x << " " << fruit.y << endl;
	}

	void SetControl(bool w, bool a, bool s, bool d) {
		up = w;
		left = a;
		down = s;
		right = d;
	}

	void Pomeri() {
		int i = length-1;

		while (i > 0) {
			niz[i] = niz[i - 1];
			i--;
		}
	}

	void Restart(Vector2i v) {
		velicina.x = v.x;
		velicina.y = v.y;

		for (int i = 0; i < 100; i++) {
			niz[i].x = -1;
			niz[i].y = -1;
		}

		Init();
	}
};

