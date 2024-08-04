// Fill out your copyright notice in the Description page of Project Settings.


#include "Soldier_particle_module.h"
#include "Kismet/GameplayStatics.h"
//#include "NiagaraFunctionLibrary.h"
//#include "NiagaraComponent.h"

// Sets default values for this component's properties
USoldier_particle_module::USoldier_particle_module()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<USoundWave>FIRE(TEXT("/Script/Engine.SoundWave'/Game/Gun_Combat_SFX/WAVS/Rifle_Shot_1_Wav.Rifle_Shot_1_Wav'"));
	static ConstructorHelpers::FObjectFinder<USoundWave>MAGAZINE_IN(TEXT("/Script/Engine.SoundWave'/Game/Gun_Combat_SFX/WAVS/Gun_Load_6_Wav.Gun_Load_6_Wav'"));
	static ConstructorHelpers::FObjectFinder<USoundWave>MAGAZINE_OUT(TEXT("/Script/Engine.SoundWave'/Game/Gun_Combat_SFX/WAVS/Generic_Reload_Wav.Generic_Reload_Wav'"));
	static ConstructorHelpers::FObjectFinder<USoundWave>STICK(TEXT("/Script/Engine.SoundWave'/Game/Gun_Combat_SFX/WAVS/Gun_Load_2_Wav.Gun_Load_2_Wav'"));
	
	if (FIRE.Succeeded()) {
		fire_sfx = FIRE.Object;
	}
	if (MAGAZINE_IN.Succeeded()) {
		magazine_in = MAGAZINE_IN.Object;
	}
	if (MAGAZINE_OUT.Succeeded()) {
		magazine_out = MAGAZINE_OUT.Object;
	}
	if (STICK.Succeeded()) {
		stick = STICK.Object;
	}


	// ...
}


// Called when the game starts
void USoldier_particle_module::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USoldier_particle_module::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

