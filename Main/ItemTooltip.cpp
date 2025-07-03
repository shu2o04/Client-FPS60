#include "stdafx.h"
#include "ItemTooltip.h"
#include "Object.h"
#include "Util.h"
#include "SItemOption.h"
#include "Common.h"
#include "Import.h"
#include "Offset.h"
#include "Config.h"
#include "TAS_ItemRong.h"
#if LUC_CHIEN
#include "CustomLucChien.h"
#endif
nCInfo GInfo;

nCInfo::nCInfo()
{
	this->m_CustomInfo.clear();
	this->m_CustomDescripcionInfo.clear();
}

void nCInfo::loadnInformation(nInformation * info) // OK
{
	for (int n = 0; n < MaxLine; n++)
	{
		if ( info[n].ItemIndex < 0 || info[n].ItemIndex > 7680)
		{
			return;
		}
		this->m_CustomInfo.insert(std::pair<int, nInformation>(info[n].ItemIndex,info[n]));
	}
}

void nCInfo::loadnText(nText * info) // OK
{
	for (int n = 0; n < MaxLine; n++)
	{
		if ( info[n].Index < 0 || info[n].Index > 7680)
		{
			return;
		}
		this->m_CustomDescripcionInfo.insert(std::pair<int, nText>(info[n].Index,info[n]));
	}
}


