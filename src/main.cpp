#include "scapplication.h"
#include "app_grid.h"
#include "colorobjectlogic.h"
#include "colormanagerlogic.h"
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[]){
	srand(time(NULL));

	Application app;
	app.init();
	
	app.setDebug(true); //set to false when ready to deploy
	
	app.log_info("Program initialized.");
	
	SDL_Rect default_position = {0, 0, 0, 0}; //for objects that are purely logic, no rendering DO NOT MODIFY (replace default renders in this code with ones that accept const SDL_rects)
	
	
	app.log_info("Initializing and adding the AppGrid to application...");
	
	AppGridLogic grid_logic(&app, &default_position, 72, 72);
	ObjectRenderer grid_renderer;
	ApplicationObject grid_object(&app, &grid_renderer, &grid_logic);
	app.addObject(&grid_object);
	
	app.log_info("AppGrid successfully added.");	
	app.log_info("Adding target_object to application...");
	
	SDL_Rect target_rect = {0, 0, 72, 72};
	SDL_Color target_color = {200, 200, 0, 1};
	AppGridCoord target_location = {3, 1};
	AppGridObjectLogic target_logic(&app, &target_rect, &grid_logic, target_location);
	SquareRenderer target_renderer(app.getRenderer(), &target_rect, &target_color);
	ApplicationObject target_object(&app, &target_renderer, &target_logic);
	app.addObject(&target_object);
	grid_logic.addObject(&target_object, target_location);
	
	app.log_info("Target_object successfully added.");
	
	
	//the manager will change colors based on whether the player answered correctly (red = no, green = yes)
	SDL_Rect manager_rect = {0, 0, 360, 72};
	SDL_Color manager_color = {150, 150, 150, 1};
	AppGridCoord manager_location = {1, 5};
	ColorManagerLogic manager_logic(&app, &manager_rect, &grid_logic, manager_location, &target_color);
	SquareRenderer manager_renderer(app.getRenderer(), &manager_rect, &manager_color);
	ApplicationObject manager_object(&app, &manager_renderer, &manager_logic);
	app.addObject(&manager_object);
	grid_logic.addObject(&manager_object, manager_location);
	
	app.log_info("Adding option1_object to application...");
	
	SDL_Rect option1_rect = {0, 0, 72, 72};
	SDL_Color option1_color = {250, 150, 0, 1};
	AppGridCoord option1_location = {1, 3};
	ColorObjectLogic option1_logic(&app, &option1_rect, &grid_logic, option1_location, &option1_color, &manager_logic);
	SquareRenderer option1_renderer(app.getRenderer(), &option1_rect, &option1_color);
	ApplicationObject option1_object(&app, &option1_renderer, &option1_logic);
	app.addObject(&option1_object);
	grid_logic.addObject(&option1_object, option1_location);
	
	app.log_info("Option1_object successfully added.");
	app.log_info("Adding option2_object to application...");
	
	SDL_Rect option2_rect = {0, 0, 72, 72};
	SDL_Color option2_color = {150, 250, 0, 1};
	AppGridCoord option2_location = {3, 3};
	ColorObjectLogic option2_logic(&app, &option2_rect, &grid_logic, option2_location, &option2_color, &manager_logic);
	SquareRenderer option2_renderer(app.getRenderer(), &option2_rect, &option2_color);
	ApplicationObject option2_object(&app, &option2_renderer, &option2_logic);
	app.addObject(&option2_object);
	grid_logic.addObject(&option2_object, option2_location);
	
	app.log_info("Option2_object successfully added.");
	app.log_info("Adding option3_object to application...");
	
	SDL_Rect option3_rect = {0, 0, 72, 72};
	SDL_Color option3_color = {150, 50, 100, 1};
	AppGridCoord option3_location = {5, 3};
	ColorObjectLogic option3_logic(&app, &option3_rect, &grid_logic, option3_location, &option3_color, &manager_logic);
	SquareRenderer option3_renderer(app.getRenderer(), &option3_rect, &option3_color);
	ApplicationObject option3_object(&app, &option3_renderer, &option3_logic);
	app.addObject(&option3_object);
	grid_logic.addObject(&option3_object, option3_location);
	
	app.log_info("Option3_object successfully added.");
	
	
	manager_logic.addShownColor(&option1_color);
	manager_logic.addShownColor(&option2_color);
	manager_logic.addShownColor(&option3_color);
	
	
	app.log_info("Entering application loop...");
	
	app.loop();
	
	app.log_info("Application loop terminated, exiting program.");
	return 0;
}