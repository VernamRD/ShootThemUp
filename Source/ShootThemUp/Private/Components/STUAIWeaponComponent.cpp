// Shoot Them Up Game. All Rights Reserved.

#include "Components/STUAIWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"

void USTUAIWeaponComponent::StartFire()
{
    if (!CanFire()) return;

    if (CurrentWeapon->IsAmmoEmpty())
    {
        NextWeapon();
    }
    else
    {
        CurrentWeapon->StartFire();
    }
}

void USTUAIWeaponComponent::NextWeapon()
{
    if (!CanEquip()) return;
    int32 NextIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    while (NextIndex != CurrentWeaponIndex)
    {
        if (!Weapons[NextIndex]->IsAmmoEmpty()) break;
        NextIndex = (NextIndex + 1) % Weapons.Num();
    }

    if (CurrentWeaponIndex != NextIndex)
    {
        CurrentWeaponIndex = NextIndex;
        EquipWeapon(CurrentWeaponIndex);
    }
}

void USTUAIWeaponComponent::NextWeapon(EWeaponType WeaponType)
{

    if (!CanEquip()) return;
    for (int32 i = 0; i < Weapons.Num(); i++)
    {
        if (WeaponType == Weapons[i]->GetWeaponType() && CurrentWeaponIndex != i)
        {
            CurrentWeaponIndex = i;
            EquipWeapon(CurrentWeaponIndex);
        }
    }
}