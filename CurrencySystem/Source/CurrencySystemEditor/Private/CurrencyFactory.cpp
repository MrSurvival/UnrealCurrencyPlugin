// Copyright 2025 Florian Nordmann. All rights reserved.

#include "CurrencyFactory.h"

#include "Classes/CurrencyData.h"

UCurrencyFactory::UCurrencyFactory(const FObjectInitializer& FObjectInitializer):Super(FObjectInitializer)
{
	SupportedClass = UCurrencyData::StaticClass();
	bCreateNew = true;
	bEditorImport = false;
	bEditAfterNew = true;
}
	 
UObject* UCurrencyFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UCurrencyData>(InParent, Class, Name, Flags | RF_Transactional);
}
