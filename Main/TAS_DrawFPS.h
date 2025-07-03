#pragma once
class TASXemFps
{
	public:
	void TASXemFps::MainFps();
	void TASXemFps::RenderObjectFps();
	bool TASXemFps::CombinedChecks();
	int lastReport;
	int frameCount;
	int frameRate;
	int iniciador;
	char FPS_REAL[30];
};
extern TASXemFps gFpsView;