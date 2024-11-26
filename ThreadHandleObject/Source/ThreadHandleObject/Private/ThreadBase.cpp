// Fill out your copyright notice in the Description page of Project Settings.


#include "ThreadBase.h"
#include "ThreadObject.h"

FThreadBase::FThreadBase(UThreadObject* threadHandleObject, bool isTickEnabled)
{
	bTickEnabled = isTickEnabled;
	RunnableThread = nullptr;
	ThreadHandleObject = threadHandleObject;
}

FThreadBase::~FThreadBase()
{
	if (RunnableThread)
	{
		delete RunnableThread;
		RunnableThread = nullptr;
	}
}

void FThreadBase::StartThread()
{
	static FThreadSafeCounter ThreadCounter;
	FString ThreadName(FString::Printf(TEXT("ThreadBase Worker # %i"), ThreadCounter.Increment()));
	RunnableThread = FRunnableThread::Create(this, *ThreadName);
}

void FThreadBase::JoinThread()
{
	if (RunnableThread)
	{
		if (bIsRunning)
		{
			RunnableThread->WaitForCompletion();
		}
	}
}

void FThreadBase::DestroyThread()
{
	if (RunnableThread)
	{
		//RunnableThread->Suspend(true);
		RunnableThread->Kill();
		delete RunnableThread;
		RunnableThread = nullptr;
	}
}

bool FThreadBase::Init()
{
	if (IsValid(ThreadHandleObject))
	{
		return ThreadHandleObject->Init();
	}
	return false;
}

uint32 FThreadBase::Run()
{
	bIsRunning = true;
	if (IsValid(ThreadHandleObject))
	{
		ThreadHandleObject->Run();
	}
	bIsRunning = false;
	return 0;
}

void FThreadBase::Stop()
{
	FRunnable::Stop();
}
