// Fill out your copyright notice in the Description page of Project Settings.


#include "VizParentPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "StructClass.h"
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
	FireRate = BlasterInfo.DataTable->FindRow<FBlasters>(BlasterInfo.RowName, "")->FireRate;
	TurretComponent->SetTurretInfo(BlasterInfo, {LeftBlaster}, { RightBlaster });
	Health = MaxHealth;
	Shield = MaxShield;
	BlasterInfos.Add(FBlasterInfo());
	BlasterInfos[0].PtrFunction = &AVizParentPawn::ShootLeft;
	BlasterInfos.Add(FBlasterInfo());
	BlasterInfos[1].PtrFunction = &AVizParentPawn::ShootLeft;
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
		EnhancedInputComponent->BindAction(LeftShootAction, ETriggerEvent::Started, this, &AVizParentPawn::ShootLeft);
		EnhancedInputComponent->BindAction(LeftShootAction, ETriggerEvent::Completed, this, &AVizParentPawn::StopShootingLeft);
		EnhancedInputComponent->BindAction(RightShootAction, ETriggerEvent::Started, this, &AVizParentPawn::ShootRight);
		EnhancedInputComponent->BindAction(RightShootAction, ETriggerEvent::Completed, this, &AVizParentPawn::StopShootingRight);
	}
}

float AVizParentPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	float Remaining = FMath::Clamp(DamageAmount - Shield, 0, DamageAmount);
	Shield = FMath::Clamp(Shield - DamageAmount, 0, MaxShield);
	float FinalRemaining = FMath::Clamp(Remaining - Health, 0, Remaining);
	Health = FMath::Clamp(Health - Remaining, 0, MaxHealth);
	if (Health <= 0)
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
	BlasterInfos[0].bShooting = true;
	TimerDelegate.BindUFunction(this, "ContinueShooting", 0);
	GetWorld()->GetTimerManager().SetTimer(BlasterInfos[0].TimerHandle, TimerDelegate, FireRate, false);
}

void AVizParentPawn::StopShootingLeft()
{
	BlasterInfos[0].bShooting = false;
}

void AVizParentPawn::ShootRight()
{
	TurretComponent->Shoot(false);
	BlasterInfos[1].bShooting = true;
	TimerDelegate.BindUFunction(this, "ContinueShooting", 1);
	GetWorld()->GetTimerManager().SetTimer(BlasterInfos[1].TimerHandle, TimerDelegate, FireRate, false);
}

void AVizParentPawn::StopShootingRight()
{
	BlasterInfos[1].bShooting = false;
}

void AVizParentPawn::ContinueShooting(int i)
{
	if (BlasterInfos[i].bShooting)
	{
		(this->*BlasterInfos[i].PtrFunction)();
	}
}



