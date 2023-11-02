#include "EnemyBase.h"
#include "BaseState.h"
#include "State_FollowPlayer.h"
#include "AIController.h"
#include "AIEnemyController.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "State_Attack.h"
#include "HealthComponent.h"
#include "Components/WidgetComponent.h"
#include "HealthBarWidget.h"


AEnemyBase::AEnemyBase() 
{
	PrimaryActorTick.bCanEverTick = true;
	
	HealthWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HealthWidgetComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	//bind collision hit
	capsuleCollider = GetCapsuleComponent();
	capsuleCollider->OnComponentHit.AddDynamic(this, &AEnemyBase::OnHit);

	boxCollider = GetComponentByClass<UBoxComponent>();

	healthComponent = GetComponentByClass<UHealthComponent>();

	UHealthBarWidget* healthbarWidget = Cast<UHealthBarWidget>(HealthWidgetComp->GetUserWidgetObject());
	healthComponent->widget = healthbarWidget;
	healthComponent->widget->UpdateHealth(healthComponent->life, healthComponent->maxLife);
	healthComponent->OndeathDelegate.BindDynamic(this, &AEnemyBase::OnDeath);

	//get ai controller
	AController* controller = GetController();

	if (controller) 
	{
		AIcontrol = Cast<AAIEnemyController>(controller);
	}

	//get player controller ref
	player = GetWorld()->GetFirstPlayerController();

	//initialize states
	followState = NewObject<UState_FollowPlayer>(this);
	attackState = NewObject<UState_Attack>(this);
	ChangeState(followState);
}

void AEnemyBase::ChangeState(UBaseState* to)
{
	if (actualState != nullptr) 
	{
		actualState->ExitBehaviour(this);
	}

	actualState = to;
	to->StartBehaviour(this);
}

void AEnemyBase::OnDeath()
{
	GetMesh()->SetSimulatePhysics(true);
	GetWorld()->GetTimerManager().ClearTimer(attackTimeHandle);
	if (actualState != nullptr) 
	{
		actualState->ExitBehaviour(this);
		actualState = nullptr;
	}

	capsuleCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FTimerHandle Timer;
	GetWorldTimerManager().SetTimer(Timer, this, &AEnemyBase::Die, 2);
}

void AEnemyBase::Die()
{
	Destroy();
}


void AEnemyBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// impletement when you touch another component, ex : player or enemy
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (actualState != nullptr)
	{
		actualState->UpdateBehaviour(this);
	}
}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
