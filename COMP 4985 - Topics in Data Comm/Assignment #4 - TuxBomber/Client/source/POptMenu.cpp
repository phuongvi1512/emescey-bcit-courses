#include "../headers/mainHeader.h"

/*------------------------------------------------------------------------------------------------------------------
 --       FUNCTION:                  POptMenu (Constructor)
 --
 --       DATE:                      April 15th, 2009
 --
 --       REVISIONS:                 None yet
 --
 --       DESIGNER:					Alin Albu
 --
 --       PROGRAMMER:				Alin Albu
 --
 --       INTERFACE:                 POptMenu::POptMenu(std::string modelNames[], std::string fileNames[], std::string mfilename, std::string smfilename, SDL_Surface* screen)
 --
 --       RETURNS:                   POptMenu
 --
 --       NOTES:
 --       Intializes the player options menu.
 ----------------------------------------------------------------------------------------------------------------------*/
POptMenu::POptMenu(std::string modelNames[], std::string fileNames[],
		std::string mfilename, std::string smfilename, SDL_Surface* screen) {
	printf("Creating Option Menu!\n");
	int i;
	loaded_ = 0;
	modelLoaded_ = 0;
	pNameColourRed_ = 0;
	pNameColourGreen_ = 0;
	pNameColourBlue_ = 0;
	this->screen_ = screen;
	for (i = 0; i < num_options_; i++) {
		this->fileNames_[i] = fileNames[i];
		if (!loadBackground(fileNames_[i], i)) {
			printf("File %s did not load.\n", fileNames_[i].c_str());
			exit(1);
		}
	}
	for (i = 0; i < num_models_; i++) {

		this->modelNames_[i] = modelNames[i];
		if (!loadModel(modelNames_[i], i)) {
			printf("File %s did not load.\n", modelNames_[i].c_str());
			exit(1);
		}
	}
	this->setMusic(Mix_LoadMUS(mfilename.c_str()));
	this->setNexMusic(Mix_LoadWAV(smfilename.c_str()));
	this->name_exists = false;
	printf("Option Menu Created!\n");

}

/*------------------------------------------------------------------------------------------------------------------
 --       FUNCTION:                  POptMenu (Destructor)
 --
 --       DATE:                      April 15th, 2009
 --
 --       REVISIONS:
 --
 --       DESIGNER:					Alin Albu
 --
 --       PROGRAMMER:				Alin Albu
 --
 --       INTERFACE:                 POptMenu::~POptMenu()
 --
 --       RETURNS:
 --
 --       NOTES:
 --       Frees screen surface.
 ----------------------------------------------------------------------------------------------------------------------*/
POptMenu::~POptMenu() {
	for (int i = 0; i < num_options_; i++) {
		SDL_FreeSurface(backgrounds_[i]);
	}
	Mix_FreeMusic(music_);
	Mix_FreeChunk(nexMusic_);
}

/*------------------------------------------------------------------------------------------------------------------
 --       FUNCTION:                  showModels
 --
 --       DATE:                      APril 15th, 2009
 --
 --       REVISIONS:                 None yet
 --
 --       DESIGNER:					Alin Albu
 --
 --       PROGRAMMER:				Alin Albu
 --
 --       INTERFACE:                 bool showModels (void)
 --
 --       RETURNS:                   Bool
 --
 --       NOTES:
 --       Shows the models available in the game with the selected one being in front
		 of the other ones.The models in the back are scaled.
 ----------------------------------------------------------------------------------------------------------------------*/
