// Fill out your copyright notice in the Description page of Project Settings.


#include "My_Default_gun.h"

// Sets default values
AMy_Default_gun::AMy_Default_gun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMy_Default_gun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMy_Default_gun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMy_Default_gun::Fire(FVector endpoint)
{
}

void AMy_Default_gun::Reload()
{
}

void AMy_Default_gun::reset_gun_ammo()
{
}

