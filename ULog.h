#pragma once

#define ULOG(a) ULog::Log(ImplIT("")+a)
#define UWARN(a) ULog::Warn(ImplIT("")+a)
#define UERROR(a) ULog::Error(ImplIT("")+a)
#define USCREEN(a) ULog::LogScreen(ImplIT("")+a)
#define USCREENC(a,c) ULog::LogScreen(ImplIT("")+a,c)
#define ULOGB(a) ULog::LogBoth(ImplIT("")+a)
#define ULOGBC(a,c) ULog::LogBoth(ImplIT("")+a,c)
#define UWARNB(a) ULog::WarnBoth(ImplIT("")+a)
#define UWARNBC(a,c) ULog::WarnBoth(ImplIT("")+a,c)
#define UERRORB(a) ULog::ErrorBoth(ImplIT("")+a)
#define UERRORBC(a,c) ULog::ErrorBoth(ImplIT("")+a,c)
#define MYNUM(a,b) ImplIT(L ## a, b)

#pragma region USEFUL_MACROS

#define NETMODE_WORLD (((GEngine == nullptr) || (GetWorld() == nullptr)) ? TEXT("") \
        : (GEngine->GetNetMode(GetWorld()) == NM_Client) ? TEXT("[Client] ") \
        : (GEngine->GetNetMode(GetWorld()) == NM_ListenServer) ? TEXT("[ListenServer] ") \
        : (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer) ? TEXT("[DedicatedServer] ") \
        : TEXT("[Standalone] "))

#define _FUNCTION_ TEXT(__FUNCTION__)

#define __ROLE__ ((Role == ROLE_Authority) ? TEXT("ROLE_Authority") \
        : (Role == ROLE_SimulatedProxy) ? TEXT("ROLE_SimulatedProxy") \
        : (Role == ROLE_AutonomousProxy) ? TEXT("ROLE_AutonomousProxy") \
        : TEXT("ROLE_None"))

#pragma endregion

class ImplIT
{
public:
	ImplIT(){}
	~ImplIT(){}

	// You CAN edit/access this if you need too, but you shouldn't use Str() and the constructors
	FString sString;
	FString Str() { return sString; }

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

	ImplIT(const char _sString[]) { sString = _sString; }
	ImplIT(bool MyBool, FString sTrue="True", FString sFalse="False") { sString = (MyBool ? sTrue : sFalse); }
	ImplIT(int MyInt) { sString = FString::FromInt(MyInt); }
	ImplIT(float MyFloat) {	sString = FString::SanitizeFloat(MyFloat); }
	ImplIT(FVector MyVector) { sString = MyVector.ToString(); }
	ImplIT(FRotator MyRotator) { sString = MyRotator.ToString(); }
	ImplIT(FName MyName) { sString = MyName.ToString(); }
	ImplIT(FText MyText) { sString = MyText.ToString(); }
	ImplIT(FString MyString) { sString = MyString; }

	// Magic Shit Ask Rusty595
	template<typename T>
	ImplIT(const TCHAR enumName[], T menum) { const UEnum* SlotEnum = FindObject<UEnum>(ANY_PACKAGE, enumName); sString= SlotEnum?SlotEnum->GetEnumName(static_cast<uint32>(menum)):"77unknown77"; }
};

static class ULog
{
public:
	ULog(){}
	~ULog(){}

	static void Log(ImplIT _ImplIT)
	{
		UE_LOG(LogClass, Log, TEXT("%s"), *_ImplIT.Str());
	}

	static void Warn(ImplIT _ImplIT)
	{
		UE_LOG(LogClass, Warning, TEXT("%s"), *_ImplIT.Str());
	}

	static void Error(ImplIT _ImplIT)
	{
		UE_LOG(LogClass, Error, TEXT("%s"), *_ImplIT.Str());
	}

	static void Fatal(ImplIT _ImplIT)
	{
		UE_LOG(LogClass, Fatal, TEXT("%s"), *_ImplIT.Str());
	}

	static void LogScreen(ImplIT _ImplIT, FColor _Color = FColor::Blue)
	{
		if ( GEngine != nullptr )
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, _Color, _ImplIT.Str());
		}
	}

	static void LogBoth(ImplIT _ImplIT, FColor _Color = FColor::Blue)
	{
		Log(_ImplIT);
		LogScreen(_ImplIT, _Color);
	}

	static void WarnBoth(ImplIT _ImplIT, FColor _Color = FColor::Yellow)
	{
		Warn(_ImplIT);
		LogScreen(_ImplIT, _Color);
	}

	static void ErrorBoth(ImplIT _ImplIT, FColor _Color = FColor::Red)
	{
		Error(_ImplIT);
		LogScreen(_ImplIT, _Color);
	}
};