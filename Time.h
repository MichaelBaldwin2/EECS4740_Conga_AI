#pragma once

class Time
{
private:
	static float logicDeltaTime;
	static float renderDeltaTime;
	static float lastLogicTicks;
	static float lastRenderTicks;

public:
	/// <summary>
	/// The completion time in seconds since the last time UpdateTick() was called on game loop.
	/// This does NOT update inbetween render calls as multiple renders can happen during one frame.
	/// </summary>
	/// <returns>A floating point value representing the number of seconds elapsed</returns>
	static float LogicDeltaTime();

	/// <summary>
	/// The completion time in seconds since the last time UpdateTick() was called on game loop.
	/// This does NOT update inbetween render calls as multiple renders can happen during one frame.
	/// </summary>
	/// <returns>A floating point value representing the number of seconds elapsed</returns>
	static float RenderDeltaTime();

	/// <summary>
	/// The time in seconds since the game started.
	/// </summary>
	/// <returns>A floating point value representing the number of seconds elapsed</returns>
	static float RealTimeSinceStartup();

	/// <summary>
	/// Internal call for the game loop. DO NOT USE UNLESS YOU KNOW WHAT IT DOES!
	/// </summary>
	static void UpdateLogicDeltaTime();

	/// <summary>
	/// Internal call for the game loop. DO NOT USE UNLESS YOU KNOW WHAT IT DOES!
	/// </summary>
	static void UpdateRenderDeltaTime();
};
