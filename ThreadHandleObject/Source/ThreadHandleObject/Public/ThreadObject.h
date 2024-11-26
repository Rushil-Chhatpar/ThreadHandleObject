// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/World.h"
#include "Runtime/Core/Public/HAL/ThreadSafeBool.h"
#include "ThreadObject.generated.h"

DECLARE_DYNAMIC_DELEGATE(FRunDelegate);

/**
 * 
 */
UCLASS()
class THREADHANDLEOBJECT_API UThreadObject : public UObject
{
	GENERATED_BODY()
public:

	UThreadObject(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	void Initialize(bool isTickEnabled, bool AutoStart);
	void BindThreadRunBody(FRunDelegate const& Delegate);

	void StartThread();
	void StopThread();
	void SleepThread(float seconds);
	void KillThread();

	void Lock();
	void Unlock();
	bool TryLock();

	bool Init();
	void Run();

	UPROPERTY()
	FRunDelegate RunDelegate;

	UWorld* GetObjectWorld();
	virtual void BeginDestroy() override;

protected:
	FCriticalSection Mutex;
	class FThreadBase* Thread;

	FThreadSafeBool bStopThread;
	FThreadSafeBool bIsTickEnabled;
	UWorld* World;
};
