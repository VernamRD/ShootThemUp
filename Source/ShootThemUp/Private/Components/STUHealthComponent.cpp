// Shoot Them Up Game. All Rights Reserved.

#include "Components/STUHealthComponent.h"
#include "Dev/STUFireDamageType.h"
#include "Dev/STUIceDamageType.h"
#include "Engine/World.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

USTUHealthComponent::USTUHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTUHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    Health = MaxHealth;

    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
    }
}
void USTUHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    Health -= Damage;
    UE_LOG(LogHealthComponent, Display, TEXT("Damage: %f"), Damage);
    if (DamageType)
    else if (AutoHeal && GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(
            HealTimerHandle, this, &USTUHealthComponent::AutoHealUpdate, AutoHealUpdateTime, true, AutoHealDelay);
    }
}

void USTUHealthComponent::Heal(const float HealAmount)
{
    if (HealAmount <= 0.0f || Health == MaxHealth) return;
    SetHealth(Health + (HealAmount * HealModifier));

    //UE_LOG(LogHealthComponent, Display, TEXT("Actor: %s - heal: %f HP"), *GetOwner()->GetName(), HealAmount);

    if (FMath::IsNearlyEqual(Health, MaxHealth) && GetWorld())
    {
        if (DamageType->IsA<USTUFireDamageType>())
        {
            UE_LOG(LogHealthComponent, Display, TEXT("So hoooooooooot !!!"));
        }
        else if (DamageType->IsA<USTUIceDamageType>())
        {
            UE_LOG(LogHealthComponent, Display, TEXT("So coooooooooold !!!"));
        }
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    }
}

void USTUHealthComponent::AutoHealUpdate()
{
    Heal(AutoHealPerSecond * AutoHealUpdateTime);
}