// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	class ATank* Tank;
	FTimerHandle MyTimerHandle;

	void TimerCallback();
	void ActivateTimer();
	bool InFireCondition();

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float FireRange = 300.f;


};
