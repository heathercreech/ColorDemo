#include "colormanagerlogic.h"

ColorManagerLogic::ColorManagerLogic(Application* app, SDL_Rect* rect, AppGridLogic* grid, AppGridCoord pos, SDL_Color* color) : AppGridObjectLogic(app, rect, grid, pos), selected_colors(), shown_colors(), color_changed(){
	target_color = color;
	changed_count = 0;
}


void ColorManagerLogic::update(){}


//adds a color to shown_colors
void ColorManagerLogic::addShownColor(SDL_Color* color){
	shown_colors.push_back(color);
	color_changed.push_back(false);
}

void ColorManagerLogic::clearColors(){
	selected_colors.clear();
}

void ColorManagerLogic::addColor(SDL_Color color){
	
	if(!findColor(color)){
		selected_colors.push_back(color);
		if(selected_colors.size() == 2){
			checkColors();
		}
	}
}

bool ColorManagerLogic::findColor(SDL_Color color){
	for(unsigned int i = 0; i < selected_colors.size(); i++){
		SDL_Color current = selected_colors[i];
		if(compare(current, color)){
			return true;
		}
	}
	return false;
}


bool ColorManagerLogic::compare(SDL_Color first, SDL_Color second){
	if(first.r == second.r && first.g == second.g && first.b == second.b && first.a == second.a){
		return true;
	}
	return false;
}


void ColorManagerLogic::checkColors(){
	SDL_Color first = selected_colors[0];
	SDL_Color second = selected_colors[1];
	
	SDL_Color combined = {(first.r + second.r)/2, (first.g + second.g)/2, (first.b + second.b)/2, 1};
	
	if(compare(combined, *target_color)){
		app->log_info("Success! Color matches.");
		changeTarget();
		
		changed_count = 0;
		
		for(unsigned int i = 0; i < 3; i++){
			color_changed[i] = false;
		}
		generateColors();
	}else{
		app->log_info("Failure! Color does not match.");
		
	}
	
	clearColors();
}


void ColorManagerLogic::generateColors(){

	while(changed_count < 3){
		int index = rand() % 3;
		if(!color_changed[index]){
			SDL_Color set_color = {0, 0, 0, 1};
			int dist = 0;
			int min = 0;
			int max = 0;
			
			switch(changed_count){
				case 0:
					dist = 255 - target_color->r;
					min = target_color->r;
					if(dist >= 127){
						max = 2 * min;
					}else{
						max = 255;
					}
					if(min != 255){
						if(min == 0){
							shown_colors[index]->r = 0;
						}else{
							shown_colors[index]->r = min + (rand() % (max-min));
						}
					}else{
						shown_colors[index]->r = 255;
					}
					
					
					dist = 255 - target_color->g;
					min = target_color->g;
					if(dist >= 127){
						max = 2 * min;
					}else{
						max = 255;
					}
					if(min != 255){
						if(min == 0){
							shown_colors[index]->g = 0;
						}else{
							shown_colors[index]->g = min + (rand() % (max-min));
						}
					}else{
						shown_colors[index]->g = 255;
					}
					
					
					dist = 255 - target_color->b;
					min = target_color->b;
					if(dist >= 127){
						max = 2 * min;
					}else{
						max = 255;
					}
					if(min != 255){
						if(min == 0){
							shown_colors[index]->b = 0;
						}else{
							shown_colors[index]->b = min + (rand() % (max-min));
						}
					}
					else{
						shown_colors[index]->b = 255;
					}
					
					
					app->getDebug().log("info", "Color at index %d set to {%d, %d, %d}", index, shown_colors[index]->r, shown_colors[index]->g, shown_colors[index]->b);
					break;
				case 1:
					for(unsigned int i = 0; i < shown_colors.size(); i++){
						if(color_changed[i]){
							set_color = *shown_colors[i];
							break;
						}
					}
					
					shown_colors[index]->r = 2 * target_color->r - set_color.r;
					shown_colors[index]->g = 2 * target_color->g - set_color.g;
					shown_colors[index]->b = 2 * target_color->b - set_color.b;
					app->getDebug().log("info", "Color at index %d set to {%d, %d, %d}", index, shown_colors[index]->r, shown_colors[index]->g, shown_colors[index]->b);
					break;
				case 2:
					shown_colors[index]->r = rand()%256;
					shown_colors[index]->g = rand()%256;
					shown_colors[index]->b = rand()%256;
					app->getDebug().log("info", "Color at index %d set to {%d, %d, %d}", index, shown_colors[index]->r, shown_colors[index]->g, shown_colors[index]->b);
					break;
			}
			color_changed[index] = true;
			changed_count++;
		}
	}
}


bool ColorManagerLogic::colorsChanged(){
	if(changed_count >= 3){
		return true;
	}else{
		return false;
	}
}


void ColorManagerLogic::changeTarget(){
	target_color->r = rand()%256;
	target_color->g = rand()%256;
	target_color->b = rand()%256;
	app->getDebug().log("info", "Target set to color {%d, %d, %d}", target_color->r, target_color->g, target_color->b);
}