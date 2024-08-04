// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"


class USkeletalMesh;
class UAnimMontage;

USTRUCT(BlueprintType)
struct FSoldierMeshRow : public FTableRowBase {

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = mesh)
	TObjectPtr<USkeletalMesh> soldier_sk;

};

USTRUCT(BlueprintType)
struct FSoldierMontageRow : public FTableRowBase {

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = montage)
	TObjectPtr<UAnimMontage> fire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = montage)
	TObjectPtr<UAnimMontage> reload;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = montage)
	TObjectPtr<UAnimMontage> reload_empty;
};


UENUM(BlueprintType)
enum class EWeaponClass : uint8
{
	E_AR_01 = 0 UMETA(DisplayName = "AR_01"),
	E_AR_03 UMETA(DisplayName = "AR_02")

};

UENUM(BlueprintType)
enum class EShootType : uint8
{
	E_SINGLE = 0 UMETA(DisplayName = "Single"),
	E_AUTO UMETA(DisplayName = "Auto")

};

UENUM(BlueprintType)
enum class EPalain_mode : uint8 
{
	E_SLEEP=0 UMETA(DisplayName="sleep"),
	E_ACTIVE UMETA(DisplayName="active")

};

UCLASS()
class THE_GUARDIAN_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
