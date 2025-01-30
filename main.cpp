#include <iostream>
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Snake.h"

#include "imgui.h"
#include "imgui-SFML.h"

using namespace std;
using namespace sf;

void AddImgui(RenderWindow& window);

RenderWindow window(VideoMode({ 1100,1060 }), "Yayy");
Texture texture("Textures.png");
Vector2i vel = { 32,32 };
Snake snake(window, texture, vel);
Grid grid(vel, texture, window);

void main() {
	srand(time(0));
	window.setFramerateLimit(12);

	Sprite sprite(texture);
	
	grid.Init();

	
	snake.Init();

	Clock deltaTime;
	Time time;

	ImGui::SFML::Init(window);

	while (window.isOpen()) {

		while (optional event = window.pollEvent()) {

			ImGui::SFML::ProcessEvent(window, *event);
			if (event->is<Event::Closed>())
				window.close();
		}
		/*time += deltaTime.restart();
		if (time > sf::seconds(0.1f)) {*/

			window.clear();
			ImGui::SFML::Update(window, deltaTime.restart());
			snake.RenderInput();

			snake.Update();


			
			//window.draw(sprite);

			grid.Draw();
			snake.Draw();

			AddImgui(window);
			ImGui::SFML::Render(window);
			window.display();

			time = sf::seconds(0);
		

		
	}
}

void AddImgui(RenderWindow& window) {

	ImGui::Begin("Settings");

	ImGui::SetWindowSize(ImVec2(500, 500));
	ImGui::InputInt("Velicina x", &vel.x);
	ImGui::InputInt("Velicina y", &vel.y);

	if (ImGui::Button("Restart", { 200,75 })) {
		grid.Restart(vel);
		snake.Restart(vel);
	}

	ImGui::End();
}