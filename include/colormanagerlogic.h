#ifndef COLOR_MANAGER_LOGIC_H
#define COLOR_MANAGER_LOGIC_H


#include "scapplication.h"
#include "app_grid.h"
#include <vector>
#include <algorithm>
#include <cstdlib>

//determines if the selected colors combine to match the target color
class ColorManagerLogic : public AppGridObjectLogic{
public:
	ColorManagerLogic(Application*, SDL_Rect*, AppGridLogic*, AppGridCoord, SDL_Color*);
	void update();
	
	void clearColors();
	void addColor(SDL_Color);
	void removeColor(SDL_Color);
	
	void addShownColor(SDL_Color*);

	bool colorsChanged();
	
	bool findColor(SDL_Color);
	
	//generates a color that will help it match the target
	void generateColors();
	
private:
	SDL_Color* target_color;
	std::vector<SDL_Color> selected_colors;
	std::vector<SDL_Color*> shown_colors;
	std::vector<bool> color_changed; //parallel with shown_colors
	
	int changed_count;
	
	void changeTarget();
	
	bool compare(SDL_Color, SDL_Color);
	void checkColors();
};

#endif