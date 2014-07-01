#ifndef UI_H_
#define UI_H_
struct SDL_Renderer;


namespace SDL_GUI {
class UI final {
public:
	static UI make_ui(SDL_Renderer &renderer);

	virtual ~UI();

	void update();

private:
	UI(SDL_Renderer &renderer);

	SDL_Renderer &m_renderer;

};
}
#endif /* UI_H_ */
