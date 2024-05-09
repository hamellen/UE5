// Fill out your copyright notice in the Description page of Project Settings.


#include "jumpscare_monster.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
Ajumpscare_monster::Ajumpscare_monster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK(TEXT("SkeletalMesh'/Game/Monster/Mesh/SKM_Monster.SKM_Monster'"));

	if (SK.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SK.Object);
	}
	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f)
	);
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	UAnimationAsset* jumpscare = LoadObject<UAnimationAsset>(nullptr, TEXT("AnimSequence'/Game/Monster/Animations/Anim_Monster_attack6.Anim_Monster_attack6'"));
	sound_jumpscare = LoadObject<USoundWave>(nullptr, TEXT("SoundWave'/Game/SFX/squeaky-jumpscare-81079.squeaky-jumpscare-81079'"));
	
}

// Called when the game starts or when spawned
void Ajumpscare_monster::BeginPlay()
{
	Super::BeginPlay();
	UAnimationAsset* jumpscare = LoadObject<UAnimationAsset>(nullptr, TEXT("AnimSequence'/Game/Monster/Animations/Anim_Monster_attack6.Anim_Monster_attack6'"));
	if (jumpscare != nullptr) {
		GetMesh()->PlayAnimation(jumpscare, true);
		UGameplayStatics::PlaySound2D(GetWorld(), sound_jumpscare,0.5f);
	}
}

// Called every frame
void Ajumpscare_monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void Ajumpscare_monster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

