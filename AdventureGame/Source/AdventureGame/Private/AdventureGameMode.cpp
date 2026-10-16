#include "AdventureGameMode.h"

void AAdventureGameMode::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Hello World!"));
	UE_LOG(LogTemp, Display, TEXT("This is a warning message!"));
}