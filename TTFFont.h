#pragma once

#include <SDL_ttf.h>
#include <string>

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

