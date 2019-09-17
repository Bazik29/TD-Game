#include "Input.hpp"

WindowGLFW* Input::window;
std::map<Input::Keyboard, bool> Input::keyMap;
std::map<Input::Mouse, bool> Input::mouseMap;

Input::Input()
{}

Input::~Input()
{}

void Input::init(WindowGLFW& window)
{
	Input::window = &window;

	// Python
	// print (re.sub(r'([\w_]+) = .+?,', r'keyMap[Keyboard::\1] = false;', str))
	keyMap[Keyboard::SPACE] = false;
	keyMap[Keyboard::APOSTROPHE] = false;
	keyMap[Keyboard::COMMA] = false;
	keyMap[Keyboard::MINUS] = false;
	keyMap[Keyboard::PERIOD] = false;
	keyMap[Keyboard::SLASH] = false;
	keyMap[Keyboard::NUM_0] = false;
	keyMap[Keyboard::NUM_1] = false;
	keyMap[Keyboard::NUM_2] = false;
	keyMap[Keyboard::NUM_3] = false;
	keyMap[Keyboard::NUM_4] = false;
	keyMap[Keyboard::NUM_5] = false;
	keyMap[Keyboard::NUM_6] = false;
	keyMap[Keyboard::NUM_7] = false;
	keyMap[Keyboard::NUM_8] = false;
	keyMap[Keyboard::NUM_9] = false;
	keyMap[Keyboard::SEMICOLON] = false;
	keyMap[Keyboard::EQUAL] = false;
	keyMap[Keyboard::A] = false;
	keyMap[Keyboard::B] = false;
	keyMap[Keyboard::C] = false;
	keyMap[Keyboard::D] = false;
	keyMap[Keyboard::E] = false;
	keyMap[Keyboard::F] = false;
	keyMap[Keyboard::G] = false;
	keyMap[Keyboard::H] = false;
	keyMap[Keyboard::I] = false;
	keyMap[Keyboard::J] = false;
	keyMap[Keyboard::K] = false;
	keyMap[Keyboard::L] = false;
	keyMap[Keyboard::M] = false;
	keyMap[Keyboard::N] = false;
	keyMap[Keyboard::O] = false;
	keyMap[Keyboard::P] = false;
	keyMap[Keyboard::Q] = false;
	keyMap[Keyboard::R] = false;
	keyMap[Keyboard::S] = false;
	keyMap[Keyboard::T] = false;
	keyMap[Keyboard::U] = false;
	keyMap[Keyboard::V] = false;
	keyMap[Keyboard::W] = false;
	keyMap[Keyboard::X] = false;
	keyMap[Keyboard::Y] = false;
	keyMap[Keyboard::Z] = false;
	keyMap[Keyboard::LEFT_BRACKET] = false;
	keyMap[Keyboard::BACKSLASH] = false;
	keyMap[Keyboard::RIGHT_BRACKET] = false;
	keyMap[Keyboard::GRAVE_ACCENT] = false;
	keyMap[Keyboard::WORLD_1] = false;
	keyMap[Keyboard::WORLD_2] = false;
	keyMap[Keyboard::ESCAPE] = false;
	keyMap[Keyboard::ENTER] = false;
	keyMap[Keyboard::TAB] = false;
	keyMap[Keyboard::BACKSPACE] = false;
	keyMap[Keyboard::INS] = false;
	keyMap[Keyboard::DEL] = false;
	keyMap[Keyboard::RIGHT] = false;
	keyMap[Keyboard::LEFT] = false;
	keyMap[Keyboard::DOWN] = false;
	keyMap[Keyboard::UP] = false;
	keyMap[Keyboard::PAGE_UP] = false;
	keyMap[Keyboard::PAGE_DOWN] = false;
	keyMap[Keyboard::HOME] = false;
	keyMap[Keyboard::END] = false;
	keyMap[Keyboard::CAPS_LOCK] = false;
	keyMap[Keyboard::SCROLL_LOCK] = false;
	keyMap[Keyboard::NUM_LOCK] = false;
	keyMap[Keyboard::PRINT_SCREEN] = false;
	keyMap[Keyboard::PAUSE] = false;
	keyMap[Keyboard::F1] = false;
	keyMap[Keyboard::F2] = false;
	keyMap[Keyboard::F3] = false;
	keyMap[Keyboard::F4] = false;
	keyMap[Keyboard::F5] = false;
	keyMap[Keyboard::F6] = false;
	keyMap[Keyboard::F7] = false;
	keyMap[Keyboard::F8] = false;
	keyMap[Keyboard::F9] = false;
	keyMap[Keyboard::F10] = false;
	keyMap[Keyboard::F11] = false;
	keyMap[Keyboard::F12] = false;
	keyMap[Keyboard::F13] = false;
	keyMap[Keyboard::F14] = false;
	keyMap[Keyboard::F15] = false;
	keyMap[Keyboard::F16] = false;
	keyMap[Keyboard::F17] = false;
	keyMap[Keyboard::F18] = false;
	keyMap[Keyboard::F19] = false;
	keyMap[Keyboard::F20] = false;
	keyMap[Keyboard::F21] = false;
	keyMap[Keyboard::F22] = false;
	keyMap[Keyboard::F23] = false;
	keyMap[Keyboard::F24] = false;
	keyMap[Keyboard::F25] = false;
	keyMap[Keyboard::KP_0] = false;
	keyMap[Keyboard::KP_1] = false;
	keyMap[Keyboard::KP_2] = false;
	keyMap[Keyboard::KP_3] = false;
	keyMap[Keyboard::KP_4] = false;
	keyMap[Keyboard::KP_5] = false;
	keyMap[Keyboard::KP_6] = false;
	keyMap[Keyboard::KP_7] = false;
	keyMap[Keyboard::KP_8] = false;
	keyMap[Keyboard::KP_9] = false;
	keyMap[Keyboard::KP_DECIMAL] = false;
	keyMap[Keyboard::KP_DIVIDE] = false;
	keyMap[Keyboard::KP_MULTIPLY] = false;
	keyMap[Keyboard::KP_SUBTRACT] = false;
	keyMap[Keyboard::KP_ADD] = false;
	keyMap[Keyboard::KP_ENTER] = false;
	keyMap[Keyboard::KP_EQUAL] = false;
	keyMap[Keyboard::LEFT_SHIFT] = false;
	keyMap[Keyboard::LEFT_CONTROL] = false;
	keyMap[Keyboard::LEFT_ALT] = false;
	keyMap[Keyboard::LEFT_SUPER] = false;
	keyMap[Keyboard::RIGHT_SHIFT] = false;
	keyMap[Keyboard::RIGHT_CONTROL] = false;
	keyMap[Keyboard::RIGHT_ALT] = false;
	keyMap[Keyboard::RIGHT_SUPER] = false;
	keyMap[Keyboard::MENU] = false;

	mouseMap[Mouse::BUTTON_LEFT] = false;
	mouseMap[Mouse::BUTTON_RIGHT] = false;
	mouseMap[Mouse::BUTTON_MIDDLE] = false;
	mouseMap[Mouse::BUTTON_4] = false;
	mouseMap[Mouse::BUTTON_5] = false;
	mouseMap[Mouse::BUTTON_6] = false;
	mouseMap[Mouse::BUTTON_7] = false;
	mouseMap[Mouse::BUTTON_8] = false;
}

