#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SlowFloor.generated.h"

UCLASS()
class FPSPROJECT2_API ASlowFloor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ASlowFloor();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Movement speed reduction factor
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
    float SpeedReductionFactor;

    // Collision component for detecting overlaps
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UBoxComponent* BoxComponent;

    // Static mesh component for the floor
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UStaticMeshComponent* FloorMesh;

private:
    // Function to handle overlap events
    UFUNCTION()
    void OnOverlapBegin(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    // Function to handle overlap end events
    UFUNCTION()
    void OnOverlapEnd(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

    // Boolean to check if the actor is currently on the floor
    bool bIsCharacterOnFloor;
};
