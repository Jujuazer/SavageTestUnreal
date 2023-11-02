// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseState.generated.h"

class AEnemyBase;

UCLASS()
class SAVAGETEST_API UBaseState : public UObject
{
	GENERATED_BODY()

public:
	UBaseState();
	
public:
	virtual void UpdateBehaviour(AEnemyBase*);
	virtual void StartBehaviour(AEnemyBase*);
	virtual void ExitBehaviour(AEnemyBase*);
};
