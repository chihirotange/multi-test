// Fill out your copyright notice in the Description page of Project Settings.


#include "Trigger.h"

#include "Components/BoxComponent.h"
#include "Interface/Activatable.h"

// Sets default values
ATrigger::ATrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	
	TriggerCollider = CreateDefaultSubobject<UBoxComponent>("Trigger Collider");
	TriggerCollider->SetCollisionProfileName(FName("OverlapOnlyPawn"));
	TriggerCollider->SetupAttachment(Root);
	
	TriggerCollider->OnComponentBeginOverlap.AddDynamic(this, &ATrigger::OnOverlap);
	TriggerCollider->OnComponentEndOverlap.AddDynamic(this, &ATrigger::StopOverlap);
}

// Called when the game starts or when spawned
void ATrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATrigger::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!HasAuthority())
	{
		return;
	}
	for (AActor* Actor : ActivatableObjects)
	{
		if (Actor->Implements<UActivatable>())
		{
			IActivatable::Execute_Activate(Actor);
		}
	}
}

void ATrigger::StopOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if(!HasAuthority())
	{
		return;
	}
	for (AActor* Actor : ActivatableObjects)
	{
		if (Actor->Implements<UActivatable>())
		{
			IActivatable::Execute_Deactivate(Actor);
		}
	}
}

// Called every frame
void ATrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

