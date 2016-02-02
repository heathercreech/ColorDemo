#include "scrender.h"

ObjectRenderer::ObjectRenderer(SDL_Renderer* renderer){
	app_renderer = renderer;
}

SquareRenderer::SquareRenderer(SDL_Renderer* ren, SDL_Rect* r, SDL_Color* c) : ObjectRenderer(ren){
	rect = r;
	color = c;
}

void SquareRenderer::render(){
	SDL_SetRenderDrawColor(app_renderer, color->r, color->g, color->b, color->a);
	SDL_RenderFillRect(app_renderer, rect);
}

SDL_Rect* SquareRenderer::getRect(){
	return rect;
}