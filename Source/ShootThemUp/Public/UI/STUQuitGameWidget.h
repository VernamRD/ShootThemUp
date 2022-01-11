// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUQuitGameWidget.generated.h"

class UButton;

UCLASS()
class SHOOTTHEMUP_API USTUQuitGameWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* QuitGameButton;

    virtual void NativeOnInitialized() override;

private:
    UFUNCTION()
    void OnQuitGame();
};
