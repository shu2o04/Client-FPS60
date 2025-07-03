#include "stdafx.h"
#if(SOIITEM)
#include "Protocol.h"
#include "TAS_SoiItem.h"
#include "Central.h"
#include "TAS_DanhHieu.h"
#include "Interface.h"
#include "Defines.h"

SEASON3B::QuickCommandWindow g_pQuickCommandWindow;

namespace SEASON3B
{
	void QuickCommandWindow::SendRequestViewItem(int pSelectedCha)
	{
		WORD p_Key = *(WORD *)(pSelectedCha + 126);

		PMSG_VIEW_REQUEST_SEND Send;
		Send.header.set(0x4F, 0x03, sizeof(Send));
		Send.index[0] = (BYTE)((p_Key) >> 8);
		Send.index[1] = (BYTE)((p_Key)& 0xff);
		DataSend((LPBYTE)&Send, Send.header.size);
	}

	BOOL QuickCommandWindow::ReceiveInventory(BYTE *ReceiveBuffer)
	{
		setStatusDetails(true);
		ResetEquipItem();
		
		LPHEADER_DEFAULT_SUBCODE_WORD DataRecv = (LPHEADER_DEFAULT_SUBCODE_WORD)ReceiveBuffer;
		int Offset = sizeof(HEADER_DEFAULT_SUBCODE_WORD);

		for (int i = 0; i<DataRecv->Value; i++)
		{
			LPRECEIVE_INVENTORY Data = (LPRECEIVE_INVENTORY)(ReceiveBuffer + Offset);
			SetEquipItem(Data->Index, Data->Item);
			Offset += sizeof(RECEIVE_INVENTORY);
		}
		return (TRUE);
	}

	bool QuickCommandWindow::ReceivePeriodItemList(BYTE* pReceiveBuffer)
	{
		LPPMSG_PERIODITEMEX_ITEMLIST Data = (LPPMSG_PERIODITEMEX_ITEMLIST)pReceiveBuffer;

		if (Data->wItemSlotIndex < 15)
		{
			SetPeriodItem(Data->wItemSlotIndex, (long)Data->lExpireDate);
		}

		return true;
	}

	void QuickCommandWindow::szInit()
	{
		Init(3400, SendRequestViewItem);
	}
}
#endif