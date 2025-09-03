// Copyright 2025 Florian Nordmann. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "CurrencySaveGame.generated.h"

/**
 * Base class for the currency save game
 */
UCLASS(BlueprintType, Blueprintable)
class CURRENCYSYSTEM_API UCurrencySaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "CurrencySystem")
	TMap<FPrimaryAssetId, int64> CurrencyData;
};
