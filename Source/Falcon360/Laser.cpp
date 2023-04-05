// Fill out your copyright notice in the Description page of Project Settings.


#include "Laser.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Falcon360GameModeBase.h"

// Sets default values
ALaser::ALaser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	LaserComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Laser Component"));
	LaserComponent->SetupAttachment(RootComponent);

	LaserCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Laser Collider"));
	LaserCollider->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

}

// Called when the game starts or when spawned
void ALaser::BeginPlay()
{
	Super::BeginPlay();

	GameModeBase = Cast<AFalcon360GameModeBase>(GetWorld()->GetAuthGameMode());

}

// Called every frame
void ALaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALaser::SetLaserType(FName LaserName)
{
	LaserComponent->SetAsset(GameModeBase->GetNiagaraSystem(LaserName));
	Damage = GameModeBase->GetDamage(LaserName);
	ProjectileMovementComponent->Velocity =  GameModeBase->GetSpeed(LaserName) * GetActorForwardVector();
	GetWorld()->GetTimerManager().SetTimer(LifetimeTimerHandle, this, &ALaser::DestroyLaser,
		GameModeBase->GetTime(LaserName), true);
}

void ALaser::DestroyLaser()
{
	Destroy();
}

