
#include "UI.h"
#include <SDL2/SDL.h>

namespace SDL_GUI {
UI::UI(SDL_Renderer &renderer) : m_renderer(renderer) {

}

UI::~UI() {
}

UI UI::make_ui(SDL_Renderer &renderer) {
	return UI{renderer};
}

void UI::update() {
	// update windows
}
}
