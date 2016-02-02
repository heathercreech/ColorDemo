#include "colorobjectlogic.h"

ColorObjectLogic::ColorObjectLogic(Application* app, SDL_Rect* rect, AppGridLogic* grid, AppGridCoord pos, SDL_Color* c, ColorManagerLogic* manager) : AppGridObjectLogic(app, rect, grid, pos){
	color = c;
	color_manager = manager;
}

void ColorObjectLogic::update(){
	MouseInfo mouse_info = app->getInput()->getMouseButtonUp(SDL_BUTTON_MIDDLE);
	
	//if mouse clicked, check if there is a collision with this object
	if(mouse_info.set){
		if(clicked(mouse_info)){
			color_manager->addColor(*color);
		}
	}
}


//returns true if a click is within the square
bool ColorObjectLogic::clicked(MouseInfo info){
	SDL_Rect logic_rect = getRect();
	
	int lower_x_bound = logic_rect.x;
	int upper_x_bound = logic_rect.x + logic_rect.w;
	
	int lower_y_bound = logic_rect.y;
	int upper_y_bound = logic_rect.y + logic_rect.h;
	
	if(info.x >= lower_x_bound && info.x <= upper_x_bound && info.y >= lower_y_bound && info.y <= upper_y_bound){
		app->getDebug().log("info", "Clickable object at {%d, %d} was clicked.", logic_rect.x, logic_rect.y);
		return true;
	}
	return false;
}