// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SharedMemoryTest.h"
#include "SharedMemoryTestGameMode.h"
#include "SharedMemoryTestHUD.h"
#include "SharedMemoryTestCharacter.h"
#include <conio.h>

#pragma comment(lib, "user32.lib")
#define BUF_SIZE 256
TCHAR szName[] = TEXT("Global\\KinectJointValues");


ASharedMemoryTestGameMode::ASharedMemoryTestGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ASharedMemoryTestHUD::StaticClass();

	ASharedMemoryTestGameMode::CreateSharedMemory();
}

void ASharedMemoryTestGameMode::CreateSharedMemory ()
{
	hMapFile = OpenFileMapping(
		FILE_MAP_ALL_ACCESS,   // read/write access
		0,                 // do not inherit the name
		szName);           // name of mapping object

	if (hMapFile == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not open file mapping object.\n"));
		return;
	}

	pBuf = (LPTSTR)MapViewOfFile(hMapFile, // handle to map object
		FILE_MAP_ALL_ACCESS,  // read/write permission
		0,
		0,
		BUF_SIZE);

	if (pBuf == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not map view of file.\n"));

		CloseHandle(hMapFile);

		return;
	}
	
	//std::string StandardString = std::string(pBuf);
	TCHAR tstrtststs[100];
	_tcscpy_s(tstrtststs, pBuf);

	UE_LOG(LogTemp, Warning, tstrtststs);

	UnmapViewOfFile(pBuf);

	CloseHandle(hMapFile);

	return;
}