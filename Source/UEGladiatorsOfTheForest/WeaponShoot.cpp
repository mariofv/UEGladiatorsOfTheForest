#include "WeaponShoot.h"

#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeaponShoot::AWeaponShoot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	m_ShootSound = CreateDefaultSubobject<UAudioComponent>(TEXT("ShootSound"));
	m_ShootSound->SetupAttachment(RootComponent);

	m_ShootMuzzleFire = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ShootMuzzleFire"));
	m_ShootMuzzleFire->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWeaponShoot::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeaponShoot::Tick(float DeltaTime)
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

void AWeaponShoot::Shoot()
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
void AWeaponShoot::HitActor(AActor* p_Actor)
{
	FDamageEvent shootDamageEvent;
	p_Actor->TakeDamage(k_ShootDamage, shootDamageEvent, m_OwnerAIController, this);
}

void AWeaponShoot::MissShoot()
{
	DrawDebugLine
	(
		GetWorld(),
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * 1000.f,
		FColor::Red,
		true
	);
}

AAIController* AWeaponShoot::SetOwnerAIController(AAIController* p_OwnerAIController)
{
	m_OwnerAIController = p_OwnerAIController;
	m_OwnerPerceptionController = 
		static_cast<UAIPerceptionComponent*>(m_OwnerAIController->GetPawn()->GetComponentByClass(UAIPerceptionComponent::StaticClass()));

	return m_OwnerAIController;
}

