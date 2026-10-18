#pragma once

#include "CoreMinimal.h"
#include "Pickups/EquippableToolBase.h"
#include "DartLauncher.generated.h"

class AFirstPersonProjectile;

UCLASS(BlueprintType, Blueprintable)
class ADVENTUREGAME_API ADartLauncher : public AEquippableToolBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Dart Launcher | Projectile")
	TSubclassOf<AFirstPersonProjectile> ProjectileClass;


	virtual void Use() override;

	virtual void BindInputAction(const UInputAction* InputToBind) override;
};
