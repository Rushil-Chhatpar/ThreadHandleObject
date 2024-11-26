// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Runtime/Core/Public/HAL/ThreadSafeBool.h"
#include "Runtime/Core/Public/HAL/Runnable.h"
#include "Runtime/Core/Public/HAL/RunnableThread.h"

/**
 * 
 */
class FThreadBase : public FRunnable
{
public:
	FThreadBase(class UThreadObject* threadHandleObject, bool isTickEnabled);
	~FThreadBase();

	void StartThread();
	// dont use this unless you know what you're doing :)
	void JoinThread();
	void DestroyThread();

	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;

private:
	class UThreadObject* ThreadHandleObject;
	FRunnableThread* RunnableThread;

	FThreadSafeBool bIsRunning;
	FThreadSafeBool bTickEnabled;
};
