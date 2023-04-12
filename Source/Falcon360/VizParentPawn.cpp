// Fill out your copyright notice in the Description page of Project Settings.


#include "VizParentPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Turret.h"
#include "Components/BoxComponent.h"

// Sets default values
AVizParentPawn::AVizParentPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	LaserHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit Box"));
	LaserHitBox->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(RootComponent);

	TurretComponent = CreateDefaultSubobject<UTurret>(TEXT("Turret"));

	LeftBlaster = CreateDefaultSubobject<USceneComponent>(TEXT("Left Blaster"));
	LeftBlaster->SetupAttachment(TurretMesh);

	RightBlaster = CreateDefaultSubobject<USceneComponent>(TEXT("Right Blaster"));
	RightBlaster->SetupAttachment(TurretMesh);
}

// Called when the game starts or when spawned
void AVizParentPawn::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	TurretComponent->SetTurretInfo(BlasterInfo, LeftBlaster, RightBlaster);
	Health = MaxHealth;
	Shield = MaxShield;
}

// Called every frame
void AVizParentPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVizParentPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &AVizParentPawn::RotatePlayer);
		EnhancedInputComponent->BindAction(LeftShootAction, ETriggerEvent::Triggered, this, &AVizParentPawn::ShootLeft);
		EnhancedInputComponent->BindAction(RightShootAction, ETriggerEvent::Triggered, this, &AVizParentPawn::ShootRight);
	}
}

float AVizParentPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	float Remaining = FMath::Clamp(DamageAmount - Shield, 0, DamageAmount);
	Shield = FMath::Clamp(Shield - DamageAmount, 0, MaxShield);
	float FinalRemaining = FMath::Clamp(Remaining - Health, 0, Remaining);
	Health = FMath::Clamp(Health - Remaining, 0, MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("Health: %d Shield: %d"), Health, Shield);
	if (Health < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Dead"));
	}
	return Health;
}

void AVizParentPawn::RotatePlayer(const FInputActionValue& Value)
{
	AddControllerYawInput(Value.Get<float>());
}

void AVizParentPawn::ShootLeft()
{
	TurretComponent->Shoot(true);
}

void AVizParentPawn::ShootRight()
{
	TurretComponent->Shoot(false);
}



