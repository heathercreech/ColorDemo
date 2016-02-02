#ifndef APP_GRID_H
#define APP_GRID_H

#define APPGRID_UP 0
#define APPGRID_DOWN 1
#define APPGRID_RIGHT 2
#define APPGRID_LEFT 3

#define APPGRID_MOVE_FAILED -1
#define APPGRID_MOVE_SUCCESS 1

#include "scapplication.h"
#include <vector>
#include <algorithm>


//for identifying ApplicationObjects in the AppGrid
struct AppGridCoord{
	int x;
	int y;
};

//a grid of application objects
class AppGridLogic: public ObjectLogic{
public:
	AppGridLogic(Application*, SDL_Rect*, int, int);
	void update(Application*);
	void addObject(ApplicationObject*, AppGridCoord);
	
	bool gridEmpty(AppGridCoord);
	
	bool contains(ApplicationObject*);
	AppGridCoord getObjectCoord(ApplicationObject*);
	
	int move(AppGridCoord, int);
	int moveLeft(AppGridCoord);
	int moveRight(AppGridCoord);
	int moveUp(AppGridCoord);
	int moveDown(AppGridCoord);
	
private:
	std::vector<std::vector<ApplicationObject*>> objects;
	int pixel_width;
	int pixel_height;
	
	//checks to see if an application object can be moved in given direction
	bool checkDirection(AppGridCoord, int);
	void updateObjectPosition(ApplicationObject*);
};


class AppGridObjectLogic: public ObjectLogic{
public:
	AppGridObjectLogic(Application*, SDL_Rect*, AppGridLogic*, AppGridCoord);
	virtual void update();
	
	AppGridCoord getPosition();
	void setGridPosition(AppGridCoord);
private:
	AppGridLogic* grid;
	AppGridCoord position;
};

#endif