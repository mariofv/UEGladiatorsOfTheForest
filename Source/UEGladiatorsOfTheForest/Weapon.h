#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Perception/AIPerceptionComponent.h"

#include "Weapon.generated.h"

class AWeaponShootImpactPool;

UCLASS()
class UEGLADIATORSOFTHEFOREST_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	enum class WeaponState
	{
		Ready,
		Shooting,
		Empty,
	};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
		
	UFUNCTION(BlueprintCallable) bool Shoot();
	UFUNCTION(BlueprintCallable) void Reload();
	
	UFUNCTION(BlueprintCallable, Category = "Set") AAIController* SetOwnerAIController(AAIController* p_OwnerAIController);

private:
	void HitActor(AActor* p_Actor);
	void MissShoot();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components") UParticleSystemComponent* m_ShootMuzzleFire = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components") UAudioComponent* m_ShootSound = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components") UAudioComponent* m_ReloadSound = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components") UChildActorComponent* m_ShootImpactVFXPool = nullptr;
	UPROPERTY(BlueprintReadWrite, Category = "Variables") AAIController* m_OwnerAIController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") int m_BulletsInMagazine = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") int m_MagazineCapacity = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") float m_ReloadTime = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") float m_WeaponShootFrequency = 0.f;

private:
	UAIPerceptionComponent* m_OwnerPerceptionController = nullptr; 
	AWeaponShootImpactPool* m_ShootImpactPool = nullptr;

private:
	WeaponState m_WeaponState = WeaponState::Ready;
	float m_CurrentStateTime = 0.f;

	const float k_ShootDamage = 5.f;
	const float k_ShootHitProbability = 0.6f;

	bool m_HasToDeactivateVFX = false;
	float m_TimeUnitlShootVFXDeactivation = 0.f;
	const float k_ShootVFXTime = 1.f;

};
