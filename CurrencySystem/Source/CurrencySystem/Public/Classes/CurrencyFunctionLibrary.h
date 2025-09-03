// Copyright 2025 Florian Nordmann. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CurrencyFunctionLibrary.generated.h"

class UCurrencyComponent;
/**
 * An extension of functions for the currency system
 */
UCLASS()
class CURRENCYSYSTEM_API UCurrencyFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Attempts to find the currency component in the actor
	 * @param Actor Pass the actor in which the component is to be searched for.
	 * @return Returns the component if it can be found, otherwise nullptr.
	 */
	UFUNCTION(BlueprintCallable, Category = "CurrencySystem")
	static UCurrencyComponent* GetActorCurrencyComponent(AActor* Actor);
};
