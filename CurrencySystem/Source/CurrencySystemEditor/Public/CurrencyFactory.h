// Copyright 2025 Florian Nordmann. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "CurrencyFactory.generated.h"

/**
 * This class creates the new custom currency class.
 */
UCLASS()
class CURRENCYSYSTEMEDITOR_API UCurrencyFactory : public UFactory
{
	GENERATED_BODY()

	UCurrencyFactory(const FObjectInitializer& FObjectInitializer);
	
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
