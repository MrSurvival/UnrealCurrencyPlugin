// Copyright 2025 Florian Nordmann. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CommonLazyImage.h"
#include "CommonNumericTextBlock.h"
#include "CurrencyWidget.generated.h"

class UCurrencyComponent;
class UCurrencyData;
/**
 * The class can be placed in another widget and automatically connects to the player's currency component.
 */
UCLASS(Abstract, Category = "Currency")
class CURRENCYSYSTEM_API UCurrencyWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	/**
	 * Is called to retrieve the value of the linked currency
	 * @param NewValue Passes the new value
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CurrencyWidget")
	void ValueChanged(int64 NewValue);

	/**
	 * Updated currency value Initial
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CurrencyWidget")
	void CurrencyLoaded();

private:
	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CurrencyWidget", meta = (AllowPrivateAccess))
	UCurrencyData* CurrencyData;
	
	UPROPERTY(meta = (BindWidgetOptional))
	UCommonLazyImage* Icon;

	UPROPERTY(meta = (BindWidget))
	UCommonNumericTextBlock* ValueText;

	UPROPERTY()
	UCurrencyComponent* OwningCurrencyComponent;
};
