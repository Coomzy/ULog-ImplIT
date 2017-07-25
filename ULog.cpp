// Fill out your copyright notice in the Description page of Project Settings.

#include "DC.h"
#include "ULog.h"

ULog::ULog(){}

void ULog::Log(FString sLog)
{
	UE_LOG(LogClass, Log, TEXT("%s"), *sLog);
}

void ULog::Log(ImplIT _ImplIT)
{
	Log(_ImplIT.Str());
}

void ULog::LogScreen(FString sLog)
{
	if ( GEngine != nullptr )
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, sLog);
	}
}

void ULog::LogScreen(ImplIT _ImplIT)
{
	LogScreen(_ImplIT.Str());
}

// Probably Not Needed Anymore
// void ULog::Log(ImplIT _ImplIT, ImplIT _ImplIT2)
// {
// 	FString sLog = _ImplIT.Get();
// 
// 	sLog += _ImplIT2.Get();
// 
// 	Log(sLog);
// }
// 
// void ULog::Log(ImplIT _ImplIT, ImplIT _ImplIT2, ImplIT _ImplIT3)
// {
// 
// 	FString sLog = _ImplIT.Get();
// 
// 	sLog += _ImplIT2.Get();
// 	sLog += _ImplIT3.Get();
// 
// 	Log(sLog);
// }

ULog::~ULog(){}
