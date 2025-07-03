#include "StdAfx.h"
#if(REGISTER_INGAME)

#include "Util.h"
#include "UIControl.h"
#include "SEASON3B.h"
#include "RegisterForm.h"
#include "Protocol.h"
#include "Defines.h"
#include "CustomFont.h"
#include "AutoLoginWin.h"
#include "Import.h"
#include "Config.h"

CRegisterForm gCRegisterForm;

CRegisterForm::CRegisterForm(void)
{
	this->CWin = NULL;
	this->m_Pos.x = 0;
	this->m_Pos.y = 0;
	this->vk_timer2D = 0;
	this->CodeAction = -1;
	this->bShowRegister = false;
	//--
	this->sprInputBox = NULL;
	this->sprInputBoxPass = NULL;
	this->sprInputBoxEmail = NULL;
	this->sprInputBoxPersonal = NULL;
	this->sprInputBoxCaptcha = NULL;
}

CRegisterForm::~CRegisterForm(void)
{
	delete this->sprInputBox;
	delete this->sprInputBoxPass;
	delete this->sprInputBoxEmail;
	delete this->sprInputBoxCaptcha;
	delete this->sprInputBoxPersonal;
}

float getX1(float x) {
	return x / g_fScreenRate_x;
}
float getY1(float y) {

	float fixResu = ((float)pWinWidth) / (((float)pWinHeight) * (640.0f / 480.0f)); //fix custom res
	return y / g_fScreenRate_x * fixResu;
}

bool IsCursorInZone1(short x, short y, short x2, short y2) {
	return pCursorX >= x && pCursorX <= x + x2 && pCursorY >= y && pCursorY <= y + y2;
}

BYTE DrawCButton2(int IMGcode, float x, float y, float w, float h, float a6 = 64.0, float a7 = 128.0, int delay = 150, bool a9 = false) {
	if (IsCursorInZone1(x, y, getX1(w), getY1(h)))
	{
		if (GetKeyState(VK_LBUTTON) & 0x8000) {
			RenderBitmap(IMGcode, x, y, w, h, 0.0, h / a7 * 2.0, w / a6, h / a7, 0, 1, 0.0);
		}
		else
		{
			RenderBitmap(IMGcode, x, y, w, h, 0.0, h / a7, w / a6, h / a7, 0, 1, 0.0);
		}
		if (pIsKeyRelease(VK_LBUTTON))
		{
			return 2;
		}
		return 1;
	}
	else
	{
		RenderBitmap(IMGcode, x, y, w, h, 0.0, 0.0, w / a6, h / a7, 0, 1, 0.0);
	}
	return 0;
}

void CRegisterForm::GenerateCaptcha()
{
	BYTE ascii = NULL; int iLen = 0; int aux = 0;
	char Char = 0;
	srand(time(NULL));

	char newCaptcha[7] = { 0, };

	while (iLen < MaxCapChar)
	{
		ascii = 33 + rand() % (126 - 33);

		Char = (char)ascii;
		if ((Char >= '0' && Char <= '9'))// || (Char >= 'A' && Char <= 'Z') || (Char >= 'a' && Char <= 'z'))
		{
			newCaptcha[iLen] = Char;
			iLen++;
		}
	}

	for (int i = 0; i < 12; i++)
	{
		if ((i % 2) == 0)
		{
			this->reCaptcha2[i] = newCaptcha[aux];
			aux++;
		}
		else
		{
			this->reCaptcha2[i] = 32;
		}
	}

	ZeroMemory(this->reCaptcha, sizeof(this->reCaptcha));
	memcpy(this->reCaptcha, newCaptcha, 6);

}

bool CheckName(char* szID)
{
	if (FindText2(szID, " ", 0) || FindText2(szID, "¡¡", 0) ||
		FindText2(szID, ".", 0) || FindText2(szID, "¡¤", 0) ||
		FindText2(szID, "¡­", 0) || FindText2(szID, "Webzen", 0) ||
		FindText2(szID, "WebZen", 0) || FindText2(szID, "webzen", 0) ||
		FindText2(szID, "WEBZEN", 0) || FindText2(szID, GlobalText(GlobalLine, 457), 0) ||
		FindText2(szID, GlobalText(GlobalLine, 458), 0))
	{
		return true;
	}
	return false;
}

