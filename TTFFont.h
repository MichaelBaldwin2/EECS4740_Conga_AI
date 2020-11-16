/* TTFFont.h
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 * Copyright 2020 by Michael Baldwin <michael.baldwin3@rockets.utoledo.edu>
 *				 and Ethan Hassett <ethan.hassett@rockets.utoledo.edu>
 */

#pragma once

#include <SDL_ttf.h>
#include <string>

/// <summary>
/// Wrapper for SDL TTF_Font
/// </summary>
class TTFFont
{
private:
	TTF_Font* ttfFont;
	int fontSize;
	std::string filePath;

public:
	TTFFont();
	TTFFont(const std::string filePath, int fontSize = 11);
	void Free();
	TTF_Font* GetTTFFont() const;
	int GetFontSize() const;
	std::string GetFilePath() const;
};

