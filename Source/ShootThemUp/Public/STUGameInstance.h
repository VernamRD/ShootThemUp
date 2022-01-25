// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STUCoreTypes.h"
#include "STUGameInstance.generated.h"

class USoundClass;

UCLASS()
class SHOOTTHEMUP_API USTUGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    FLevelData GetStartupLevel() const { return StartupLevel; }
    void SetStartupLevel(const FLevelData& Data) { StartupLevel = Data; }

    TArray<FLevelData> GetLevelsData() const { return LevelsData; }

    FName GetMainMenuLevelName() const { return MainMenuLevelName; }

    void ToggleVolume();

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (ToolTip = "Level names must be unique"))
    TArray<FLevelData> LevelsData;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FName MainMenuLevelName = NAME_None;

    UPROPERTY(EditDefaultsOnly, Category = "Sound")
    USoundClass* MasterSoundClass;

private:
    FLevelData StartupLevel;
};
