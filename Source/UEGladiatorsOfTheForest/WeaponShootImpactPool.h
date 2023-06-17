

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponShootImpactPool.generated.h"


UENUM(BlueprintType)
enum class WeaponShootImpactType : uint8
{
	Blood,
	Concrete
};

UCLASS()
class UEGLADIATORSOFTHEFOREST_API AWeaponShootImpactPool : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponShootImpactPool();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void SpawnImpact(WeaponShootImpactType p_ImpactType, const FVector& p_ImpactLocation, const FRotator& p_ImpactDirection);

};