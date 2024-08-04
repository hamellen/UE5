// Fill out your copyright notice in the Description page of Project Settings.


#include "crunch_rocket.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
// Sets default values
Acrunch_rocket::Acrunch_rocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>ROCKET(TEXT("/Script/Engine.StaticMesh'/Game/rocket/rocket_2/rocket.rocket'"));
	static ConstructorHelpers::FObjectFinder<USoundWave>FIRE_SFX(TEXT("/Script/Engine.SoundWave'/Game/Gun_Combat_SFX/WAVS/CannonGun_Shot_Variation_03_Wav.CannonGun_Shot_Variation_03_Wav'"));
	static ConstructorHelpers::FObjectFinder<USoundWave>EXPLOSION_SFX(TEXT("/Script/Engine.SoundWave'/Game/Gun_Combat_SFX/WAVS/Impact_Explosion_Sound_01_Wav.Impact_Explosion_Sound_01_Wav'"));
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem>FIRE_VFX(TEXT("/Script/Niagara.NiagaraSystem'/Game/sA_Megapack_v1/sA_ShootingVfxPack/FX/NiagaraSystems/NS_ROCKET_Muzzle.NS_ROCKET_Muzzle'"));
	//static ConstructorHelpers::FObjectFinder<UNiagaraSystem>CLUSTER_VFX(TEXT("/Script/Niagara.NiagaraSystem'/Game/sA_Megapack_v1/sA_Projectilevfx/Vfx/Fx/Niagara_Systems/NS_Projectile2_Small.NS_Projectile2_Small'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem>EXPLOSION_VFX(TEXT("/Script/Engine.ParticleSystem'/Game/Realistic_Starter_VFX_Pack_Vol2/Particles/Explosion/P_Explosion_Big_B.P_Explosion_Big_B'"));

	capsule= CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	rocket_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ROCKET"));
	cluster_component = CreateDefaultSubobject<UNiagaraComponent>(TEXT("CLUSTER"));
	projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("PROJECTILE"));
	RootComponent = capsule;
	capsule->SetCapsuleSize(60.f,420.f);
	rocket_mesh->SetupAttachment(capsule);
	rocket_mesh->SetRelativeLocation(FVector(0.f,0.f,-350.f));
	cluster_component->SetupAttachment(rocket_mesh);
	if (ROCKET.Succeeded()) {
		rocket_mesh->SetStaticMesh(ROCKET.Object);
	}
	if (FIRE_SFX.Succeeded()) {
		rocket_fire_sfx=FIRE_SFX.Object;
	}
	if (EXPLOSION_SFX.Succeeded()) {
		rocket_explosion_sfx = EXPLOSION_SFX.Object;
	}
	if (FIRE_VFX.Succeeded()) {
		fire_vfx = FIRE_VFX.Object;
	}
	/*if (CLUSTER_VFX.Succeeded()) {
		cluster_vfx = CLUSTER_VFX.Object;
	}*/
	if (EXPLOSION_VFX.Succeeded()) {
		explosion_vfx = EXPLOSION_VFX.Object;
	}
	explosion_size = 2.f;
	volume = 3.0f;
	base_damage = 100.f;
}

void Acrunch_rocket::OnAttackHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), rocket_explosion_sfx, NormalImpulse, volume);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosion_vfx, Hit.ImpactPoint, FRotator::ZeroRotator, FVector(explosion_size, explosion_size, explosion_size), true);
	UGameplayStatics::ApplyRadialDamage(GetWorld(), base_damage, Hit.ImpactPoint, 500.f, NULL, TArray<AActor*>(), this, nullptr);
	Destroy();
}

// Called when the game starts or when spawned
void Acrunch_rocket::BeginPlay()
{
	Super::BeginPlay();
	
	//UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), fire_vfx, GetActorLocation(), FRotator::ZeroRotator);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), rocket_fire_sfx, GetActorLocation(), volume);
	capsule->OnComponentHit.AddDynamic(this, &Acrunch_rocket::OnAttackHit);
}

// Called every frame
void Acrunch_rocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

