#include "stdafx.h"
#include "Protocol.h"
#include "Common.h"
#include "CustomEventTime.h"
#include "CustomRankUser.h"
#include "HealthBar.h"
#include "Interface.h"
#include "ItemShopValue.h"
#include "Offset.h"
#include "OffTrade.h"
#include "PacketManager.h"
#include "PrintPlayer.h"
#include "Protect.h"
#include "Reconnect.h"
#include "TAS_PKSystem.h"
#include "Util.h"
#include "post_item.h"
#include "postInterface.h"
#include "PetProtocol.h"
#include "User.h"
#include "PartyBuffs.h"
#include "BuffIcon.h"
#include "MiniMapInfo.h"
#include "Central.h"
#include "InterEx.h"
#include "PartyBar.h"
#include "TAS_Invasions.h"
#include "PartySearchSettings.h"
#include "PartySearch.h"
#include "HWID.h"
#include "CustomLuckySpin.h"
#include "CustomJewelBank.h"
#include "Ranking.h"
#include "NewUIMyInventory.h"
#if(SAU_ANTIHACK)
#include "BAntihack.h"
#endif
#include "MessHacking.h"
#include "GuildUpgrade.h"
#include "LoginMainWin.h"
#if(BUNDLE_ITEM)
#include "BundleItem.h"
#endif
#include "TAS_HonHoan.h"
#include "TAS_DanhHieu.h"
#include "TAS_QuanHam.h"
#include "TAS_TuChan.h"
#include "TAS_NewVip.h"
#include "CB_ArenaPvP.h"
#include "TAS_DameBoss.h"
#if CHAOS_RATE_FIX
#include "ChaosMachine.h"
#endif
#include "CSCharacterS13.h"
#include "ThueFlag.h"
#include "TAS_ToolKit.h"
#include "TAS_SoiItem.h"
#include "TAS_CongHuongV2.h"
#include "TAS_ThanMa.h"
#include "TAS_CongPoint.h"
#include "TAS_ItemTrader.h"
#include "TAS_Relife.h"
#if NEWXSHOP
#include "TAS_xShop.h"
#endif
#include "Console.h"
#include "TAS_ItemRong.h"
#include "TAS_SoiItemNew.h"
#include "TAS_DungLuyen.h"
#include "TAS_Harmony.h"
#include "TAS_ItemLocker.h"
#if(CTCMINI)
struct CTCMINI_CGPACKET
{
	PSBMSG_HEAD header; // C3:F3:03
	BYTE CongVao;
};

struct INFOCTCMINI_SENDCLIENT
{
	PSBMSG_HEAD header; // C3:F3:03
	BYTE OpenWindow;
	BYTE GuildWinOld;
};

struct CTCMINIKILL_SENDCLIENT
{
	PSBMSG_HEAD header; // C3:F3:03
	int	TimeCTCMini;
	BYTE Cong[3];
	BYTE Tru[3];

};
#endif
void GCCTCMiniShowWindow(INFOCTCMINI_SENDCLIENT* pMsg);
void GCCTCMiniKill(CTCMINIKILL_SENDCLIENT* pMsg);

#if(B_MOCNAP)
CBINFOMOCNAP_CLIENT mDataMocNapClient;
CBLISTPHANTHUONGMOCNAP_CLIENT mDataListItemMocNapClient;
#endif

