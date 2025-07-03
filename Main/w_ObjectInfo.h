// w_ObjectInfo.h: interface for the ObjectInfo class.
//////////////////////////////////////////////////////////////////////
#pragma once

#include <vector>
#include <Windows.h>
#include "ZzzMathLib.h"

class	CInterpolateContainer
{
	public:
	struct INTERPOLATE_FACTOR
	{
		float	fRateStart;
		float	fRateEnd;

		vec3_t	v3Start;
		vec3_t	v3End;
		INTERPOLATE_FACTOR(float fRateStart_, float fRateEnd_,
			vec3_t& v3Start_, vec3_t& v3End_)
		{
			fRateStart = fRateStart_;
			fRateEnd = fRateEnd_;

			VectorCopy(v3Start_, v3Start);
			VectorCopy(v3End_, v3End);
		};

		INTERPOLATE_FACTOR()
		{

		};
	};

	struct INTERPOLATE_FACTOR_F
	{
		float	fRateStart;
		float	fRateEnd;

		float	fStart;
		float	fEnd;
		INTERPOLATE_FACTOR_F(float fRateStart_, float fRateEnd_,
			float& fStart_, float& fEnd_)
		{
			fRateStart = fRateStart_;
			fRateEnd = fRateEnd_;

			fStart = fStart_;
			fEnd = fEnd_;
		};

		INTERPOLATE_FACTOR_F()
		{

		};
	};
	typedef std::vector<INTERPOLATE_FACTOR>		VEC_INTERPOLATES;
	typedef std::vector<INTERPOLATE_FACTOR_F>	VEC_INTERPOLATES_F;
	VEC_INTERPOLATES						m_vecInterpolatesAngle;
	VEC_INTERPOLATES						m_vecInterpolatesPos;
	VEC_INTERPOLATES_F						m_vecInterpolatesScale;
	VEC_INTERPOLATES_F						m_vecInterpolatesAlpha;

	CInterpolateContainer(){};
	~CInterpolateContainer(){};
};

typedef struct tagMU_POINTF
{
	float x;
	float y;
} MU_POINTF;

typedef struct tagSIZEF
{
	float cx;
	float cy;
} SIZEF;

class OBJECT
{
	public:
	bool          Live;
	bool          bBillBoard;
	bool          m_bCollisionCheck;
	bool          m_bRenderShadow;
	bool          EnableShadow;
	bool		  LightEnable;
	bool		  m_bActionStart;
	bool		  m_bRenderAfterCharacter;
	bool	      Visible;
	bool	      AlphaEnable;
	bool          EnableBoneMatrix;
	bool		  ContrastEnable;
	bool          ChromeEnable;

	unsigned char AI;
	unsigned char CurrentAction;
	unsigned char PriorAction;

	BYTE          ExtState;
	BYTE          Teleport;
	BYTE          Kind;
	WORD		Skill;
	BYTE		  m_byNumCloth;
	BYTE		  m_byHurtByOneToOne;
	BYTE          WeaponLevel;
	BYTE          DamageTime;
	BYTE          m_byBuildTime;
	BYTE		  m_bySkillCount;
	BYTE		m_bySkillSerialNum;
	BYTE		  Block;
	void*		  m_pCloth;

	short         ScreenX;
	short         ScreenY;
	short         PKKey;
	short         Weapon;

	int			  Type;
	int           SubType;
	int			  m_iAnimation;
	int           HiddenMesh;
	int           LifeTime;
	int           BlendMesh;
	int           AttackPoint[2];
	int           RenderType;
	int			  InitialSceneFrame;
	int           LinkBone;

	DWORD			m_dwTime;

	float         Scale;
	float         BlendMeshLight;
	float         BlendMeshTexCoordU;
	float         BlendMeshTexCoordV;
	float         Timer;
	float         m_fEdgeScale;
	float         Velocity;
	float		  CollisionRange;
	float         ShadowScale;
	float         Gravity;
	float         Distance;
	float         AnimationFrame;
	float         PriorAnimationFrame;
	float	      AlphaTarget;
	float         Alpha;
	vec3_t        Light;
	vec3_t        Direction;
	vec3_t		  m_vPosSword;
	vec3_t		  StartPosition;
	vec3_t        BoundingBoxMin;
	vec3_t        BoundingBoxMax;
	vec3_t		  m_vDownAngle;
	vec3_t		  m_vDeadPosition;
	vec3_t        Position;
	vec3_t	 	  Angle;
	vec3_t	 	  HeadAngle;
	vec3_t	   	  HeadTargetAngle;
	vec3_t  	  EyeLeft;
	vec3_t  	  EyeRight;
	vec3_t		  EyeLeft2;
	vec3_t		  EyeRight2;
	vec3_t		  EyeLeft3;
	vec3_t		  EyeRight3;
	vec34_t	 	  Matrix;
	vec34_t       *BoneTransform;
	OBB_t		  OBB;
	OBJECT        *Owner;
	OBJECT		  *Prior;
	OBJECT		  *Next;
	short int		m_sTargetIndex;
	BOOL		m_bpcroom;
	vec3_t		m_v3PrePos1;
	vec3_t		m_v3PrePos2;
	CInterpolateContainer	m_Interpolates;
};

