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
	
protected:

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMesh = nullptr;

	UPROPERTY(EditDefaultsOnly)
	URadialForceComponent* ForceComp = nullptr;
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void Receive_Explode();

public:	

	virtual void Tick(float DeltaTime) override;

};
