#pragma once

class CCapeAnimation
{
public:
	void Load();
	static void DrawViewPort(DWORD ObjectPointer, DWORD ModelPointer, DWORD a3);
};

extern CCapeAnimation gCapeAnimation;