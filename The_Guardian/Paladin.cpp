// Fill out your copyright notice in the Description page of Project Settings.


#include "Paladin.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Paladin_animinstance.h"
#include "crunch_rocket.h"
#include "Kismet/GameplayStatics.h"
#include "Paladin_animinstance.h"
#include "Engine/DamageEvents.h"
#include "Kismet/KismetMathLibrary.h"
#include "Paladin_animinstance.h"
// Sets default values
APaladin::APaladin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>PALADIN_SK(TEXT("/Script/Engine.SkeletalMesh'/Game/RoboDog/Robo_Dog/Meshes/SK_RoboDog_NoVT.SK_RoboDog_NoVT'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem>HITED_VFX(TEXT("/Script/Engine.ParticleSystem'/Game/Realistic_Starter_VFX_Pack_Vol2/Particles/Sparks/P_Sparks_C.P_Sparks_C'"));
	static ConstructorHelpers::FObjectFinder<USoundBase>HITED_SFX(TEXT("/Script/Engine.SoundWave'/Game/Gun_Combat_SFX/WAVS/Impact_Metal_Wav.Impact_Metal_Wav'"));
	static ConstructorHelpers::FObjectFinder<USoundBase>WAKE_SFX(TEXT("/Script/Engine.SoundWave'/Game/Monster/monster_sfx/mechanicalclamp-6217.mechanicalclamp-6217'"));
	static ConstructorHelpers::FClassFinder<Acrunch_rocket>BP_ROCKET(TEXT("/Script/Engine.Blueprint'/Game/rocket/rocket_2/BP_crunch_rocket.BP_crunch_rocket_C'"));
	if (PALADIN_SK.Succeeded()) {
		GetMesh()->SetSkeletalMesh(PALADIN_SK.Object);
	}
	
	if (HITED_SFX.Succeeded()) {
		hited_sfx = HITED_SFX.Object;
	}

	if (WAKE_SFX.Succeeded()) {
		wake_up = WAKE_SFX.Object;
	}

	if (HITED_VFX.Succeeded()) {
		hited_vfx = HITED_VFX.Object;
	}

	if (BP_ROCKET.Succeeded()) {
		rocket_class = BP_ROCKET.Class;
	}
	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f)
	);
	wakeup_figure = 10;
	hp = 10000;
	sensing_rad = 5000;
	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = false;
}

void APaladin::play_attack()
{
	auto animinstance = Cast<UPaladin_animinstance>(GetMesh()->GetAnimInstance());
	if (animinstance) {
		animinstance->Play_paladin_attack();
		UE_LOG(LogTemp, Error, TEXT("paladin attacked"));
		
		FVector location = GetMesh()->GetSocketLocation(FName(TEXT("Paladin_attack_start")));
		FRotator rotator = GetMesh()->GetSocketRotation(FName(TEXT("Paladin_attack_start")));
		auto rocket =GetWorld()->SpawnActor<Acrunch_rocket>(rocket_class, location, rotator);
		rocket->SetActorScale3D(FVector(0.5f));
	}
}

void APaladin::Montage_ended(UAnimMontage* Montage, bool bInterrupted)
{
	dele_paladin_montage_ended.Broadcast();
}

// Called when the game starts or when spawned
void APaladin::BeginPlay()
{
	Super::BeginPlay();
	
	auto animainstance = Cast<UPaladin_animinstance>(GetMesh()->GetAnimInstance());
	animainstance->OnMontageEnded.AddDynamic(this, &APaladin::Montage_ended);
	is_active = false;
}

// Called every frame
void APaladin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APaladin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float APaladin::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (DamageEvent.IsOfType(FPointDamageEvent::ClassID))
	{
		const auto pointDamageEvent = (FPointDamageEvent*)&DamageEvent;
		FHitResult result = pointDamageEvent->HitInfo;

		//UGameplayStatics::SpawnEmitterAttached(hited_vfx, GetMesh(), result.BoneName , result.Location, FRotator::ZeroRotator, FVector(1.0f, 1.0f, 1.0f));
		//UE_LOG(LogTemp, Warning, TEXT("crunch hited bone : %s"),*result.BoneName.ToString());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), hited_sfx, result.ImpactPoint);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hited_vfx, result.ImpactPoint, FRotator::ZeroRotator, FVector(1.0f, 1.0f, 1.0f), true);
		UE_LOG(LogTemp, Warning, TEXT("crunch point hited"));
		//const FPointDamageEvent* PointDamageEvent = static_cast<const FPointDamageEvent*>(&DamageEvent);

		switch (mode)
		{
		case EPalain_mode::E_SLEEP:

			//wakeup_figure--;

			if (wakeup_figure == 0) {
				auto animinstance = Cast<UPaladin_animinstance>(GetMesh()->GetAnimInstance());
				animinstance->wakeup();
				is_active = true;
				mode = EPalain_mode::E_ACTIVE;
				UGameplayStatics::PlaySoundAtLocation(GetWorld(),wake_up,GetActorLocation());
			}
			wakeup_figure--;
			break;
		case EPalain_mode::E_ACTIVE:

			hp -= DamageAmount;

			break;
		
		}

	}
	




	return Damage;
}

