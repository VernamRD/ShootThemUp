// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "STUPlayerHUDWidget.generated.h"

class ASTUPlayerState;
class ASTUGameModeBase;

UCLASS()
class SHOOTTHEMUP_API USTUPlayerHUDWidget : public UUserWidget
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

    UFUNCTION()

    virtual bool Initialize() override;

private:
    void OnHealthChanged(float Health, float HealthDelta);

    void OnNewPawn(APawn* NewPawn);

    FGameData GetSTUGameData() const;
    ASTUPlayerState* GetSTUPlayerState() const;
    ASTUGameModeBase* GetSTUGameMode() const;
};