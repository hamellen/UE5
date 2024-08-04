// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_01.h"
#include "AR_01_animinstance.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"

AAR_01::AAR_01() {

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>MAIN(TEXT("/Script/Engine.SkeletalMesh'/Game/AnimatedLowPolyWeapons/Art/Weapons/ARs/SK_AR_01.SK_AR_01'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>GRIP(TEXT("/Script/Engine.StaticMesh'/Game/AnimatedLowPolyWeapons/Art/Weapons/_Common/Attachments/Models/SM_ATT_Grip_01.SM_ATT_Grip_01'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MAGAZINE(TEXT("/Script/Engine.StaticMesh'/Game/AnimatedLowPolyWeapons/Art/Weapons/ARs/SM_AR_01_Magazine_Default.SM_AR_01_Magazine_Default'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SCOPE(TEXT("/Script/Engine.StaticMesh'/Game/AnimatedLowPolyWeapons/Art/Weapons/ARs/SM_AR_01_Scope_Default.SM_AR_01_Scope_Default'"));

	static ConstructorHelpers::FObjectFinder<USoundWave>FIRE(TEXT("/Script/Engine.SoundWave'/Game/Gun_Combat_SFX/WAVS/Rifle_Shot_1_Wav.Rifle_Shot_1_Wav'"));
	static ConstructorHelpers::FObjectFinder<USoundWave>MAGAZINE_IN(TEXT("/Script/Engine.SoundWave'/Game/Gun_Combat_SFX/WAVS/Gun_Load_6_Wav.Gun_Load_6_Wav'"));
	static ConstructorHelpers::FObjectFinder<USoundWave>MAGAZINE_OUT(TEXT("/Script/Engine.SoundWave'/Game/Gun_Combat_SFX/WAVS/Generic_Reload_Wav.Generic_Reload_Wav'"));
	static ConstructorHelpers::FObjectFinder<USoundWave>STICK(TEXT("/Script/Engine.SoundWave'/Game/Gun_Combat_SFX/WAVS/Gun_Load_2_Wav.Gun_Load_2_Wav'"));
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem>FIRE_VFX(TEXT("/Script/Niagara.NiagaraSystem'/Game/sA_Megapack_v1/sA_ShootingVfxPack/FX/NiagaraSystems/NS_AR_Muzzleflash_1_ONCE.NS_AR_Muzzleflash_1_ONCE'"));





	grip_socket = TEXT("socket_grip");
	magazine_socket = TEXT("socket_magazine");
	scope_socket = TEXT("socket_scope");
	muzzle_socket = TEXT("socket_muzzle");
	gun_damage = 20.f;
	max_ammo = 30;
	current_ammo = max_ammo;
	launch_interval = 0.15f;
	
	main_part = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MAIN_PART"));
	grip = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GRIP"));
	magazine = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MAGAZINE"));
	scope = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SCOPE"));

	if (MAIN.Succeeded()) {
		main_part->SetSkeletalMesh(MAIN.Object);
	}
	if (GRIP.Succeeded()) {
		grip->SetStaticMesh(GRIP.Object);
		grip->SetupAttachment(main_part, grip_socket);
	}
	if (MAGAZINE.Succeeded()) {
		magazine->SetStaticMesh(MAGAZINE.Object);
		magazine->SetupAttachment(main_part, magazine_socket);
	}
	if (SCOPE.Succeeded()) {
		scope->SetStaticMesh(SCOPE.Object);
		scope->SetupAttachment(main_part, scope_socket);
	}

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
	if (FIRE_VFX.Succeeded()) {
		fire_vfx = FIRE_VFX.Object;
	}
}

void AAR_01::Reload()
{
	auto animinstance = Cast<UAR_01_animinstance>(main_part->GetAnimInstance());

	if (current_ammo > 0) {
		animinstance->Play_reload();
		UE_LOG(LogTemp, Warning, TEXT("ar _01_reload_animation_playing"));
	}
	else {
		animinstance->Play_reload_empty();
		
	}

}



void AAR_01::Fire(FVector endpoint)
{
	auto animinstance = Cast<UAR_01_animinstance>(main_part->GetAnimInstance());
	//UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), fire_vfx, FVector(0, 0, 0));
	gun_muzzle_location = main_part->GetSocketLocation(muzzle_socket);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), fire_sfx, gun_muzzle_location);
	gun_muzzle_rotation = main_part->GetSocketRotation(muzzle_socket);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), fire_vfx, gun_muzzle_location, gun_muzzle_rotation);
	gun_foward_vector = FRotationMatrix(gun_muzzle_rotation).GetUnitAxis(EAxis::X);

	FHitResult Hit;
	bool isColl = GetWorld()->LineTraceSingleByChannel(Hit, gun_muzzle_location, endpoint + gun_foward_vector * 100, ECC_GameTraceChannel1);
	//DrawDebugLine(GetWorld(), gun_muzzle_location, endpoint + gun_foward_vector * 100, FColor::Red, true);
	DrawDebugLine(GetWorld(), gun_muzzle_location, endpoint + gun_foward_vector * 100, FColor::Red, false,5.0f);
	if (isColl) {
		UE_LOG(LogTemp, Warning, TEXT("collision activeate"));
		//UGameplayStatics::ApplyDamage(Hit.GetActor(), gun_damage,nullptr, this, NULL);
		UGameplayStatics::ApplyPointDamage(Hit.GetActor(), gun_damage, Hit.GetActor()->GetActorLocation(), Hit,nullptr,this, NULL);
		
	}

	if (current_ammo > 0) {
		animinstance->Play_gun_fire();
		current_ammo--;
	}


}

void AAR_01::reset_gun_ammo()
{
	current_ammo = max_ammo;
}

void AAR_01::play_reload_sound(int index)
{
	//gun_reload_vector = main_part->GetSocketLocation(magazine_socket);

	switch (index)
	{
	case 1:
		UE_LOG(LogTemp, Warning, TEXT("magazine out"));
		//UGameplayStatics::SpawnSoundAttached(magazine_out, main_part->GetAttachmentRoot(), magazine_socket);
		//UGameplayStatics::PlaySoundAtLocation(GetWorld(), magazine_out, gun_reload_vector);
		break;
	case 2:
		UE_LOG(LogTemp, Warning, TEXT("magazine in"));
		//UGameplayStatics::SpawnSoundAttached(magazine_in, main_part->GetAttachmentRoot(), magazine_socket);
		//UGameplayStatics::PlaySoundAtLocation(GetWorld(), magazine_in, gun_reload_vector);
		break;

	case 3:
		UE_LOG(LogTemp, Warning, TEXT("stick"));
		//UGameplayStatics::SpawnSoundAttached(stick, main_part->GetAttachmentRoot(),FName(TEXT("socket_eject")));
		//UGameplayStatics::PlaySoundAtLocation(GetWorld(), stick, main_part->GetSocketLocation(FName(TEXT("socket_eject"))));
		break;
	}
}
