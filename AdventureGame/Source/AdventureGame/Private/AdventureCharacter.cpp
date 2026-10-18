#include "AdventureCharacter.h"
#include "Components/InventoryComponent.h"
#include "Data/EquippableToolDefinition.h"
#include "Pickups/EquippableToolBase.h"

#pragma region Public
AAdventureCharacter::AAdventureCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	InitializeMeshes();
	InitializeCamera();

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

void AAdventureCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAdventureCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAdventureCharacter::Move);

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAdventureCharacter::Look);
}

void AAdventureCharacter::Move(const FInputActionValue& Value)
{
	if (!Controller) { return; }
	const FVector2D MovementValue = Value.Get<FVector2D>();

	const FVector Right = GetActorRightVector();
	AddMovementInput(Right, MovementValue.X);

	const FVector Forward = GetActorForwardVector();
	AddMovementInput(Forward, MovementValue.Y);
}

void AAdventureCharacter::Look(const FInputActionValue& Value)
{
	if (!Controller) { return; }
	const FVector2D LookAxisValue = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisValue.X);
	AddControllerPitchInput(LookAxisValue.Y);
}

bool AAdventureCharacter::IsToolAlreadyOwned(UEquippableToolDefinition* ToolDefinition)
{
	for (UEquippableToolDefinition* InventoryItem : InventoryComponent->ToolInventory)
	{
		if (ToolDefinition->ID == InventoryItem->ID) { 
			return true; 
		}
	}

	return false;
}

void AAdventureCharacter::AttachTool(UEquippableToolDefinition* ToolDefinition)
{
	if (!IsToolAlreadyOwned(ToolDefinition))
	{
		AEquippableToolBase* ToolToEquip = GetWorld()->SpawnActor<AEquippableToolBase>(ToolDefinition->ToolAsset, this->GetActorTransform());

		// Attach the tool to the First Person Character
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);

		// Attach the tool to this character, and then the right hand of their first-person mesh
		ToolToEquip->AttachToActor(this, AttachmentRules);
		ToolToEquip->AttachToComponent(FirstPersonMeshComponent, AttachmentRules, FName(TEXT("HandGrip_R")));

		// Set the animations on the character's meshes.
		if (ensure(ToolToEquip->FirstPersonToolAnimClass))
		{
			FirstPersonMeshComponent->SetAnimInstanceClass(ToolToEquip->FirstPersonToolAnimClass);
		}
		if (ensure(ToolToEquip->ThirdPersonToolAnimClass))
		{
			GetMesh()->SetAnimInstanceClass(ToolToEquip->ThirdPersonToolAnimClass);
		}

		InventoryComponent->ToolInventory.Add(ToolDefinition);
		ToolToEquip->OwningCharacter = this;
		EquippedTool = ToolToEquip;

		APlayerController* PlayerController = Cast<APlayerController>(Controller);
		if (!ensure(PlayerController)) { return; }

		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (!ensure(Subsystem)) { return; }
		if (!ensure(UseAction)) { return; }

		Subsystem->AddMappingContext(ToolToEquip->ToolMappingContext, 1);
		ToolToEquip->BindInputAction(UseAction);
	}
}

void AAdventureCharacter::GiveItem(UItemDefinition* ItemDefinition)
{
	switch (ItemDefinition->ItemType)
	{
		case EItemType::Tool:
		{
			UEquippableToolDefinition* ToolDefinition = Cast<UEquippableToolDefinition>(ItemDefinition);
			if (!ToolDefinition) { break; }

			AttachTool(ToolDefinition);
			break;
		}
		case EItemType::Consumable:
		{ break; }

		default:
		{ break; }
	}
}

FVector AAdventureCharacter::GetCameraTargetLocation()
{
	FVector TargetPosition;
	const UWorld* World = GetWorld();
	if (!World) { return TargetPosition; }

	FHitResult HitResult;

	// simulate a line trace from the character along the vector they are looking down
	const FVector TraceStart = FirstPersonCameraComponent->GetComponentLocation();
	const FVector TraceEnd = TraceStart + FirstPersonCameraComponent->GetForwardVector() * 10000.f;

	// simulate a line trace and result in hit
	World->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);

	// if the trace made a blocking hit, use the impact point as the target; otherwise, use the end point of trace
	TargetPosition = HitResult.bBlockingHit ? HitResult.ImpactPoint : HitResult.TraceEnd;

	return TargetPosition;
}
#pragma endregion

#pragma region Protected
void AAdventureCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!ensure(GEngine)) { return; }
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using AdventureCharacter."));

	SetupAnimations();
	SetupMeshes();

	FirstPersonCameraComponent->SetRelativeLocation(FVector(2.8f, 5.9f, 0.0f));

	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (!ensure(PlayerController)) { return; }

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (!ensure(Subsystem)) { return; }

	Subsystem->AddMappingContext(FirstPersonContext, 0);
}
#pragma endregion

#pragma region Private
void AAdventureCharacter::InitializeMeshes()
{
	FirstPersonMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	if (!ensure(FirstPersonMeshComponent)) { return; }
	if (!ensure(GetMesh())) { return; }

	FirstPersonMeshComponent->SetupAttachment(GetMesh());
	FirstPersonMeshComponent->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	FirstPersonMeshComponent->SetCollisionProfileName(FName("NoCollision"));

	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;
}

void AAdventureCharacter::InitializeCamera()
{
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	if (!ensure(FirstPersonCameraComponent)) { return; }

	FirstPersonCameraComponent->SetupAttachment(FirstPersonMeshComponent, FName("head"));

	// Position the camera slightly above the eyes and rotate it to behind the player's head
	FirstPersonCameraComponent->SetRelativeLocationAndRotation(FirstPersonCameraOffset, FRotator(0.0f, 90.0f, -90.0f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Enable first-person rendering on the camera and set default FOV and scale values
	FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
	FirstPersonCameraComponent->bEnableFirstPersonScale = true;
	FirstPersonCameraComponent->FirstPersonFieldOfView = FirstPersonFieldOfView;
	FirstPersonCameraComponent->FirstPersonScale = FirstPersonScale;
}

void AAdventureCharacter::SetupMeshes()
{
	if (!ensure(FirstPersonMeshComponent)) { return; }
	if (!ensure(GetMesh())) { return; }

	// only the owning player sees the first-person mesh
	FirstPersonMeshComponent->SetOnlyOwnerSee(true);

	// hide the 3rd-person mesh from the owning player
	GetMesh()->SetOwnerNoSee(true);

	// make the 3rd-person mesh cast a shadow
	GetMesh()->CastShadow = true;
	GetMesh()->bCastHiddenShadow = true;
}

void AAdventureCharacter::SetupAnimations()
{
	if (!ensure(FirstPersonDefaultAnimationClass)) { return; }
	if (!ensure(FirstPersonMeshComponent)) { return; }
	if (!ensure(GetMesh())) { return; }

	FirstPersonMeshComponent->SetAnimInstanceClass(FirstPersonDefaultAnimationClass);
	GetMesh()->SetAnimInstanceClass(FirstPersonDefaultAnimationClass);
}
#pragma endregion