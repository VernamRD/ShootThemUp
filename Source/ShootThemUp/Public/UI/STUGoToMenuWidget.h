// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUGoToMenuWidget.generated.h"

class UButton;

UCLASS() class SHOOTTHEMUP_API USTUGoToMenuWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* GoToMainMenuButton;

    virtual void NativeOnInitialized() override;

private:
    UFUNCTION()
    void GoToMainMenu();
};