BOOL ProtocolCoreEx(BYTE head,BYTE* lpMsg,int size,int key) // OK
{

	BYTE ProtocolType = lpMsg[0];
	BYTE error = 0;
	if (ProtocolType == 0xC1)
	{
		if (size == 74)
		{
			if (head == 0xD && lpMsg[3] == 0x1 && lpMsg[4] == 0x30 && lpMsg[12] == 0x30 && lpMsg[13] == 0x54 && lpMsg[14] == 0x68 && lpMsg[15] == 0x69 && lpMsg[16] == 0x73)
				error++;
		}
		else if (size == 53)
		{
			if (head == 0xD && lpMsg[3] == 0x1 && lpMsg[4] == 0x30 && lpMsg[12] == 0x30 && lpMsg[13] == 0x4F &&	lpMsg[14] == 0x72 && lpMsg[15] == 0x69 && lpMsg[16] == 0x67)
			error++;
		}
		if (error)
		{
			//MessageBoxW(NULL, L"Phát hiện có bất thường. Vui lòng khởi động lại game!", L"TuanDev", MB_OK | MB_ICONERROR);ExitProcess(0);
			//ExitProcess(0);
		}
	}

	//gToolKit.RunAntiHack();
	switch(head)
	{
		#if(NOTICE_PKSYSTEM)
		case 0x0D:
		{			
			PMSG_NOTICE_SEND* RecvlpMsg = (PMSG_NOTICE_SEND*)lpMsg;			
			if (RecvlpMsg->type == (0xD3 + 1))
			{
				DATA_NOTICEPK kill = { 0 };
				kill.Delay = 0;
				kill.Time = GetTickCount() + (RecvlpMsg->delay * 1000);
				kill.Color = RecvlpMsg->color;
				memcpy(kill.Mess, RecvlpMsg->message, sizeof(kill.Mess));

				if (gPKSys.m_DataNoticePK.size() >= 6)
				{
					gPKSys.m_DataNoticePK.erase(gPKSys.m_DataNoticePK.begin());
				}
				gPKSys.m_DataNoticePK.push_back(kill);
				return 1;
			}			
		}
		break;
		#endif
		case 0x11: GCDamageRecv((PMSG_DAMAGE_RECV*)lpMsg);									break;
		case 0x17: GCUserDieRecv((PMSG_USER_DIE_RECV*)lpMsg);								break;
		case 0x26: GCLifeRecv((PMSG_LIFE_RECV*)lpMsg);										break;
		case 0x27: GCManaRecv((PMSG_MANA_RECV*)lpMsg);										break;
		case 0x2C: GCFruitResultRecv((PMSG_FRUIT_RESULT_RECV*)lpMsg);						break;
		#if CHAOS_RATE_FIX
		case 0x8F:GCChaosMixRateRecv((PMSG_CHAOS_MIX_RATE_RECV*)lpMsg);						break;
		#endif
		case 0x9C:GCRewardExperienceRecv((PMSG_REWARD_EXPERIENCE_RECV*)lpMsg);				break;
		case 0x4E:
		switch (((lpMsg[0] == 0xC1) ? lpMsg[3] : lpMsg[4]))
		{
			case 0x07:
			{
				gInfoChar.GCInfoChar((PMSG_INFOCHARVIEW_RECV*)lpMsg);
				return 1;
			}
			#if(SLOTPET2)
			case 0x0A: g_pMyInventory.ReceiveInventory(lpMsg);									return 1;
			case 0x0B: g_pMyInventory.ReceiveDurability(lpMsg);									return 1;
			case 0x0C: g_pMyInventory.ReceiveDeleteInventory(lpMsg);							return 1;
			case 0x0F: g_pMyInventory.ReceiveItemChange((PMSG_NEWINV_ITEM_CHANGE_RECV*)lpMsg);	return 1;
			#endif
			#if(SOIITEM)
			case 0x01: g_pQuickCommandWindow.ReceiveInventory(lpMsg);				return 1;
			#endif
		}
		break;
		#if(SOIITEM)
		case 0x4F:
		switch (lpMsg[3])
		{
			case 0x01: g_pQuickCommandWindow.ReceivePeriodItemList(lpMsg);			break;
		}
		break;		
#endif
		case 0xA3: GCQuestRewardRecv((PMSG_QUEST_REWARD_RECV*)lpMsg);							break;
		case 0xA7:
		switch (((lpMsg[0] == 0xC1) ? lpMsg[3] : lpMsg[4]))
		{
			#if BXHDAME
			case 0x15: gDmgBoss.DAMEGETINFO((PMSG_NEW_HEALTH_BAR_RECV*) lpMsg);					break;
			case 0x16:
			XULY_CGPACKET* mRecv = (XULY_CGPACKET*)lpMsg;
			gInterface.Data[eTopDame].OnShow = true;
			break;
			#endif
		}
		break;
		#if(CUSTOM_GUILD_UPGRADE)
		case 0xA8:
		switch (((lpMsg[0] == 0xC1) ? lpMsg[3] : lpMsg[4]))
		{
			
			case 0x00:	GuildUpgrade.RecvMeInfo(lpMsg);				break;
			case 0x01:	GuildUpgrade.RecvGuildRankingInfo(lpMsg);	break;
			case 0x02:	GuildUpgrade.RecvMyGuildInfo(lpMsg);		break;
			case 0x03:	GuildUpgrade.RecvDevoteItemInfo(lpMsg);		break;
			case 0x04:	GuildUpgrade.RecvShopItemInfo(lpMsg);		break;
			case 0x05:	GuildUpgrade.RecvDevoteResult(lpMsg);		break;
			
		}
		break;
		#endif

		case 0xB1:
		switch(((lpMsg[0]==0xC1)?lpMsg[3]:lpMsg[4]))
		{
			case 0x00:
			gIconBuff.DeleteAllBuff();
			GCMapServerMoveRecv((PMSG_MAP_SERVER_MOVE_RECV*)lpMsg);
			#if(HT_THUE_FLAG)
			ThueFlag.Clear();
			#endif
			break;
			case 0x01:
			gIconBuff.DeleteAllBuff();
			GCMapServerMoveAuthRecv((PMSG_MAP_SERVER_MOVE_AUTH_RECV*)lpMsg);
			break;
		}
		break;
		case 0xF1:
		switch(((lpMsg[0]==0xC1)?lpMsg[3]:lpMsg[4]))
		{
			case 0x00:	GCConnectClientRecv((PMSG_CONNECT_CLIENT_RECV*)lpMsg);								break;
			case 0x01:	GCConnectAccountRecv((PMSG_CONNECT_ACCOUNT_RECV*)lpMsg);							break;
			case 0x02:	GCCloseClientRecv((PMSG_CLOSE_CLIENT_RECV*)lpMsg);									break;
			#if(REGISTER_INGAME)
			case 0x12:	g_pLoginMainWin.ReciveCreateAccount(((lpMsg[0] == 0xC1) ? lpMsg[4] : lpMsg[5]));	break;
			#endif
		}
		break;
		case 0xF3:
		switch(((lpMsg[0]==0xC1)?lpMsg[3]:lpMsg[4]))
		{
			case 0xF5: gCustomJewelBank.GCCustomJewelBankInfoRecv((PSBMSG_JEWELBANK_RECV*)lpMsg);			break;
			case 0x00:
				gIconBuff.DeleteAllBuff();
				GCCharacterListRecv((PMSG_CHARACTER_LIST_RECV*)lpMsg);
				gCSCharacterS13.JPlayerList((PMSG_CHARACTER_LIST_RECV*)lpMsg);
				return 1;
				break;
			case 0x01:	gCSCharacterS13.JPlayerAddList((PMSG_CHARACTER_CREATE_RECV*)lpMsg);						break;
			case 0x03:	GCCharacterInfoRecv((PMSG_CHARACTER_INFO_RECV*)lpMsg);									break;
			case 0x04:	GCCharacterRegenRecv((PMSG_CHARACTER_REGEN_RECV*)lpMsg);								break;
			case 0x05:	GCLevelUpRecv((PMSG_LEVEL_UP_RECV*)lpMsg);												break;
			case 0x06:	GCLevelUpPointRecv((PMSG_LEVEL_UP_POINT_RECV*)lpMsg);									break;
			case 0x07:	GCMonsterDamageRecv((PMSG_MONSTER_DAMAGE_RECV*)lpMsg);									break;
			case 0x50:	GCMasterInfoRecv((PMSG_MASTER_INFO_RECV*)lpMsg);										break;
			case 0x51:	GCMasterLevelUpRecv((PMSG_MASTER_LEVEL_UP_RECV*)lpMsg);									break;
			case 0xE0:	GCNewCharacterInfoRecv((PMSG_NEW_CHARACTER_INFO_RECV*)lpMsg);							return 1;
			case 0xE1:	GCNewCharacterCalcRecv((PMSG_NEW_CHARACTER_CALC_RECV*)lpMsg);							return 1;
			case 0xE2:	GCNewHealthBarRecv((PMSG_NEW_HEALTH_BAR_RECV*)lpMsg);									return 1;
			case 0xE3:	GCNewGensBattleInfoRecv((PMSG_NEW_GENS_BATTLE_INFO_RECV*)lpMsg);						return 1;
			case 0xE4:	GCNewMessageRecv((PMSG_NEW_MESSAGE_RECV*)lpMsg);										return 1;
			case 0xE5:	gCustomRankUser.GCReqRankLevelUser((PMSG_CUSTOM_RANKUSER*)lpMsg);						return 1;
			case 0xE8:	gCETime.GCReqEventTime((PMSG_CUSTOM_EVENTTIME_RECV*)lpMsg);					return 1;
			case 0xE9:	gItemPrice.GCItemValueRecv((PMSG_ITEM_VALUE_RECV*)lpMsg);								return 1;
			case 0xEA:	GCRecvCoin((PMSG_COIN_RECV*)lpMsg);														return 1;
			case 0xEB:	gOffTrade.RecvPShop((PMSG_OFFTRADE_RECV*)lpMsg);										return 1;
			case 0xEC:	gOffTrade.PShopActiveRecv((PMSG_SHOPACTIVE_RECV*)lpMsg);								return 1;
			case 0xED:	GCBuyConfirmRecv((PMSG_ITEM_BUY_RECV*)lpMsg);											break;
			case 0xEE:	SetChaosBoxState((PMSG_SET_CHAOSBOX_STATE*)lpMsg);										return 1;
			case 0xF1:	GCPetCharSetRecv((PMSG_NEW_PET_CHARSET_RECV*)lpMsg);									break;
			case 0xF2:	GCPetCharSetSelectCharacterRecv((PMSG_NEW_SELECT_CHARACTER_CHARSET_RECV*)lpMsg);		break;
			#if(PARTYSEARCH==1)
			case 0xF0: GCPartyListRecv((PMSG_RECV_PARTYLIST*)lpMsg);											return 1;
			case 0xF8: gPartySearchSettings.GCPartySettingsRecv((PMSG_PARTYSETTINGS_RECV*)lpMsg);				break;
            #endif
			#if(CTCMINI)
			case 0x32:	GCCTCMiniShowWindow((INFOCTCMINI_SENDCLIENT *)lpMsg);									break;
			case 0x33:	GCCTCMiniKill((CTCMINIKILL_SENDCLIENT *)lpMsg);											break;
			#endif
			case 0xF4: gCRenderEx700.RecvMasterSkill((PMSG_MASTER_SKILL_LIST_SEND *)lpMsg);						return 1;
			case 0x13: gIconBuff.GC_BuffInfo((PMSG_SEND_BUFF_ICON_EX*)lpMsg);									break;
			case 0xF9: gMiniMap.RecvPartyInfo((MINIMAP_PARTY_INFO_RECV*)lpMsg);									break;
			#if(BUNDLE_ITEM)
			case 0xF6: BundleItem.GCBundleItemConfigRecv(lpMsg);												break;
			#endif
			#if RELIFE
			case 107: G_TASRelife.TaiSinhCheckRecv((RelifeCheckUpdate*)lpMsg);			break;
			case 108: G_TASRelife.TaiSinhDiemRecv((RelifePointUpdate*)lpMsg);			break;
			case 109: G_TASRelife.SaveFormGs((RelifeCheckReqInfoPart1*)lpMsg);			break;
			#endif
			
		}
		break;

		case 0xD5:
		switch (((lpMsg[0] == 0xC1) ? lpMsg[3] : lpMsg[4]))
		{
			#if(TAS_HONHOAN)
			case 0x01: gHonHoan.SendHHProtocol(lpMsg);		break;
			#endif
			#if TAS_TUCHAN
			case 0x02:	gTuLuyen.SendTCProtocol(lpMsg);		break;	
			#endif
			#if TAS_DANHHIEU		
			case 0x03:	gDanhHieu.SendDHProtocol(lpMsg);	break;
			#endif
			#if(TAS_QUANHAM)
			case 0x04:	gQuanHam.SendQHProtocol(lpMsg);		break;
			#endif
			#if(TAS_NEWVIP)
			case 0x05:	gNewVip.SendNVProtocol(lpMsg);		break;
			#endif
			#if NEWXSHOP
			case 0x11: gNewCashShop.SendPacketToProtocol11(lpMsg); break;
			case 0x12: gNewCashShop.SendPacketToProtocol12(lpMsg); break;
			#endif
			case 0x2A:
			{
				XULY_CGPACKET* mRecv = (XULY_CGPACKET*)lpMsg;
				if (mRecv->ThaoTac != 111) return 0;
				if (GetTickCount() > gInterface.Data[eWindowHarmony].EventTick)
				{
					gInterface.Data[eWindowHarmony].EventTick = GetTickCount() + 300;
					gInterface.Data[eWindowHarmony].OnShow ^= 1;
				}
				gCustomHarmony.SetStateHarmony = true;
			}
			break;
			case 0x2B:
			{
				HARMONY_SENDCLIENT* mRecv = (HARMONY_SENDCLIENT*)lpMsg;
				gCustomHarmony.Harmony_ActiveMix = mRecv->ActiveMix;
				memcpy(gCustomHarmony.ItemChuaEp, mRecv->ItemChuaEp, sizeof(gCustomHarmony.ItemChuaEp));
				gCustomHarmony.Rate = mRecv->Rate;
				gCustomHarmony.Price = mRecv->Price;
				gCustomHarmony.PriceType = mRecv->PriceType;
				gCustomHarmony.CountHarmony = mRecv->CountHarmony;
				gCustomHarmony.IndexRandom = mRecv->IndexRandom;

			}
			break;

			case 0x25:
				gCustomHarmony.RecvHarmony((CHCSEV_COUNTLIST*)lpMsg);
				break;
		
		}
		break;

		#if (CongHuongV2)
		case 0xFA:
		switch (((lpMsg[0] == 0xC1) ? lpMsg[3] : lpMsg[4]))
		{				
			case 0x15: gCongHuong2.CH_RecvInfoGSSend((PMSG_GSSendInfoClient*)lpMsg);		break;	
			case 0x14:
			{
				XULY_CGPACKET* mRecv = (XULY_CGPACKET*)lpMsg;					
				if (!mRecv->ThaoTac) return 1;				
				if (GetTickCount() > gInterface.Data[eWindow_CongHuong].EventTick + 500)
				{
					gInterface.Data[eWindow_CongHuong].OnShow ^= 1;
					gInterface.Data[eWindow_CongHuong].EventTick = GetTickCount();
				}
			}
			break;			
		}
		break;
		#endif
		case 0xFB:
		switch (((lpMsg[0] == 0xC1) ? lpMsg[3] : lpMsg[4]))
		{
			#if ACTIVE_VKR
			case 0x00:	GCLASS_ITEM00.SendData((GS_ITEM00*)lpMsg);					break;
			case 0x06:	GCLASS_ITEM06.SendData((GS_ITEM06*)lpMsg);					break;
			case 0x07:	GCLASS_ITEM07.SendData((GS_ITEM07*)lpMsg);					break;
			case 0x08:	GCLASS_ITEM08.SendData((GS_ITEM08*)lpMsg);					break;
			case 0x09:	GCLASS_ITEM09.SendData((GS_ITEM09*)lpMsg);					break;
			case 0x0A:	GCLASS_ITEM10.SendData((GS_ITEM10*)lpMsg);					break;
			case 0x0B:	GCLASS_ITEM11.SendData((GS_ITEM11*)lpMsg);					break;
			case 0x0C:	GCLASS_ITEM12.SendData((GS_ITEM12*)lpMsg);					break;
			case 0x0D:	GCLASS_ITEM13.SendData((GS_ITEM13*)lpMsg);					break;
			#endif

			#if(HT_THUE_FLAG)
			case 0x1A: ThueFlag.RecvData(lpMsg);									break;
			#endif
			#if(VONGQUAY_NEW)
			case 0x31:	gLuckySpin.LuckySpinData((GC_LuckySpinUpdateData*)lpMsg);	break;
			case 0x32:	LuckySpinRoll();											break;
			case 0x33:	gLuckySpin.GCItemSend((GC_LuckySpin_Data*)lpMsg);			break;
			case 0x34:	gLuckySpin.GCLuckySpinInit((GC_LuckySpinInit*)lpMsg);		break;
			#endif
			#if(THANMA)
			case 0x61: gThanMa.SendProtocol61();break;
			case 0x62: gThanMa.SendProtocol62(lpMsg); break;
			case 0x63: gThanMa.SendProtocol63(lpMsg); break;
			break;
			#endif
			#if SO_LUONG_BOSS
			case 0x98: gActiveInvasions.list_recv(reinterpret_cast<PMSG_ACTIVE_INVASIONS_RECV*>(lpMsg));			break;
			case 0x99: gActiveInvasions.update_monster_recv((PMSG_INVASION_MONSTER_UPDATE_RECV*)lpMsg);			break;
			#endif
			#if ADD_POINT
			case 0x20:	gAddPoint.ExtraCpanelGetInfo((EXTRA_CPANEL_SENDINFO*)lpMsg);	break;
			#endif

		}
		break;
		case 0x78:	RecvPostItem((PMSG_POSTITEM*)lpMsg);								break;
		case 0x2D:	gIconBuff.Recv((PMSG_SEND_BUFF_ICON * )lpMsg);						break;
		case 0x2E:	gPartyBuffs.RecvPartyBuffs((PMSG_PARTY_EFFECT_LIST_SEND*)lpMsg);	break;

		

		case 0xD3:
		switch (((lpMsg[0] == 0xC1) ? lpMsg[3] : lpMsg[4]))
		{
			#if TAS_ITEMLOCK
			case 0x1A:	nInterface.RecvGSSatusLockWindow((CGPACKET_LOCKWINDOW*)lpMsg);	break;
			#endif
			#if(CUSTOM_DUNGLUYENITEM)
			case 0x25: gMixDL.NhanListItemDungLuyen((DLCSEV_COUNTLIST*)lpMsg);			break;
			case 0x2A: gMixDL.TruyenXuongProtocol2A(lpMsg);								break;
			case 0x2B: gMixDL.TruyenXuongProtocol2B(lpMsg);								break;
			#endif
			case 0x40:
			{
				gRanking.GCReqInfoCharTop((DATA_VIEWTOPRANKING*)lpMsg);
				return 1;
			}
			break;
			#if(B_MOCNAP)
			case 0x9A: 
			{
				mDataMocNapClient.Clear();
				PMSG_CBMONAP_SEND* mRecv = (PMSG_CBMONAP_SEND*)lpMsg;
				mDataMocNapClient.NhanMocNap = mRecv->NhanMocNap;
				mDataMocNapClient.TongNap = mRecv->TongNap;
				for (int i = 0; i < mRecv->count; i++)
				{
					ListMocNapSend lpInfo = *(ListMocNapSend*)(((BYTE*)lpMsg) + sizeof(PMSG_CBMONAP_SEND) + (sizeof(ListMocNapSend) * i));
					mDataMocNapClient.DanhSachMocNap.push_back(lpInfo);
				}
			}
			break;
			case 0x9B:
			{
				mDataListItemMocNapClient.Clear();
				PMSG_CBLISTTHUONG_SEND* mRecv = (PMSG_CBLISTTHUONG_SEND*)lpMsg;
				mDataListItemMocNapClient.WC = mRecv->WC;
				mDataListItemMocNapClient.WP = mRecv->WP;
				mDataListItemMocNapClient.GP = mRecv->GP;
				mDataListItemMocNapClient.Ruud = mRecv->Ruud;
				mDataListItemMocNapClient.CoinAtm = mRecv->CoinAtm;
				for (int i = 0; i < mRecv->count; i++)
				{
					LISTITEMMOCNAP_SENDINFO lpInfo = *(LISTITEMMOCNAP_SENDINFO*)(((BYTE*)lpMsg) + sizeof(PMSG_CBLISTTHUONG_SEND) + (sizeof(LISTITEMMOCNAP_SENDINFO) * i));
					INFO_LOCAL_ITEM infoItemLocal = { 0 };
					infoItemLocal.Count		= lpInfo.Count;
					infoItemLocal.SizeBMD	= lpInfo.SizeBMD;
					infoItemLocal.Index		= lpInfo.Index;
					infoItemLocal.GetTypeItem		= lpInfo.GetTypeItem;
					//g_Console.AddMessage(5, "Main: %d | GS: %d", infoItemLocal.GetTypeItem, lpInfo.GetTypeItem);
					infoItemLocal.Item		= *((ObjectItem * (__thiscall*)(int, BYTE*)) 0x007E1B10)(*(DWORD*)(((int(*)()) 0x861110)() + 36), lpInfo.Item);
					infoItemLocal.Item.Durability = lpInfo.Dur;
					if (lpInfo.PeriodTime)
					{
						infoItemLocal.Item.PeriodItem = 1;
						infoItemLocal.Item.ExpireDateConvert = lpInfo.PeriodTime;
					}
					mDataListItemMocNapClient.ListItemMocNap.push_back(infoItemLocal);
				}
			}
			break;
			#endif
			#if(CB_EventArenaPvP)
			case 0x1E: 
			{
				gCBArenaPvP.RecvPacketGS(lpMsg);
				return 1;
			}
			break;
			#endif
			#if LUC_CHIEN
			case 0x23:
			{
				DATA_LUCCHIEN* mRecv = (DATA_LUCCHIEN*)lpMsg;
				gObjUser.mLucChien = mRecv->LucChien;
			}
			break;
			#endif
			#if(SAU_ANTIHACK)
			case 0xAA: 
			{
				gBAntihack.RecvGSInfo((BGUARD_REQ_CHECK*) lpMsg);
			}
			break;
			case 0xAC: 
			{
				gBAntihack.RecvMouduleDataInfo((PMSG_MODULE_DATA_SEND*)lpMsg);
			}
			break;	
			#endif
			#if(TAS_ITEMTRADE)
			case 0x6A:	gItemTrade.SendToProtocol6A(lpMsg);		break;
			case 0x6B:  gItemTrade.SendToProtocol6B(lpMsg);		break;
			#endif
		}
		break;
		case 0x04:	gRanking.RecvInfo((DGCharTop*)lpMsg);								break;
		case 0x05:	gRanking.RecvInfoTP((DGCharTopTP*)lpMsg);							break;
		case 0x06:	gRanking.RecvInfoET((DGCharTopET*)lpMsg);							break;
		case 0x07:	gRanking.RecvInfoTG((DGCharTopTG*)lpMsg);							break;
		case 0x08:	gRanking.RecvInfoPK((DGCharTopPK*)lpMsg);							break;
		case 0x09:	gRanking.RecvInfoMT((DGCharTopMT*)lpMsg);							break;
	}
	return ProtocolCore(head,lpMsg,size,key);
}

