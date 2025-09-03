// Copyright 2025 Florian Nordmann. All rights reserved.

#include "Classes/CurrencyData.h"

#include "Misc/DataValidation.h"

#if WITH_EDITOR
EDataValidationResult UCurrencyData::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult ValidationResult = Super::IsDataValid(Context);

	if(DisplayName.IsEmpty())
	{
		Context.AddError(NSLOCTEXT("CurrencyData", "DataIsInvalid", "DisplayName is empty!"));
		ValidationResult = EDataValidationResult::Invalid;
	}

	if (Icon.IsNull())
	{
		Context.AddError(NSLOCTEXT("CurrencyData", "DataIsInvalid", "Icon is empty!"));
		ValidationResult = EDataValidationResult::Invalid;
	}

	if (!DepositSound)
	{
		Context.AddError(NSLOCTEXT("CurrencyData", "DataIsInvalid", "DepositSound is empty!"));
		ValidationResult = EDataValidationResult::Invalid;
	}

	if (!WithdrawSound)
	{
		Context.AddError(NSLOCTEXT("CurrencyData", "DataIsInvalid", "WithdrawSound is empty!"));
		ValidationResult = EDataValidationResult::Invalid;
	}
	return ValidationResult;
}
#endif
