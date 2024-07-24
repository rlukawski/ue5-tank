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
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

        // Check to see if the Tank is in range
        if (Distance <= FireRange)
        {
            if (!GetWorld()->GetTimerManager().IsTimerActive(MyTimerHandle))
            {
                ActivateTimer();
            }
            // If in range, rotate turret toward Tank
            RotateTurret(Tank->GetActorLocation());
        }
        else
        {
            if (GetWorld()->GetTimerManager().IsTimerActive(MyTimerHandle))
            {
                GetWorld()->GetTimerManager().ClearTimer(MyTimerHandle);
            }
        }
    }
}

void ATower::ActivateTimer()
{
    // Zakładając, że MyTimerHandle to FTimerHandle zadeklarowany w klasie
    float TimerInterval = 2.0f; // Interwał w sekundach
    bool bLooping = true;       // Czy timer ma się powtarzać

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
}

void ATower::TimerCallback()
{
    Fire();
}