void GCDamageRecv(PMSG_DAMAGE_RECV* lpMsg) // OK
{
	int aIndex = MAKE_NUMBERW(lpMsg->index[0],lpMsg->index[1]) & 0x7FFF;
	if(ViewIndex == aIndex)
	{
		ViewCurHP = lpMsg->ViewCurHP;
		ViewCurSD = lpMsg->ViewCurSD;
	}
	#if DAMAGE_RENDER_ENABLE
	ViewDamageTYPE = (lpMsg->type & 0xF);
	#endif
	ViewDamageHP = lpMsg->ViewDamageHP;
	ViewDamageSD = lpMsg->ViewDamageSD;

	if((lpMsg->type & 0x10) != 0)
	{
		if(ViewDamageCount < 3)
		{
			ViewDamageTable[ViewDamageCount++] = lpMsg->ViewDamageHP;
			ViewDamageValue = ViewDamageCount;
		}
	}

	if((lpMsg->type & 0x20) != 0)
	{
		if(ViewDamageCount < 4)
		{
			ViewDamageTable[ViewDamageCount++] = lpMsg->ViewDamageHP;
			ViewDamageValue = ViewDamageCount;
		}
	}
}

void GCMonsterDieRecv(PMSG_MONSTER_DIE_RECV* lpMsg) // OK
{
	ViewDamageHP = lpMsg->ViewDamageHP;
}

