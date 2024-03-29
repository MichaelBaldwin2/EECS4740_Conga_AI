/* TTFFont.cpp
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 * Copyright 2020 by Michael Baldwin <michael.baldwin3@rockets.utoledo.edu>
 *				 and Ethan Hassett <ethan.hassett@rockets.utoledo.edu>
 */

#include "TTFFont.h"
#include <SDL_ttf.h>
#include <spdlog/spdlog.h>
#include <string>

TTFFont::TTFFont() : ttfFont(nullptr), fontSize(0), filePath() {}

TTFFont::TTFFont(const std::string filePath, int fontSize) : ttfFont(nullptr), fontSize(fontSize), filePath()
{
	ttfFont = TTF_OpenFont(filePath.c_str(), fontSize);
	if(ttfFont == nullptr)
	{
		spdlog::error("Unable to open TTF_Font from ttf font file at {0}! TTF_Error: {1}", filePath, TTF_GetError());
		TTF_CloseFont(ttfFont);
		ttfFont = nullptr;
	}
}

void TTFFont::Free()
{
	TTF_CloseFont(ttfFont);
	ttfFont = nullptr;
}

TTF_Font* TTFFont::GetTTFFont() const
{
	return ttfFont;
}

int TTFFont::GetFontSize() const
{
	return fontSize;
}

std::string TTFFont::GetFilePath() const
{
	return filePath;
}
