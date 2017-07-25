// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class /*DC_API*/ ImplIT
{
public:
	ImplIT(){}
	~ImplIT(){}

	// You CAN edit/access this if you need too, but you shouldn't use Str() and the constructors
	FString sString;
	FString Str() { return sString; }

	// ImplIT(52) + MyString = 52MyString
	ImplIT operator+ (const FString& _sString)
	{
		FString sLog;
		sLog = sString + _sString;

		return ImplIT(sLog);
	}

	// ImplIT(52) + ImplIT("MyString") = 52MyString
	ImplIT operator+ (const ImplIT& iIT)
	{
		FString sLog;
		sLog = sString + iIT.sString;

		return ImplIT(sLog);
	}

	// ImplIT(52) + ImplIT("MyString") = 52MyString
	ImplIT operator* (const FString& _sString)
	{
		FString sLog;
		sLog = sString + " " + _sString;

		return ImplIT(sLog);
	}

	// ImplIT(52) * ImplIT("MyString") * 52MyString
	ImplIT operator* (const ImplIT& iIT)
	{
		FString sLog;
		sLog = sString + " " + iIT.sString;

		return ImplIT(sLog);
	}

	// ImplIT Constructors Used To Convert Values

	//ImplIT(bool MyBool) { sString = (MyBool ? "True" : "False"); }
	//ImplIT(bool MyBool, FString sTrue, FString sFalse) { sString = (MyBool ? sTrue : sFalse); }
	ImplIT(int MyInt) { sString = FString::FromInt(MyInt); }
	ImplIT(float MyFloat) {	sString = FString::SanitizeFloat(MyFloat); }
	ImplIT(FString _sString) { sString = _sString; }
};

static class /*DC_API*/ ULog
{
public:
	ULog(){}
	~ULog(){}

// 	static void Log(FString sLog);
// 	static void Log(ImplIT _ImplIT);
// 	static void LogScreen(FString sLog);
// 	static void LogScreen(ImplIT _ImplIT);
// 	static void LogBoth(FString sLog);
// 	static void LogBoth(ImplIT _ImplIT);

	static void Log(FString sLog)
	{
		UE_LOG(LogClass, Log, TEXT("%s"), *sLog);
	}

	static void Log(ImplIT _ImplIT)
	{
		Log(_ImplIT.Str());
	}

	static void LogScreen(FString sLog)
	{
		if ( GEngine != nullptr )
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, sLog);
		}
	}

	static void LogScreen(ImplIT _ImplIT)
	{
		LogScreen(_ImplIT.Str());
	}

	static void LogBoth(FString sLog)
	{
		Log(sLog);
		LogScreen(sLog);
	}

	static void LogBoth(ImplIT _ImplIT)
	{
		Log(_ImplIT);
		LogScreen(_ImplIT);
	}
};