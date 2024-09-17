// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplodingBarrel.h"
#include "Engine/StaticMesh.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ASExplodingBarrel::ASExplodingBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>("BarrelMesh");
	BarrelMesh->SetSimulatePhysics(true);
	RootComponent = BarrelMesh;

	RadialComp = CreateDefaultSubobject<URadialForceComponent>("RadialComp");
	RadialComp->SetupAttachment(BarrelMesh);

	RadialComp->SetAutoActivate(false);

	RadialComp->Radius = 750.0f;
	RadialComp->ImpulseStrength = 2500.0f;

	RadialComp->bImpulseVelChange = true;

	RadialComp->AddCollisionChannelToAffect(ECC_WorldDynamic);


}

// Called when the game starts or when spawned
void ASExplodingBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	BarrelMesh->OnComponentHit.AddDynamic(this, &ASExplodingBarrel::OnActorHit);
}


void ASExplodingBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	RadialComp->FireImpulse();
	UE_LOG(LogTemp, Log, TEXT("OnActorHit in Explosive Barrel"));

	UE_LOG(LogTemp, Warning, TEXT("OnActorHit %s, at game time: %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);


	FString CombinedString = FString::Printf(TEXT("Hit at location: %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, nullptr, FColor::Green, 2.0f, true);
}

