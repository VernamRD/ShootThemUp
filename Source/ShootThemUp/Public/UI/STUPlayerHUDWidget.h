// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/STUBaseWidget.h"
#include "STUCoreTypes.h"
#include "STUPlayerHUDWidget.generated.h"

class ASTUPlayerState;
class ASTUGameModeBase;
class UProgressBar;

UCLASS()
class SHOOTTHEMUP_API USTUPlayerHUDWidget : public USTUBaseWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealthPercent() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetInvertHealthPercent() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerAlive() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerSpectating() const;

    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void OnTakeDamage(float HealthDelta);

    UFUNCTION(BlueprintCallable, Category = "UI")
    FString FormatBullets(int32 BulletsNum) const;

    // GameData

    UFUNCTION(BlueprintCallable, Category = "GameData")
    int32 GetRoundCountDown() const;

    UFUNCTION(BlueprintCallable, Category = "GameData")
    int32 GetCurrentRound() const;

    UFUNCTION(BlueprintCallable, Category = "GameData")
    int32 GetRoundsNum() const;

    UFUNCTION(BlueprintCallable, Category = "GameData")
    int32 GetKills() const;

    UFUNCTION(BlueprintCallable, Category = "GameData")
    int32 GetDeaths() const;

protected:
    UPROPERTY(meta = (BindWidget))
    UProgressBar* HealthProgressBar;

    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* DamageAnimation;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    float PercentColorThreshold = 0.3f;

    UPROPERTY(EditDefaultsOnly, BLueprintReadWrite, Category = "UI")
    FLinearColor GoodColor = FLinearColor::Green;

    UPROPERTY(EditDefaultsOnly, BLueprintReadWrite, Category = "UI")
    FLinearColor BadColor = FLinearColor::Red;

    virtual void NativeOnInitialized() override;

private:
    void OnHealthChanged(float Health, float HealthDelta);
    void UpdateHealthBar();
    void OnNewPawn(APawn* NewPawn);

    FGameData GetSTUGameData() const;
    ASTUPlayerState* GetSTUPlayerState() const;
    ASTUGameModeBase* GetSTUGameMode() const;
};