void CRegisterForm::Create(BYTE* thisa)
{
	this->CWin = thisa;
	sprInputBox = new CUITextInputBox;
	sprInputBoxPass = new CUITextInputBox;
	sprInputBoxEmail = new CUITextInputBox;
	sprInputBoxPersonal = new CUITextInputBox;
	sprInputBoxCaptcha = new CUITextInputBox;

	sprInputBox->Init(g_hWnd		, 60, 14, MAX_ID_SIZE);
	sprInputBoxPass->Init(g_hWnd	, 60, 14, MAX_ID_SIZE, TRUE);
	sprInputBoxEmail->Init(g_hWnd	, 60, 14, 50);
	sprInputBoxPersonal->Init(g_hWnd, 60, 14, 7);
	sprInputBoxCaptcha->Init(g_hWnd	, 60, 14, MaxCapChar);
	//--
	sprInputBox->SetBackColor(0, 0, 0, 255);
	sprInputBox->SetTextColor(255, 255, 230, 210);
	sprInputBox->SetFont(g_hFixFont);
	sprInputBox->SetState(UISTATE_NORMAL);
	//--
	sprInputBoxPass->SetBackColor(0, 0, 0, 25);
	sprInputBoxPass->SetTextColor(255, 255, 230, 210);
	sprInputBoxPass->SetFont(g_hFixFont);
	sprInputBoxPass->SetState(UISTATE_NORMAL);
	//--
	sprInputBoxEmail->SetBackColor(0, 0, 0, 255);
	sprInputBoxEmail->SetTextColor(255, 255, 230, 210);
	sprInputBoxEmail->SetFont(g_hFixFont);
	sprInputBoxEmail->SetState(UISTATE_NORMAL);
	//--
	sprInputBoxPersonal->SetBackColor(0, 0, 0, 25);
	sprInputBoxPersonal->SetTextColor(255, 255, 230, 210);
	sprInputBoxPersonal->SetFont(g_hFixFont);
	sprInputBoxPersonal->SetState(UISTATE_NORMAL);
	//--
	sprInputBoxCaptcha->SetBackColor(0, 0, 0, 255);
	sprInputBoxCaptcha->SetTextColor(255, 255, 230, 210);
	sprInputBoxCaptcha->SetFont(g_FontBold);
	sprInputBoxCaptcha->SetState(UISTATE_NORMAL);

	sprInputBox->SetTabTarget(sprInputBoxPass);
	sprInputBoxPass->SetTabTarget(sprInputBoxEmail);
	sprInputBoxEmail->SetTabTarget(sprInputBoxPersonal);
	sprInputBoxPersonal->SetTabTarget(sprInputBoxCaptcha);
	sprInputBoxCaptcha->SetTabTarget(sprInputBox);
}

void CRegisterForm::SetPosicion(int x, int y)
{
	this->m_Pos.x = x;
	this->m_Pos.y = y;
	sprInputBox->SetPosition		(x + 80	, y + 60);
	sprInputBoxPass->SetPosition	(x + 80	, y + 76);
	sprInputBoxEmail->SetPosition	(x + 80	, y + 88);
	sprInputBoxPersonal->SetPosition(x + 80	, y + 103);
	sprInputBoxCaptcha->SetPosition	(x + 118, y + 117);
}

void CRegisterForm::Show(bool bShow)
{
	if (bShow)
	{
		this->GenerateCaptcha();
	}
	this->bShowRegister = bShow;
}

bool CRegisterForm::CheckShow()
{
	return this->bShowRegister;
}

