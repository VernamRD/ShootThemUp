// Shoot Them Up Game. All Rights Reserved.

#include "UI/STUPauseWidget.h"
#include "GameFramework/GameModeBase.h"
#include "STUGameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void USTUPauseWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (!ClearPauseButton) return;

    ClearPauseButton->OnClicked.AddDynamic(this, &USTUPauseWidget::OnClearPause);
}

void USTUPauseWidget::OnClearPause()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->ClearPause();
}
