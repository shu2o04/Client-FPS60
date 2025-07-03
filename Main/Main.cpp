#include "stdafx.h"
#include "resource.h"
#include "Main.h"
#include "..\\..\\Util\\CCRC32.H"
#include "Common.h"
#include "Controller.h"
#include "CustomCommandInfo.h"
#include "CustomEventTime.h"
#include "CustomItem.h"
#include "CustomJewel.h"
#include "CustomMap.h"
#include "CustomMonster.h"
#include "CustomNpcName.h"
#include "CustomWing.h"
#include "Fix.h"
#include "StaticEffect.h"
#include "DynamicEffect.h"
#include "HackCheck.h"
#include "HealthBar.h"
#include "Item.h"
#include "ItemShopValue.h" 
#include "ItemSmoke.h"
#include "Interface.h"
#include "OffTrade.h"
#include "PacketManager.h"
#include "PrintPlayer.h"
#include "Protect.h"
#include "Protocol.h"
#include "Reconnect.h"
#include "Resolution.h"
#include "User.h"
#include "Util.h"
#include "TMemory.h"
#include "Console.h"
#include "InterEx.h"
#include "postInterface.h"
#include "CustomBow.h"
#include "CustomGloves.h"
#include "CustomPet.h"
#include "Pet.h"
#include "PetHook.h"
#include "CustomCloak.h"
#include "cape.h"
#include "ItemTRSData.h"
#include "CustomEffectRemake.h"
#include "ItemRemake.h"
#include "ItemManager.h"
#include "ItemInfoEx.h"
#include "CSCharacterS13.h"
#include "CustomItemPrice.h"
#include "MonsterGlow.h"
#include "CustomMonsterGlow.h"
#include "ModelEffect.h"
#include "CChatEx.h"
#include "CustomPetEffect.h"
#include "CChatClassic.h"
#include "CMacroUIEx.h"
#include "TrayModeNew.h"
#include "MiniMap.h"
#include "WindowsStruct.h"
#include "SItemOption.h"
#include "ItemTooltip.h"
#include "PetMontura.h"
#include "Central.h"
#include "BuffIcon.h"
#include "MuHelper.h"
#include "CChatClassic.h"
#include "cCPetRenderMesh.h"
#include "MultiSelect.h"
#include "ItemTooltip.h"
#include "JCRendernoItemGlow.h"
#include "ItemGlow.h"
#include "CustomNameColor.h"
#include "PartyBar.h"
#include "WeatherEffect.h"
#include "Antilag.h"
#include "CustomPhysicsBody.h"
#include "Rotate360Character.h"
#include "MiniMapTron.h"
#include "Config.h"
#include "GuildLogo.h"
#include "NPC.h"
#include "Font.h"
#include "CustomJewelBank.h"
#include "NewUIMyInventory.h"
#include "NewUIButton.h"
#include "LoginMainWin.h"
#include "UIControl.h"
#include "CUIMng.h"
#include "ServerListMove.h"
#include "AutoLoginWin.h"
#if(SAU_ANTIHACK)
#include "BAntihack.h"
#endif
#if(ANTI_CRACK_MAIN == 1)
#include "AntiCrack.h"
#endif
#if(BUNDLE_ITEM)
#include "BundleItem.h"
#endif
#if LUC_CHIEN
#include "CustomLucChien.h"
#endif
#if CHAOS_RATE_FIX
#include "ChaosMachine.h"
#endif
#include "TAS_CharacterList.h"
#include "TAS_DameBoss.h"

#include "CustomModelFlag.h"
#include "Luna_CNewflag.h"
#include "ThueFlag.h"
#include "TAS_SoiItem.h"
#include "TAS_MobileAvt.h"
#if SLOTPET2
#include "WSclient.h"
#endif
#include "JCSceneCreate.h"
#include "TAS_InterSS2.h"
#include "TAS_CashShop.h"
#include "Widescreen.h"
#include "Interfaces6.h"
#include "CameraMove.h"
#include "ItemMove.h"
#include "AtlansAbbys.h"
#include "FixAttack.h"
#include "CustomEarthQuakeSkill.h"
#include "CustomFog.h"
#include "SkyBox.h"
#include "Graphics/Graphics.h"

HINSTANCE hins;
void StartAddress(LPVOID lpThreadParameter)
{
	HANDLE v1;
	HANDLE v2;

	while ( TRUE )
	{
		Sleep(5000);
		v1 = GetCurrentProcess();
		SetProcessWorkingSetSize(v1, 0xFFFFFFFF, 0xFFFFFFFF);
		v2 = GetCurrentProcess();
		SetThreadPriority(v2, -2);

		char* charPointerAt0x8128AC4 = (char*)*(DWORD*)(0x8128AC4);

		if ((pPlayerState == 5 || pPlayerState == 4 || pPlayerState == 2) && charPointerAt0x8128AC4 == NULL)
		{
			ExitProcess(0);
		}

	}
}

