#pragma once

#include "f4se/GameTypes.h"
#include "f4se/NiTypes.h"

class NiRTTI;
class NiExtraData;
class NiNode;
class NiSwitchNode;
class TESObjectREFR;
class NiGeometry;
class BSGeometry;
class BSTriShape;
class BSDynamicTriShape;
class BSSubIndexTriShape;

// 10
class NiRefObject
{
public:
	NiRefObject() : m_uiRefCount(0) { };
	virtual ~NiRefObject() { };

	virtual void	DeleteThis(void) { delete this; };	// calls virtual dtor

	void	IncRef(void);
	void	DecRef(void);
	bool	Release(void);

//	void	** _vtbl;		// 00
	volatile SInt32	m_uiRefCount;	// 08
};

// 10
class NiObject : public NiRefObject
{
public:
	virtual NiRTTI				* GetRTTI(void) { return nullptr; };
	virtual NiNode				* GetAsNiNode(void) { return nullptr; };
	virtual NiSwitchNode		* GetAsNiSwitchNode(void) { return nullptr; };
	virtual void				* Unk_05() { return nullptr; };
	virtual void				* Unk_06() { return nullptr; };
	virtual void				* Unk_07() { return nullptr; };
	virtual BSGeometry			* GetAsBSGeometry(void) { return nullptr; };
	virtual void				* GetAsBStriStrips() { return nullptr; };
	virtual BSTriShape			* GetAsBSTriShape(void) { return nullptr; };
	virtual BSDynamicTriShape	* GetAsBSDynamicTriShape(void) { return nullptr; };
	virtual void				* GetAsSegmentedTriShape() { return nullptr; };
	virtual BSSubIndexTriShape	* GetAsBSSubIndexTriShape(void) { return nullptr; };
	virtual void				* GetAsNiGeometry() { return nullptr; };
	virtual void				* GetAsNiTriBasedGeom() { return nullptr; };
	virtual void				* GetAsNiTriShape() { return nullptr; };
	virtual void				* GetAsParticlesGeom() { return nullptr; };
	virtual void				* GetAsParticleSystem() { return nullptr; };
	virtual void				* GetAsLinesGeom() { return nullptr; };
	virtual void				* GetAsLight() { return nullptr; };
	virtual void				* GetAsBhkNiCollisionObject() { return nullptr; };
	virtual void				* GetAsBhkBlendCollisionObject() { return nullptr; };
	virtual void				* GetAsBhkRigidBody() { return nullptr; };
	virtual void				* GetAsBhkLimitedHingeConstraint() { return nullptr; };
	virtual void				* GetAsbhkNPCollisionObject() { return nullptr; };
	virtual NiObject			* CreateClone(void * unk1) { return nullptr; };
	virtual void				LoadBinary(void * stream) { }; // LoadBinary
	virtual void				Unk_1C() { };
	virtual bool				Unk_1D() { return false; };
	virtual void				SaveBinary(void * stream) { }; // SaveBinary
	virtual bool				IsEqual(NiObject * object) { return false; }	// IsEqual
	virtual bool				Unk_20(void * unk1) { return false; };
	virtual void				Unk_21() { };
	virtual bool				Unk_22() { return false; };
	virtual NiRTTI				* GetStreamableRTTI() { return GetRTTI(); };
	virtual bool				Unk_24() { return false; };
	virtual bool				Unk_25() { return false; };
	virtual void				Unk_26() { };
	virtual bool				Unk_27() { return false; };
};

// 28
class NiObjectNET : public NiObject
{
public:
	BSFixedString					m_name;			// 10
	void							* unk10;		// 18 - Controller?
	tMutexArray<NiExtraData*>		* m_extraData;	// 20 - must be locked/unlocked when altering/acquiring

	bool AddExtraData(NiExtraData * extraData);
	NiExtraData * GetExtraData(const BSFixedString & name);
	bool HasExtraData(const BSFixedString & name) { return GetExtraData(name) != nullptr; }

