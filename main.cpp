#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "cleanup.h"

using namespace std;


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TILE_SIZE = 40;

const string path = "D:/users/alex/downloads/";
SDL_Window* window;
SDL_Renderer* renderer;



void printError(const string& s)
{
	cout << s << " error: " << SDL_GetError() << endl;
}

void createWindow(const string &title, const int &width, const int &height)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		printError("SDL_INIT");

	window = SDL_CreateWindow(title.c_str(), 100, 100, width, height, SDL_WINDOW_SHOWN);

	if (window == nullptr) {
		printError("Window");
		SDL_Quit();
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == nullptr) {
		printError("Renderer");
		cleanup(window);
		SDL_Quit();
	}
}

SDL_Texture* loadTexture(const string &file, SDL_Renderer* ren) 
{
	SDL_Texture* texture = IMG_LoadTexture(ren, file.c_str());
	
	if (texture == nullptr) 
		printError("LoadTexture");
	
	return texture;
}

void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, int w, int h)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;

	SDL_RenderCopy(ren, tex, NULL, &dst);
}
void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y)
{
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	renderTexture(tex, ren, x, y, w, h);
}

void renderTextureCentred(SDL_Texture* tex, SDL_Renderer* ren)
{
		int w, h;
		SDL_QueryTexture(tex, NULL, NULL, &w, &h);
		renderTexture(tex, ren, (SCREEN_WIDTH / 2) - (w / 2), (SCREEN_HEIGHT / 2) - (h / 2), w, h);
}

void lessonsBefore()
{
	createWindow("hello", SCREEN_WIDTH, SCREEN_HEIGHT);

	//	SDL_Texture* tex = loadTexture(path+"a.bmp", renderer);
	SDL_Texture* tex1 = loadTexture(path + "background.png", renderer);
	SDL_Texture* tex2 = loadTexture(path + "image.png", renderer);

	if (tex1 == nullptr || tex2 == nullptr) {
		cleanup(tex1, tex2, renderer, window);
		SDL_Quit();
	}


	SDL_RenderClear(renderer);

	for (int i = 0; i <= SCREEN_HEIGHT; i += TILE_SIZE) {
		for (int j = 0; j <= SCREEN_WIDTH - TILE_SIZE; j += TILE_SIZE)
			renderTexture(tex1, renderer, j, i, TILE_SIZE, TILE_SIZE);
	}

	renderTextureCentred(tex2, renderer);


	SDL_RenderPresent(renderer);
	SDL_Delay(3000);


	cleanup(tex1, tex2, renderer, window);
	IMG_Quit();
	SDL_Quit();
}




int main(int argc, char *argv[])
{
	createWindow("hello", SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_Texture* tex = loadTexture(path+"start.png", renderer);
	SDL_Texture* tex1 = loadTexture(path + "background.png", renderer);
	SDL_Texture* tex2 = loadTexture(path + "image.png", renderer);

	if (tex1 == nullptr || tex2 == nullptr) {
		cleanup(tex1, tex2, renderer, window);
		SDL_Quit();
	}


	SDL_RenderClear(renderer);

	for (int i = 0; i <= SCREEN_HEIGHT; i += TILE_SIZE) {
		for (int j = 0; j <= SCREEN_WIDTH - TILE_SIZE; j += TILE_SIZE)
			renderTexture(tex1, renderer, j, i, TILE_SIZE, TILE_SIZE);
	}

	renderTextureCentred(tex2, renderer);

	SDL_RenderPresent(renderer);
	SDL_Event e;
	bool quit = false;
	int a = 0;

	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				quit = true;

			if (e.type == SDL_KEYDOWN)
				a += 20;

			if (e.type == SDL_MOUSEBUTTONDOWN)
				quit = true;
		}
		SDL_RenderClear(renderer);
		renderTexture(tex, renderer, NULL+a, NULL, 64, 48);
		SDL_RenderPresent(renderer);
	}



	cleanup(tex1, tex2, renderer, window);
	IMG_Quit();
	SDL_Quit();


	cout << "yeah" << endl;

	system("PAUSE");
	return 0;
}


