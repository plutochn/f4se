#include "f4se/ScaleformValue.h"

GFxValue::~GFxValue()
{
	CleanManaged();
}

void GFxValue::CleanManaged(void)
{
	if(IsManaged())
	{
		CALL_MEMBER_FN(objectInterface, ReleaseManaged_Internal)(this, data.obj);

		objectInterface = NULL;
		type = kType_Undefined;
	}
}

void GFxValue::SetUndefined(void)
{
	CleanManaged();

	type = kType_Undefined;
}

void GFxValue::SetNull(void)
{
	CleanManaged();

	type = kType_Null;
}

void GFxValue::SetBool(bool value)
{
	CleanManaged();

	type = kType_Bool;
	data.boolean = value;
}

void GFxValue::SetNumber(double value)
{
	CleanManaged();

	type = kType_Number;
	data.number = value;
}

void GFxValue::SetInt(SInt32 value)
{
	CleanManaged();

	type = kType_Int;
	data.s32 = value;
}
void GFxValue::SetUInt(UInt32 value)
{
	CleanManaged();

	type = kType_UInt;
	data.u32 = value;
}

void GFxValue::SetString(const char * value)
{
	CleanManaged();

	type = kType_String;
	data.string = value;
}

bool GFxValue::GetBool(void) const
{
	switch(GetType())
	{
		case kType_Bool:	return data.boolean;
		case kType_Number:	return data.number != 0;
		case kType_Int:		return data.s32 != 0;
		case kType_UInt:	return data.u32 != 0;
		default: HALT("GFxValue::GetBool: bad type"); return false;
	}
}

const char * GFxValue::GetString(void) const
{
	if(GetType() != kType_String)
		return NULL;

	if(IsManaged())
		return *data.managedString;
	else
		return data.string;
}

double GFxValue::GetNumber(void) const
{
	switch(GetType())
	{
		case kType_Int:		return (double)data.s32;
		case kType_UInt:	return (double)data.u32;
		case kType_Number:	return data.number;
		case kType_Bool:	return data.boolean ? 1 : 0;
		default:			HALT("GFxValue::GetNumber: bad type"); return 0;
	}
}

SInt32 GFxValue::GetInt(void) const
{
	switch(GetType())
	{
		case kType_Int:		return data.s32;
		case kType_UInt:	return (SInt32)data.u32;
		case kType_Number:	return (SInt32)data.number;
		case kType_Bool:	return data.boolean ? 1 : 0;
		default:			HALT("GFxValue::GetInt: bad type"); return 0;
	}
}

UInt32 GFxValue::GetUInt(void) const
{
	switch(GetType())
	{
		case kType_Int:		return (UInt32)data.s32;
		case kType_UInt:	return data.u32;
		case kType_Number:	return (UInt32)data.number;
		case kType_Bool:	return data.boolean ? 1 : 0;
		default:			HALT("GFxValue::GetUInt: bad type"); return 0;
	}
}

bool GFxValue::HasMember(const char * name)
{
	return CALL_MEMBER_FN(objectInterface, HasMember)(data.obj, name);
}

bool GFxValue::SetMember(const char * name, GFxValue * value)
{
	return CALL_MEMBER_FN(objectInterface, SetMember)(data.obj, name, value, IsDisplayObject());
}

bool GFxValue::GetMember(const char * name, GFxValue * value)
{
	return CALL_MEMBER_FN(objectInterface, GetMember)(data.obj, name, value, IsDisplayObject());
}

bool GFxValue::Invoke(const char * name, GFxValue * result, GFxValue * args, UInt32 numArgs)
{
	return CALL_MEMBER_FN(objectInterface, Invoke)(data.obj, result, name, args, numArgs, IsDisplayObject());
}

bool GFxValue::CreateEmptyMovieClip(GFxValue* pValue, const char* instanceName, SInt32 depth)
{
	return CALL_MEMBER_FN(objectInterface, CreateEmptyMovieClip)(data.obj, pValue, instanceName, depth);
}

bool GFxValue::AttachMovie(GFxValue* pValue, const char* symbolName, const char* instanceName, SInt32 depth, const void * initArgs)
{
	return CALL_MEMBER_FN(objectInterface, AttachMovie)(data.obj, pValue, symbolName, instanceName, depth, initArgs);
}

UInt32 GFxValue::GetArraySize()
{
	return CALL_MEMBER_FN(objectInterface, GetArraySize)(data.obj);
}

bool GFxValue::SetArraySize(UInt32 size)
{
	return CALL_MEMBER_FN(objectInterface, SetArraySize)(data.obj, size);
}

bool GFxValue::GetElement(UInt32 index, GFxValue * value)
{
	return CALL_MEMBER_FN(objectInterface, GetElement)(data.obj, index, value);
}

bool GFxValue::PushBack(GFxValue * value)
{
	return CALL_MEMBER_FN(objectInterface, PushBack)(data.obj, value);
}

bool GFxValue::PopBack(GFxValue * value)
{
	return CALL_MEMBER_FN(objectInterface, PopBack)(data.obj, value);
}

void GFxValue::VisitElements(ObjectInterface::ArrayVisitor * visitor, UInt32 idx, SInt32 count)
{
	CALL_MEMBER_FN(objectInterface, VisitElements)(data.obj, visitor, idx, count);
}

bool GFxValue::GetText(GFxValue * value, bool html)
{
	return CALL_MEMBER_FN(objectInterface, GetText)(data.obj, value, html);
}

bool GFxValue::SetText(const char * text, bool html)
{
	return CALL_MEMBER_FN(objectInterface, SetText)(data.obj, text, html);
}

void GFxValue::VisitMembers(ObjectInterface::ObjVisitor * visitor)
{
	CALL_MEMBER_FN(objectInterface, VisitMembers)(data.obj, visitor, IsDisplayObject());
}