void Input::update()
{
	for (auto it = keyMap.begin(); it != keyMap.end(); it++)
		it->second = isKey(it->first);
	for (auto it = mouseMap.begin(); it != mouseMap.end(); it++)
		it->second = isMouse(it->first);

	glfwPollEvents();
}

bool Input::isKey(Keyboard key)
{
	return glfwGetKey(window->getHandle(), static_cast<unsigned>(key)) == GLFW_PRESS;
}

bool Input::isKeyDown(Keyboard key)
{
	return isKey(key) && !keyMap[key];
}

bool Input::isKeyUp(Keyboard key)
{
	return !isKey(key) && keyMap[key];
}

bool Input::isMouse(Mouse key)
{
	return glfwGetMouseButton(window->getHandle(), static_cast<unsigned>(key)) == GLFW_PRESS;
}

bool Input::isMouseDown(Mouse key)
{
	return isMouse(key) && !mouseMap[key];
}

bool Input::isMouseUp(Mouse key)
{
	return !isMouse(key) && mouseMap[key];
}

glm::dvec2 Input::getMousePosition()
{
	double xpos, ypos;
	glfwGetCursorPos(window->getHandle(), &xpos, &ypos);
	return glm::dvec2(xpos, ypos);
}

void Input::setMousePosition(glm::fvec2 position)
{
	glfwSetCursorPos(window->getHandle(), position.x, position.y);
}
