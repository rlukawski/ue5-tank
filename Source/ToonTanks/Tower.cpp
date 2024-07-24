// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Find the distance to the Tank
    if (Tank)
    {
        if (InFireCondition())
        {
            RotateTurret(Tank->GetActorLocation());
        }
    }
}

void ATower::ActivateTimer()
{
    GetWorld()->GetTimerManager().SetTimer(
        MyTimerHandle,
        this,
        &ATower::TimerCallback,
        2.0f,
        true);
}

void ATower::BeginPlay()
{
    Super::BeginPlay();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    ActivateTimer();
}

bool ATower::InFireCondition()
{
    return FVector::Dist(GetActorLocation(), Tank->GetActorLocation()) <= FireRange;
}

void ATower::TimerCallback()
{
    if (InFireCondition())
    {
        Fire();
    }
}