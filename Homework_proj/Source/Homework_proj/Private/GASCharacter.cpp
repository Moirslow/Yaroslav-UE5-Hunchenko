// Fill out your copyright notice in the Description page of Project Settings.


#include "GASCharacter.h"
#include "AbilitySystemComponent.h"

// Sets default values
AGASCharacter::AGASCharacter()
{

AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

}

UAbilitySystemComponent* AGASCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void AGASCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{

		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		UE_LOG(LogTemp, Warning, TEXT("GASCharacter: ASC valid=%s | ActorInfo valid=%s"),
			AbilitySystemComponent ? TEXT("true") : TEXT("false"),
			AbilitySystemComponent->AbilityActorInfo.IsValid() ? TEXT("true") : TEXT("false"));

	}
	
}



