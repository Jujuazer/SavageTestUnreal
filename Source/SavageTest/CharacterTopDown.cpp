#include "CharacterTopDown.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "HealthComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/WidgetComponent.h"
#include "HealthBarWidget.h"

// Sets default values
ACharacterTopDown::ACharacterTopDown()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    HealthWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
    HealthWidgetComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    
}

// Called when the game starts or when spawned
void ACharacterTopDown::BeginPlay()
{
    Super::BeginPlay();
    APlayerController* PC = Cast<APlayerController>(GetController());

    if (PC)
    {
        PC->bShowMouseCursor = true;
        PC->bEnableClickEvents = true;
        PC->bEnableMouseOverEvents = true;
    }
     
    // setup health component and delegate on death
    healthComponent = GetComponentByClass<UHealthComponent>();
    healthComponent->OndeathDelegate.BindDynamic(this, &ACharacterTopDown::OnDeath);

    // setup health widget bar
    UHealthBarWidget* healthbarWidget = Cast<UHealthBarWidget>(HealthWidgetComp->GetUserWidgetObject());
    healthComponent->widget = healthbarWidget;
    healthComponent->widget->UpdateHealth(healthComponent->life, healthComponent->maxLife);

    // search for FirePointNiagara component from childrens of player
    TArray<USceneComponent*> children;
    GetComponents<USceneComponent>(children);

    for (int i = 0; i < children.Num(); i++)
    {
        if (children[i]->GetName() == "FirePointNiagara") 
        {
            niagaraSpawnPoint = children[i];
        }
    }

    // spawn fire and smoke effects (setup to be used when shooting)
    if (niagaraFire && niagaraSmoke)
    {
        fire = UNiagaraFunctionLibrary::SpawnSystemAttached(niagaraFire, niagaraSpawnPoint, TEXT("nul"), FVector::Zero(), FRotator::ZeroRotator, EAttachLocation::Type::SnapToTarget, false, false);
        smoke = UNiagaraFunctionLibrary::SpawnSystemAttached(niagaraSmoke, niagaraSpawnPoint, TEXT("nul"), FVector::Zero(), FRotator::ZeroRotator, EAttachLocation::Type::SnapToTarget, false, false);
    }
}

void ACharacterTopDown::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // Get the player controller, set mouse position on world and rotate player
    APlayerController* PC = Cast<APlayerController>(GetController());
    FHitResult hitResult;

    if (PC != nullptr) {
        PC->GetHitResultUnderCursorByChannel(MousePosLayerMask, false, hitResult);
        HitMousePos = hitResult.ImpactPoint;
    }

    RotateToward(HitMousePos);
}

void ACharacterTopDown::OnDeath()
{
    GetMesh()->SetSimulatePhysics(true);
}


void ACharacterTopDown::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        // Move right/left
        AddMovementInput(FVector(0, 1, 0), MovementVector.Y);

        // Move forward/backward
        AddMovementInput(FVector(1, 0, 0), MovementVector.X);
    }
}

void ACharacterTopDown::StartShoot(const FInputActionValue& Value)
{
    // start repeating function when click down
    GetWorldTimerManager().SetTimer(shootTimerHandle, this, &ACharacterTopDown::Shoot, fireRate, true);
}

void ACharacterTopDown::EndShoot(const FInputActionValue& Value)
{
    // end repeating function when click up
    GetWorldTimerManager().ClearTimer(shootTimerHandle);
}

void ACharacterTopDown::Shoot()
{
    FHitResult raycastHit;
    FVector endPositionShoot = GetActorForwardVector() * fireRange + GetActorLocation();

    FCollisionQueryParams query;
    query.AddIgnoredActor(this);

    // activate niagara systems when shooting
    if (fire && smoke) 
    {
        fire->Activate();
        smoke->Activate();
    }

    // shoot raycast and damage enemy if hit
    if (GetWorld()->LineTraceSingleByChannel(raycastHit, GetActorLocation(), endPositionShoot, ECC_Visibility, query)) 
    {
        UHealthComponent* health = raycastHit.GetActor()->GetComponentByClass<UHealthComponent>();
        if (health != nullptr) 
        {
            health->TakeDamage(damage);
        }
    }

    //DrawDebugLine(GetWorld(), GetActorLocation(), endPositionShoot, FColor::Yellow, true, 2);
}


void ACharacterTopDown::RotateToward(const FVector position)
{
    FVector direction = position - GetActorLocation();

    direction.Normalize();
    FRotator rotation = direction.Rotation();
    rotation.Pitch = 0;
    rotation.Roll = 0;

    SetActorRotation(rotation);
}


void ACharacterTopDown::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    APlayerController* PC = Cast<APlayerController>(GetController());

    // Get the local player subsystem
    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
    // Clear out existing mapping and add mapping
    Subsystem->ClearAllMappings();
    Subsystem->AddMappingContext(InputMapping, 0);

    // Get the EnhancedInputComponent
    UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);

    // Bind the actions
    PEI->BindAction(InputMove, ETriggerEvent::Triggered, this, &ACharacterTopDown::Move);
    PEI->BindAction(InputShoot, ETriggerEvent::Started, this, &ACharacterTopDown::StartShoot);
    PEI->BindAction(InputShoot, ETriggerEvent::Completed, this, &ACharacterTopDown::EndShoot);
}

