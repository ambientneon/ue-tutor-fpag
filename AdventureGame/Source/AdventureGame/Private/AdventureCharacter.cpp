#include "AdventureCharacter.h"

AAdventureCharacter::AAdventureCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	InitializeMeshes();
	InitializeCamera();
}

void AAdventureCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!ensure(GEngine)) { return; }
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using AdventureCharacter."));

	SetupMeshes();
	SetupAnimations();

	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (!ensure(PlayerController)) { return; }

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (!ensure(Subsystem)) { return; }

	Subsystem->AddMappingContext(FirstPersonContext, 0);
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


// private
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