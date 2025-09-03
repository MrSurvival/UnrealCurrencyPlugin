// Copyright 2025 Florian Nordmann. All rights reserved.

#include "Widgets/CurrencyWidget.h"

#include "Classes/CurrencyComponent.h"
#include "GameFramework/Pawn.h"
#include "Classes/CurrencyData.h"

void UCurrencyWidget::ValueChanged_Implementation(const int64 NewValue)
{
	constexpr float MaximumInterpolationDuration = 0.5f;
	ValueText->InterpolateToValue(NewValue, MaximumInterpolationDuration);
}

void UCurrencyWidget::CurrencyLoaded_Implementation()
{
	ValueText->SetCurrentValue(OwningCurrencyComponent->GetCurrencyValue(CurrencyData));
}

void UCurrencyWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (!CurrencyData)
	{
		return;
	}

	if (Icon)
	{
		Icon->SetBrushFromLazyTexture(CurrencyData->Icon);
		Icon->SetColorAndOpacity(CurrencyData->Color);
	}

	ValueText->SetColorAndOpacity(CurrencyData->Color);
}

void UCurrencyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!GetOwningPlayer())
	{
		return;
	}

	if (!GetOwningPlayer()->GetPawn())
	{
		return;
	}

	OwningCurrencyComponent = GetOwningPlayer()->GetPawn()->FindComponentByClass<UCurrencyComponent>();

	if (!OwningCurrencyComponent)
	{
		return;
	}

	if (!OwningCurrencyComponent->OnCurrencyChanged.IsAlreadyBound(this, &ThisClass::ValueChanged))
	{
		OwningCurrencyComponent->OnCurrencyChanged.AddDynamic(this, &ThisClass::ValueChanged);
	}

	if (OwningCurrencyComponent->IsCurrencyLoaded())
	{
		ValueChanged(OwningCurrencyComponent->GetCurrencyValue(CurrencyData));
	}
	else
	{
		OwningCurrencyComponent->OnCurrencyLoaded.AddDynamic(this, &ThisClass::CurrencyLoaded);
	}
}
