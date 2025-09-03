// Copyright 2025 Florian Nordmann. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AssetDefinitionDefault.h"
#include "Classes/CurrencyData.h"
#include "CurrencyAssetDefinition.generated.h"

/**
 * This class defines the appearance of the custom file type for currency.
 */
UCLASS()
class CURRENCYSYSTEMEDITOR_API UCurrencyAssetDefinition : public UAssetDefinitionDefault
{
	GENERATED_BODY()

	virtual TSoftClassPtr<UObject>GetAssetClass() const override;
	
	virtual FText GetAssetDisplayName() const override;
	
	virtual FLinearColor GetAssetColor() const override;
	
	virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;

	const FText AssetDisplayName = FText::FromString(TEXT("Currency"));

	const FLinearColor AssetColor = FLinearColor::FromSRGBColor({233, 189, 0, 255});
};
