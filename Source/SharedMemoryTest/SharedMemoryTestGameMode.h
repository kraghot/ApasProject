// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "SharedMemoryTestGameMode.generated.h"

UCLASS(minimalapi)
class ASharedMemoryTestGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ASharedMemoryTestGameMode();
	void CreateSharedMemory();

private:
	HANDLE hMapFile;
	LPCTSTR pBuf;
};