bool POptMenu::showModels() {
	printf("Loading Models:");
	SDL_Rect offset;
	int i, toLoad, result;
	double center, left1, left2, left3, right1, right2, right3;
	offset.y = screen_->h - 300;

	center = screen_->w / 2;
	left1 = 0.75 * center;
	left2 = 0.50 * center;
	left3 = 0.25 * center;

	right1 = center + left3;
	right2 = center + left2;
	right3 = center + left1;

	for (i = 0; i < 3; i++) {
		toLoad = (modelLoaded_ - 3) + i;
		printf(".");
		if (toLoad < 0) {
			continue;
		}

		switch (i) {
		case 0: {
			zoomed_[i] = zoomSurface(models_[toLoad], 0.7, 0.7, 1);
			optimizeImg(&zoomed_[i]);
			offset.x = (int) left3 - (zoomed_[i]->w / 2);
			result = SDL_BlitSurface(zoomed_[i], 0, screen_, &offset);
			break;

		}

		case 1: {
			zoomed_[i] = zoomSurface(models_[toLoad], 0.8, 0.8, 1);
			optimizeImg(&zoomed_[i]);
			offset.x = (int) left2 - (zoomed_[i]->w / 2);
			result = SDL_BlitSurface(zoomed_[i], 0, screen_, &offset);
			break;

		}
		case 2: {
			zoomed_[i] = zoomSurface(models_[toLoad], 0.9, 0.9, 1);
			optimizeImg(&zoomed_[i]);
			offset.x = (int) left1 - (zoomed_[i]->w / 2);
			result = SDL_BlitSurface(zoomed_[i], 0, screen_, &offset);
			break;

		}
		}
	}

	for (i = 6; i > 3; i--) {
		toLoad = (modelLoaded_ - 3) + i;
		if (toLoad >= num_models_) {
			continue;
		}

		switch (i) {
		case 4: {
			zoomed_[i] = zoomSurface(models_[toLoad], 0.9, 0.9, 1);
			optimizeImg(&zoomed_[i]);
			offset.x = (int) right1 - (zoomed_[i]->w / 2);
			;
			result = SDL_BlitSurface(zoomed_[i], 0, screen_, &offset);
			break;

		}
		case 5: {
			zoomed_[i] = zoomSurface(models_[toLoad], 0.8, 0.8, 1);
			optimizeImg(&zoomed_[i]);
			offset.x = (int) right2 - (zoomed_[i]->w / 2);
			result = SDL_BlitSurface(zoomed_[i], 0, screen_, &offset);
			break;

		}
		case 6: {
			zoomed_[i] = zoomSurface(models_[toLoad], 0.7, 0.7, 1);
			optimizeImg(&zoomed_[i]);
			offset.x = (int) right3 - (zoomed_[i]->w / 2);
			result = SDL_BlitSurface(zoomed_[i], 0, screen_, &offset);
			break;
		}
		}
	}

	offset.x = (int) center - (int) (models_[modelLoaded_]->w / 2);
	result = SDL_BlitSurface(models_[modelLoaded_], 0, screen_, &offset);

	if (result == 0)
		return (SDL_Flip(screen_) != -1);
	else
		return false;
}

/*------------------------------------------------------------------------------------------------------------------
 --       FUNCTION:                  showloaded
 --
 --       DATE:                      April 15th, 2009
 --
 --       REVISIONS:                 None yet
 --
 --       DESIGNER:					Alin Albu
 --
 --       PROGRAMMER:				Alin Albu
 --
 --       INTERFACE:                 bool POptMenu::showloaded()
 --
 --       RETURNS:                   bool
 --
 --       NOTES:
 --          Shows loaded background .
 ----------------------------------------------------------------------------------------------------------------------*/
bool POptMenu::showloaded() {
	TTF_Font *font;
	SDL_Surface *name;
	SDL_Color text_color = { pNameColourRed_, pNameColourGreen_, pNameColourBlue_ };

	printf("Loading backgrounds\n");
	bool result = false;
	result = move(0, 0);
	if (result) {
		if ((font = TTF_OpenFont("resources/fonts/igloo.ttf", 50)) == NULL) {
			printf("Couldn't open desired font type: %s\n", SDL_GetError());
			exit(4);
		}
		printf("Background Loaded\n");
		result = showModels();
		if (name_exists) {

			if ((name = TTF_RenderText_Solid(font, pName_.c_str(), text_color))
					== NULL)
				printf("Could not update text");
			apply_surface((350 - (name->w / 2)), 120, name, screen_);
			SDL_Flip(screen_);
			printf("TESTING");
		}

	}
	return result;
}
/*------------------------------------------------------------------------------------------------------------------
 --       FUNCTION:                  move
 --
 --       DATE:                      April 15, 2008
 --
 --       REVISIONS:                 None yet
 --
 --       DESIGNER:					Alin Albu
 --
 --       PROGRAMMER:				Alin Albu
 --
 --       INTERFACE:                 bool POptMenu::move(int xStep, int yStep)
 --
 --       RETURNS:                   void.
 --
 --       NOTES:
 --          Moves the option menu around the screen.
 ----------------------------------------------------------------------------------------------------------------------*/
bool POptMenu::move(int xStep, int yStep) {
	printf("Moving Option Menu");
	SDL_Rect offset;
	offset.x = xStep;
	offset.y = yStep;
	int i = SDL_BlitSurface(backgrounds_[loaded_], 0, screen_, &offset);
	return i == 0;
}

/*------------------------------------------------------------------------------------------------------------------
 --       FUNCTION:                  start
 --
 --       DATE:                      April 16, 2009
 --
 --       REVISIONS:                 None yet
 --
 --       DESIGNER:					Alin Albu
 --
 --       PROGRAMMER:				Alin Albu
 --
 --       INTERFACE:                 int POptMenu::start()
 --
 --       RETURNS:                   int.
 --
 --       NOTES:
 --          Waits for user input from the option menu. Calls different stuff ///
 --          depending on what was entered.
 ----------------------------------------------------------------------------------------------------------------------*/
