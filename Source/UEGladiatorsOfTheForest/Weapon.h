#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Perception/AIPerceptionComponent.h"

#include "Weapon.generated.h"

UCLASS()
class UEGLADIATORSOFTHEFOREST_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
		
	UFUNCTION(BlueprintCallable) void Shoot();
	
	UFUNCTION(BlueprintCallable, Category = "Set") AAIController* SetOwnerAIController(AAIController* p_OwnerAIController);

private:
	void HitActor(AActor* p_Actor);
	void MissShoot();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) UParticleSystemComponent* m_ShootMuzzleFire;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) UAudioComponent* m_ShootSound;
	UPROPERTY(BlueprintReadWrite, Category = "Variables") AAIController* m_OwnerAIController;

private:
	UAIPerceptionComponent* m_OwnerPerceptionController;

private:
	const float k_ShootDamage = 5.f;

	bool m_HasShootRecently = false;
	float m_TimeUnitlShootVFXDeactivation = 0.f;
	const float k_ShootVFXTime = 1.f;

};
