// Shoot Them Up Game. All Rights Reserved.

#include "UI/STUGoToMenuWidget.h"
#include "Components/Button.h"
#include "STUGameInstance.h"
#include "STUGameInstance.h"
#include "Kismet/GameplayStatics.h"

void USTUGoToMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GoToMainMenuButton)
    {
        GoToMainMenuButton->OnClicked.AddDynamic(this, &USTUGoToMenuWidget::GoToMainMenu);
    }
}

void USTUGoToMenuWidget::GoToMainMenu()
{
    if (!GetWorld() || !GetWorld()->GetGameInstance()) return;

    const auto GameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();
    if (!GameInstance) return;

    UGameplayStatics::OpenLevel(this, GameInstance->GetMainMenuLevelName());
}