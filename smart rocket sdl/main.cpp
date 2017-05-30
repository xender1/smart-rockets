#include "main.h"
#include "SimpleRect.h"
#include "Population.h"


//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Globally used font
TTF_Font *gFont = NULL;

//Text texture
LTexture gTextTexture;

bool init()
{
	//Initialization flag
	bool success = true;

	srand(unsigned int(time(NULL)));

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Smart Rockets", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	gFont = TTF_OpenFont("lazy.ttf", 28);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}

	return success;
}

void close()
{
	//Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;

	gTextTexture.free();

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;


	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}


int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//target rectangle
			SDL_Rect targetRect;
			targetRect.w = 30; targetRect.h = 30;
			targetRect.x = SCREEN_WIDTH / 2 - targetRect.w / 2;
			targetRect.y = 60;
			unsigned char rgba[4] = { 0, 0, 0, 255 };

			vector<CollisionObject*> collisionObjects;

			//add target to collision objects
			collisionObjects.push_back(new CollisionObject(gRenderer, 30, 30, SCREEN_WIDTH / 2 - 15, 60, rgba, true));

			//create a wall
			collisionObjects.push_back(new CollisionObject(gRenderer, 350, 20, SCREEN_WIDTH / 2 - 175, SCREEN_HEIGHT / 2 - 10, rgba, false));
			collisionObjects[1]->setAngle(45);
			
			//my test movement dot
			SimpleRect myRect(gRenderer, "rectangle.png");

			//Population of rockets
			Population myPop(gRenderer, 100);

			//Current time start time
			Uint32 startTime = 0;

			//Set text color as black
			SDL_Color textColor = { 0, 0, 0, 255 };

			//stores text to render to screen
			stringstream timeText;

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}					
					//Reset start time on return keypress
					else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN)
					{
						startTime = SDL_GetTicks();
						myPop.recreate(gRenderer);
					}

					myRect.handleEvent(e);
				}
				//clear text
				timeText.str("");

				//see if population has finished
				if (myPop.isComplete()) {
					timeText.str("Complete");
					myPop.evaluate(targetRect);
					myPop.createMatingPool(gRenderer);
					myPop.createNextGeneration(gRenderer);
				}
				else {
					//timeText << to_string(dot.getDistance()) << " " << to_string(100 * (1 / dot.getDistance()));
					timeText << to_string(myPop.getGenerationNum()) << " " << to_string(myPop.getMaxFitScore());
				}
				//Render text
				if (!gTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor, gFont, gRenderer))
				{
					printf("Unable to render time texture!\n");
				}

				//move my rect
				myRect.move();

				myPop.updateRockets(collisionObjects);

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//Render collision objects
				for (vector<CollisionObject*>::const_iterator it = collisionObjects.begin(); it != collisionObjects.end(); ++it) {
					(*it)->render(gRenderer);
				}
				//render rockets in popluation
				myPop.renderRockets(gRenderer);
				myRect.render(gRenderer);
				//render text
				gTextTexture.render(gRenderer, 10, SCREEN_HEIGHT - gTextTexture.getHeight()*2, NULL, 0, NULL, SDL_FLIP_NONE);

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}