// Shoot Them Up Game. All Rights Reserved.

#include "Components/STUHealthComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraShakeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

USTUHealthComponent::USTUHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTUHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    checkf(MaxHealth > 0, TEXT("Max health cannot be equal to zero"));

    SetHealth(MaxHealth);
    
    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
    }
}

void USTUHealthComponent::SetHealth(const float NewHealth)
{
    const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    const auto HealthDelta = NextHealth - Health;

    Health = NextHealth;
    OnHealthChanged.Broadcast(Health, HealthDelta);
}

void USTUHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if (Damage <= 0.0f || IsDead() || !GetWorld()) return;

    GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

    SetHealth(Health - Damage);

    if (IsDead())
    {
        OnDeath.Broadcast();
    }
    else if (AutoHeal && GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(
            HealTimerHandle, this, &USTUHealthComponent::AutoHealUpdate, AutoHealUpdateTime, true, AutoHealDelay);
    }

    PlayCameraShake(Damage);
}

void USTUHealthComponent::Heal(const float HealAmount)
{
    if (HealAmount <= 0.0f || Health == MaxHealth) return;
    SetHealth(Health + (HealAmount * HealModifier));

    //UE_LOG(LogHealthComponent, Display, TEXT("Actor: %s - heal: %f HP"), *GetOwner()->GetName(), HealAmount);

    if (FMath::IsNearlyEqual(Health, MaxHealth) && GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    }
}

void USTUHealthComponent::AutoHealUpdate()
{
    Heal(AutoHealPerSecond * AutoHealUpdateTime);
}

void USTUHealthComponent::PlayCameraShake(const float Damage)
{
    if (IsDead()) return;

    const auto Player = Cast<APawn>(GetOwner());
    if (!Player) return;

    const auto Controller = Player->GetController<APlayerController>();
    if (!Controller || !Controller->PlayerCameraManager) return;

    const auto ScaleShake = FMath::GetMappedRangeValueClamped(FVector2D(0.0f, MaxHealth*0.7f), FVector2D(0.0f, 1.0f), Damage);

    Controller->PlayerCameraManager->StartCameraShake(CameraShake, ScaleShake);
}