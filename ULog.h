// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class DC_API ImplIT
{
public:
	ImplIT(){}

	FString sString;
	FString Str() { return sString; }

	ImplIT operator= (const int& _iInt)
	{
		sString = ImplIT(_iInt).Str();

		return ImplIT(_iInt);
	}

	// ImplIT(52) + MyString = 52MyString
	ImplIT operator+ (const FString& _sString)
	{
		FString sLog;
		sLog = sString + _sString;

		return ImplIT(sLog);
	}

	// ImplIT(52) + ImplIT() = 52MyString
	ImplIT operator+ (const ImplIT& iIT)
	{
		FString sLog;
		sLog = sString + iIT.sString;

		return ImplIT(sLog);
	}

	ImplIT operator* (const ImplIT& iIT)
	{
		FString sLog;
		sLog = sString + " " + iIT.sString;

		return ImplIT(sLog);
	}

	ImplIT(int MyInt)
	{
		sString = FString::FromInt(MyInt);
	}

	ImplIT(float MyFloat)
	{
		sString = FString::SanitizeFloat(MyFloat);
	}

	ImplIT(FString _sString)
	{
		sString = _sString;
	}

	~ImplIT(){}
};

static class DC_API ULog
{
public:
	ULog();

	static void Log(FString sLog);
	static void Log(ImplIT _ImplIT);
	static void LogScreen(FString sLog);
	static void LogScreen(ImplIT _ImplIT);

	// Probably not needed anymore
	//static void Log(ImplIT _ImplIT, ImplIT _ImplIT2);
	//static void Log(ImplIT _ImplIT, ImplIT _ImplIT2, ImplIT _ImplIT3);

	~ULog();
};