__declspec(naked) void OffButtonQuestInStats()
{
	static DWORD ButtonAddress = 0x0077EBB5;
	_asm{jmp ButtonAddress}
}

__declspec(naked) void OffButtonPetsInStats()
{
	static DWORD ButtonAddress = 0x0077EC5E;
	_asm{jmp ButtonAddress}
}

__declspec(naked) void OffButtonSkillMasterInStats()
{
	static DWORD ButtonAddress = 0x0077ECE7;
	_asm{jmp ButtonAddress}
}

__declspec(naked) void OffButtonInventoryExt()
{
	static DWORD ButtonAddress = 0x00836A28;
	_asm{jmp ButtonAddress}
}

__declspec(naked) void OffButtonOpenStore()
{
	static DWORD ButtonAddress = 0x008369B4;
	_asm{jmp ButtonAddress}
}
__declspec(naked) void OffButtonRepeirInInventory()
{
	static DWORD ButtonAddress = 0x00836941;
	_asm{jmp ButtonAddress}
}
DWORD		Test_Buff;
char		Test_LevelBuff[40];
Naked(Credit)
{
	//gInterface.DrawFormat(eWhite, 35, 463, 150, 1,	"Cập nhật cuối: 18:13:22 PM (13/07/2024)");
	_asm
	{
		lea eax, Test_LevelBuff
		push eax
	}
	_asm
	{
		mov Test_Buff, 0x004D7D1D
		jmp Test_Buff
	}
}
void MyLogoMUm()
{
	if (SceneFlag == 2)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		*(float*)0xE8CB18 = *(float*)0xE8CB18 + 0.01999999955296516;
		if (*(float*)0xE8CB18 > 10.0)
			*(float*)0xE8CB18 = 10.0;
		EnableAlphaBlend();
		float v25 = *(float*)0xE8CB18 - 0.300000011920929;
		float v24 = *(float*)0xE8CB18 - 0.300000011920929;
		float v23 = *(float*)0xE8CB18 - 0.300000011920929;
		float v22 = *(float*)0xE8CB18 - 0.300000011920929;
		glColor4f(v22, v23, v24, v25);
		EnableAlphaTest(1);
		glColor4f(*(float*)0xE8CB18, *(float*)0xE8CB18, *(float*)0xE8CB18, *(float*)0xE8CB18);
		RenderBitmap(0x17905, 217.60001, 25.0, 204.8, 142.4, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glEnable(GL_TEXTURE_2D);
	}
}
void MyLogo(int a1)
{
	MyLogoMUm();
	RenderInfomationR();
}
#if ACTIVE_FIX_DISMOVE
#define MAX_SENDBUF		8192
#define MAX_RECVBUF		8192

