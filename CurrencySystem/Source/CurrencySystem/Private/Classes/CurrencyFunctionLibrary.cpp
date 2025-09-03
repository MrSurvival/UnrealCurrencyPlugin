// Copyright 2025 Florian Nordmann. All rights reserved.

#include "Classes/CurrencyFunctionLibrary.h"

#include "Classes/CurrencyComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerState.h"

UCurrencyComponent* UCurrencyFunctionLibrary::GetActorCurrencyComponent(AActor* Actor)
{
	if (!Actor)
	{
		return nullptr;
	}

	// Check if the actor has a currency component
	UCurrencyComponent* LocalCurrencyComponent = Actor->GetComponentByClass<UCurrencyComponent>();

	if (LocalCurrencyComponent)
	{
		return LocalCurrencyComponent;
	}

	// Check if the actor is a pawn and has a currency component on the controller
	if (!Actor->IsA<APawn>())
	{
		return nullptr;	
	}

	const APawn* LocalPawn = Cast<APawn>(Actor);
	LocalCurrencyComponent = LocalPawn->GetController()->FindComponentByClass<UCurrencyComponent>();

	if (LocalCurrencyComponent)
	{
		return LocalCurrencyComponent;
	}

	// Check if the actor is a pawn and has a currency component on the player state
	const APlayerState* LocalPlayerState = LocalPawn->GetPlayerState();

	if (!LocalPlayerState)
	{
		return nullptr;
	}

	LocalCurrencyComponent = LocalPlayerState->FindComponentByClass<UCurrencyComponent>();

	if (LocalCurrencyComponent)
	{
		return LocalCurrencyComponent;
	}

	return nullptr;
}
