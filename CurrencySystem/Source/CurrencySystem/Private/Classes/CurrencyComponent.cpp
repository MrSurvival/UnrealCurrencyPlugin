// Copyright 2025 Florian Nordmann. All rights reserved.

#include "Classes/CurrencyComponent.h"

#ifdef UE_WITH_PLUGIN_SAVEGAMEMANAGER
#include "SaveGameManagerSubsystem.h"
#endif

#include "Classes/CurrencyData.h"
#include "Kismet/GameplayStatics.h"
#include "Classes/CurrencySaveGame.h"

UCurrencyComponent::UCurrencyComponent(): SaveGame(nullptr)
{
	PrimaryComponentTick.bCanEverTick = true;
}

bool UCurrencyComponent::AddCurrencyValue(const UCurrencyData* Currency, const int64 Value)
{
	if (!SaveGame)
	{
		return false;
	}
	
	int64* LocalCurrencyValue = SaveGame->CurrencyData.Find(Currency->GetPrimaryAssetId());

	if (!LocalCurrencyValue)
	{
		return false;
	}

	*LocalCurrencyValue += Value;

	if (Currency->bClamp)
	{
		*LocalCurrencyValue = FMath::Clamp(*LocalCurrencyValue, Currency->ClampRange.X, Currency->ClampRange.Y);
	}

	UGameplayStatics::PlaySoundAtLocation(this, Currency->DepositSound, GetOwner()->GetActorLocation());

	OnCurrencyChanged.Broadcast(*LocalCurrencyValue);
	
	return true;
}

bool UCurrencyComponent::SetCurrencyValue(const UCurrencyData* Currency, const int64 Value)
{
	int64* LocalCurrencyValue = SaveGame->CurrencyData.Find(Currency->GetPrimaryAssetId());

	if (!LocalCurrencyValue)
	{
		return false;
	}
	
	*LocalCurrencyValue = Value;

	if (Currency->bClamp)
	{
		FMath::Clamp(*LocalCurrencyValue, Currency->ClampRange.X, Currency->ClampRange.Y);
	}

	UGameplayStatics::PlaySoundAtLocation(this, Currency->WithdrawSound, GetOwner()->GetActorLocation());

	OnCurrencyChanged.Broadcast(*LocalCurrencyValue);
	
	return true;
}

int64 UCurrencyComponent::GetCurrencyValue(const UCurrencyData* Currency)
{
	const int64* LocalCurrencyValue = SaveGame->CurrencyData.Find(Currency->GetPrimaryAssetId());

	if (!LocalCurrencyValue)
	{
		return -1;
	}
	
	return *LocalCurrencyValue;
}

TArray<UCurrencyData*> UCurrencyComponent::GetAllCurrencyData()
{
	TArray<UCurrencyData*> LocalKeys;
	DefaultCurrencyStorage.GetKeys(LocalKeys);
	return LocalKeys;
}

void UCurrencyComponent::ResetAllCurrencies()
{
	SaveGame->CurrencyData.Empty();

	for (const TPair<UCurrencyData*, int64>& Element : DefaultCurrencyStorage)
	{
		SaveGame->CurrencyData.Add(Element.Key->GetPrimaryAssetId(), Element.Value);
		OnCurrencyChanged.Broadcast(Element.Value);
	}
}

void UCurrencyComponent::LoadCurrency()
{
#ifdef UE_WITH_PLUGIN_SAVEGAMEMANAGER
	
	if (!SaveGameGuid.IsValid())
	{
		return;
	}
	
	USaveGameManagerSubsystem* LocalSaveGameManagerSubsystem = UGameplayStatics::GetGameInstance(this)->GetSubsystem<USaveGameManagerSubsystem>();

	if (!LocalSaveGameManagerSubsystem)
	{
		return;
	}
	
	USaveGame* LocalSaveGame;
	LocalSaveGameManagerSubsystem->GetPlayerSaveGame(CurrencySaveGameName, UCurrencySaveGame::StaticClass(), LocalSaveGame);

	if (!LocalSaveGame)
	{
		return;
	}
	
	SaveGame = Cast<UCurrencySaveGame>(LocalSaveGame);

	if (SaveGame->CurrencyData.IsEmpty())
	{
		for (const TPair<UCurrencyData*, int64>& Element : DefaultCurrencyStorage)
		{
			SaveGame->CurrencyData.Add(Element.Key->GetPrimaryAssetId(), Element.Value);
		}
	}
	
	OnCurrencyLoaded.Broadcast();
	
#endif
}

bool UCurrencyComponent::IsCurrencyLoaded() const
{
	return SaveGame != nullptr;
}

void UCurrencyComponent::DefaultLoad()
{
	SaveGame = NewObject<UCurrencySaveGame>(this, UCurrencySaveGame::StaticClass(), CurrencySaveGameName, RF_Public | RF_Standalone);

	for (const TPair<UCurrencyData*, int64>& Element : DefaultCurrencyStorage)
	{
		SaveGame->CurrencyData.Add(Element.Key->GetPrimaryAssetId(), Element.Value);
	}
	
	OnCurrencyLoaded.Broadcast();
}

void UCurrencyComponent::BeginPlay()
{
	Super::BeginPlay();

#ifdef UE_WITH_PLUGIN_SAVEGAMEMANAGER
	LoadCurrency();
#endif
	
	if (!SaveGame)
	{
		DefaultLoad();
	}
}

void UCurrencyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

