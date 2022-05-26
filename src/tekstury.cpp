#include"tekstury.h"

SDL_Texture * Tekstura::Load(const char* nazwa, SDL_Renderer* ren)
{
	SDL_Surface * powierzchnia = IMG_Load(nazwa);
	SDL_Texture* textur = SDL_CreateTextureFromSurface(ren, powierzchnia);
	SDL_FreeSurface(powierzchnia);

	return textur;
}