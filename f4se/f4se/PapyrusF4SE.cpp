#include "f4se/PapyrusF4SE.h"

#include "f4se/PapyrusVM.h"
#include "f4se/PapyrusNativeFunctions.h"

#include "f4se_common/f4se_version.h"
#include "f4se/PluginManager.h"

extern PluginManager	g_pluginManager;

namespace papyrusF4SE {

	UInt32 GetVersion(StaticFunctionTag* base)
	{
		return F4SE_VERSION_INTEGER;
	}
	UInt32 GetVersionMinor(StaticFunctionTag* base)
	{
		return F4SE_VERSION_INTEGER_MINOR;
	}

	UInt32 GetVersionBeta(StaticFunctionTag* base)
	{
		return F4SE_VERSION_INTEGER_BETA;
	}

	UInt32 GetVersionRelease(StaticFunctionTag* base)
	{
		return F4SE_VERSION_RELEASEIDX;
	}

	UInt32 GetPluginVersion(StaticFunctionTag* base, BSFixedString name)
	{
		PluginInfo * info = g_pluginManager.GetInfoByName(name);
		if(info) {
			return info->version;
		}

		return -1;
	}
}

void papyrusF4SE::RegisterFuncs(VirtualMachine* vm)
{
	vm->RegisterFunction(
		new NativeFunction0<StaticFunctionTag, UInt32>("GetVersion", "F4SE", papyrusF4SE::GetVersion, vm));

	vm->RegisterFunction(
		new NativeFunction0<StaticFunctionTag, UInt32>("GetVersionMinor", "F4SE", papyrusF4SE::GetVersionMinor, vm));

	vm->RegisterFunction(
		new NativeFunction0<StaticFunctionTag, UInt32>("GetVersionBeta", "F4SE", papyrusF4SE::GetVersionBeta, vm));

	vm->RegisterFunction(
		new NativeFunction0<StaticFunctionTag, UInt32>("GetVersionRelease", "F4SE", papyrusF4SE::GetVersionRelease, vm));

	vm->RegisterFunction(
		new NativeFunction1<StaticFunctionTag, UInt32, BSFixedString>("GetPluginVersion", "F4SE", papyrusF4SE::GetPluginVersion, vm));

	vm->SetFunctionFlags("F4SE", "GetVersion", IFunction::kFunctionFlag_NoWait);
	vm->SetFunctionFlags("F4SE", "GetVersionMinor", IFunction::kFunctionFlag_NoWait);
	vm->SetFunctionFlags("F4SE", "GetVersionBeta", IFunction::kFunctionFlag_NoWait);
	vm->SetFunctionFlags("F4SE", "GetVersionRelease", IFunction::kFunctionFlag_NoWait);
	vm->SetFunctionFlags("F4SE", "GetPluginVersion", IFunction::kFunctionFlag_NoWait);
}