	MEMBER_FN_PREFIX(NiObjectNET);
	DEFINE_MEMBER_FN(Internal_AddExtraData, bool, 0x01B6AE50, NiExtraData * extraData);
};

// 120
class NiAVObject : public NiObjectNET
{
public:

	struct NiUpdateData
	{
		float	fTime;				// 00
		UInt32	RenderUseDepth;		// 04
		UInt32	bParentsChecked;	// 08
		UInt32	unk0C;				// 0C
		void	* pCamera;			// 10
		UInt32	Flags;				// 18
		UInt32	RenderObjects;		// 1C
		UInt32	FadeNodeDepth;		// 20
	};

	virtual void UpdateControllers();
	virtual void PerformOp();
	virtual void AttachProperty();
	virtual void SetMaterialNeedsUpdate();
	virtual void SetDefaultMaterialNeedsUpdateFlag();
	virtual void SetAppCulled();
	virtual NiAVObject * GetObjectByName(const BSFixedString * nodeName);
	virtual void SetSelectiveUpdateFlags();
	virtual void UpdateDownwardPass();
	virtual void UpdateSelectedDownwardPass();
	virtual void UpdateRigidDownwardPass();
	virtual void UpdateWorldBound();
	virtual void UpdateWorldData(NiUpdateData * ctx);
	virtual void UpdateTransformAndBounds();
	virtual void UpdateTransforms();
	virtual void Unk_37();
	virtual void Unk_38();

	NiNode			* m_parent;			// 28
	NiTransform		m_localTransform;	// 30
	NiTransform		m_worldTransform;	// 70
	NiPoint3		unkB0;				// B0
	float			unkBC;				// BC
	NiTransform		unkC0;				// C0
	UInt64			unk100;				// 100

	enum : UInt64
	{
		kFlagAlwaysDraw = (1 << 11),
		kFlagIsMeshLOD = (1 << 12),
		kFlagFixedBound = (1 << 13),
		kFlagTopFadeNode = (1 << 14),
		kFlagIgnoreFade = (1 << 15),
		kFlagNoAnimSyncX = (1 << 16),
		kFlagNoAnimSyncY = (1 << 17),
		kFlagNoAnimSyncZ = (1 << 18),
		kFlagNoAnimSyncS = (1 << 19),
		kFlagNoDismember = (1 << 20),
		kFlagNoDismemberValidity = (1 << 21),
		kFlagRenderUse = (1 << 22),
		kFlagMaterialsApplied = (1 << 23),
		kFlagHighDetail = (1 << 24),
		kFlagForceUpdate = (1 << 25),
		kFlagPreProcessedNode = (1 << 26),
		kFlagScenegraphChange = (1 << 29),
		kFlagInInstanceGroup = (1LL << 35),
		kFlagLODFadingOut = (1LL << 36),
		kFlagFadedIn = (1LL << 37),
		kFlagForcedFadeOut = (1LL << 38),
		kFlagNotVisible = (1LL << 39),
		kFlagShadowCaster = (1LL << 40),
		kFlagNeedsRendererData = (1LL << 41),
		kFlagAccumulated = (1LL << 42),
		kFlagAlreadyTraversed = (1LL << 43),
		kFlagPickOff = (1LL << 44),
		kFlagHasPropController = (1LL << 46),
		kFlagHasLockedChildAccess = (1LL << 47),
		kFlagHasMovingSound = (1LL << 49),
	};

	UInt64			flags;				// 108
	TESObjectREFR	* m_reference;		// 110
	float			unk118;				// 118
	UInt32			unk11C;				// 11C

	MEMBER_FN_PREFIX(NiAVObject);
	DEFINE_MEMBER_FN(GetAVObjectByName, NiAVObject*, 0x01C73590, BSFixedString * name, bool unk1, bool unk2);
};
STATIC_ASSERT(offsetof(NiAVObject, m_reference) == 0x110);
STATIC_ASSERT(sizeof(NiAVObject) == 0x120);
