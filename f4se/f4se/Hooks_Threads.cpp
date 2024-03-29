#include "f4se/Hooks_Threads.h"
#include "common/ICriticalSection.h"
#include "f4se/GameThreads.h"
#include "f4se_common/Relocation.h"
#include "f4se_common/BranchTrampoline.h"
#include "xbyak/xbyak.h"

#include <queue>

ICriticalSection		s_taskQueueLock;
std::queue<ITaskDelegate*>	s_tasks;

typedef bool (* _MessageQueueProcessTask)(void * messageQueue, float timeout, UInt32 unk1);
RelocAddr <_MessageQueueProcessTask> MessageQueueProcessTask(0x00D3A310);
_MessageQueueProcessTask MessageQueueProcessTask_Original = nullptr;

bool MessageQueueProcessTask_Hook(void * messageQueue, float timeout, UInt32 unk1)
{
	bool result = MessageQueueProcessTask_Original(messageQueue, timeout, unk1);

	s_taskQueueLock.Enter();
	while (!s_tasks.empty())
	{
		ITaskDelegate * cmd = s_tasks.front();
		s_tasks.pop();
		cmd->Run();
		delete cmd;
	}
	s_taskQueueLock.Leave();

	return result;
}

void TaskInterface::AddTask(ITaskDelegate * task)
{
	s_taskQueueLock.Enter();
	s_tasks.push(task);
	s_taskQueueLock.Leave();
}

void Hooks_Threads_Init(void)
{
	
}

void Hooks_Threads_Commit(void)
{
	// hook message queue to pump our own messages
	{
		struct MessageQueueProcessTask_Code : Xbyak::CodeGenerator {
			MessageQueueProcessTask_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
			{
				Xbyak::Label retnLabel;

				mov(ptr[rsp+0x10], rbx);

				jmp(ptr [rip + retnLabel]);

				L(retnLabel);
				dq(MessageQueueProcessTask.GetUIntPtr() + 5);
			}
		};

		void * codeBuf = g_localTrampoline.StartAlloc();
		MessageQueueProcessTask_Code code(codeBuf);
		g_localTrampoline.EndAlloc(code.getCurr());

		MessageQueueProcessTask_Original = (_MessageQueueProcessTask)codeBuf;

		g_branchTrampoline.Write5Branch(MessageQueueProcessTask.GetUIntPtr(), (uintptr_t)MessageQueueProcessTask_Hook);
	}
}
