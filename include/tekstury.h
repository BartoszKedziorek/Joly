#include<SDL.h>
#include<SDL_image.h>

class Tekstura
{

public:
	static SDL_Texture * Load(const char* nazwa, SDL_Renderer * ren);
};