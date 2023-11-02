// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "CharacterTopDown.generated.h"

class UHealthComponent;
class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class SAVAGETEST_API ACharacterTopDown : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterTopDown();

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HealthWidgetComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* InputMove;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* InputShoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float fireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float fireRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
	TEnumAsByte<ETraceTypeQuery> MousePosLayerMask;

	UPROPERTY(EditDefaultsOnly, Category = "Shoot")
	UNiagaraSystem* niagaraSmoke;
	UNiagaraComponent* smoke;

	UPROPERTY(EditDefaultsOnly, Category = "Shoot")
	UNiagaraSystem* niagaraFire;
	UNiagaraComponent* fire;

	//runtime
	USceneComponent* niagaraSpawnPoint;
	FVector HitMousePos;
	FTimerHandle shootTimerHandle;
	UHealthComponent* healthComponent;

	// use inputs to move
	void Move(const FInputActionValue& Value);

	// use inputs to shoot
	void StartShoot(const FInputActionValue& Value);
	void EndShoot(const FInputActionValue& Value);
	void Shoot();

	// rotate towards vector (used to rotate towards mouse position)
	void RotateToward(const FVector position);

	// function delegate from health component
	UFUNCTION()
	void OnDeath();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
