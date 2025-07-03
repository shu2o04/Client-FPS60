#pragma once

#include "CustomCommandInfo.h"
#include "CustomEventTime.h"

#include "CustomItem.h"
#include "CustomJewel.h"
#include "CustomMessage.h"
#include "CustomMonster.h"
#include "CustomNpcName.h"
#include "CustomWing.h"
#include "ItemSmoke.h"
#include "StaticEffect.h"
#include "DynamicEffect.h"
//--
#include "CustomGloves.h"
#include "CustomBow.h"
#include "CustomPet.h"
#include "CustomCloak.h"
#include "ItemTRSData.h"
#include "CustomEffectRemake.h"
#include "ItemManager.h"
#include "CustomItemPrice.h"
#include "CustomMonsterGlow.h"
#include "ModelEffect.h"
#include "CustomPetEffect.h"
#include "SetEffect.h"
//--
#include "BuffIcon.h"
#include "cCPetRenderMesh.h"
#include "MultiSelect.h"
//--
#include "ItemTooltip.h"
#include "MonsterEffect.h"
#include "JCRendernoItemGlow.h"
#include "ItemGlow.h"
#if LUC_CHIEN
#include "CustomLucChien.h"
#endif
#include "CustomModelFlag.h"
struct MAIN_FILE_INFO
{
	BYTE LauncherType; 
	char LauncherName[32];
	char CustomerName[32];
	char IpAddress[32];
	WORD IpAddressPort;
	char ClientVersion[8];
	char ClientSerial[17];
	char WindowName[32];
	char ScreenShotPath[50];
	char ClientName[32];
	char HackName[32];
	char PluginName5[32];
	char PluginName1[32];
	char PluginName2[32];
	char PluginName3[32];
	char PluginName4[32];
	char CameraName[32];
	char ServerName1[32];
	char ServerName2[32];
	char ServerName3[32];
	char ServerName4[32];
	DWORD ClientCRC32;
	DWORD HackCRC32;
	DWORD Plugin5CRC32;
	DWORD Plugin1CRC32;
	DWORD Plugin2CRC32;
	DWORD Plugin3CRC32;
	DWORD Plugin4CRC32;
	DWORD CameraCRC32;
	DWORD HelperActiveAlert;
	DWORD HelperActiveLevel;
	DWORD DWMaxAttackSpeed;
	DWORD DKMaxAttackSpeed;
	DWORD FEMaxAttackSpeed;
	DWORD MGMaxAttackSpeed;
	DWORD DLMaxAttackSpeed;
	DWORD SUMaxAttackSpeed;
	DWORD RFMaxAttackSpeed;
	DWORD ReconnectTime;
	DWORD ReduceMemory;
	DWORD EnableMiniMapCircular;
	DWORD MaxGameInstances;
	DWORD MinimapX;
	DWORD MinimapY;
	DWORD RemoveClass;
	DWORD RankUserType;
	DWORD DisableTree; 
	DWORD CsSkill; 
	DWORD DisableReflectEffect;
	DWORD EnableVipShop;
	DWORD VipTypes;
	DWORD PrintLogo;
	DWORD CustomMenuSwitch;
	DWORD CustomMenuType;
	DWORD MenuButtons[30];
	DWORD EnableCoinStatus;
	DWORD EnableShopValueSystem;
	DWORD CustomStoreEnableJoB;
	DWORD CustomStoreEnableJoS;
	DWORD CustomStoreEnableJoC;
	DWORD CustomStoreEnableCoin1;
	DWORD CustomStoreEnableCoin2;
	DWORD CustomStoreEnableCoin3;
	DWORD CustomOffStoreEnable;
	DWORD CustomMonsterEnable;
	DWORD DisablePartyHpBar;
	DWORD RankUserShowOverHead;
	DWORD RankUserOnlyOnSafeZone;
	DWORD RankUserShowReset;
	DWORD RankUserShowMasterReset;
	DWORD RankUserNeedAltKey;
	DWORD EnableRankVIP;
	DWORD EnableRankTuChan;
	//---
	DWORD CustomInterfaceType;
	DWORD SocketItemAcceptHarmonySwitch;
	DWORD CustomRemoveCoord;
	DWORD TIME_GMT;
	DWORD MonitorFPS;
	DWORD MonitorMS;
	DWORD LimitFPS;
	DWORD EffectPlus15;
	DWORD DisableGens;
	DWORD DisableTabMap;
	DWORD DisableHelper;
	DWORD Disable380ButtonChaoBox;
	DWORD DisableAdvance;
	DWORD DisableEffectRemake;
	DWORD DisableCustomClaws;
	DWORD DisableCustomBow;
	DWORD DisableCustomCloack;
	DWORD DisableCustomPosition;
	DWORD DisableCustomPet;
	DWORD DisableSocketInvetori;
	DWORD DisableRepeirInInventory;
	DWORD DisableButtonOpenStore;
	DWORD DisableButtonInventoryExt;
	DWORD DisableButtonQuestInStats;
	DWORD DisableButtonPetsInStats;
	DWORD DisableButtonSkillMaster;
	DWORD SelectCharAnimate;
	DWORD SelectCharS13;
	DWORD EnableCameraZoom;
	DWORD Cam_ZoomMax;
	DWORD Cam_ZoomMin;
	DWORD InventoryUPGRADE;
	DWORD CameraZoom;


