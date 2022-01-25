// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUCoreTypes.h"
#include "STUBaseWeapon.generated.h"

class USTUWeaponComponent;
class ASTUBaseCharacter;
class USkeletalMeshComponent;
class UNiagaraSystem;
class UNigaraComponent;
class USoundCue;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    ASTUBaseWeapon();

    FOnClipEmptySignature OnClipEmpty;

    virtual void StartFire();
    virtual void StopFire();
    virtual void Zoom(bool Enabled) {};

    void SetComponentOwner(USTUWeaponComponent* STUWeaponComponent);

    USTUWeaponComponent* GetComponentOwner() { return WeaponComponentOwner; };

    bool CanFire() const;
    void ChangeClip();
    void ReloadFinished();

    bool IsAmmoEmpty() const;

    void EquipInProgress();
    void EquipFinished();

    bool CanReload() const;
    bool IsReloading() const { return Reloading; }

    FWeaponUIData GetUIData() const { return UIData; }
    FAmmoData GetAmmoData() const { return CurrentAmmo; }
    EWeaponType GetWeaponType() const { return WeaponType; }

    float GetAmmoPercent() const;

    bool TryToAddAmmo(int32 ClipsAmount);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    EWeaponType WeaponType;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float TraceMaxDistance = 8000.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FAmmoData DefaultAmmo{30, 10, false};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FWeaponUIData UIData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* FireSound;

    virtual void BeginPlay() override;

    virtual void MakeShot();
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    FVector GetMuzzleWorldLocation() const;

    void MakeHit(FHitResult& HitResult, const FVector& TraceStart, FVector& TraceEnd);

    void DecreaseAmmo();
    bool IsClipEmpty() const;
    bool IsAmmoFull() const;

    void LogAmmo();

    bool Reloading = false;

    USTUWeaponComponent* WeaponComponentOwner = nullptr;

private:
    FAmmoData CurrentAmmo;
};