void CRegisterForm::GiveFocus(BYTE bIndex, BOOL bSel)
{
	switch (bIndex)
	{
	case 1:
		sprInputBox->GiveFocus(TRUE);
		break;
	case 2:
		sprInputBoxPass->GiveFocus(TRUE);
		break;
	case 3:
		sprInputBoxPersonal->GiveFocus(TRUE);
		break;
	case 4:
		sprInputBoxCaptcha->GiveFocus(TRUE);
		break;
	default:
		sprInputBox->GiveFocus(TRUE);
		break;
	}
}
void CRegisterForm::RenderForm()
{
	if (this->bShowRegister == false) { return; }

	glAlphaFunc(GL_GREATER, 0.0f);

	int x = this->m_Pos.x;
	int y = this->m_Pos.y;

	EnableAlphaTest(true);
	glColor4f(1.f, 1.f, 1.f, 1.f);

	CRenderBitmaps(71621, (float)x+20, (float)y+30, 150.f, 150.f, 0.0, 0.0, 190.f / 256.f, 250.f / 256.f, true, true, 0.0);
	g_pRenderText.SetBgColor(0);
	g_pRenderText.SetFont(g_FontBold);

	g_pRenderText.SetTextColor(CLRDW_YELLOW);
	char strTipText[255]; char szServerName[255];
	g_pRenderText.SetFont(g_hFixFont);
	g_pRenderText.SetTextColor(CLRDW_WHITE);
	g_pRenderText.RenderText(x + 25, y + 60, GlobalText(GlobalLine, 450),	40, 3, RT3_SORT_RIGHT);
	g_pRenderText.RenderText(x + 25, y + 74, GlobalText(GlobalLine, 451),	40, 3, RT3_SORT_RIGHT);
	g_pRenderText.RenderText(x + 25, y + 88, "E-mail",						40, 3, RT3_SORT_RIGHT);
	g_pRenderText.RenderText(x + 25, y + 103, "Mã Cá Nhân",					40, 3, RT3_SORT_RIGHT);
	g_pRenderText.RenderText(x + 25, y + 117, "Mã Capcha",					40, 3, RT3_SORT_RIGHT);
	g_pRenderText.SetFont(g_FontBold);
	g_pRenderText.RenderText(x + 79, y + 117, this->reCaptcha2);
	//--
	sprInputBox->Render();
	sprInputBoxPass->Render();
	sprInputBoxEmail->Render();
	sprInputBoxPersonal->Render();
	sprInputBoxCaptcha->Render();

	if (pCheckInMouse(x + 80, y + 55, 60, 14))
	{
		if (MouseLButton)
		{
			PlayBuffer(25, 0, 0);
			sprInputBox->GiveFocus(TRUE);
		}
	}
	if (pCheckInMouse(x + 80, y + 74, 60, 14))
	{
		if (MouseLButton)
		{
			PlayBuffer(25, 0, 0);
			sprInputBoxPass->GiveFocus(TRUE);
		}
	}
	if (pCheckInMouse(x + 80, y + 88, 60, 14))
	{
		if (MouseLButton)
		{
			PlayBuffer(25, 0, 0);
			sprInputBoxEmail->GiveFocus(TRUE);
		}
	}
	if (pCheckInMouse(x + 80, y + 103, 60, 14))
	{
		if (MouseLButton)
		{
			PlayBuffer(25, 0, 0);
			sprInputBoxPersonal->GiveFocus(TRUE);
		}
	}
	if (pCheckInMouse(x + 120, y + 117, 60, 14))
	{
		if (MouseLButton)
		{
			PlayBuffer(25, 0, 0);
			sprInputBoxCaptcha->GiveFocus(TRUE);
		}
	}

	RenderUI2DButton1(0x7A5B, (float)x + 60,	(float)y + 130, 64.0, 30.0, 13.0, 15.0, 16.0, 64.0, RequestRegister);
	RenderUI2DButton1(0x7A5C, (float)x + 100,	(float)y + 130, 64.0, 30.0, 13.0, 15.0, 16.0, 64.0, CloseFormRegister);

	EndRenderColor();
	glColor4f(1.f, 1.f, 1.f, 1.f);
	glAlphaFunc(GL_GREATER, 0.25f);
}

void CRegisterForm::RenderUI2DButton2(float x, float y, float w, float h, char* text, PUSHEVENT_CALLBACK_LPVOID pCallbackFunc)
{
	float cy = 0.0; int iLineHeight;

	iLineHeight = FontHeight / g_fScreenRate_y / 2;

	int dy = y + (h / 2) - iLineHeight;

	if (pCheckInMouse((int)x, (int)y, (int)w, (int)h))
	{
		if (MouseLButton)
		{
			if (GetTickCount() >= (vk_timer2D + 700))
			{
				PlayBuffer(25, 0, 0);
				this->vk_timer2D = GetTickCount();
				pCallbackFunc(this);
			}
		}
	}
	RenderImageD(0x7908, x, y, w, h, 0.0, cy);

	g_pRenderText.SetFont(g_hFixFont);
	g_pRenderText.SetTextColor(CLRDW_WHITE);
	g_pRenderText.RenderText(x, dy, text, w, 0, RT3_SORT_CENTER);
}

void CRegisterForm::RenderUI2DButton1(int IMGcode, float x, float y, float w, float h, float uw, float uh, float a8, float a9, PUSHEVENT_CALLBACK_LPVOID pCallbackFunc)
{
	if (IsCursorInZone1((int)x, (int)y, (int)w - 30, (int)h))
	{
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			RenderBitmap(IMGcode, x, y, w, h, 0.0, uh / a9 * 2.0, uw / a8, uh / a9, 0, 1, 0.0);
		}
		else
		{
			RenderBitmap(IMGcode, x, y, w, h, 0.0, uh / a9, uw / a8, uh / a9, 0, 1, 0.0);
		}
		if (pIsKeyRelease(VK_LBUTTON))
		{
			PlayBuffer(25, 0, 0);
			pCallbackFunc(this);
			return;
		}
		return;
	}
	else
	{
		RenderBitmap(IMGcode, x, y, w, h, 0.0, 0.0, uw / a8, uh / a9, 0, 1, 0.0);
	}
	return;
}

