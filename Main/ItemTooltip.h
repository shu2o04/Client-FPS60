#pragma once
#define MaxLine 2000
#if BXH_LUCHIEN
#include "Object.h"
#endif
struct nInformation
{
	int ItemIndex;
	char OptionName[32];
	int OptionColor;
	int TextIndex[15];
	int TextColor[15];
};

struct nText
{
	int Index;
	char Text[254];
};
class nCInfo
{
	public:
	nCInfo();
	void loadnInformation(nInformation * info);
	void loadnText(nText * info);
	#if LUC_CHIEN
	int nInformationOP(int CurrenLine, ObjectItem* ItemSearch);
	#else
	int nInformationOP(int CurrenLine, int ItemSearch);
	#endif
	std::map<int, nInformation> m_CustomInfo;
	std::map<int, nText> m_CustomDescripcionInfo;
};
extern nCInfo GInfo;