// Shoot Them Up Game. All Rights Reserved.

#include "AI/Services/STUChangeWeaponService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/STUWeaponComponent.h"
#include "AI/STUAIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "STUUtils.h"

USTUChangeWeaponService::USTUChangeWeaponService()
{
    NodeName = "ChangeWeapon";
}

void USTUChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    switch (ConditionChange)
    {
        case EConditions::Random:
        {

            const auto Controller = OwnerComp.GetAIOwner();
            const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Controller->GetPawn());

            if (UKismetMathLibrary::RandomBoolWithWeight(ChangeWeaponChance))
            {
                WeaponComponent->NextWeapon();
            }
            break;
        }

        case EConditions::Distance:
        {

            const auto Controller = OwnerComp.GetAIOwner();
            const auto Blackboard = OwnerComp.GetBlackboardComponent();
            if (!Blackboard || !Controller) break;

            const auto Enemy = Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);
            if (!Enemy) break;

            const auto OwnerLocation = Controller->GetPawn()->GetActorLocation();
            const auto EnemyLocation = Cast<AActor>(Enemy)->GetActorLocation();

            if ((EnemyLocation - OwnerLocation).Size() <= Distance)
            {
                const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Controller->GetPawn());
                check(WeaponComponent);

                WeaponComponent->NextWeapon(EWeaponType::Near);
            }
            else
            {
                const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Controller->GetPawn());
                check(WeaponComponent);

                WeaponComponent->NextWeapon(EWeaponType::LongRange);
            }

            break;
        }
        default: break;
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