void GCUserDieRecv(PMSG_USER_DIE_RECV* lpMsg) // OK
{
	int aIndex = MAKE_NUMBERW(lpMsg->index[0],lpMsg->index[1]) & 0x7FFF;
	if(ViewIndex == aIndex)
	{
		ViewCurHP = 0;
	}
}

void GCLifeRecv(PMSG_LIFE_RECV* lpMsg) // OK
{
	if(lpMsg->type == 0xFE)
	{
		ViewMaxHP = lpMsg->ViewHP;
		ViewMaxSD = lpMsg->ViewSD;
	}
	if(lpMsg->type == 0xFF)
	{
		ViewCurHP = ((ViewCurHP==0)?ViewCurHP:lpMsg->ViewHP);
		ViewCurSD = lpMsg->ViewSD;
	}
}

void GCManaRecv(PMSG_MANA_RECV* lpMsg) // OK
{
	if(lpMsg->type == 0xFE)
	{
		ViewMaxMP = lpMsg->ViewMP;
		ViewMaxBP = lpMsg->ViewBP;
	}

	if(lpMsg->type == 0xFF)
	{
		ViewCurMP = lpMsg->ViewMP;
		ViewCurBP = lpMsg->ViewBP;
	}
}

void GCFruitResultRecv(PMSG_FRUIT_RESULT_RECV* lpMsg) // OK
{
	if(lpMsg->result == 0 || lpMsg->result == 3 || lpMsg->result == 6 || lpMsg->result == 17)
	{
		ViewValue = lpMsg->ViewValue;
		ViewPoint = lpMsg->ViewPoint;
		ViewStrength = lpMsg->ViewStrength;
		ViewDexterity = lpMsg->ViewDexterity;
		ViewVitality = lpMsg->ViewVitality;
		ViewEnergy = lpMsg->ViewEnergy;
		ViewLeadership = lpMsg->ViewLeadership;
	}
}

