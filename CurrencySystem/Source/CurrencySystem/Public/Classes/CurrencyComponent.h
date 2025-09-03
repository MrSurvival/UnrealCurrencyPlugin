// Copyright 2025 Florian Nordmann. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CurrencyComponent.generated.h"

class UCurrencyData;
class UCurrencySaveGame;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurrencyChanged, int64, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCurrencyLoaded);


UCLASS(ClassGroup = (Currency), meta = (BlueprintSpawnableComponent))
class CURRENCYSYSTEM_API UCurrencyComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCurrencyComponent();

	/**
	* Adds a specified value to the current amount of a given currency type.
	*
	* @param Currency  The currency type to which the value should be added.
	* @param Value     The amount to add to the specified currency. Can be negative to subtract.
	* @return          true if the value was successfully added; false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "CurrencySystem")
	bool AddCurrencyValue(const UCurrencyData* Currency, int64 Value);

	/**
	* Sets a specified value to the current amount of a given currency type.
	*
	* @param Currency  The currency type to which the value should be added.
	* @param Value     The amount to set the specified currency.
	* @return          true if the value was successfully added; false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "CurrencySystem")
	bool SetCurrencyValue(const UCurrencyData* Currency, int64 Value);

	/**
	* Retrieves the current value of the specified currency type.
	*
	* @param Currency  The currency type whose value should be retrieved.
	* @return          The current amount associated with the given currency. Returns -1 if the currency is invalid or not found.
	*/
	UFUNCTION(BlueprintPure, Category = "CurrencySystem")
	int64 GetCurrencyValue(const UCurrencyData* Currency);

	/**
	* Returns an array containing all defined currency data objects in the system.
	*
	* @return  An array of UCurrencyData pointers representing all available currencies.
	*          The array may be empty if no currency data is registered.
	*/
	UFUNCTION(BlueprintPure, Category = "CurrencySystem")
	TArray<UCurrencyData*> GetAllCurrencyData();

	/**
	* Resets all registered currency values to their default state.
	*/
	UFUNCTION(BlueprintCallable, Category = "CurrencySystem")
	void ResetAllCurrencies();

	/**
	 * Loads the currency values from the savegame.
	 */
	UFUNCTION(BlueprintCallable, Category = "CurrencySystem")
	void LoadCurrency();

	/**
	 * Checked whether a valid savegame could be loaded.
	 * 
	 * @return true if savegame could be loaded.
	 */
	UFUNCTION(BlueprintPure, Category = "CurrencySystem")
	bool IsCurrencyLoaded() const;

	/**
	 * If no savegame is used for saving, this function creates the necessary classes.
	 */
	UFUNCTION()
	void DefaultLoad();

	UPROPERTY(BlueprintAssignable, Category = "CurrencySystem")
	FOnCurrencyChanged OnCurrencyChanged;

	UPROPERTY(BlueprintAssignable, Category = "CurrencySystem")
	FOnCurrencyLoaded OnCurrencyLoaded;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "CurrencySystem")
	TMap<UCurrencyData*, int64> DefaultCurrencyStorage;

	UPROPERTY(EditAnywhere, Category = "CurrencySystem")
	FGuid SaveGameGuid;

	/**
	 * Should match the definition of the savegame name in the SaveGameManager, if used.
	 */
	UPROPERTY(EditAnywhere, Category = "CurrencySystem")
	FName CurrencySaveGameName = TEXT("CurrencySaveGame");

	UPROPERTY(BlueprintReadOnly, Category = "CurrencySystem", meta = (AllowPrivateAccess))
	UCurrencySaveGame* SaveGame;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
