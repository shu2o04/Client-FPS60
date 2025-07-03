#pragma once
#include "JCEntryproy.h"

class JCButton
{
public:
	JCButton( );
	void SetText( char * Unknown );
	void SetBounds( JCRECT Bound );
	void SetBounds(float x, float y, float Width, float Height);
	void LoadAction( int Pointer, int Action );
	int SetVisible( );
	void SetSize(float Width, float Height);
	void SetLocation(float x, float y);
	void SetLocationX(float x);
	void SetLocationY(float y);
	char * GetText( );
	JCRECT GetBounds( );
	void mouseClicked( );
	void mouseEntered( );
	void ActionListener( );
	private:
	char JCtext[32];
	float JCRenderX;
	float JCRenderY;
	float JCWidth;
	float JCHeight;
	int JCActive;
	int JCAction;
	int JCTimerEvent;
};