void CRegisterForm::RenderUI2DButton3(int IMGcode, float x, float y, float w, float h, float uw, float uh, float a8, float a9)
{
	if (IsCursorInZone1((int)x, (int)y, (int)w, (int)h))
	{
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			RenderBitmap(IMGcode, x, y, w, h, 0.0, uh / a9 * 2.0, uw / a8, uh / a9, 0, 1, 0.0);
		}
		else
		{
			RenderBitmap(IMGcode, x, y, w, h, 0.0, uh / a9, uw / a8, uh / a9, 0, 1, 0.0);
		}
	}
	else
	{
		RenderBitmap(IMGcode, x, y, w, h, 0.0, 0.0, uw / a8, uh / a9, 0, 1, 0.0);
	}
	return;
}

void CRegisterForm::CloseFormRegister(LPVOID pClass)
{
	CRegisterForm* szth = (CRegisterForm*)pClass;

	szth->Show(false);
	if (CurrentProtocolState == RECEIVE_JOIN_SERVER_SUCCESS)
	{
		CUIMngShowWin(CharMakeWin(), szth->CWin);
	}
}

void SendRequestRegister(char* p_lpszID, char* p_lpszPassword, char* p_lpszPCode, char* p_lpszEmail)
{
	PBMSG_REGISTER_ACCOUNT spe;
	BYTE version[SIZE_PROTOCOLVERSION];

	spe.Header.setE(0xF1, 0x12, sizeof(spe));
	PacketArgumentEncrypt(spe.lpszID, p_lpszID, 10);
	PacketArgumentEncrypt(spe.lpszPass, p_lpszPassword, 10);
	PacketArgumentEncrypt(spe.lpszPCode, p_lpszPCode, 10);
	PacketArgumentEncrypt(spe.lpszEmail, p_lpszEmail, sizeof(spe.lpszEmail));
	memcpy(version, (void*)0xE61F68, sizeof(version));
	spe.TickCount = GetTickCount();

	for (int i = 0; i < SIZE_PROTOCOLVERSION; i++)
	{
		spe.Version[i] = (version[i] - (i + 1));
	}
	memcpy(spe.Serial, (void*)0x00E61F70, sizeof(spe.Serial));

	DataSend((BYTE*)&spe, spe.Header.size);
}

