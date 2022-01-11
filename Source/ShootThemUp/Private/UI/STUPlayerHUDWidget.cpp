// Shoot Them Up Game. All Rights Reserved.

#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "Player/STUPlayerController.h"
#include "STUGameModeBase.h"
#include "STUUtils.h"
#include "Components/ProgressBar.h"

void USTUPlayerHUDWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (!GetOwningPlayer()) return;

    GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &USTUPlayerHUDWidget::OnNewPawn);
    OnNewPawn(GetOwningPlayerPawn());
}

void USTUPlayerHUDWidget::OnNewPawn(APawn* NewPawn)
{
    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(NewPawn);
    if (HealthComponent)
    {
        HealthComponent->OnHealthChanged.AddUObject(this, &USTUPlayerHUDWidget::OnHealthChanged);
    }

    UpdateHealthBar();
}

void USTUPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
    if (HealthDelta < 0)
    {
        OnTakeDamage(HealthDelta);

        if (!IsAnimationPlaying(DamageAnimation))
        {
            PlayAnimation(DamageAnimation);
        }
    }

    UpdateHealthBar();
}

void USTUPlayerHUDWidget::UpdateHealthBar()
{
    if (HealthProgressBar)
    {
        HealthProgressBar->SetFillColorAndOpacity(GetHealthPercent() > PercentColorThreshold ? GoodColor : BadColor);
        HealthProgressBar->SetPercent(GetHealthPercent());
    }
}

float USTUPlayerHUDWidget::GetHealthPercent() const
{
    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
    if (!HealthComponent) return 0.0f;

    return HealthComponent->GetHealthPercent();
}

float USTUPlayerHUDWidget::GetInvertHealthPercent() const
{
    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
    if (!HealthComponent) return 0.0f;

    return 1.0f - HealthComponent->GetHealthPercent();
}

bool USTUPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
    const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent) return false;

    return WeaponComponent->GetWeaponUIData(UIData);
}

bool USTUPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
    const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent) return false;

    return WeaponComponent->GetWeaponAmmoData(AmmoData);
}

bool USTUPlayerHUDWidget::IsPlayerAlive() const
{
    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
    return HealthComponent && !HealthComponent->IsDead();
}

bool USTUPlayerHUDWidget::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;
}

FString USTUPlayerHUDWidget::FormatBullets(int32 BulletsNum) const 
{
    const int32 MaxLen = 3;
    const TCHAR PrefixSymbol = '0';

    auto BulletStr = FString::FromInt(BulletsNum);
    const auto SymbolsNumToAdd = MaxLen - BulletStr.Len();

    if (SymbolsNumToAdd > 0)
    {
        BulletStr = FString::ChrN(SymbolsNumToAdd, PrefixSymbol).Append(BulletStr);
    }

    return BulletStr;
}

// GameData

FGameData USTUPlayerHUDWidget::GetSTUGameData() const
{
    return GetSTUGameMode()->GetGameData();
}

ASTUPlayerState* USTUPlayerHUDWidget::GetSTUPlayerState() const
{
    const auto Controller = GetOwningPlayer();
    if (!Controller) return nullptr;

    return Cast<ASTUPlayerState>(Controller->PlayerState);
}

ASTUGameModeBase* USTUPlayerHUDWidget::GetSTUGameMode() const
{
    return Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
}

int32 USTUPlayerHUDWidget::GetCurrentRound() const
{
    if (!GetSTUGameMode()) return 0;

    return GetSTUGameMode()->GetCurrentRound();
}

int32 USTUPlayerHUDWidget::GetRoundCountDown() const
{
    if (!GetSTUGameMode()) return 0;

    return GetSTUGameMode()->GetRoundCountDown();
}

int32 USTUPlayerHUDWidget::GetRoundsNum() const
{
    return GetSTUGameData().RoundsNum;
}

int32 USTUPlayerHUDWidget::GetKills() const
{
    if (!GetSTUPlayerState()) return 0;

    return GetSTUPlayerState()->GetKillsNum();
}

int32 USTUPlayerHUDWidget::GetDeaths() const
{
    if (!GetSTUPlayerState()) return 0;

    return GetSTUPlayerState()->GetDeathNum();
}