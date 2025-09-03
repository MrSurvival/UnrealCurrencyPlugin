// Copyright 2025 Florian Nordmann. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CurrencyData.generated.h"

class USoundBase;
class UTexture2D;

/**
 * The base class for currency types
 */
UCLASS(BlueprintType, DisplayName = "Currency")
class CURRENCYSYSTEM_API UCurrencyData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Currency")
	FText DisplayName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Currency")
	TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Currency")
	FLinearColor Color;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Currency", meta = (InlineEditConditionToggle))
	bool bClamp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Currency", meta = (EditCondition = "bClamp"))
	FVector2D ClampRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Currency")
	USoundBase* DepositSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Currency")
	USoundBase* WithdrawSound;

#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif
};
