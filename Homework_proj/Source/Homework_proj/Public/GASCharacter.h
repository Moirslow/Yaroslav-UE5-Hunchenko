// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GASCharacter.generated.h"

class UAbilitySystemComponent;
class UGameplayAbility;

UCLASS()
class HOMEWORK_PROJ_API AGASCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AGASCharacter();

	// IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY (VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	TSubclassOf<UGameplayAbility> DebugAbilityClass;

	UFUNCTION(BlueprintCallable, Category = "GAS")
	void ActivateDebugAbility();
};
