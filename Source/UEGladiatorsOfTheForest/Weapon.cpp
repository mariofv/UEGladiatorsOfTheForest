#include "Weapon.h"

#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "WeaponShootImpactPool.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	m_ShootSound = CreateDefaultSubobject<UAudioComponent>(TEXT("ShootSound"));
	m_ShootSound->SetupAttachment(RootComponent);

	m_ShootMuzzleFire = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ShootMuzzleFire"));
	m_ShootMuzzleFire->SetupAttachment(RootComponent);

	m_ShootImpactVFXPool = CreateDefaultSubobject<UChildActorComponent>(TEXT("ShootImpactVFXPool"));
	m_ShootImpactVFXPool->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	m_ShootImpactPool = static_cast<AWeaponShootImpactPool*>(m_ShootImpactVFXPool->GetChildActor());
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_HasShootRecently)
	{
		m_TimeUnitlShootVFXDeactivation -= DeltaTime;
		if (m_TimeUnitlShootVFXDeactivation <= 0.f)
		{
			m_ShootMuzzleFire->Deactivate();
			m_HasShootRecently = false;
		}
	}

}

void AWeapon::Shoot()
{
	m_ShootSound->Play();
	m_ShootMuzzleFire->Activate();

	TArray<AActor*> percivedActors;
	m_OwnerPerceptionController->GetKnownPerceivedActors(TSubclassOf<UAISense>(), percivedActors);
	verify(percivedActors.Num() <= 1);
	if (percivedActors.IsEmpty())
	{
		MissShoot();
	}
	else
	{
		HitActor(percivedActors[0]);
	}

	m_HasShootRecently = true;
	m_TimeUnitlShootVFXDeactivation = k_ShootVFXTime;
}
void AWeapon::HitActor(AActor* p_Actor)
{
	FVector shootDirection = p_Actor->GetActorLocation() - GetActorLocation();
	FDamageEvent shootDamageEvent;
	p_Actor->TakeDamage(k_ShootDamage, shootDamageEvent, m_OwnerAIController, this);
	m_ShootImpactPool->SpawnImpact(WeaponShootImpactType::Blood, p_Actor->GetTargetLocation(), shootDirection.Rotation());
}

void AWeapon::MissShoot()
{
	FVector shootDirection = GetActorForwardVector();

	FHitResult hit;
	bool hasHit = GetWorld()->LineTraceSingleByChannel(hit, GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 1000.f, ECC_Pawn);
	DrawDebugLine
	(
		GetWorld(),
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * 1000.f,
		FColor::Red,
		true
	);

	if (hasHit && hit.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit the actor %s"), *hit.GetActor()->GetName())
	}
}

AAIController* AWeapon::SetOwnerAIController(AAIController* p_OwnerAIController)
{
	m_OwnerAIController = p_OwnerAIController;
	m_OwnerPerceptionController = 
		static_cast<UAIPerceptionComponent*>(m_OwnerAIController->GetPawn()->GetComponentByClass(UAIPerceptionComponent::StaticClass()));

	return m_OwnerAIController;
}