int POptMenu::start() {
	printf("Option menu execution started\n");
	SDL_Event event;
	std::string exitOpts[3] = { "resources/img/menus/OK_CANCEL_EXIT.xcf",
			"resources/img/menus/OK_EXIT.xcf", "resources/img/menus/CANCEL_EXIT.xcf" };
	InputOkCancel *player_name = new InputOkCancel(exitOpts, "resources/sound/menu_move.wav",screen_, 20);
	InputOkCancel *player_name_colour_red = new InputOkCancel(exitOpts, "resources/sound/menu_move.wav",screen_, 3);
	InputOkCancel *player_name_colour_green = new InputOkCancel(exitOpts, "resources/sound/menu_move.wav",screen_, 3);
	InputOkCancel *player_name_colour_blue = new InputOkCancel(exitOpts, "resources/sound/menu_move.wav",screen_, 3);
	loaded_ = 0;
	if (!this->showloaded())
		return 0;
	while (true) {
		SDL_WaitEvent(&event);
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_UP:
				Mix_PlayChannel(-1, nexMusic_, 0);
				if (loaded_ == num_options_ - 1) {
					loaded_ = 1;
				} else {
					++loaded_;
				}
				if (!this->showloaded())
					return 0;
				break;

			case SDLK_DOWN:
				Mix_PlayChannel(-1, nexMusic_, 0);
				if (loaded_ < 2) {
					loaded_ = num_options_ - 1;
				} else {
					--loaded_;
				}
				if (!this->showloaded())
					return 0;
				break;
			case SDLK_LEFT:
				if (loaded_ == 2) {
					if (!this->move(0, 0))
						return 0;
					this->setModelLoaded(this->getModelLoaded() - 1);
					this->showModels();
					break;
				}
				break;
			case SDLK_RIGHT:
				if (loaded_ == 2) {
					if (!this->move(0, 0))
						return 0;
					this->setModelLoaded(this->getModelLoaded() + 1);
					this->showModels();
					break;
				}
				break;
			case SDLK_F11:
				return 'f';
			case SDLK_ESCAPE:
				Mix_PlayChannel(-1, nexMusic_, 0);
				return 1;
			case SDLK_RETURN:
				if (loaded_ == 1) {
					Mix_PlayChannel(-1, nexMusic_, 0);
					return loaded_;
				} else if (loaded_ == 4) {
					pName_ = player_name->start(event);
					name_exists = true;
					this->showloaded();
				}
				break;
			default:
				break;
			}
		} else if (event.type == SDL_QUIT) {
			loaded_ = 1;
			exit(25);
		} else if (event.type == SDL_MOUSEMOTION) {
			if ((event.motion.x > 40) && (event.motion.x < 112)
					&& (event.motion.y > 110) && (event.motion.y < 160)) {
				if (loaded_ == num_options_ - 1)
					continue;
				loaded_ = num_options_ - 1;
				Mix_PlayChannel(-1, nexMusic_, 0);
				if (!this->showloaded())
					return 0;
			} else if ((event.motion.x > 40) && (event.motion.y > 210)
					&& (event.motion.y < 260)) {

				if (loaded_ == num_options_ - 2)
					continue;

				loaded_ = num_options_ - 2;
				Mix_PlayChannel(-1, nexMusic_, 0);
				if (!this->showloaded())
					return 0;

			} else if ((event.motion.x > 40) && (event.motion.x < 235)
					&& (event.motion.y > 310) && (event.motion.y < 360)) {

				if (loaded_ == num_options_ - 3)
					continue;

				loaded_ = num_options_ - 3;
				Mix_PlayChannel(-1, nexMusic_, 0);
				if (!this->showloaded())
					return 0;

			} else if ((event.motion.x > 40) && (event.motion.x < 135)
					&& (event.motion.y > 710) && (event.motion.y < 760)) {

				if (loaded_ == num_options_ - 4)
					continue;
				loaded_ = num_options_ - 4;
				Mix_PlayChannel(-1, nexMusic_, 0);
				if (!this->showloaded())
					return 0;

			} else if (loaded_ != 0) {
				loaded_ = 0;
				if (!this->showloaded())
					return 0;
			}
		} else if (event.type == SDL_MOUSEBUTTONUP) {
			if (loaded_ == 1) {
				return loaded_;
			} else if (loaded_ == 4) {
				pName_ = player_name->start(event);
				name_exists = true;
				this->showloaded();
			}else if(loaded_ == 3){
				pNameColourRed_ = atoi(player_name_colour_red->start(event).c_str());
				pNameColourGreen_ = atoi(player_name_colour_green->start(event).c_str());
				pNameColourBlue_ = atoi(player_name_colour_blue->start(event).c_str());
			}
		}

	}
	return 0;

}
