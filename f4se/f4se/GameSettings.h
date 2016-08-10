#pragma once

#include "f4se_common/Utilities.h"

// 18
class Setting
{
public:
	virtual ~Setting();

	enum
	{
		kType_Unknown = 0,
		kType_Integer,
		kType_Float,
		kType_String,
		kType_Bool,
		kType_ID6,	// need to find an example of this
		kType_ID,
	};

	union Data
	{
		UInt32	u32;
		SInt32	s32;
		float	f32;
		UInt8	u8;		// used for bool
		char	* s;
	};

//	void	** _vtbl;	// 00
	Data	data;		// 08
	char	* name;		// 10

	UInt32	GetType(void) const;
};

// 118
class SettingCollection
{
public:
	virtual ~SettingCollection();

	virtual void Unk_01() = 0;
	virtual void Unk_02() = 0;
	virtual void Unk_03() = 0;
	virtual void Unk_04() = 0;
	virtual bool Unk_05();
	virtual bool Unk_06();
	virtual bool Unk_07();
	virtual bool Unk_08();	// return unk110 != 0;
	virtual bool Unk_09();	// return unk110 != 0;

//	void	** _vtbl;		// 000
	char	unk004[260];	// 008
	UInt32	pad10C;			// 10C
	void	* unk110;		// 110
};

// 128
class SettingCollectionList : public SettingCollection
{
public:
	virtual ~SettingCollectionList();

	// this is almost certainly a templated linked list type
	struct Node
	{
		Setting	* data;
		Node	* next;
	};

	void	* unk118;	// 118
	Node	* data;		// 120
};

// 128
class INISettingCollection : public SettingCollectionList
{
public:
	virtual ~INISettingCollection();
};

// 128
class INIPrefSettingCollection : public INISettingCollection
{
public:
	virtual ~INIPrefSettingCollection();
};

// 128
class RegSettingCollection : public SettingCollectionList
{
public:
	virtual ~RegSettingCollection();
};

extern RelocPtr <INISettingCollection *> g_iniSettings;
extern RelocPtr <INIPrefSettingCollection *> g_iniPrefSettings;
extern RelocPtr <RegSettingCollection*> g_regSettings;