class IsMyMoveDis
{
	public:
	HWND		m_hWnd;
	BOOL		m_bGame;
	int			m_iMaxSockets;
	SOCKET		m_socket;
	BYTE		m_SendBuf[MAX_SENDBUF];
	int			m_nSendBufLen;
	BYTE		m_RecvBuf[MAX_RECVBUF];
	int			m_nRecvBufLen;
	int			m_LogPrint;
	DWORD		m_logfp;
	DWORD		m_pPacketQueue;
	DWORD		m_pBuff;
	DWORD	    FuncToDWORD;
	BOOL Close();
};
extern void PackedFixOverflow();
BOOL IsMyMoveDis::Close()
{
	m_nSendBufLen = 0;
	m_nRecvBufLen = 0;
	ZeroMemory(m_RecvBuf, sizeof(MAX_RECVBUF));
	ZeroMemory(m_SendBuf, sizeof(MAX_SENDBUF));
	return TRUE;
}
void PackedFixOverflow()
{
	SetCompleteHook(0xE8, 0x004051B9, FuncToDWORD(&IsMyMoveDis::Close));
}
#endif
void RunMyFuncTion()
{
	//PackedFixOverflow();
	//gCashShop.Load();
	//gSkyBox.Load();

	GCCharacter.Load();
	InitLoad();
	g_Console.Load();
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)StartAddress, 0, 0, 0);
	SetByte((PVOID)(0x00649E24 + 3), 14);

	#if(SLOTPET2)
	g_pMyInventory.Init();
	g_pWSclient.Init();
	#endif
	#if(SOIITEM)
	g_pQuickCommandWindow.szInit();
	#endif
	#if(HT_THUE_FLAG)
	Flag.Load();
	#endif
	#if CHAOS_RATE_FIX
	InitChaosBox();
	#endif
	//#if LUC_CHIEN
	//gCustomLucChien.Load(gProtect.m_MainInfo.m_LucChienDataItem);
	//#endif
	#if(BUNDLE_ITEM)
	BundleItem.Hook();
	#endif
	#if(REGISTER_INGAME)
	g_pLoginMainWin.Init();
	#endif
	SetByte((PVOID)(0x81C03FA), 1);
	
	SetCompleteHook(0xE8, 0x004D7EB1, &MyLogo);				//TAS NEW - Xóa logo cũ, Ghi lại logo mới	
	g_ServerSelWin.Init();									//Move Server Login
	SetOp((LPVOID)0x004D7D13, (LPVOID)Credit, ASM::JMP);	//Tạo dòng CopyRight
	g_pRenderText.Init();									//Custom Font
	AutoLogin.Load();										//Tự động đăng nhập
	//gCUIMng.Load();										//Loading New
	//g_MuunSystem.Init();									//PetMuunInventory	
	//g_Option.Init();

	//===================
	SetRange(0x008429CB, 0x59, 0x90);						// Tắt Name Quái ( gốc )
	MemorySet(0x005AD691, 0x90, 0x5);						// Fix Skill
	InitGuildIcon();
}
extern "C" _declspec(dllexport) void EntryProc() // OK
{
	if (gProtect.ReadMainFile("Tas\\Loader.tas") == 0)
	{
		MessageBoxW(NULL, L"Library was not found, contact to administrator for help!\nZalo: 0862 798 624\nError Code: 0x0000000A", L"TuanDev", MB_OK); ExitProcess(0);
	}

	if (gProtect.ReadTooltipTRSData("Data\\Local\\TooltipTRSData.bmd") == 0)
	{
		MessageBoxW(NULL, L"Library was not found, contact to administrator for help!\nZalo: 0862 798 624\nError Code: 0x0000000B", L"TuanDev", MB_OK); ExitProcess(0);
	}

	if (gProtect.ReadMakeViewTRSData("Data\\Local\\MakeWorldTRSData.bmd") == 0)
	{
		MessageBoxW(NULL, L"Library was not found, contact to administrator for help!\nZalo: 0862 798 624\nError Code: 0x0000000C", L"TuanDev", MB_OK); ExitProcess(0);
	}

	if (gProtect.ReadPetEffectBMD("Data\\Local\\EffectTRSData.bmd") == 0)
	{
		MessageBoxW(NULL, L"Library was not found, contact to administrator for help!\nZalo: 0862 798 624\nError Code: 0x0000000D", L"TuanDev", MB_OK); ExitProcess(0);
	}
	QTFrame.InitFrameOpenGL();
	//gInterfaceBar.Load();
#if(ANTI_CRACK_MAIN == 1)
	MainProtection();
#endif
	SetByte(0x00E61144, 0xA0); // Accent
	SetByte(0x004D1E69, 0xEB); // Crack (mu.exe)
	SetByte(0x004D228D, 0xE9); // Crack (GameGuard)
	SetByte(0x004D228E, 0x8B); // Crack (GameGuard)
	SetByte(0x004D228F, 0x00); // Crack (GameGuard)
	SetByte(0x004D2290, 0x00); // Crack (GameGuard)
	SetByte(0x004D2291, 0x00); // Crack (GameGuard)
	SetByte(0x004D559C, 0xEB); // Crack (ResourceGuard)
	SetByte(0x00633F7A, 0xEB); // Crack (ResourceGuard)
	SetByte(0x00634403, 0xEB); // Crack (ResourceGuard)
	SetByte(0x0063E6C4, 0xEB); // Crack (ResourceGuard)
	SetByte(0x004D2246, 0xEB); // Crack (ResourceGuard)
	SetByte(0x00501163, 0xEB); // Crack (ResourceGuard)
	SetByte(0x0040AF0A, 0x00); // Crack (ResourceGuard)
	SetByte(0x0040B4BC,0x50); // Login Screen
	SetByte(0x0040B4C5,0x50); // Login Screen
	SetByte(0x0040B4CF,0x18); // Login Screen
	SetByte(0x0040AF0A,0x00); // Login Screen
	SetByte(0x0040AFD5,0xEB); // Login Screen
	SetByte(0x00777FD6, 0x70); // Item Text Limit
	SetByte(0x00777FD7, 0x17); // Item Text Limit
	SetByte(0x004EBEC7, 0x3C); // Item Text Limit
	SetByte(0x005C4004, 0x3C); // Item Text Limit
	SetByte(0x007E40BB, 0x3C); // Item Text Limit
	SetByte(0x0081B546, 0x3C); // Item Text Limit
	SetByte(0x0081B58D, 0x3C); // Item Text Limit
	SetByte(0x0086E284, 0x3C); // Item Text Limit
	SetByte(0x0086E44C, 0x3C); // Item Text Limit
	SetByte(0x0086E573, 0x3C); // Item Text Limit
	SetByte(0x0086F8FC, 0x3C); // Item Text Limit
	SetByte(0x007DA373, 0xB7); // Item Type Limit
	SetByte(0x007E1C44, 0xB7); // Item Type Limit
	SetByte(0x0052100D, 0xEB); // Ctrl Fix
	SetByte(0x0052101B, 0x02); // Ctrl Fix
	SetByte(0x009543C4, 0x00); // Move Vulcanus


	SetByte(0x004D128F, 0x1D); // Fix Resolucion 640x480
	SetCompleteHook(0xE9, 0x004D1CF0, 0x004D1DC2); //-- Remoce MuError.DMP
	MemorySet(0x00D20170, 0x90, 0x1B); //-- Remove Creation MuError.log
	SetByte(0x0064CBD1, ((gProtect.m_MainInfo.HelperActiveAlert == 0) ? 0xEB : 0x75)); //-- Helper Message Box
	SetByte(0x0064CBD0, (BYTE)gProtect.m_MainInfo.HelperActiveLevel); //-- Helper Active Level
	SetByte(0x0095CEEF, (BYTE)gProtect.m_MainInfo.HelperActiveLevel); //-- Helper Active Level
	SetByte(0x0095CF14, (BYTE)gProtect.m_MainInfo.HelperActiveLevel); //-- Helper Active Level
	SetByte(0x00E61F68, (gProtect.m_MainInfo.ClientVersion[0] + 1)); //-- Version
	SetByte(0x00E61F69, (gProtect.m_MainInfo.ClientVersion[2] + 2)); //-- Version
	SetByte(0x00E61F6A, (gProtect.m_MainInfo.ClientVersion[3] + 3)); //-- Version
	SetByte(0x00E61F6B, (gProtect.m_MainInfo.ClientVersion[5] + 4)); //-- Version
	SetByte(0x00E61F6C, (gProtect.m_MainInfo.ClientVersion[6] + 5)); //-- Version

	SetWord(0x00E609E4, (gProtect.m_MainInfo.IpAddressPort)); //-- IpAddressPort
	SetDword(0x004D9D3B, (DWORD)&FrameValue);
	SetDword(0x004DAC60, (DWORD)&FrameValue);
	SetDword(0x7B55338, (DWORD)10);
	SetDword(0x004D597B, (DWORD)&MainTickCount);
	SetDword(0x004DA289, (DWORD)&MainTickCount);
	SetDword(0x004DA297, (DWORD)&MainTickCount);
	SetDword(0x004DA3A2, (DWORD)&MainTickCount);
	SetDword(0x004DA3CE, (DWORD)&MainTickCount);
	SetDword(0x004DA3D9, (DWORD)&MainTickCount);
	SetDword(0x0063D326, (DWORD)&MainTickCount);
	SetDword(0x00642112, (DWORD)&MainTickCount);
	SetDword(0x004D0E09, (DWORD)gProtect.m_MainInfo.WindowName);
	SetDword(0x004D9F55, (DWORD)gProtect.m_MainInfo.ScreenShotPath);
	InitAtlansAbbys();
	FixVisualSpeedAttack();
	gCustomEarthQuake.LoadRenderSkill();

	//TAS Fix Sub:	
	SetDword(0x009540E2 + 1, (DWORD)gProtect.m_MainInfo.ServerName1); // %s-%d (Non-PVP) %s
	SetDword(0x009540AC + 1, (DWORD)gProtect.m_MainInfo.ServerName2); // %s-%d (ALL PVP) %s	
	SetDword(0x00954115 + 1, (DWORD)gProtect.m_MainInfo.ServerName3); // %s-%d (Gold PVP) %s
	SetDword(0x00954148 + 1, (DWORD)gProtect.m_MainInfo.ServerName4); // Công Thành Chiến

	SetByte(0x005C914B + 3, 0x00); //-- LuckItemmove
	MemorySet(0x0063E908, 0x90, 20); //-- C1:F3:04
	SetCompleteHook(0xE9, 0x0064452A, 0x00644537); //-- Fix montura
	SetCompleteHook(0xE9, 0x005880F0, 0x0058811F); //Fix gm wing on Blood castle
	SetDword(0x00588444 + 3, 4095); //Fix gm wing on Blood castle
	MemoryCpy(0x00E611B2, gProtect.m_MainInfo.IpAddress, sizeof(gProtect.m_MainInfo.IpAddress)); //-- IpAddress
	MemoryCpy(0x00E61F70, gProtect.m_MainInfo.ClientSerial, sizeof(gProtect.m_MainInfo.ClientSerial)); //-- ClientSerial
	SetCompleteHook(0xFF, 0x0065FD79, &ProtocolCoreEx);
	if (gProtect.m_MainInfo.CustomInterfaceType == 0)
	{
		SetDword(0x004D9D3B, (DWORD)&FrameValue);
		SetDword(0x004DAC60, (DWORD)&FrameValue);
		SetDword(0x7B55338, (DWORD)10);
		SetDword(0x004D597B, (DWORD)&MainTickCount);
		SetDword(0x004DA289, (DWORD)&MainTickCount);
		SetDword(0x004DA297, (DWORD)&MainTickCount);
		SetDword(0x004DA3A2, (DWORD)&MainTickCount);
		SetDword(0x004DA3CE, (DWORD)&MainTickCount);
		SetDword(0x004DA3D9, (DWORD)&MainTickCount);
		SetDword(0x0063D326, (DWORD)&MainTickCount);
		SetDword(0x00642112, (DWORD)&MainTickCount);

		SetCompleteHook(0xE9, 0x004DA280, &CheckTickCount1);

		SetCompleteHook(0xE9, 0x004DA3A1, &CheckTickCount2);

		g_CameraWalkInstance.Init();

	}

	SetCompleteHook(0xE8,0x005B96E8,&DrawNewHealthBar); //HP và Icon VIP
	SetCompleteHook(0xE8, 0x005DB3BE, 0x005DB490); // Vocanus
	VirtualizeOffset(0x004D9D39,12);
	VirtualizeOffset(0x004D9D45,7);
	VirtualizeOffset(0x004D9EFC,15);
	VirtualizeOffset(0x004DAC5C,8);
	VirtualizeOffset(0x005451F7,5);
	VirtualizeOffset(0x00545230,8);
	VirtualizeOffset(0x005A52E9,8);	
	
	LoadReferenceAddressTable((HMODULE)hins, MAKEINTRESOURCE(IDR_BIN1),(DWORD)&NewAddressData1);
	LoadReferenceAddressTable((HMODULE)hins, MAKEINTRESOURCE(IDR_BIN2),(DWORD)&NewAddressData2);
	LoadReferenceAddressTable((HMODULE)hins, MAKEINTRESOURCE(IDR_BIN3),(DWORD)&NewAddressData3);

	gCustomMessage.LoadEng(gProtect.m_MainInfo.EngCustomMessageInfo);
	gCustomMessage.LoadPor(gProtect.m_MainInfo.PorCustomMessageInfo);
	gCustomMessage.LoadSpn(gProtect.m_MainInfo.SpnCustomMessageInfo);
	gCustomJewel.Load(gProtect.m_MainInfo.CustomJewelInfo);
	gCustomWing.Load(gProtect.m_MainInfo.CustomWingInfo);
	gCustomItem.Load(gProtect.m_MainInfo.CustomItemInfo);
	gCustomCommandInfo.Load(gProtect.m_MainInfo.CustomCommandInfo);
	gCETime.Load(gProtect.m_MainInfo.CustomEventInfo);
	gSmokeEffect.Load(gProtect.m_MainInfo.CustomSmokeEffect);
	gCustomMonster.Load(gProtect.m_MainInfo.CustomMonsters);
	gNPCName.Load(gProtect.m_MainInfo.CustomNPCName);	//--
	gCustomBattleGloves.Load(gProtect.m_MainInfo.CustomGloves);
	gCustomBow.Load(gProtect.m_MainInfo.CustomBowInfo);
	gCustomPet2.Load(gProtect.m_MainInfo.CustomPetInfo);
	gCloak.Load(gProtect.m_MainInfo.m_CustomCloak);
	ItemTRSData.Load(gProtect.m_MainInfo.CustomPosition);
	gCustomRemake.Load(gProtect.m_MainInfo.CustomRemake);
	gItemManager.Load(gProtect.m_MainInfo.m_ItemInfoEx);
	gCustomModelEffect.Load(gProtect.m_MainInfo.m_CustomModelInfo);	//--
	gCustomCEffectPet.Load(gProtect.m_ReadBMD.m_PetCEffectBMD);
	gCustomWingEffect.Load(gProtect.m_ReadBMD.CustomWingEffectInfo);
	gDynamicWingEffect.Load(gProtect.m_ReadBMD.DynamicWingEffectInfo);
	cRender.Load(gProtect.m_ReadBMD.RenderMeshPet);
	gCustomMonsterGlow.LoadGlow(gProtect.m_ReadBMD.m_CustomMonsterGlow);
	gCustomMonsterGlow.LoadBrightness(gProtect.m_ReadBMD.m_CustomMonsterbrightness);
	JCEffectMonster.Load( gProtect.m_ReadBMD.m_CustomMonsterEffect );
	JCRemoveGlow.Load( gProtect.m_ReadBMD.m_JCWRemoveGlow );
	#if(HT_THUE_FLAG)
	gCustomModelFlag.SetInfo(gProtect.m_MainInfo.m_mModelFlagData);
	gCustomModelFlag.SetInfoJPG(gProtect.m_MainInfo.m_mJPGFlagData);
	#endif
	#if UPDATE > 15
	JCRender.Load( gProtect.m_ReadBMD.m_JCWRenderMesh );
	#endif
	gIconBuff.LoadEng(gProtect.m_ReadTooltipTRSData.m_TooltipTRSDataEng);
	gIconBuff.LoadSpn(gProtect.m_ReadTooltipTRSData.m_TooltipTRSDataSpn);
	gIconBuff.LoadPor(gProtect.m_ReadTooltipTRSData.m_TooltipTRSDataPor);
	GInfo.loadnInformation( gProtect.m_ReadTooltipTRSData.m_TRSTooltipData );
	GInfo.loadnText( gProtect.m_ReadTooltipTRSData.m_TRSTooltipText );
	#if UPDATE >= 15
	gSelectCharRamdon.LoadMultiChar(gProtect.m_MakeViewTRSData.m_RenderSelect);
	#endif
	gPacketManager.LoadEncryptionKey("Data\\Enc1.dat");
	gPacketManager.LoadDecryptionKey("Data\\Dec2.dat");
	gProtect.CheckLauncher();
	gProtect.CheckInstance();
	gProtect.CheckClientFile();
	gProtect.CheckHackFile();
	gProtect.CheckPluginFile1();
	gProtect.CheckPluginFile2();
	gProtect.CheckPluginFile3();
	gProtect.CheckPluginFile4();
	gProtect.CheckPluginFile5();
	gProtect.CheckCameraFile();
	gProtect.CheckMaxGameInstances();
	InitHackCheck();
	gTrayMode.Load();
	InitCommon();
	JCRemoveGlow.Init();
	#if UPDATE > 15
	JCRender.Init();
	#endif
	gConfig.Load();
	gCentral.InitCentral();//-- Control: camara||mouse
	QTPary.Load();
	gItemInfoEx.Load();
	gMuHelper.LoadHelper();
	gSelectCharRamdon.InitMultiChar();
	gCSCharacterS13.initCharacter();
	ItemTRSData.Init();

	if(gProtect.m_MainInfo.DisableCustomCloack == 0)
	{
		gCapeAnimation.Load();
	}

	if(gProtect.m_MainInfo.DisableCustomPet == 0)
	{
		gCustomPet.Load();
		gObjCreatePetExHook();
		gCustomCEffectPet.Init();
		initmontura();
	}

	gRenderMap.MiniMapload();
	InitItem();
	InitJewel();
	InitPrintPlayer();
	gCustomNameColor.Load();
	InitReconnect();
	InitResolution();
	gController.Load();
	InitWing();
	gObjUser.Load();
	gInterface.RenderObjectSystem();
	gCMacroUIEx.Load();	
	gNPC.Load();
	
	gCustomJewelBank.Load();
	if (FontON)
	{
		gFont.Load();
	}

	switch(gProtect.m_MainInfo.CustomInterfaceType)
	{
		case 2:
		InitInter3();
		gCChatClassic.Load();
		break;
		case 4:
		gCRenderEx700.Init();
		gCChatEx.Load();
		break;
	}
	gOffTrade.Init();
	if(gProtect.m_MainInfo.CustomMonsterEnable == 1)
	{
		gCustomMonster.InitMonster();
	}

	InitloadGlow();

	if(gProtect.m_MainInfo.DisableCustomBow == 0)
	{
		gCustomBow.Init();
	}

	if(gProtect.m_MainInfo.DisableCustomClaws == 0)
	{
		gCustomBattleGloves.Init();
	}

	gCustomMap.Load();

	if(gProtect.m_MainInfo.EnableShopValueSystem == 1)
	{
		gItemPrice.Init();
	}

	if(gProtect.m_MainInfo.CsSkill == 1)
	{
		//Liberar CS Skills
		SetByte((0x005B89C3+3), 0x00);
		SetByte((0x005B89C9+3), 0x00);
		SetByte((0x005B89CF+3), 0x00);
		SetByte((0x005B89D5+3), 0x00);
		SetByte((0x005B89DB+3), 0x00);
		SetByte((0x005B89E1+3), 0x00);
		SetWord((0x005B89E7+3), 0x00);
		SetByte((0x005C6314+2), 0x00);
		SetByte((0x005C6327+2), 0x00);
		SetByte((0x005C633A+2), 0x00);
		SetByte((0x005C634D+2), 0x00);
		SetByte((0x005C6360+2), 0x00);
		SetByte((0x005C6373+2), 0x00);
		SetWord((0x005C6386+2), 0x00);
	}

	if(gProtect.m_MainInfo.RemoveClass == 3)
	{
		SetByte(0x004030D1+3,6);
	}

	if(gProtect.m_MainInfo.RemoveClass == 2)
	{
		SetByte(0x004030D1+3,5);
	}
	if(gProtect.m_MainInfo.RemoveClass == 1)
	{
		SetByte(0x004030D1+3,4);
	}

	SetWord(0x00405B7C, gProtect.m_MainInfo.ReduceMemory);
	SetWord(0x0040CC40, gProtect.m_MainInfo.ReduceMemory);
	
	if(gProtect.m_MainInfo.DisableTree == 1)
	{
		MemorySet(0x008193F0,0x90,0xC8); //Remove Master Skill Tree Window(A Buttom)
	}
	if(gProtect.m_MainInfo.EffectPlus15 == 0)
	{
		MemorySet(0x006097B0,0x90,0x69D);
	}

	if(gProtect.m_MainInfo.DisableGens == 1)
	{
		MemorySet(0x007C5AD2, 0x90, 0x05);			//-> Disable Gens (Key B)
	}

	if(gProtect.m_MainInfo.DisableTabMap == 1)
	{
		MemorySet(0x0062F876, 0x90, 0x30);			//-> Disable ViewMap (Key TAB)
	}
	if(gProtect.m_MainInfo.DisableRepeirInInventory == 1)
	{
		SetCompleteHook(0xE9, 0x0083693C, &OffButtonRepeirInInventory);
	}
	if(gProtect.m_MainInfo.DisableButtonOpenStore == 1)
	{
		SetCompleteHook(0xE9, 0x008369AF, &OffButtonOpenStore);
	}

	if(gProtect.m_MainInfo.DisableButtonInventoryExt == 1)
	{
		SetCompleteHook(0xE9, 0x00836A23, &OffButtonInventoryExt);
	}

	if(gProtect.m_MainInfo.DisableButtonQuestInStats == 1)
	{
		SetCompleteHook(0xE9, 0x0077EBB0, &OffButtonQuestInStats);
	}
	if(gProtect.m_MainInfo.DisableButtonPetsInStats == 1)
	{
		SetCompleteHook(0xE9, 0x0077EC59, &OffButtonPetsInStats);
	}
	if(gProtect.m_MainInfo.DisableButtonSkillMaster == 1)
	{
		SetCompleteHook(0xE9, 0x0077ECE2, &OffButtonSkillMasterInStats);
	}
	if(gProtect.m_MainInfo.DisableEffectRemake == 0)
	{
		gCreateEffect.Load();
	}
	if(gProtect.m_MainInfo.CustomInterfaceType == 1)
	{
		SetByte(0x005528A0, 0xC3); // [Fix] Remover Recuo PVP		
	}
	if(gProtect.m_MainInfo.DisableHelper == 1)
	{
		MemorySet(0x0085B6AC, 0x90, 0x05);			//-> Remove Helper Top Screen
		MemorySet(0x0085CC50, 0x90, 0x05);			//-> Disable Helper (Key Z)
		MemorySet(0x007D40A2, 0x90, 0x05);			//-> Disable Helper (Key Home)
	}
	gPostInterface.Load();	//<-- post item
	gCItemSetOption.Load();
	SetCompleteHook(0xE9, 0x0071B1A3, 0x00720894);	//-- Fix RF
	InitAttackSpeed();								//-- Fix Agilidad
	SetCompleteHook(0xE9, 0x0095DFBE, 0x0095DFD3);	//-- Fix RF
	SetCompleteHook(0xE9, 0x0071AE92, 0x00720894);	//Fix RF Skill
	SetCompleteHook(0xE9, 0x0071B1A3, 0x00720894);	//Fix RF Skill
	SetFloat(0x0D27B1C, 1110.000);					// 1100.000
	SetFloat(0xD477AC, 1.0);						//Fix ItemStack in Itemtoolip/Shop		
	MemorySet(0x0064452A, 0x90, 0x0D); // Fix Dark horse look around
	SetByte(0x005C914B + 3, 0x00); // LuckItemmove

	#if(FIX_GIAM_LAG_MAIN)
	InitReduceCPU();								//Giam lag main
	#endif
	#if(FIX_LAG_QOAI)
	SetCompleteHook(0xE8, 0x0059AFFA, 0x0059B00E); // -- Fix lag quái new
	#endif
	#if(TAT_QUEST_T)
	SetCompleteHook(0xE9, 0x007D399F, 0x007D39D8); // Tắt Quest (T)
	SetCompleteHook(0xE9, 0x0077EB65, 0x0077EC0E); // Tắt Quest ở trạng thái ký tự
	#endif
	//InitItemMove();

	#if(FIX_MONTER_TRABE)
	SetCompleteHook(0xE8, 0x0059AFFA, 0x0059B00E); // Fix Monster Trabe
	#endif
	gDmgBoss.Initz();
	#if(SAU_ANTIHACK)
	gBAntihack.LoadBB();
	#endif
	RunMyFuncTion();
}
void TAS_HideMain(HINSTANCE hModule)
{
	DWORD dwPEB_LDR_DATA = 0;
	_asm
	{
		pushad;
		pushfd;
		mov eax, fs:[30h]
		mov eax, [eax+0Ch]
		mov dwPEB_LDR_DATA, eax	 
		InLoadOrderModuleList:
		mov esi, [eax+0Ch]
		mov edx, [eax+10h]
		LoopInLoadOrderModuleList: 
		lodsd
		mov esi, eax
		mov ecx, [eax+18h]
		cmp ecx, hModule
		jne SkipA
		mov ebx, [eax]
		mov ecx, [eax+4]
		mov [ecx], ebx
		mov [ebx+4], ecx
		jmp InMemoryOrderModuleList
		SkipA:
		cmp edx, esi
		jne LoopInLoadOrderModuleList
		InMemoryOrderModuleList:
		mov eax, dwPEB_LDR_DATA
		mov esi, [eax+14h]
		mov edx, [eax+18h]
		LoopInMemoryOrderModuleList: 
		lodsd
		mov esi, eax
		mov ecx, [eax+10h]
		cmp ecx, hModule
		jne SkipB
		mov ebx, [eax] 
		mov ecx, [eax+4]
		mov [ecx], ebx
		mov [ebx+4], ecx
		jmp InInitializationOrderModuleList
		SkipB:
		cmp edx, esi
		jne LoopInMemoryOrderModuleList
		InInitializationOrderModuleList:
		mov eax, dwPEB_LDR_DATA	
		mov esi, [eax+1Ch]
		mov edx, [eax+20h]
		LoopInInitializationOrderModuleList: 
		lodsd
		mov esi, eax		
		mov ecx, [eax+08h]
		cmp ecx, hModule		
		jne SkipC
		mov ebx, [eax] 
		mov ecx, [eax+4]
		mov [ecx], ebx
		mov [ebx+4], ecx
		jmp Finished
		SkipC:
		cmp edx, esi
		jne LoopInInitializationOrderModuleList
		Finished:
		popfd;
		popad;
	}
}
void ShellBMD() 
{
	system("iMain.tas");
}

int main() 
{
	ShellBMD();
	return 0;
}
BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) // OK
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		hins = (HINSTANCE)hModule;
		gController.Instance = static_cast<HMODULE>(hModule);
		break;
	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	default:
		break;
	}

	return 1;
}
//BOOL APIENTRY DllMain(HMODULE hModule,DWORD ul_reason_for_call,LPVOID lpReserved) // OK
//{
//	switch(ul_reason_for_call)
//	{
//		case DLL_PROCESS_ATTACH:
//		hins = (HINSTANCE)hModule;
//		gController.Instance = hModule;
//		//main();
//		OSVERSIONINFO KiemTraHDH;
//		KiemTraHDH.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
//		GetVersionEx(&KiemTraHDH);
//		if (KiemTraHDH.dwMajorVersion == 6 && KiemTraHDH.dwMinorVersion == 0 || KiemTraHDH.dwMajorVersion == 6 && KiemTraHDH.dwMinorVersion == 1)
//		{
//			//Nothing
//		}
//		else
//		{
//			TAS_HideMain(hModule);
//		}
//		case DLL_PROCESS_DETACH:		break;
//		case DLL_THREAD_ATTACH:			break;
//		case DLL_THREAD_DETACH:			break;
//	}
//	return 1;
//}