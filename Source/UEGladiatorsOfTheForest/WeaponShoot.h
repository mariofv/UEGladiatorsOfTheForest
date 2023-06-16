

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "WeaponShoot.generated.h"

UCLASS()
class UEGLADIATORSOFTHEFOREST_API AWeaponShoot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponShoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
		
	UFUNCTION(BlueprintCallable) void Shoot();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) UParticleSystemComponent* m_ShootMuzzleFire;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) UAudioComponent* m_ShootSound;

private:
	bool m_HasShootRecently = false;
	float m_TimeUnitlShootVFXDeactivation = 0.f;
	const float k_ShootVFXTime = 1.f;

};