char * nGetTextLine(int TextIndex)
{
	std::map<int, nText>::iterator it = GInfo.m_CustomDescripcionInfo.find( TextIndex );

	if(it !=  GInfo.m_CustomDescripcionInfo.end())
	{
		return it->second.Text;
	}

	return "no found";
}
#if LUC_CHIEN
int nCInfo::nInformationOP(int CurrenLine, ObjectItem* ItemSearch)
{
	std::map<int, nInformation>::iterator it = GInfo.m_CustomInfo.find(ItemSearch->ItemID);

#else
int nCInfo::nInformationOP(int CurrenLine, int ItemSearch)
{
	std::map<int, nInformation>::iterator it = GInfo.m_CustomInfo.find(ItemSearch);
#endif
	if(it !=  GInfo.m_CustomInfo.end())
	{
		tooltiparray * TooltipLine = (tooltiparray*)NewAddressData3;
		int * ColorTexto = (int*)NewAddressData1;
		int * LineWeight = (int*)NewAddressData2;

		wsprintf(TooltipLine[ CurrenLine ], it->second.OptionName);
		ColorTexto[ CurrenLine ] = it->second.OptionColor;
		LineWeight[ CurrenLine++ ] = 1;

		wsprintf(TooltipLine[CurrenLine++], "\n");
		
		for( int i = 0 ; i < 15 ; i++ )
		{
			#if ACTIVE_VKR
			if ((((ItemSearch->ItemID - (ItemSearch->ItemID % 512)) / 512) == 0) // Vu Khi
			 || (((ItemSearch->ItemID - (ItemSearch->ItemID % 512)) / 512) == 1) // Riu
			 || (((ItemSearch->ItemID - (ItemSearch->ItemID % 512)) / 512) == 2) // Chuy
			 || (((ItemSearch->ItemID - (ItemSearch->ItemID % 512)) / 512) == 3) // Giao
			 || (((ItemSearch->ItemID - (ItemSearch->ItemID % 512)) / 512) == 4) // Cung
			 || (((ItemSearch->ItemID - (ItemSearch->ItemID % 512)) / 512) == 5) // Gay
			)
			{
				if (it->second.TextIndex[i] == -1) { continue; }

				if (GCLASS_ITEM00.ItemRong >= 1 && i == 1)
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = it->second.TextColor[i];
				}
				else if (GCLASS_ITEM00.ItemRong >= 2 && i == 2)
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = it->second.TextColor[i];
				}
				else if (GCLASS_ITEM00.ItemRong >= 3 && i == 3)
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = it->second.TextColor[i];
				}
				else
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = 10;
				}
				LineWeight[CurrenLine++] = 0;
			}
			if ((((ItemSearch->ItemID - (ItemSearch->ItemID % 512)) / 512) == 6))
			{
				if (it->second.TextIndex[i] == -1) { continue; }

				if (GCLASS_ITEM06.ItemRong >= 1 && i == 1)
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = it->second.TextColor[i];
				}
				else if (GCLASS_ITEM06.ItemRong >= 2 && i == 2)
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = it->second.TextColor[i];
				}
				else if (GCLASS_ITEM06.ItemRong >= 3 && i == 3)
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = it->second.TextColor[i];
				}
				else
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = 10;
				}
				LineWeight[CurrenLine++] = 0;
			}
			if ((((ItemSearch->ItemID - (ItemSearch->ItemID % 512)) / 512) == 7))
			{
				if (it->second.TextIndex[i] == -1) { continue; }

				if (GCLASS_ITEM07.ItemRong >= 1 && i == 1)
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = it->second.TextColor[i];
				}
				else if (GCLASS_ITEM07.ItemRong >= 2 && i == 2)
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = it->second.TextColor[i];
				}
				else if (GCLASS_ITEM07.ItemRong >= 3 && i == 3)
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = it->second.TextColor[i];
				}
				else
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = 10;
				}
				LineWeight[CurrenLine++] = 0;
			}
			if ((((ItemSearch->ItemID - (ItemSearch->ItemID % 512)) / 512) == 8))
			{
				if (it->second.TextIndex[i] == -1) { continue; }

				if (GCLASS_ITEM08.ItemRong >= 1 && i == 1)
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = it->second.TextColor[i];
				}
				else if (GCLASS_ITEM08.ItemRong >= 2 && i == 2)
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = it->second.TextColor[i];
				}
				else if (GCLASS_ITEM08.ItemRong >= 3 && i == 3)
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = it->second.TextColor[i];
				}
				else
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = 10;
				}
				LineWeight[CurrenLine++] = 0;
			}
			if ((((ItemSearch->ItemID - (ItemSearch->ItemID % 512)) / 512) == 9))
			{
				if (it->second.TextIndex[i] == -1) { continue; }

				if (GCLASS_ITEM09.ItemRong >= 1 && i == 1)
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = it->second.TextColor[i];
				}
				else if (GCLASS_ITEM09.ItemRong >= 2 && i == 2)
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = it->second.TextColor[i];
				}
				else if (GCLASS_ITEM09.ItemRong >= 3 && i == 3)
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = it->second.TextColor[i];
				}
				else
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = 10;
				}
				LineWeight[CurrenLine++] = 0;
			}
			if ((((ItemSearch->ItemID - (ItemSearch->ItemID % 512)) / 512) == 10))
			{
				if (it->second.TextIndex[i] == -1) { continue; }

				if (GCLASS_ITEM10.ItemRong >= 1 && i == 1)
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = it->second.TextColor[i];
				}
				else if (GCLASS_ITEM10.ItemRong >= 2 && i == 2)
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = it->second.TextColor[i];
				}
				else if (GCLASS_ITEM10.ItemRong >= 3 && i == 3)
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = it->second.TextColor[i];
				}
				else
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = 10;
				}
				LineWeight[CurrenLine++] = 0;
			}
			if ((((ItemSearch->ItemID - (ItemSearch->ItemID % 512)) / 512) == 11))
			{
				if (it->second.TextIndex[i] == -1) { continue; }

				if (GCLASS_ITEM11.ItemRong >= 1 && i == 1)
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = it->second.TextColor[i];
				}
				else if (GCLASS_ITEM11.ItemRong >= 2 && i == 2)
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = it->second.TextColor[i];
				}
				else if (GCLASS_ITEM11.ItemRong >= 3 && i == 3)
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = it->second.TextColor[i];
				}
				else
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = 10;
				}
				LineWeight[CurrenLine++] = 0;
			}
			if ((((ItemSearch->ItemID - (ItemSearch->ItemID % 512)) / 512) == 12))
			{
				if (it->second.TextIndex[i] == -1) { continue; }

				if (GCLASS_ITEM12.ItemRong >= 1 && i == 1)
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = it->second.TextColor[i];
				}
				else if (GCLASS_ITEM12.ItemRong >= 2 && i == 2)
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = it->second.TextColor[i];
				}
				else if (GCLASS_ITEM12.ItemRong >= 3 && i == 3)
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = it->second.TextColor[i];
				}
				else
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = 10;
				}
				LineWeight[CurrenLine++] = 0;
			}
			if ((((ItemSearch->ItemID - (ItemSearch->ItemID % 512)) / 512) == 13))
			{
				if (it->second.TextIndex[i] == -1) { continue; }

				if (GCLASS_ITEM13.ItemRong >= 1 && i == 1)
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = it->second.TextColor[i];
				}
				else if (GCLASS_ITEM13.ItemRong >= 2 && i == 2)
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = it->second.TextColor[i];
				}
				else if (GCLASS_ITEM13.ItemRong >= 3 && i == 3)
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = it->second.TextColor[i];
				}
				else
				{
					wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
					ColorTexto[CurrenLine] = 10;
				}
				LineWeight[CurrenLine++] = 0;
			}
			
			#else
			if (it->second.TextIndex[i] == -1)
			{
				continue;
			}
			wsprintf(TooltipLine[CurrenLine], "%s", nGetTextLine(it->second.TextIndex[i]));
			ColorTexto[CurrenLine] = it->second.TextColor[i];
			LineWeight[CurrenLine++] = 0;
			#endif
		}
		wsprintf(TooltipLine[CurrenLine++], "\n");
		wsprintf(TooltipLine[CurrenLine], gConfig.TTAS_TEXT_ENGINE[107]);
		ColorTexto[CurrenLine] = 3;
		LineWeight[CurrenLine++] = 1;
	}
	
	DWORD TinhToanLucChien = gCustomLucChien.TinhToanLucChien(ItemSearch);
	if (TinhToanLucChien != 0)
	{
		tooltiparray* TooltipLine = (tooltiparray*)NewAddressData3;
		int* ColorTexto = (int*)NewAddressData1;
		int* LineWeight = (int*)NewAddressData2;
		wsprintf(TooltipLine[CurrenLine++], "\n");
		wsprintf(TooltipLine[CurrenLine], "[Lực Chiến : %d]", TinhToanLucChien);
		ColorTexto[CurrenLine] = 16;
		LineWeight[CurrenLine++] = 1;
	}
	return CurrenLine;
}

