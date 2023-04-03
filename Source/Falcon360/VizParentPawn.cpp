// Fill out your copyright notice in the Description page of Project Settings.


#include "VizParentPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
AVizParentPawn::AVizParentPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(RootComponent);
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
		EnhancedInputComponent->BindAction(LeftShootAction, ETriggerEvent::Triggered, this, &AVizParentPawn::ShootLeft);
		EnhancedInputComponent->BindAction(RightShootAction, ETriggerEvent::Triggered, this, &AVizParentPawn::ShootRight);
	}
}

void AVizParentPawn::RotatePlayer(const FInputActionValue& Value)
{
	AddControllerYawInput(Value.Get<float>());
}

void AVizParentPawn::ShootLeft()
{
	//UE_LOG(LogTemp, Warning, TEXT("Left"));
}

void AVizParentPawn::ShootRight()
{
	//UE_LOG(LogTemp, Warning, TEXT("Right"));
}



