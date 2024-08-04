// Fill out your copyright notice in the Description page of Project Settings.


#include "Crunch.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/CapsuleComponent.h"
#include "NiagaraComponent.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"
#include "Kismet/KismetMathLibrary.h"
#include "Crunch_animinstance.h"
// Sets default values
ACrunch::ACrunch()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>CRUNCH_SK(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonCrunch/Characters/Heroes/Crunch/Skins/Tier_3/BlackSite/Meshes/Crunch_Black_Site.Crunch_Black_Site'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem>HITED_VFX(TEXT("/Script/Engine.ParticleSystem'/Game/Realistic_Starter_VFX_Pack_Vol2/Particles/Sparks/P_Sparks_C.P_Sparks_C'"));
	static ConstructorHelpers::FObjectFinder<USoundBase>HITED_SFX(TEXT("/Script/Engine.SoundWave'/Game/Gun_Combat_SFX/WAVS/Impact_Metal_Wav.Impact_Metal_Wav'"));

	if (CRUNCH_SK.Succeeded()) {
		GetMesh()->SetSkeletalMesh(CRUNCH_SK.Object);
	}

	if (HITED_VFX.Succeeded()) {
		hited_vfx = HITED_VFX.Object;
	}

	if (HITED_SFX.Succeeded()) {
		hited_sfx = HITED_SFX.Object;
	}
	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f)
	);

	//GetMesh()->SetupAttachment(RootComponent);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	sensing_rad = 3000.f;
	hp = 5000.f;
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

}

void ACrunch::Play_jumpattack()
{
	auto animainstance = Cast<UCrunch_animinstance>(GetMesh()->GetAnimInstance());
	
	if (animainstance) {
		animainstance->Play_crunch_jump_attack();
		
	}
}

void ACrunch::Play_meleeattack()
{
	auto animainstance = Cast<UCrunch_animinstance>(GetMesh()->GetAnimInstance());
	
	if (animainstance) {
		animainstance->Play_crunch_melee_attack();
		
	}

}

void ACrunch::Montage_ended(UAnimMontage* Montage, bool bInterrupted)
{
	dele_crunch_montage_ended.Broadcast();
}



// Called when the game starts or when spawned
void ACrunch::BeginPlay()
{
	Super::BeginPlay();
	auto animainstance = Cast<UCrunch_animinstance>(GetMesh()->GetAnimInstance());
	animainstance->OnMontageEnded.AddDynamic(this, &ACrunch::Montage_ended);

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("SEARCHING_POINT"), Actors);
	central_point = Cast<ATargetPoint>(Actors[0]);

	target_location = central_point->GetActorLocation();
}

// Called every frame
void ACrunch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACrunch::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACrunch::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
}

float ACrunch::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (DamageEvent.IsOfType(FPointDamageEvent::ClassID))
	{
		const auto pointDamageEvent = (FPointDamageEvent*)&DamageEvent;
		FHitResult result = pointDamageEvent->HitInfo;
		
		//UGameplayStatics::SpawnEmitterAttached(hited_vfx, GetMesh(), result.BoneName , result.Location, FRotator::ZeroRotator, FVector(1.0f, 1.0f, 1.0f));
		//UE_LOG(LogTemp, Warning, TEXT("crunch hited bone : %s"),*result.BoneName.ToString());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), hited_sfx, result.ImpactPoint);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hited_vfx, result.ImpactPoint, FRotator::ZeroRotator, FVector(1.0f, 1.0f, 1.0f),true);
		UE_LOG(LogTemp, Warning, TEXT("crunch point hited"));
		hp -= DamageAmount;
		//const FPointDamageEvent* PointDamageEvent = static_cast<const FPointDamageEvent*>(&DamageEvent);
	
	}

	if (hp <= 0) {
		GetMesh()->SetSimulatePhysics(true);
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
	}

	//UE_LOG(LogTemp, Warning, TEXT("crunch hited"));

	return Damage;
}

