// Shoot Them Up Game. All Rights Reserved.


#include "UI/STUQuitGameWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

void USTUQuitGameWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (QuitGameButton)
    {
        QuitGameButton->OnClicked.AddDynamic(this, &USTUQuitGameWidget::OnQuitGame);
    }
}

void USTUQuitGameWidget::OnQuitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}