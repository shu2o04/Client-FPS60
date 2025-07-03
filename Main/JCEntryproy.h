#pragma once

struct JCRECT
{
	float x;
	float y;
	float w;
	float h;
};


enum ActionList
{
	JCDINAMIC_EFFECT	= 1,
	JCSTATIC_EFFECT		= 2,
	JCSKILL_EFFECT		= 3,
	JCITEMGLOW_EFFECT	= 4,
	JCOBJECTSHADOW		= 5,
	JCOBJECTWORLDHIDE	= 6,
	JTWINGSOBJECT		= 7,
	JTWEAPONOBJECT		= 8,
	JTCLOACKOBJECT		= 9,
	JCHIDEPLAYER		= 10,
	NONE				= 11,
	DEFAULT				= 12,
};