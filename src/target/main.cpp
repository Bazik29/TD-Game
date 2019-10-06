
#include "Model.hpp"
#include <iostream>

int main(int argc, char const* argv[])
{
	fs::path path = "models/Tower.obj";
	std::string name = "tower_1";

	Model* model = load_model(path, name);

	std::cout << "-----BODY------\n";
	
	unload_model(name);

	std::cout << "-----END------\n";

	return 0;
}
