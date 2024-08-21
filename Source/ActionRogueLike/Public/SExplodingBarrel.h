#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SExplodingBarrel.generated.h"

class UStaticMeshComponent;
class URadialForceComponent;

UCLASS(BlueprintType,Blueprintable)
class ACTIONROGUELIKE_API ASExplodingBarrel : public AActor
{
	GENERATED_BODY()
	
public:	

	ASExplodingBarrel();

	UFUNCTION(BlueprintCallable)
	void Explode();
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
protected:
	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void Receive_Explode();
	
protected:

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> StaticMesh = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<URadialForceComponent> ForceComp = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float Damage = 30.0f;
};
