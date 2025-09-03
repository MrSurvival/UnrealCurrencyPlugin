// Copyright 2025 Florian Nordmann. All rights reserved.

#include "CurrencyAssetDefinition.h"

TSoftClassPtr<UObject> UCurrencyAssetDefinition::GetAssetClass() const
{
	return UCurrencyData::StaticClass();
}

FText UCurrencyAssetDefinition::GetAssetDisplayName() const
{
	return AssetDisplayName;
}

FLinearColor UCurrencyAssetDefinition::GetAssetColor() const
{
	return AssetColor;
}

TConstArrayView<FAssetCategoryPath> UCurrencyAssetDefinition::GetAssetCategories() const
{
	static const FAssetCategoryPath Categories[] = {FText::FromString(TEXT("Voxelgate"))};
	return Categories;
}