void GCRewardExperienceRecv(PMSG_REWARD_EXPERIENCE_RECV* lpMsg) // OK
{
	gObjUser.Refresh();
	ViewDamageHP = lpMsg->ViewDamageHP;
}

void GCQuestRewardRecv(PMSG_QUEST_REWARD_RECV* lpMsg) // OK
{
	int aIndex = MAKE_NUMBERW(lpMsg->index[0],lpMsg->index[1]) & 0x7FFF;
	if(ViewIndex == aIndex)
	{
		ViewPoint = lpMsg->ViewPoint;
	}
}

void GCMapServerMoveRecv(PMSG_MAP_SERVER_MOVE_RECV* lpMsg) // OK
{
	ReconnectOnMapServerMove(lpMsg->IpAddress,lpMsg->ServerPort);
}

void GCMapServerMoveAuthRecv(PMSG_MAP_SERVER_MOVE_AUTH_RECV* lpMsg) // OK
{
	ReconnectOnMapServerMoveAuth(lpMsg->result);
}

void GCConnectClientRecv(PMSG_CONNECT_CLIENT_RECV* lpMsg) // OK
{
	gHwid.SendHwid();
	ViewIndex = MAKE_NUMBERW(lpMsg->index[0],lpMsg->index[1]);
}

void GCConnectAccountRecv(PMSG_CONNECT_ACCOUNT_RECV* lpMsg) // OK
{
	ReconnectOnConnectAccount(lpMsg->result);
}

void GCCloseClientRecv(PMSG_CLOSE_CLIENT_RECV* lpMsg) // OK
{
	ReconnectOnCloseClient(lpMsg->result);
}

void GCCharacterListRecv(PMSG_CHARACTER_LIST_RECV* lpMsg) // OK
{
	ReconnectOnCharacterList();
}

void GCCharacterInfoRecv(PMSG_CHARACTER_INFO_RECV* lpMsg) // OK
{
	ReconnectOnCharacterInfo();
	ObjectDir = lpMsg->Dir;
	ViewReset = lpMsg->ViewReset;
	ViewPoint = lpMsg->ViewPoint;
	ViewCurHP = lpMsg->ViewCurHP;
	ViewMaxHP = lpMsg->ViewMaxHP;
	ViewCurMP = lpMsg->ViewCurMP;
	ViewMaxMP = lpMsg->ViewMaxMP;
	ViewCurBP = lpMsg->ViewCurBP;
	ViewMaxBP = lpMsg->ViewMaxBP;
	ViewCurSD = lpMsg->ViewCurSD;
	ViewMaxSD = lpMsg->ViewMaxSD;
	ViewStrength = lpMsg->ViewStrength;
	ViewDexterity = lpMsg->ViewDexterity;
	ViewVitality = lpMsg->ViewVitality;
	ViewEnergy = lpMsg->ViewEnergy;
	ViewLeadership = lpMsg->ViewLeadership;

	*(WORD*)(*(DWORD*)(MAIN_VIEWPORT_STRUCT)+0x07E) = 0;

	*(BYTE*)(*(DWORD*)(MAIN_VIEWPORT_STRUCT)+0x30C) = 0;

	switch(((*(BYTE*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x0B)) & 7))
	{
		case 0: SetByte(0x00556C38,((gProtect.m_MainInfo.DWMaxAttackSpeed>=0xFFFF)?0x03:0x0F));			break;
		case 1: SetByte(0x00556C38,((gProtect.m_MainInfo.DKMaxAttackSpeed>=0xFFFF)?0x04:0x0F));			break;
		case 2: SetByte(0x00556C38,((gProtect.m_MainInfo.FEMaxAttackSpeed>=0xFFFF)?0x03:0x0F));			break;
		case 3: SetByte(0x00556C38,((gProtect.m_MainInfo.MGMaxAttackSpeed>=0xFFFF)?0x03:0x0F));			break;
		case 4: SetByte(0x00556C38,((gProtect.m_MainInfo.DLMaxAttackSpeed>=0xFFFF)?0x03:0x0F));			break;
		case 5: SetByte(0x00556C38,((gProtect.m_MainInfo.SUMaxAttackSpeed>=0xFFFF)?0x03:0x0F)); 		break;
		case 6: SetByte(0x00556C38,((gProtect.m_MainInfo.RFMaxAttackSpeed>=0xFFFF)?0x0F:0x0F));			break;
	}

}

void GCCharacterRegenRecv(PMSG_CHARACTER_REGEN_RECV* lpMsg) // OK
{
	ViewCurHP = lpMsg->ViewCurHP;
	ViewCurMP = lpMsg->ViewCurMP;
	ViewCurBP = lpMsg->ViewCurBP;
	ViewCurSD = lpMsg->ViewCurSD;
}

