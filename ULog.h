#pragma once

#pragma region USEFUL_MACROS

#define L_NETMODE_WORLD (((GEngine == nullptr) || (GetWorld() == nullptr)) ? "" \
        : (GEngine->GetNetMode(GetWorld()) == NM_Client) ? "[Client] " \
        : (GEngine->GetNetMode(GetWorld()) == NM_ListenServer) ? "[ListenServer] " \
        : (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer) ? "[DedicatedServer] " \
        : "[Standalone] ")

#define L_ROLE ((Role == ROLE_Authority) ? "ROLE_Authority" \
        : (Role == ROLE_SimulatedProxy) ? "ROLE_SimulatedProxy" \
        : (Role == ROLE_AutonomousProxy) ? "ROLE_AutonomousProxy" \
        : "ROLE_None")

#pragma endregion

#define VERBOSE_LOGGING false
#if VERBOSE_LOGGING
#define LOG_PREFIX ImplIT("")+L_NETMODE_WORLD+L_ROLE+" "+__FUNCTION__+" "
#else
#define LOG_PREFIX ImplIT("")
#endif

#define ULOG(a) ULog::Log(LOG_PREFIX+a)
#define UWARN(a) ULog::Warn(LOG_PREFIX+a)
#define UERROR(a) ULog::Error(LOG_PREFIX+a)
#define USCREEN(a) ULog::LogScreen(LOG_PREFIX+a)
#define USCREENC(a,c) ULog::LogScreen(LOG_PREFIX+a,0,c)
#define USCREENT(a,t) ULog::LogScreen(LOG_PREFIX+a,t)
#define USCREENTC(a,t,c) ULog::LogScreen(LOG_PREFIX+a,t,c)
#define ULOGB(a) ULog::LogBoth(LOG_PREFIX+a)
#define ULOGBC(a,c) ULog::LogBoth(LOG_PREFIX+a,0,c)
#define ULOGBT(a,t) ULog::LogBoth(LOG_PREFIX+a,t)
#define ULOGBTC(a,t,c) ULog::LogBoth(LOG_PREFIX+a,t,c)
#define UWARNB(a) ULog::WarnBoth(LOG_PREFIX+a)
#define UWARNBC(a,c) ULog::WarnBoth(LOG_PREFIX+a,0,c)
#define UWARNBT(a,t) ULog::WarnBoth(LOG_PREFIX+a,t)
#define UWARNBTC(a,t,c) ULog::WarnBoth(LOG_PREFIX+a,t,c)
#define UERRORB(a) ULog::ErrorBoth(LOG_PREFIX+a)
#define UERRORBC(a,c) ULog::ErrorBoth(LOG_PREFIX+a,0,c)
#define UERRORBT(a,t) ULog::ErrorBoth(LOG_PREFIX+a,t)
#define UERRORBTC(a,t,c) ULog::ErrorBoth(LOG_PREFIX+a,t,c)
#define MYENUM(a,b) ImplIT(L ## a, b)
#define UCRASH(a) ULog::Fatal(LOG_PREFIX+a)

class ImplIT
{
public:
	ImplIT(){}
	~ImplIT(){}

	// You CAN edit/access this if you need too, but you shouldn't use Str() and the constructors
	FString sString;
	FString Str() { return sString; }

	// ImplIT(52) + ImplIT("MyString") = "52MyString"
	ImplIT operator+ (const ImplIT& iIT)
	{
		FString sLog;
		sLog = sString + iIT.sString;

		return ImplIT(sLog);
	}

	// ImplIT(52) * ImplIT("MyString") = "52 MyString"
	ImplIT operator* (const FString& _sString)
	{
		FString sLog;
		sLog = sString + " " + _sString;

		return ImplIT(sLog);
	}

	// ImplIT(52) * ImplIT("MyString") = "52 MyString"
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
	ImplIT(AActor* MyActor) { sString = MyActor->GetName(); }

	// Magic Shit Ask Rusty595 (Enum Support, Use MYENUM("EENumType", EnumValue) Macro!)
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

	static void LogScreen(ImplIT _ImplIT, float _Time=0, FColor _Color = FColor::White)
	{
		if ( GEngine != nullptr )
		{
			GEngine->AddOnScreenDebugMessage(-1, _Time, _Color, _ImplIT.Str());
		}
	}

	static void LogBoth(ImplIT _ImplIT, float _Time=0, FColor _Color = FColor::White)
	{
		Log(_ImplIT);
		LogScreen(_ImplIT, _Time, _Color);
	}

	static void WarnBoth(ImplIT _ImplIT, float _Time = 0, FColor _Color = FColor::Yellow)
	{
		Warn(_ImplIT);
		LogScreen(_ImplIT, _Time, _Color);
	}

	static void ErrorBoth(ImplIT _ImplIT, float _Time = 0, FColor _Color = FColor::Red)
	{
		Error(_ImplIT);
		LogScreen(_ImplIT, _Time, _Color);
	}
};