bool CRegisterForm::IsForbiddenChar(char c)
{
    // Các ký tự cấm: !#$%^&*();':
    const char forbiddenChars[] = "!#$%^&*();':";
    for (int i = 0; i < strlen(forbiddenChars); i++)
    {
        if (c == forbiddenChars[i])
        {
            return true; // Ký tự cấm
        }
    }
    return false; // Ký tự không cấm
}
bool CRegisterForm::IsValidEmail(const char *email)
{
    // Kiểm tra độ dài
    if (strlen(email) <= 0 || strlen(email) >= 50)
    {
        return false;
    }
    for (int i = 0; i < strlen(email); i++)
    {
        if (!isalnum(email[i]) && email[i] != '@' && email[i] != '.' && !IsForbiddenChar(email[i]))
        {
            return false;
        }
    }

    // Kiểm tra sự hiện diện của '@' và '.'
    int atCount = 0;
    int dotCount = 0;
    for (int i = 0; i < strlen(email); i++)
    {
        if (email[i] == '@')
        {
            atCount++;
        }
        else if (email[i] == '.')
        {
            dotCount++;
        }
    }

    return (atCount == 1 && dotCount >= 1);
}
void CRegisterForm::RequestRegister(LPVOID pClass)
{
	if (CurrentProtocolState == REQUEST_JOIN_SERVER)
		return;

	char szID[MAX_ID_SIZE + 1] = { 0, };
	char szPass1[MAX_PASSWORD_SIZE + 1] = { 0, };
	char szPCode[MAX_PASSWORD_SIZE + 1] = { 0, };
	char szEmail[50 + 1] = { 0, };
	char szCaptcha[6 + 1] = { 0, };

	CRegisterForm* szth = (CRegisterForm*)pClass;

	szth->sprInputBox->GetText(szID, MAX_ID_SIZE + 1);
	szth->sprInputBoxPass->GetText(szPass1, MAX_PASSWORD_SIZE + 1);
	szth->sprInputBoxEmail->GetText(szEmail, sizeof(szEmail));
	szth->sprInputBoxPersonal->GetText(szPCode, MAX_PASSWORD_SIZE + 1);
	szth->sprInputBoxCaptcha->GetText(szCaptcha, 6 + 1);

	if (strlen(szID) <= 0)
	{
		szth->CodeAction = CREATE_ACCOUNT_FAIL_USERID;
		PopUpMsgWin(CharMakeWin(), MESSAGE_FREE_MSG_NOT_BTN, GlobalText(GlobalLine, 403));
	}
	else if (!isdigit(szID[0]))
	{
		szth->CodeAction = CREATE_ACCOUNT_FAIL_USERID;
		PopUpMsgWin(CharMakeWin(), MESSAGE_FREE_MSG_NOT_BTN, gConfig.TTAS_TEXT_ENGINE[175]);
	}
	else if (strlen(szID) < 4)
	{
		szth->CodeAction = CREATE_ACCOUNT_FAIL_USERID;
		PopUpMsgWin(CharMakeWin(), MESSAGE_FREE_MSG_NOT_BTN, GlobalText(GlobalLine, 390));
	}
	else if (strlen(szPass1) <= 0)
	{
		szth->CodeAction = CREATE_ACCOUNT_FAIL_PASSWORD;
		PopUpMsgWin(CharMakeWin(), MESSAGE_FREE_MSG_NOT_BTN, GlobalText(GlobalLine, 404));
	}
	else if (strlen(szPCode) <= 0)
	{
		szth->CodeAction = CREATE_ACCOUNT_FAIL_CAPTCHA;
		PopUpMsgWin(CharMakeWin(), MESSAGE_FREE_MSG_NOT_BTN, GlobalText(GlobalLine, 428));
	}
	if (strlen(szEmail) <= 0)
    {
        szth->CodeAction = CREATE_ACCOUNT_FAIL_CAPTCHA;
        PopUpMsgWin(CharMakeWin(), MESSAGE_FREE_MSG_NOT_BTN, GlobalText(GlobalLine, 1008));
    }
    else if (!gCRegisterForm.IsValidEmail(szEmail))
    {
        szth->CodeAction = CREATE_ACCOUNT_FAIL_CAPTCHA;
        PopUpMsgWin(CharMakeWin(), MESSAGE_FREE_MSG_NOT_BTN, gConfig.TTAS_TEXT_ENGINE[176]);
    }
	else if (strlen(szCaptcha) <= 0)
	{
		szth->CodeAction = CREATE_ACCOUNT_FAIL_CAPTCHA;
		PopUpMsgWin(CharMakeWin(), MESSAGE_FREE_MSG_NOT_BTN, gConfig.TTAS_TEXT_ENGINE[177]);
	}
	else if (strcmp(szth->reCaptcha, szCaptcha) != NULL)
	{
		szth->CodeAction = CREATE_ACCOUNT_FAIL_CAPTCHA;
		PopUpMsgWin(CharMakeWin(), MESSAGE_FREE_MSG_NOT_BTN, gConfig.TTAS_TEXT_ENGINE[178]);
	}
	else
	{
		bool coKyTuDacBiet = false;

		for (int i = 0; szID[i] != '\0'; ++i)
		{
			if (ispunct(szID[i])) 
			{
				coKyTuDacBiet = true;
				break;
			}
		}
		if (CheckName(szID) || coKyTuDacBiet == true)
		{
			PopUpMsgWin(CharMakeWin(), MESSAGE_FREE_MSG_NOT_BTN, GlobalText(GlobalLine, 1715));
		}
		else
		{
			if (CurrentProtocolState == RECEIVE_JOIN_SERVER_SUCCESS)
			{
				SendRequestRegister(szID, szPass1, szPCode, szEmail);
			}
		}
	}
}

void CRegisterForm::RequestAccount(BYTE code)
{
	this->Show(false);
	this->CodeAction = code;
	switch (code)
	{
		case CREATE_ACCOUNT_FAIL_ID:			PopUpMsgWin(CharMakeWin(), MESSAGE_FREE_MSG_NOT_BTN, gConfig.TTAS_TEXT_ENGINE[179]);			break;
		case CREATE_ACCOUNT_SUCCESS:			PopUpMsgWin(CharMakeWin(), MESSAGE_FREE_MSG_NOT_BTN, gConfig.TTAS_TEXT_ENGINE[180]);			break;
		case CREATE_ACCOUNT_FAIL_RESIDENT:		PopUpMsgWin(CharMakeWin(), MESSAGE_FREE_MSG_NOT_BTN, gConfig.TTAS_TEXT_ENGINE[181]);			break;
		default:								PopUpMsgWin(CharMakeWin(), MESSAGE_FREE_MSG_NOT_BTN, gConfig.TTAS_TEXT_ENGINE[182]);			break;
	}
}
#endif