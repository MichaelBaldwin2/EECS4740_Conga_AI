  
#pragma once

#include "Renderer.h"
#include <SDL.h>
#include <string>

class Texture
{
private:
	SDL_Texture* sdlTexture;
	std::string filePath;
	int width;
	int height;

public:
	Texture();
	Texture(const Renderer renderer, const std::string filePath = "");
	Texture(SDL_Texture* sdlTexture, std::string filePath, int width, int height);
	Texture(Renderer renderer, SDL_Surface* surface);
	void Free();
	SDL_Texture* GetSDLTexture() const;
	int GetWidth() const;
	int GetHeight() const;
	std::string GetFilePath() const;
};