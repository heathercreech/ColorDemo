#include "app_grid.h"


//
AppGridLogic::AppGridLogic(Application* application, SDL_Rect* rect, int width, int height) : ObjectLogic(application, rect), objects(10, std::vector<ApplicationObject*>(8)){
	pixel_width = width;
	pixel_height = height;
}


//
void AppGridLogic::update(Application*){
	
}


//
int AppGridLogic::move(AppGridCoord pos, int direction){
	switch(direction){
	case APPGRID_LEFT:
		return moveLeft(pos);
		break;
	case APPGRID_RIGHT:
		return moveRight(pos);
		break;
	case APPGRID_UP:
		return moveUp(pos);
		break;
	case APPGRID_DOWN:
		return moveDown(pos);
		break;
	}
	return APPGRID_MOVE_FAILED;
}


//
int AppGridLogic::moveLeft(AppGridCoord pos){
	AppGridCoord new_pos = {pos.x-1, pos.y};
	if(checkDirection(new_pos, APPGRID_LEFT)){
		ApplicationObject* obj_holder = objects[pos.x][pos.y];
		objects[pos.x][pos.y] = NULL;
		objects[new_pos.x][new_pos.y] = obj_holder;
		updateObjectPosition(obj_holder);
		return APPGRID_MOVE_SUCCESS;
	}
	return APPGRID_MOVE_FAILED;
}


//
int AppGridLogic::moveRight(AppGridCoord pos){
	AppGridCoord new_pos = {pos.x+1, pos.y};
	if(checkDirection(new_pos, APPGRID_RIGHT)){
		ApplicationObject* obj_holder = objects[pos.x][pos.y];
		objects[pos.x][pos.y] = NULL;
		objects[new_pos.x][new_pos.y] = obj_holder;
		updateObjectPosition(obj_holder);
		return APPGRID_MOVE_SUCCESS;
	}
	return APPGRID_MOVE_FAILED;
}


//
int AppGridLogic::moveUp(AppGridCoord pos){
	AppGridCoord new_pos = {pos.x, pos.y-1};
	if(checkDirection(new_pos, APPGRID_UP)){
		ApplicationObject* obj_holder = objects[pos.x][pos.y];
		objects[pos.x][pos.y] = NULL;
		objects[new_pos.x][new_pos.y] = obj_holder;
		updateObjectPosition(obj_holder);
		return APPGRID_MOVE_SUCCESS;
	}
	return APPGRID_MOVE_FAILED;
}


//
int AppGridLogic::moveDown(AppGridCoord pos){
	AppGridCoord new_pos = {pos.x, pos.y+1};
	if(checkDirection(new_pos, APPGRID_DOWN)){
		ApplicationObject* obj_holder = objects[pos.x][pos.y];
		objects[pos.x][pos.y] = NULL;
		objects[new_pos.x][new_pos.y] = obj_holder;
		updateObjectPosition(obj_holder);
		return APPGRID_MOVE_SUCCESS;
	}
	return APPGRID_MOVE_FAILED;
}


//determines if a specific grid is occupied
bool AppGridLogic::gridEmpty(AppGridCoord pos){
	if(objects[pos.x][pos.y] == NULL){
		return true;
	}else{
		return false;
	}
}


//determines if the new position is valid
bool AppGridLogic::checkDirection(AppGridCoord new_pos, int direction){

	switch(direction){
	case APPGRID_LEFT:
		if((new_pos.x >= 0) && gridEmpty(new_pos)){
			return true;
		}
		break;
	case APPGRID_RIGHT:
		if(gridEmpty(new_pos)){
			return true;
		}
		break;
	case APPGRID_UP:
		if((new_pos.y >= 0) && gridEmpty(new_pos)){
			return true;
		}
		break;
	case APPGRID_DOWN:
		if(gridEmpty(new_pos)){
			return true;
		}
		break;
	}
	
	return false;
}


//checks if obj is currently in the grid so that two of the same pointers are not added
bool AppGridLogic::contains(ApplicationObject* obj){
	std::vector<ApplicationObject*>::iterator it;
	
	for(unsigned int i = 0; i < objects.size(); i++){
		it = std::find(objects[i].begin(), objects[i].end(), obj);
		if(it != objects[i].end()){
			return true;
		}
	}
	return false;
}


//returns the position of obj, can also be used to determine if the object is in the grid
AppGridCoord AppGridLogic::getObjectCoord(ApplicationObject* obj){
	std::vector<ApplicationObject*>::iterator it;
	AppGridCoord pos = {-1, -1};
	
	for(unsigned int i = 0; i < objects.size(); i++){
		it = std::find(objects[i].begin(), objects[i].end(), obj);
		if(it != objects[i].end()){
			pos = {(int)i, it-objects[i].begin()};
		}
	}
	
	return pos;
}


//updates an objects position on screen
void AppGridLogic::updateObjectPosition(ApplicationObject* obj){
	AppGridCoord obj_coord = getObjectCoord(obj);
	int x = obj_coord.x * pixel_width;
	int y = obj_coord.y * pixel_height;
	
	//log_info("Attempting to update position to {%d, %d}\n", x, y);
	obj->getLogic()->setPosition(x, y);
	//log_info("Object position has been updated.\n");
}


//adds an object to the grid at the specified location after determining that it is not already in the array, then updates it location on screen
void AppGridLogic::addObject(ApplicationObject* obj, AppGridCoord pos){
	if(!contains(obj) && gridEmpty(pos)){
		objects[pos.x][pos.y] = obj;
		updateObjectPosition(obj);
	}
}


//START APP GRID OBJECT LOGIC
AppGridObjectLogic::AppGridObjectLogic(Application* application, SDL_Rect* rect, AppGridLogic* grid_logic, AppGridCoord pos) : ObjectLogic(application, rect){
	grid = grid_logic;
	position = pos;
}

void AppGridObjectLogic::update(){
	if(app->getInput()->getKeyUp(SDLK_RIGHT)){
		if(grid->moveRight(position) == APPGRID_MOVE_SUCCESS){
			AppGridCoord new_pos = {position.x+1, position.y};
			setGridPosition(new_pos);
		}
	}
	
	if(app->getInput()->getKeyUp(SDLK_LEFT)){
		if(grid->moveLeft(position) == APPGRID_MOVE_SUCCESS){
			AppGridCoord new_pos = {position.x-1, position.y};
			setGridPosition(new_pos);
		}
	}
	
	if(app->getInput()->getKeyUp(SDLK_UP)){
		if(grid->moveUp(position) == APPGRID_MOVE_SUCCESS){
			AppGridCoord new_pos = {position.x, position.y-1};
			setGridPosition(new_pos);
		}
	}
	
	if(app->getInput()->getKeyUp(SDLK_DOWN)){
		if(grid->moveDown(position) == APPGRID_MOVE_SUCCESS){
			AppGridCoord new_pos = {position.x, position.y+1};
			setGridPosition(new_pos);
		}
	}
}

AppGridCoord AppGridObjectLogic::getPosition(){
	return position;
}

void AppGridObjectLogic::setGridPosition(AppGridCoord pos){
	position = pos;
}