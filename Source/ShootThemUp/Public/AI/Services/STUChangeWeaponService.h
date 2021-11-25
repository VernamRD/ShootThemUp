// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "STUChangeWeaponService.generated.h"

UENUM(BlueprintType)
enum class EConditions : uint8
{
    Random UMETA(DisplayName = "Random"),
    Distance UMETA(DisplayName = "Distance"),
};

UCLASS()
class SHOOTTHEMUP_API USTUChangeWeaponService : public UBTService
{
    GENERATED_BODY()

public:
    USTUChangeWeaponService();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    EConditions ConditionChange = EConditions::Random;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (EditCondition = "ConditionChange == EConditions::Random"))
    float ChangeWeaponChance = 0.5f;

    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AI", meta = (EditCondition = "ConditionChange == EConditions::Distance"))
    float Distance = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (EditCondition = "ConditionChange == EConditions::Distance"))
    FBlackboardKeySelector EnemyActorKey;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
