#ifndef COLOR_OBJECT_LOGIC_H
#define COLOR_OBJECT_LOGIC_H

#include "scapplication.h"
#include "app_grid.h"
#include "colormanagerlogic.h"

class ColorObjectLogic : public AppGridObjectLogic{
public:
	ColorObjectLogic(Application*, SDL_Rect*, AppGridLogic*, AppGridCoord, SDL_Color*, ColorManagerLogic*);
	void update();
private:
	bool clicked(MouseInfo); //returns true if the mouse was over the object when it was clicked
	SDL_Color* color;
	ColorManagerLogic* color_manager;
};

#endif