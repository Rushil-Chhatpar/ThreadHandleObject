// Fill out your copyright notice in the Description page of Project Settings.


#include "ThreadObject.h"
#include "ThreadBase.h"

UThreadObject::UThreadObject(const FObjectInitializer& ObjectInitializer)
{

	Thread = nullptr;
	bStopThread = false;
	World = nullptr;
}

void UThreadObject::Initialize(bool isTickEnabled, bool AutoStart)
{
	World = GetWorld();
	bIsTickEnabled = isTickEnabled;
	Thread = new FThreadBase(this, isTickEnabled);
	if (AutoStart)
	{
		Thread->StartThread();
	}
}

void UThreadObject::BindThreadRunBody(FRunDelegate const& Delegate)
{
	if (IsValid(this))
	{
		RunDelegate = Delegate;
	}
}

void UThreadObject::StartThread()
{
	if (Thread)
	{
		Thread->StartThread();
	}
}

void UThreadObject::StopThread()
{
	bStopThread = true;
}

void UThreadObject::SleepThread(float seconds)
{
	FPlatformProcess::Sleep(seconds);
}

void UThreadObject::KillThread()
{
	if (Thread)
	{
		Thread->DestroyThread();
	}
}

void UThreadObject::Lock()
{
	Mutex.Lock();
}

void UThreadObject::Unlock()
{
	Mutex.Unlock();
}

bool UThreadObject::TryLock()
{
#if PLATFORM_WINDOWS
	return Mutex.TryLock();
#else
	return false;
#endif
}

bool UThreadObject::Init()
{
	bStopThread = false;
	return true;
}

void UThreadObject::Run()
{
	if (Thread)
	{
		while (!bStopThread)
		{
			if (bIsTickEnabled)
			{
				SleepThread(World->DeltaTimeSeconds);
			}
			if (RunDelegate.IsBound())
			{
				RunDelegate.ExecuteIfBound();
			}
		}
		if (Thread)
		{
			Thread->DestroyThread();
		}
	}
}

UWorld* UThreadObject::GetObjectWorld()
{
	return World;
}

void UThreadObject::BeginDestroy()
{
	bStopThread = true;
	if (Thread)
	{
		Thread->Stop();
		delete Thread;
		Thread = nullptr;
	}

	Super::BeginDestroy();
}
