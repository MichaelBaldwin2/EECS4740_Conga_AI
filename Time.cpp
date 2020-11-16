/* Time.cpp
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
 * Copyright 2020 by Michael Baldwin <michael.baldwin3@rockets.utoledo.edu>
 *				 and Ethan Hassett <ethan.hassett@rockets.utoledo.edu>
 */

#include "Time.h"
#include <SDL.h>

float Time::logicDeltaTime = 0.0f;
float Time::renderDeltaTime = 0.0f;
float Time::lastLogicTicks = 0.0f;
float Time::lastRenderTicks = 0.0f;

float Time::LogicDeltaTime()
{
	return logicDeltaTime;
}

float Time::RenderDeltaTime()
{
	return renderDeltaTime;
}

float Time::RealTimeSinceStartup()
{
	return static_cast<float>((static_cast<double>(SDL_GetPerformanceCounter()) / static_cast<double>(SDL_GetPerformanceFrequency())));
}

void Time::UpdateLogicDeltaTime()
{
	logicDeltaTime = RealTimeSinceStartup() - lastLogicTicks;
	lastLogicTicks = RealTimeSinceStartup();
}

void Time::UpdateRenderDeltaTime()
{
	renderDeltaTime = RealTimeSinceStartup() - lastRenderTicks;
	lastRenderTicks = RealTimeSinceStartup();
}