	CUSTOM_MESSAGE_INFO EngCustomMessageInfo[MAX_CUSTOM_MESSAGE];
	CUSTOM_MESSAGE_INFO PorCustomMessageInfo[MAX_CUSTOM_MESSAGE];
	CUSTOM_MESSAGE_INFO SpnCustomMessageInfo[MAX_CUSTOM_MESSAGE];
	CUSTOM_JEWEL_INFO CustomJewelInfo[MAX_CUSTOM_JEWEL];
	CUSTOM_WING_INFO CustomWingInfo[MAX_CUSTOM_WING];
	CUSTOM_ITEM_INFO CustomItemInfo[MAX_CUSTOM_ITEM];
	CUSTOM_COMMAND_INFO CustomCommandInfo[MAX_CUSTOM_COMMAND];
	CUSTOM_EVENT_INFO CustomEventInfo[MAX_EVENTTIME];
	CUSTOM_SMOKEEFFECT CustomSmokeEffect[MAX_SMOKE_ITEMS];
	CUSTOMMONSTER_DATA CustomMonsters[MAX_CUSTOMMONSTER];
	NPCNAME_DATA CustomNPCName[MAX_CUSTOM_NPCNAME];
	//--
	CUSTOM_BOW_INFO CustomBowInfo[MAX_CUSTOM_BOW];
	CUSTOM_RF_GLOVES CustomGloves[MAX_CUSTOM_GLOVES];
	CUSTOM_PET_INFO CustomPetInfo[MAX_PET_ITEM];
	CUSTOMCLOAK_DATA m_CustomCloak[MAX_CUSTOMCLOAK];
	CUSTOM_POSITION_INFO CustomPosition[MAX_POSITION_ITEM];
	REMAKE_EFFECT CustomRemake[MAX_REMAKE_EFFECT];
	//--
	ITEM_INFO m_ItemInfoEx[MAX_ITEM2];
	CUSTOM_MODEL_EFFECT_INFO m_CustomModelInfo[MAX_MODEL_EFFECT];
	//Custom NPC
	#if LUC_CHIEN
	ITEMDATA_LUCCHIEN m_LucChienDataItem[MAX_CUSTOM_LUCCHIEN];
	#endif
	#if(HT_THUE_FLAG)
	MODEL_FLAG m_mModelFlagData[MAX_MODEL_FLAG];
	JPG_FLAG m_mJPGFlagData[MAX_MODEL_FLAG];
	#endif
};

struct PETEFFECT_BMD
{
	PET_EFFECT_CUSTOM m_PetCEffectBMD[max_ceffect];
	CUSTOM_WING_EFFECT_INFO CustomWingEffectInfo[MAX_CUSTOM_WING_EFFECT];
	DYNAMIC_WING_EFFECT_INFO DynamicWingEffectInfo[MAX_DYNAMIC_WING_EFFECT];
	RENDER_MESH RenderMeshPet[MAX_RENDER_MESH];
	CUSTOM_MONSTERGLOW_INFO m_CustomMonsterGlow[MAX_CUSTOM_MONSTERGLOW];
	CUSTOM_GLOW_INFO m_CustomMonsterbrightness[MAX_CUSTOM_MONSTERGLOW];
	//--
	xMonsterEffect m_CustomMonsterEffect[MAX_EFFECT_MONSTER];
	//--
	JCItemnoGlow m_JCWRemoveGlow[ MAX_NOGLOW ];
	//--
};

struct TOOLTIP_BMD
{
	RenderTooltipBuff m_TooltipTRSDataEng[256];
	RenderTooltipBuff m_TooltipTRSDataSpn[256];
	RenderTooltipBuff m_TooltipTRSDataPor[256];

	nInformation m_TRSTooltipData[MaxLine];
	nText m_TRSTooltipText[MaxLine];

	;
};

struct RENDER_MAKE_VIEW
{
	#if UPDATE >= 15
	SelectChar m_RenderSelect[MAX_WORLD_SETTINGS];
	DWORD TooltipS15;
	#endif
};

class CProtect
{
public:
	bool ReadMainFile(char* name);
	bool ReadPetEffectBMD(char* name);
	bool ReadTooltipTRSData(char* name);
	bool ReadMakeViewTRSData(char* name);
	void CheckLauncher();
	void CheckInstance();
	void CheckClientFile();
	void CheckHackFile();
	void CheckPluginFile1();
	void CheckPluginFile2();
	void CheckPluginFile3();
	void CheckPluginFile4();
	void CheckPluginFile5();
	void CheckCameraFile();
	void CheckMaxGameInstances();
	MAIN_FILE_INFO m_MainInfo;
	PETEFFECT_BMD m_ReadBMD;
	TOOLTIP_BMD m_ReadTooltipTRSData;
	RENDER_MAKE_VIEW m_MakeViewTRSData;
	DWORD m_ClientFileCRC;
	DWORD m_ReadBMDFileCRC;
	DWORD m_ReadTooltipTRSDataFileCRC;
	DWORD m_MakeViewTRSDataFileCRC;
};

extern CProtect gProtect;
