// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "MonsterAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "Playerable_char.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Monster_AIController.h"
//#include "Components/SceneComponent.h"
// Sets default values
AMonster::AMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f)
	);
	//Is_Attack = false;
	sound_monster_attack= LoadObject<USoundWave>(nullptr, TEXT("SoundWave'/Game/SFX/hit-swing-sword-small-2-95566.hit-swing-sword-small-2-95566'"));
	//auto AnimInstance = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	//AnimInstance->OnMontageEnded.AddDynamic(this, &AMonster::stop_mode);//문제 덩어리 
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK(TEXT("SkeletalMesh'/Game/Monster/Mesh/SKM_Monster.SKM_Monster'"));

	/*if (SK.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SK.Object);
	}*/

	hited_damage = 15.f;
	attack_damage = 3.f;
	monster_hp = 100.f;
}

void AMonster::MonsterAttack()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);


	auto animinstance = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	if (animinstance) {
		animinstance->PlayMonsterMontage();
	}
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * 100.f,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(30.f),
		Params
	);

	UGameplayStatics::PlaySound2D(GetWorld(), sound_monster_attack);

	/*FVector TraceVec = GetActorForwardVector() * 100.f;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = 100.f * 0.5f + 30.f;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 3.0f;

	DrawDebugCapsule
	(
		GetWorld(),
		Center,
		HalfHeight,
		30.f,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime
	);*/



	if (bResult && HitResult.GetActor()) {//플레이어 체력 깍이는 코드 작성
		UE_LOG(LogTemp, Warning, TEXT(" monster player detected"));
		auto player = Cast<APlayerable_char>(HitResult.GetActor());
		if (player) {
			player->player_hited(attack_damage);
		}
	}
	
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMonster::Counter_Attack(FVector start, FVector target)//반격 코드 작성
{
	AAIController* AI_C = UAIBlueprintHelperLibrary::GetAIController(this);

	auto monster_ai = Cast<AMonster_AIController>(AI_C);
	monster_ai->activate_counter();


	//UKismetMathLibrary::FindLookAtRotation(start, target);

	FRotator normal = FRotator(GetActorRotation().Pitch, UKismetMathLibrary::FindLookAtRotation(start, target).Yaw, GetActorRotation().Roll);
	
	SetActorRelativeRotation(normal);

	//USceneComponent::SetWorldRotation(normal);
	MonsterAttack();

	
}

void AMonster::Monster_Hited()//몬스터 피격시 
{
	monster_hp -= hited_damage;

	if (monster_hp <= 0) {
		auto animinstance = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
		animinstance->monster_dead = true;
		SetActorEnableCollision(false);
	
	}
}

void AMonster::stop_mode(UAnimMontage* Montage, bool bInterrupted)//애님 인스턴스에서 델리게이트로 
{
	AAIController* AI_C= UAIBlueprintHelperLibrary::GetAIController(this);

	auto monster_ai = Cast<AMonster_AIController>(AI_C);
	monster_ai->Reset_mode();
}



// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}





void AMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

//void AMonster::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
//{
//
//}