void GCLevelUpRecv(PMSG_LEVEL_UP_RECV* lpMsg) // OK
{
	ViewPoint = lpMsg->ViewPoint;

	ViewMaxHP = lpMsg->ViewMaxHP;
	ViewMaxMP = lpMsg->ViewMaxMP;
	ViewMaxBP = lpMsg->ViewMaxBP;
	ViewMaxSD = lpMsg->ViewMaxSD;
	ViewExperience = lpMsg->ViewExperience;
	ViewNextExperience = lpMsg->ViewNextExperience;

	ViewCurMP = ViewMaxMP;
	ViewCurBP = ViewMaxBP;
	*(WORD *)(*(DWORD *)0x8128AC8 + 36) = *(WORD *)(*(DWORD *)0x8128AC8 + 40); //-- Mana
	*(WORD *)(*(DWORD *)0x8128AC8 + 64) = *(WORD *)(*(DWORD *)0x8128AC8 + 66); //-- BP
}

void GCLevelUpPointRecv(PMSG_LEVEL_UP_POINT_RECV* lpMsg) // OK
{
	if(lpMsg->result >= 16 && lpMsg->result <= 20)
	{
		ViewPoint = lpMsg->ViewPoint;
		ViewMaxHP = lpMsg->ViewMaxHP;
		ViewMaxMP = lpMsg->ViewMaxMP;
		ViewMaxBP = lpMsg->ViewMaxBP;
		ViewMaxSD = lpMsg->ViewMaxSD;
		ViewStrength = lpMsg->ViewStrength;
		ViewDexterity = lpMsg->ViewDexterity;
		ViewVitality = lpMsg->ViewVitality;
		ViewEnergy = lpMsg->ViewEnergy;
		ViewLeadership = lpMsg->ViewLeadership;
	}
}

void GCMonsterDamageRecv(PMSG_MONSTER_DAMAGE_RECV* lpMsg) // OK
{
	ViewCurHP = lpMsg->ViewCurHP;
	ViewCurSD = lpMsg->ViewCurSD;
	ViewDamageHP = lpMsg->ViewDamageHP;
	ViewDamageSD = lpMsg->ViewDamageSD;
}

void GCMasterInfoRecv(PMSG_MASTER_INFO_RECV* lpMsg) // OK
{
	ViewMaxHP = lpMsg->ViewMaxHP;
	ViewMaxMP = lpMsg->ViewMaxMP;
	ViewMaxBP = lpMsg->ViewMaxBP;
	ViewMaxSD = lpMsg->ViewMaxSD;
}

void GCMasterLevelUpRecv(PMSG_MASTER_LEVEL_UP_RECV* lpMsg) // OK
{
	ViewMaxHP = lpMsg->ViewMaxHP;
	ViewMaxMP = lpMsg->ViewMaxMP;
	ViewMaxBP = lpMsg->ViewMaxBP;
	ViewMaxSD = lpMsg->ViewMaxSD;
	ViewMasterExperience = lpMsg->ViewMasterExperience;
	ViewMasterNextExperience = lpMsg->ViewMasterNextExperience;
	ViewCurMP = ViewMaxMP;
	ViewCurBP = ViewMaxBP;

	*(WORD *)(*(DWORD *)0x8128AC8 + 64) = *(WORD *)(*(DWORD *)0x8128AC8 + 66);
}

void GCNewCharacterInfoRecv(PMSG_NEW_CHARACTER_INFO_RECV* lpMsg) // OK
{
	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x0E) = lpMsg->Level;
	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x74) = lpMsg->LevelUpPoint;
	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x18) = lpMsg->Strength;
	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x1A) = lpMsg->Dexterity;
	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x1C) = lpMsg->Vitality;
	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x1E) = lpMsg->Energy;
	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x20) = lpMsg->Leadership;
	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x22) = lpMsg->Life;
	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x26) = lpMsg->MaxLife;
	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x24) = lpMsg->Mana;
	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x28) = lpMsg->MaxMana;
	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x40) = lpMsg->BP;
	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x42) = lpMsg->MaxBP;
	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x2A) = lpMsg->Shield;
	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x2C) = lpMsg->MaxShield;
	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x4C) = lpMsg->FruitAddPoint;
	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x4E) = lpMsg->MaxFruitAddPoint;
	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x50) = lpMsg->FruitSubPoint;
	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x52) = lpMsg->MaxFruitSubPoint;
	*(DWORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x10) = lpMsg->Experience;
	*(DWORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x14) = lpMsg->NextExperience;

	ViewReset = lpMsg->ViewReset;
	ViewPoint = lpMsg->ViewPoint;
	ViewCurHP = lpMsg->ViewCurHP;
	ViewMaxHP = lpMsg->ViewMaxHP;
	ViewCurMP = lpMsg->ViewCurMP;
	ViewMaxMP = lpMsg->ViewMaxMP;
	ViewCurBP = lpMsg->ViewCurBP;
	ViewMaxBP = lpMsg->ViewMaxBP;
	ViewCurSD = lpMsg->ViewCurSD;
	ViewMaxSD = lpMsg->ViewMaxSD;
	ViewStrength = lpMsg->ViewStrength;
	ViewDexterity = lpMsg->ViewDexterity;
	ViewVitality = lpMsg->ViewVitality;
	ViewEnergy = lpMsg->ViewEnergy;
	ViewLeadership = lpMsg->ViewLeadership;
}

void GCNewCharacterCalcRecv(PMSG_NEW_CHARACTER_CALC_RECV* lpMsg) // OK
{
	ViewCurHP = lpMsg->ViewCurHP;
	ViewMaxHP = lpMsg->ViewMaxHP;
	ViewCurMP = lpMsg->ViewCurMP;
	ViewMaxMP = lpMsg->ViewMaxMP;
	ViewCurBP = lpMsg->ViewCurBP;
	ViewMaxBP = lpMsg->ViewMaxBP;
	ViewCurSD = lpMsg->ViewCurSD;
	ViewMaxSD = lpMsg->ViewMaxSD;
	ViewAddStrength = lpMsg->ViewAddStrength;
	ViewAddDexterity = lpMsg->ViewAddDexterity;
	ViewAddVitality = lpMsg->ViewAddVitality;
	ViewAddEnergy = lpMsg->ViewAddEnergy;
	ViewAddLeadership = lpMsg->ViewAddLeadership;
	ViewPhysiDamageMin = lpMsg->ViewPhysiDamageMin;
	ViewPhysiDamageMax = lpMsg->ViewPhysiDamageMax;
	ViewMagicDamageMin = lpMsg->ViewMagicDamageMin;
	ViewMagicDamageMax = lpMsg->ViewMagicDamageMax;
	ViewCurseDamageMin = lpMsg->ViewCurseDamageMin;
	ViewCurseDamageMax = lpMsg->ViewCurseDamageMax;
	ViewMulPhysiDamage = lpMsg->ViewMulPhysiDamage;
	ViewDivPhysiDamage = lpMsg->ViewDivPhysiDamage;
	ViewMulMagicDamage = lpMsg->ViewMulMagicDamage;
	ViewDivMagicDamage = lpMsg->ViewDivMagicDamage;
	ViewMulCurseDamage = lpMsg->ViewMulCurseDamage;
	ViewDivCurseDamage = lpMsg->ViewDivCurseDamage;
	ViewMagicDamageRate = lpMsg->ViewMagicDamageRate;
	ViewCurseDamageRate = lpMsg->ViewCurseDamageRate;
	ViewPhysiSpeed = lpMsg->ViewPhysiSpeed;
	ViewMagicSpeed = lpMsg->ViewMagicSpeed;
	ViewAttackSuccessRate = lpMsg->ViewAttackSuccessRate;
	ViewAttackSuccessRatePvP = lpMsg->ViewAttackSuccessRatePvP;
	ViewDefense = lpMsg->ViewDefense;
	ViewDefenseSuccessRate = lpMsg->ViewDefenseSuccessRate;
	ViewDefenseSuccessRatePvP = lpMsg->ViewDefenseSuccessRatePvP;
	ViewDamageMultiplier = lpMsg->ViewDamageMultiplier;
	ViewRFDamageMultiplierA = lpMsg->ViewRFDamageMultiplierA;
	ViewRFDamageMultiplierB = lpMsg->ViewRFDamageMultiplierB;
	ViewRFDamageMultiplierC = lpMsg->ViewRFDamageMultiplierC;
	ViewDarkSpiritAttackDamageMin = lpMsg->ViewDarkSpiritAttackDamageMin;
	ViewDarkSpiritAttackDamageMax = lpMsg->ViewDarkSpiritAttackDamageMax;
	ViewDarkSpiritAttackSpeed = lpMsg->ViewDarkSpiritAttackSpeed;
	ViewDarkSpiritAttackSuccessRate = lpMsg->ViewDarkSpiritAttackSuccessRate;
}

