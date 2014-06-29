
#include "UI.h"
#include <SDL2/SDL.h>

UI::UI(SDL_Renderer &renderer) : m_renderer(renderer) {

}

UI::~UI() {
}

UI UI::make_ui(SDL_Renderer &renderer) {
	return UI{renderer};
}
