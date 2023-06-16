#include "Components/SceneComponent.h"
#include "WeaponShoot.h"

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

	m_HasShootRecently = true;
	m_TimeUnitlShootVFXDeactivation = k_ShootVFXTime;
}

