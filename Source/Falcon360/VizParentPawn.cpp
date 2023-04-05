// Fill out your copyright notice in the Description page of Project Settings.


#include "VizParentPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Turret.h"

// Sets default values
AVizParentPawn::AVizParentPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

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
		EnhancedInputComponent->BindAction(RightShootAction, ETriggerEvent::Started, this, &AVizParentPawn::ShootRight);
	}
}

void AVizParentPawn::RotatePlayer(const FInputActionValue& Value)
{
	AddControllerYawInput(Value.Get<float>());
}

void AVizParentPawn::ShootLeft()
{
	TurretComponent->Shoot(LeftBlaster->GetComponentLocation(), LeftBlaster->GetComponentRotation());
}

void AVizParentPawn::ShootRight()
{
	TurretComponent->Shoot(RightBlaster->GetComponentLocation(), RightBlaster->GetComponentRotation());
}



