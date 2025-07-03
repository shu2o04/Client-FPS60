#pragma once
struct ITEM_HELPER
{
	char IndexItem[5][300];
};

class NewIntros
{
	public:
	void DrawWindowMocNap();
	void OpenWindowMocNap();
	std::vector<ITEM_HELPER> m_IndexItem;
};
extern NewIntros gNewIntros;