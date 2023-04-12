// Fill out your copyright notice in the Description page of Project Settings.


#include "Laser.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Falcon360GameModeBase.h"
#include "Kismet/GameplayStatics.h"

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
	LaserCollider->SetCollisionObjectType(GameModeBase->GetCollisionChannel(LaserName));
	GetWorld()->GetTimerManager().SetTimer(LifetimeTimerHandle, this, &ALaser::DestroyLaser,
		GameModeBase->GetTime(LaserName), true);
	LaserCollider->OnComponentBeginOverlap.AddDynamic(this, &ALaser::OnLaserOverlap);
}

void ALaser::SetLaserType(FName LaserName, FVector InitialVelocity)
{
	SetLaserType(LaserName);
	ProjectileMovementComponent->Velocity = GameModeBase->GetSpeed(LaserName) * GetActorForwardVector() + InitialVelocity;
}

void ALaser::OnLaserOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		OtherActor->Destroy();
	}
	Destroy();
}

void ALaser::DestroyLaser()
{
	Destroy();
}

