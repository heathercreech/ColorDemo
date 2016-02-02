#ifndef SCRENDER_H
#define SCRENDER_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "scapplication.h"

class ObjectRenderer{
public:
	ObjectRenderer(){};
	ObjectRenderer(SDL_Renderer*);
	virtual ~ObjectRenderer(){};
	virtual void render(){};
	SDL_Renderer* app_renderer;
};

//wrapper for SDL_Texture
class SquareRenderer: public ObjectRenderer{
public:
	SquareRenderer(SDL_Renderer*, SDL_Rect*, SDL_Color*);
	~SquareRenderer(){};
	SDL_Rect* getRect();
	void render();
private:
	SDL_Color* color;
	SDL_Rect* rect;
};

#endif