void Borde(float PosX, float PosY, float Width, float Height, float Arg5, int Arg6)
{
	glColor4f(0.0, 0.0, 0.0, 0.80000001);
	pDrawBarForm(PosX, PosY, Width, Height, Arg5, Arg6); //central
	glEnable(0xDE1u);
	glColor4f(0.0, 0.0, 0.0, 1.00000001);
	pDrawBarForm(PosX, PosY, 2, Height, Arg5, Arg6); //central
	pDrawBarForm(PosX + Width - 2, PosY, 2, Height, Arg5, Arg6); //central
	pDrawBarForm(PosX, PosY, Width, 2, Arg5, Arg6); //central
	pDrawBarForm(PosX, PosY + Height - 2, Width, 2, Arg5, Arg6); //central
	glEnable(0xDE1u);
}

void GetTextColor( int ColorTexto )
{
	SetTextColorByHDC(pTextThis(),-1);

	switch ( ColorTexto )
	{
		case 0:
		case TEXT_WHITE:
		case TEXT_WHITE_RED:
		case TEXT_WHITE_BLUE:
		case TEXT_WHITE_YELLOW:		glColor3f(1.0, 1.0, 1.0);								break;
		case TEXT_BLUE:				glColor3f(0.5f, 0.69999999f, 1.0);						break;
		case TEXT_GRAY:				glColor3f(0.40000001f, 0.40000001f, 0.40000001f);		break;
		case TEXT_GREN_BLUE:		glColor3f(1.0, 1.0, 1.0);								break;
		case TEXT_RED:				glColor3f(1.0, 0.2f, 0.1);								break;
		case TEXT_GOLD:				glColor3f(1.0, 0.80000001f, 0.1);						break;
		case TEXT_GREN:				glColor3f(0.1, 1.0, 0.5f);								break;
		case TEXT_PINK:				glColor3f(1.0, 0.1, 1.0);								break;
		case TEXT_PINK2:			glColor3f(0.80000001f, 0.5, 0.80000001f);				break;
		case TEXT_PURPLE:			glColor3f(0.69999999f, 0.40000001f, 1.0);				break;
		case TEXT_ORANGE:			glColor3f(0.89999998f, 0.41999999f, 0.039999999f);		break;
		default:
		break;
	}

	switch ( ColorTexto )
	{
		case TEXT_WHITE_RED:
			pSetBackgroundTextColor(pTextThis(), 0xA0u, 0, 0, 0xFFu);
			break;
		case TEXT_WHITE_BLUE:
			pSetBackgroundTextColor(pTextThis(), 0, 0, 0xA0u, 0xFFu);
			break;
		case TEXT_WHITE_YELLOW:
			pSetBackgroundTextColor(pTextThis(), 0xA0u, 0x66u, 0, 0xFFu);
			break;
		case TEXT_GREN_BLUE:
			pSetBackgroundTextColor(pTextThis(), 0x3Cu, 0x3Cu, 0xC8u, 0xFFu);
			pSetTextColor(pTextThis(), 0, 0xFFu, 0, 0xFFu);
			break;
		case 15: //-- DeepPink1
			pSetBackgroundTextColor(pTextThis(), 255, 20, 147, 0xFFu);
			pSetTextColor(pTextThis(), 0xFFu, 0xFFu, 0xFFu, 0xFFu);
			break;
		case 16: //-- RoyalBlue1
			pSetBackgroundTextColor(pTextThis(), 72, 118, 255, 0xFFu);
			pSetTextColor(pTextThis(), 0xFFu, 0xFFu, 0xFFu, 0xFFu);
			break;
		case 17: //-- SlateBlue1
			pSetBackgroundTextColor(pTextThis(), 131, 111, 255, 0xFFu);
			pSetTextColor(pTextThis(), 0xFFu, 0xFFu, 0xFFu, 0xFFu);
			break;
		case 18: //-- Azure2
			pSetBackgroundTextColor(pTextThis(), 224, 238, 238, 0xFFu);
			pSetTextColor(pTextThis(), 0xFFu, 0xFFu, 0xFFu, 0xFFu);
			break;
		case 19: //-- DarkSlateGray1
			pSetBackgroundTextColor(pTextThis(), 151, 255, 255, 0xFFu);
			pSetTextColor(pTextThis(), 0xFFu, 0xFFu, 0xFFu, 0xFFu);
			break;
		case 20: //-- SlateGray1
			pSetBackgroundTextColor(pTextThis(), 198, 226, 255, 0xFFu);
			pSetTextColor(pTextThis(), 0xFFu, 0xFFu, 0xFFu, 0xFFu);
			break;
		case 21: //-- MistyRose1
			pSetBackgroundTextColor(pTextThis(), 255, 228, 225, 0xFFu);
			pSetTextColor(pTextThis(), 0xFFu, 0xFFu, 0xFFu, 0xFFu);
			break;
		case 22: //-- LightSlateBlue
			pSetBackgroundTextColor(pTextThis(), 132, 112, 255, 0xFFu);
			pSetTextColor(pTextThis(), 0xFFu, 0xFFu, 0xFFu, 0xFFu);
			break;
		case 23: //-- DeepSkyBlue1
			pSetBackgroundTextColor(pTextThis(), 0, 191, 255, 0xFFu);
			pSetTextColor(pTextThis(), 0xFFu, 0xFFu, 0xFFu, 0xFFu);
			break;
		case 24: //-- Turquoise1
			pSetBackgroundTextColor(pTextThis(), 0, 245, 255, 0xFFu);
			pSetTextColor(pTextThis(), 0xFFu, 0xFFu, 0xFFu, 0xFFu);
			break;
		default:
			sub_4200F0_Addr(pTextThis(), 0);
			break;
	}
}
