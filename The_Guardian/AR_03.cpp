// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_03.h"
#include "AR_03_animinstance.h"

AAR_03::AAR_03() {

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>MAIN(TEXT("/Script/Engine.SkeletalMesh'/Game/AnimatedLowPolyWeapons/Art/Weapons/ARs/SK_AR_03.SK_AR_03'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>GRIP(TEXT("/Script/Engine.StaticMesh'/Game/AnimatedLowPolyWeapons/Art/Weapons/_Common/Attachments/Models/SM_ATT_Grip_01.SM_ATT_Grip_01'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MAGAZINE(TEXT("/Script/Engine.StaticMesh'/Game/AnimatedLowPolyWeapons/Art/Weapons/ARs/SM_AR_03_Magazine_Default.SM_AR_03_Magazine_Default'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SCOPE(TEXT("/Script/Engine.StaticMesh'/Game/AnimatedLowPolyWeapons/Art/Weapons/ARs/SM_AR_03_Scope_Default.SM_AR_03_Scope_Default'"));

	grip_socket = TEXT("socket_grip");
	magazine_socket = TEXT("socket_magazine");
	scope_socket = TEXT("socket_scope");


	max_ammo = 30;
	current_ammo = max_ammo;
	launch_interval = 0.1f;

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


}

void AAR_03::Reload()
{
	auto animinstance = Cast<UAR_03_animinstance>(main_part->GetAnimInstance());

	if (current_ammo > 0) {
		animinstance->Play_reload();
		UE_LOG(LogTemp, Warning, TEXT("ar _01_reload_animation_playing"));
	}
	else {
		animinstance->Play_reload_empty();

	}

}




void AAR_03::Fire(FVector endpoint)
{

	auto animinstance = Cast<UAR_03_animinstance>(main_part->GetAnimInstance());
	if (current_ammo > 0) {
		animinstance->Play_gun_fire();
		current_ammo--;
	}
}

void AAR_03::reset_gun_ammo()
{
	current_ammo = max_ammo;
}
