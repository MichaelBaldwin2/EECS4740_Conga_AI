/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 * Copyright 2020 by Michael Baldwin <michael.baldwin3@rockets.utoledo.edu>
 *				 and Ethan Hassett <ethan.hassett@rockets.utoledo.edu>
 */

#include "Texture.h"
#include <SDL.h>
#include <SDL_image.h>
#include <spdlog/spdlog.h>
#include <string>

Texture::Texture() : sdlTexture(nullptr), filePath(), width(0), height(0) {}

Texture::Texture(const Renderer renderer, const std::string filePath) : sdlTexture(nullptr), filePath(filePath), width(0), height(0)
{
	spdlog::info("Loading sprite from file: {0}", filePath);

	SDL_Surface* surface = nullptr;
	surface = IMG_Load(filePath.c_str());
	if(surface == nullptr)
	{
		spdlog::error("Unable to load image file at {0}! SDL_Error: {1}", filePath, SDL_GetError());
		SDL_FreeSurface(surface);
		return;
	}

	SDL_Texture* texture = nullptr;
	texture = SDL_CreateTextureFromSurface(renderer.GetSDLRenderer(), surface);
	if(texture == nullptr)
	{
		spdlog::error("Unable to create SDL_Texture from image file at {0}! SDL_Error: {1}", filePath, SDL_GetError());
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
		return;
	}

	sdlTexture = texture;
	width = surface->w;
	height = surface->h;
	SDL_FreeSurface(surface);
}

Texture::Texture(SDL_Texture* sdlTexture, std::string filePath, int width, int height) : sdlTexture(sdlTexture), filePath(filePath), width(width), height(height) {}

Texture::Texture(Renderer renderer, SDL_Surface* surface) : sdlTexture(nullptr), filePath(filePath), width(0), height(0)
{
	SDL_Texture* texture = nullptr;
	texture = SDL_CreateTextureFromSurface(renderer.GetSDLRenderer(), surface);
	if(texture == nullptr)
	{
		spdlog::error("Unable to create SDL_Texture from SDL_Surface! SDL_Error: {0}", SDL_GetError());
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
		return;
	}

	sdlTexture = texture;
	width = surface->w;
	height = surface->h;
}

void Texture::Free()
{
	SDL_DestroyTexture(sdlTexture);
	sdlTexture = nullptr;
}

std::string Texture::GetFilePath() const
{
	return filePath;
}

int Texture::GetWidth() const
{
	return width;
}

int Texture::GetHeight() const
{
	return height;
}

SDL_Texture* Texture::GetSDLTexture() const
{
	return sdlTexture;
}