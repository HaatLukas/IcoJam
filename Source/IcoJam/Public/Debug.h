#pragma once

#include "Misc/MessageDialog.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"

static TAutoConsoleVariable CVShowDebug(
	TEXT("d.PrintDebug"),
	0,
	TEXT("Draws debug info.\n")
	TEXT("0: Disabled\n")
	TEXT("1: Enabled"),
	ECVF_Cheat);


inline void Print(const UObject* Instigator,const FString &Message, const FColor &Color = FColor::Green, const float &Duration = 5.f)
{
	if (!CVShowDebug.GetValueOnAnyThread()) return;
	
	if (GEngine)
	{
		const FString InstigatorName = Instigator ? GetNameSafe(Instigator) : "None";
		const FString FinalMessage = InstigatorName + ": " + Message;
		
		GEngine->AddOnScreenDebugMessage(-1, Duration, Color, FinalMessage);
	}
}

inline void PrintLog(const FString &Message)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
}

inline void DebugLine(const UWorld* World, const FVector& Start, const FVector& End, const FColor Color = FColor::Red, const float Duration = 2.f)
{
	if (!CVShowDebug.GetValueOnAnyThread()) return;
	
	DrawDebugLine(World, Start, End, Color, false, Duration, 0, 5.f);
}

inline EAppReturnType::Type ShowMsgDialog(const EAppMsgType::Type &MsgType, const FString &Message, const bool bError = false)
{
	const FText Title = bError ? FText::FromString("Error") : FText::FromString("Message");
	
	return FMessageDialog::Open(MsgType, FText::FromString(Message), &Title);
}

inline void ShowNotification(const FString &Message, const float &Duration = 7.f)
{
	FNotificationInfo NotifyInfo(FText::FromString(Message));
	NotifyInfo.bUseLargeFont = true;
	NotifyInfo.FadeOutDuration = Duration;

	FSlateNotificationManager::Get().AddNotification(NotifyInfo);
}