#include <WindowGLFW.hpp>

#include <Input.hpp>

#include <Renderer.hpp>

#include <BattleManager.hpp>
#include <ResourceManager.hpp>


int main(int argc, char const* argv[])
{

	struct Settings
	{
		char* win_title = "TD-game";
		unsigned int win_w = 640;
		unsigned int win_h = 480;
		bool win_resizable = true;

		float fov = 45.f;
	} settings;

	WindowGLFW window;
	window.create(settings.win_w, settings.win_h, settings.win_title, settings.win_resizable);


	Input input;
	input.init(window);

	Renderer render;

	ResourceManager resMng;

	resMng.loadTower("../../resources/tower.json", 0);
	resMng.loadEnemy("../../resources/enemy.json", 0);

	BattleManager battle_manager;

	std::vector<glm::vec2> spiral =
	{
		{0.0, 0.0},
		{0.14067442439954783, 0.14067442439954783},
		{2.4363573953246096e-17, 0.3978873577297383},
		{-0.4220232731986434, 0.42202327319864347},
		{-0.7957747154594766, 9.745429581298438e-17},
		{-0.7033721219977392, -0.703372121997739},
		{-2.1927216557921485e-16, -1.193662073189215},
		{0.9847209707968345, -0.984720970796835},
		{1.5915494309189533, -3.8981718325193754e-16},
		{1.2660698195959308, 1.2660698195959301},
		{6.090893488311524e-16, 1.9894367886486917},
		{-1.5474186683950242, 1.5474186683950277},
		{-2.38732414637843, 8.770886623168594e-16},
		{-1.8287675171941207, -1.828767517194123},
		{-1.1938151237090587e-15, -2.7852115041081684},
		{2.1101163659932145, -2.1101163659932203},
		{3.1830988618379066, -1.5592687330077501e-15},
		{2.391465214792312, 2.391465214792314},
		{1.973449490212934e-15, 3.580986219567645},
		{-2.6728140635914044, 2.6728140635914124},
		{-3.9788735772973833, 2.4363573953246096e-15},
		{-2.9541629123905033, -2.9541629123905047},
		{-1.0722681669698039e-14, -4.3767609350271215},
		{3.2355117611895943, -3.235511761189605},
		{4.77464829275686, -3.5083546492674376e-15},
	};

	battle_manager.init(100, spiral);

	battle_manager.createEnemy(resMng.getEnemyProperty(0), { 0.0, 0.0 });
	battle_manager.createEnemy(resMng.getEnemyProperty(0), { 3.0, 3.0 });
	battle_manager.createTower(resMng.getTowerProperty(0), { -4.0, 0.0 });



	//gl::ClearColor(1, 0.5, 0.5, 1);
	while (!window.shouldClose())
	{
		input.update();
		window.pollEvents();

		if (input.isKeyDown(Input::Keyboard::ESCAPE))
		{
			window.close();
		}
		gl::ClearColor(0, 1, 1, 1);
		gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
		battle_manager.update(0.001);

		//gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

		render.draw(battle_manager.enemies);
		render.draw(battle_manager.towers);
		render.draw(battle_manager.shells);

		window.display();
	}


	window.close();
	window.destroy();

	return 0;
}
