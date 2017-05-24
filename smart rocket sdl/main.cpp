/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

#include "main.h"
#include "Rocket.h"


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


//Scene textures
LTexture gTimeTextTexture;

bool init()
{
	//Initialization flag
	bool success = true;

	srand(time(NULL));

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

	gTimeTextTexture.free();

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
			SDL_Rect targetRect{ SCREEN_WIDTH / 2, 60, 30, 30 };
			Dot dot;

			//test rocket creation
			Rocket rocket(gRenderer, "rocket_mini.png");

			//Current time start time
			Uint32 startTime = 0;

			//Set text color as black
			SDL_Color textColor = { 0, 0, 0, 255 };

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
						rocket.recreate();
					}

					//dot.handleEvent(e);
					rocket.handleEvent(e);
				}
				//Set text to be rendered
				timeText.str("");
				timeText << SDL_GetTicks() - startTime;
				timeText.str(to_string(rocket.getDnaCount()));
				//Render text
				if (!gTimeTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor, gFont, gRenderer))
				{
					printf("Unable to render time texture!\n");
				}

				//move the dot
				dot.move();
				rocket.move();

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);


				//Render objects
				//target
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0xFF);
				SDL_RenderFillRect(gRenderer, &targetRect);

				dot.render(gRenderer);
				rocket.render(gRenderer);

				gTimeTextTexture.render(gRenderer, 10, SCREEN_HEIGHT / 2, NULL, 0, NULL, SDL_FLIP_NONE);

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}