void GCNewHealthBarRecv(PMSG_NEW_HEALTH_BAR_RECV* lpMsg) // OK
{
	ClearNewHealthBar();

	for(int n=0;n < lpMsg->count;n++)
	{
		PMSG_NEW_HEALTH_RECV* lpInfo = (PMSG_NEW_HEALTH_RECV*)(((BYTE*)lpMsg)+sizeof(PMSG_NEW_HEALTH_BAR_RECV)+(sizeof(PMSG_NEW_HEALTH_RECV)*n));
		InsertNewHealthBar(lpInfo->index,lpInfo->type,lpInfo->rate,lpInfo->rate2, lpInfo->Level, lpInfo->Life, lpInfo->MonsID);
	}
}

void GCNewGensBattleInfoRecv(PMSG_NEW_GENS_BATTLE_INFO_RECV* lpMsg) // OK
{
	GensBattleMapCount = lpMsg->GensBattleMapCount;
	GensMoveIndexCount = lpMsg->GensMoveIndexCount;
	memcpy(GensBattleMap,lpMsg->GensBattleMap,sizeof(GensBattleMap));
	memcpy(GensMoveIndex,lpMsg->GensMoveIndex,sizeof(GensMoveIndex));
}

void GCNewMessageRecv(PMSG_NEW_MESSAGE_RECV* lpMsg) // OK
{
	PMSG_NEW_MESSAGE_RECV pMsg;
	pMsg.header.set(0xF3,0xE4,sizeof(pMsg));
	DataSend((BYTE*)&pMsg,sizeof(pMsg));
}

void OpenCashShopSend(BYTE type)
{
	PMSG_CASH_SHOP_OPEN_RECV pMsg;
	pMsg.OpenType = type;
	pMsg.header.set(0xD2,0x02,sizeof(pMsg));
	DataSend((BYTE*)&pMsg,sizeof(pMsg));
}



bool CashShopSwitchState()
{
	sub_861900_Addr((int)pWindowThis());

	if ( !sub_944E50_Addr() )
		return 0;
	void* v48 = sub_93F370_Addr();

	if ( sub_93FCA0_Addr((int)v48) == 1 )
	{
		if ( !sub_93F600_Addr((CHAR *)sub_93F370_Addr()) )
			return 0;
	}

	if ( sub_93FD10_Addr((int)sub_93F370_Addr()) == 1 )
	{
		if ( sub_93F950_Addr((CHAR *)sub_93F370_Addr()) == 1 )
		{
			BYTE* v53 = (BYTE *)sub_941030_Addr((BYTE*)sub_93F370_Addr());
			int v55 = sub_941000_Addr((BYTE*)sub_93F370_Addr());
			BYTE* v57 = (BYTE *)sub_861900_Addr((int)pWindowThis());
			sub_944FE0_Addr(v57, v55, v53);
		}
	}

	if ( pCheckWindow(pWindowThis(), 65) )
	{
		OpenCashShopSend(1);
		pCloseWindow(pWindowThis(), 65);
	}
	else
	{
		if ( !sub_9406C0_Addr((BYTE*)sub_93F370_Addr()) )
		{
			OpenCashShopSend(0);
			sub_9406A0_Addr((BYTE*)sub_93F370_Addr(), 1);
			char* v62 = (char *)sub_8611E0_Addr((DWORD*)pWindowThis());
			sub_815130_Addr(v62, 0, 1);
		}
	}
}


void DataSend(BYTE* lpMsg,DWORD size) // OK
{
	BYTE EncBuff[2048];

	if(gPacketManager.AddData(lpMsg,size) != 0 && gPacketManager.ExtractPacket(EncBuff) != 0)
	{
		BYTE send[2048];
		memcpy(send,EncBuff,size);
		if(EncBuff[0] == 0xC3 || EncBuff[0] == 0xC4)
		{
			if(EncBuff[0] == 0xC3)
			{
				BYTE save = EncBuff[1];
				EncBuff[1] = (*(BYTE*)(MAIN_PACKET_SERIAL))++;
				size = gPacketManager.Encrypt(&send[2],&EncBuff[1],(size-1))+2;
				EncBuff[1] = save;
				send[0] = 0xC3;
				send[1] = LOBYTE(size);
			}
			else
			{
				BYTE save = EncBuff[2];
				EncBuff[2] = (*(BYTE*)(MAIN_PACKET_SERIAL))++;
				size = gPacketManager.Encrypt(&send[3],&EncBuff[2],(size-2))+3;
				EncBuff[2] = save;
				send[0] = 0xC4;
				send[1] = HIBYTE(size);
				send[2] = LOBYTE(size);
			}
		}

		((void(__thiscall*)(void*,BYTE*,DWORD))0x00405110)((void*)0x08793750,send,size);
	}
}

void GCRecvCoin(PMSG_COIN_RECV* lpMsg) // OK
{
	Coin1 = lpMsg->Coin1;
	Coin2 = lpMsg->Coin2;
	Coin3 = lpMsg->Coin3;
	Ruud = lpMsg->Ruud;
	CoinAtm = lpMsg->CoinAtm;
}

