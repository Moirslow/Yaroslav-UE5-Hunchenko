// Fill out your copyright notice in the Description page of Project Settings.


#include "GASCharacter.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "GASAttributeSet.h"

// Sets default values
AGASCharacter::AGASCharacter()
{

AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
AttributeSet = CreateDefaultSubobject<UGASAttributeSet>(TEXT("AttributeSet"));

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

		if (HasAuthority() && DebugAbilityClass)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(DebugAbilityClass, 1, 0));
		}

		UE_LOG(LogTemp, Warning, TEXT("GASCharacter: ASC valid=%s | ActorInfo valid=%s"),
			AbilitySystemComponent ? TEXT("true") : TEXT("false"),
			AbilitySystemComponent->AbilityActorInfo.IsValid() ? TEXT("true") : TEXT("false"));

	}
	
}

void AGASCharacter::ActivateDebugAbility()
{
	if (!AbilitySystemComponent || !DebugAbilityClass) return;
	AbilitySystemComponent->TryActivateAbilityByClass(DebugAbilityClass);
}