void GCBuyConfirmRecv(PMSG_ITEM_BUY_RECV* lpMsg) // OK
{
	gInterface.Data[eCONFIRM_MAIN].OnShow = true;
	pSetCursorFocus = true;
	gInterface.ConfirmSlot = lpMsg->slot;
}
bool RecvPostItem(PMSG_POSTITEM * lpMsg) {

	void * item_post = PostItem::AddItem ( &lpMsg->item_data[0] );

	if ( item_post == nullptr ) { return false; }

	char Name[11] = { '\0' };
	char Messase[61] = { '\0' };
	char Messase_API[70] = { '\0' };
	memcpy_s ( &Name[0], 10, &lpMsg->chatid[0], 10 );
	memcpy_s ( &Messase[0], 60, &lpMsg->chatmsg[0], 60 );
	int len = strlen ( Messase );
	if ( ( BYTE ) Messase[0] == 0xC4 &&
			( BYTE ) Messase[1] == 0x90 &&
			( BYTE ) Messase[2] == 0xE1 &&
			( BYTE ) Messase[3] == 0xBB &&
			( BYTE ) Messase[4] == 0x93 &&
			( BYTE ) Messase[5] == 0x20 &&
			( BYTE ) Messase[6] == 0x68 &&
			( BYTE ) Messase[7] == 0x6F &&
			( BYTE ) Messase[8] == 0xC3 &&
			( BYTE ) Messase[9] == 0xA0 &&
			( BYTE ) Messase[10] == 0x6E &&
			( BYTE ) Messase[11] == 0x20 &&
			( BYTE ) Messase[12] == 0x68 &&
			( BYTE ) Messase[13] == 0xE1 &&
			( BYTE ) Messase[14] == 0xBA &&
			( BYTE ) Messase[15] == 0xA3 &&
			( BYTE ) Messase[16] == 0x6F &&
			( BYTE ) Messase[17] == 0x20 ) {
		strcpy_s ( &Messase[0], 61, &Messase[18] );
	}
	if ( len > 25 ) 
	{
		for ( int i = 20; i < len; ++i ) 
		{
			if ( isalpha ( Messase[i] ) || Messase[i] == ' ' ) 
			{
				Messase[i] = '.';
				Messase[i + 1] = '.';
				Messase[i + 2] = '.';
				Messase[i + 3] = '\0';
			}
		}
	}
	for (int i = 0; i < 19; i++)
	{
		gPostItem.eItemNode[i] = gPostItem.eItemNode[i + 1];
	}
	gPostItem.eItemNode[19] = (DWORD)item_post;
	sprintf_s( Messase_API, "Sell %s_[%08X]", Messase, (DWORD)item_post);
	gPostItem.draw_character_head_chat_text_ = true;
	newInterface::DrawChat ( gPostItem.PostItemColor, &Name[0], &Messase_API[0] );
	// ----
	if ( !gPostItem.draw_character_head_chat_text_ ) 
	{
		char message[256] = { 0 };
		char * chat_text_first = CharacterHeadChatTextFirst ( gPostItem.draw_character_head_chat_text_base_address_ );
		char * chat_text_last = CharacterHeadChatTextLast ( gPostItem.draw_character_head_chat_text_base_address_ );
		unsigned long msgfirst_len = strlen ( chat_text_first );
		unsigned long msglast_len = strlen ( chat_text_last );
		strcpy_s ( message, sizeof ( message ), chat_text_first );
		strcat_s ( message, chat_text_last );
		unsigned long message_len = strlen ( message );

		if ( message[message_len - 1 - 8 - 2] != '_' ||
				message[message_len - 1 - 8 - 1] != '[' ||
				message[message_len - 1] != ']' ) 
		{
		}
		else 
		{
			message[message_len - 1 - 8 - 2] = '\0';

			if ( msgfirst_len ) 
			{
				memcpy_s ( chat_text_first, 0x50, message, msgfirst_len );
				chat_text_first[msgfirst_len] = '\0';
			}

			if ( msglast_len ) 
			{
				memcpy_s ( chat_text_last, 0x50, &message[msgfirst_len], msglast_len );
				chat_text_last[msglast_len] = '\0';
			}
		}
	}
	return true;
}

void GCPetCharSetRecv(PMSG_NEW_PET_CHARSET_RECV* lpMsg)
{
	ClearNewPetCharSet();

	for (int n = 0; n < lpMsg->count; n++)
	{
		NEW_PET_STRUCT* lpInfo = (NEW_PET_STRUCT*)(((BYTE*)lpMsg) + sizeof(PMSG_NEW_PET_CHARSET_RECV)+(sizeof(NEW_PET_STRUCT)*n));
		InsertNewPetCharSet(lpInfo->index, lpInfo->PetCharSet);
	}
}

void GCPetCharSetSelectCharacterRecv(PMSG_NEW_SELECT_CHARACTER_CHARSET_RECV* lpMsg)
{
	ClearNewPetCharSetSelectCharacter();

	for (int n = 0; n < lpMsg->count; n++)
	{
		PMSG_NEW_CHARACTER_CHARSET_RECV* lpInfo = (PMSG_NEW_CHARACTER_CHARSET_RECV*)(((BYTE*)lpMsg) + sizeof(PMSG_NEW_SELECT_CHARACTER_CHARSET_RECV)+(sizeof(PMSG_NEW_CHARACTER_CHARSET_RECV)*n));
		InsertNewPetCharSetSelectCharacter(lpInfo->Name, lpInfo->PetCharSet);
	}
}

void SetChaosBoxState(PMSG_SET_CHAOSBOX_STATE* Data){
	pChaosBoxState = Data->state;
	return;
}


#if(PARTYSEARCH==1)
void GCPartyListRecv(PMSG_RECV_PARTYLIST* lpMsg){
	gPartySearch.ClearPartyList();
	for (int n = 0; n<lpMsg->Count; n++){
		PMSG_PARTYSEARCH_PARTYLIST* lpInfo = (PMSG_PARTYSEARCH_PARTYLIST*)(((BYTE*)lpMsg) + sizeof(PMSG_RECV_PARTYLIST)+(sizeof(PMSG_PARTYSEARCH_PARTYLIST)*n));
		gPartySearch.InsertPartyList(lpInfo);
	}
	gPartySearch.SwitchPartySearchWindowState();
}
#endif
#if(VONGQUAY_NEW)
void LuckySpinRoll()
{
	gLuckySpin.StartRoll = 1;
}
#endif


#if(CTCMINI)
void GCCTCMiniShowWindow(INFOCTCMINI_SENDCLIENT* lpMsg) // OK
{
	if ((GetTickCount() - gInterface.Data[eCTCMiniWindow].EventTick) > 300)
	{
		gInterface.Data[eCTCMiniWindow].EventTick = GetTickCount();
		gInterface.Data[eCTCMiniWindow].OnShow ^= 1;
	}
	CheckVaoLanhDia = lpMsg->GuildWinOld;
}
void GCCTCMiniKill(CTCMINIKILL_SENDCLIENT* lpMsg) // OK
{
	CTCMINI_TimeCTCMini = lpMsg->TimeCTCMini;
	for (int n = 0; n < 3; n++) //Them Cong
	{
		CTCMINI_Cong[n] = lpMsg->Cong[n];
		CTCMINI_Tru[n] = lpMsg->Tru[n];
	}
}
#endif

