// Shoot Them Up Game. All Rights Reserved.

#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUWeaponFXComp, All, All);

USTUWeaponFXComponent::USTUWeaponFXComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
    if (!DefaultImpactData.ImpactSound)
        UE_LOG(LogSTUWeaponFXComp, Warning, TEXT("Default Impact sound is NULL in: %s"), *GetOwner()->GetName());
    if (!DefaultImpactData.NiagaraEffect)
        UE_LOG(LogSTUWeaponFXComp, Warning, TEXT("Default Niagara Effect is NULL in: %s"), *GetOwner()->GetName());

    auto ImpactData = DefaultImpactData;
    if (Hit.PhysMaterial.IsValid())
    {
        const auto PhysMat = Hit.PhysMaterial.Get();
        if (ImpactDataMap.Contains(PhysMat))
        {
            if (ImpactDataMap.Find(PhysMat)->ImpactSound  //
                && ImpactDataMap.Find(PhysMat)->NiagaraEffect)
            {
                ImpactData = ImpactDataMap[PhysMat];
            }
            else
            {
                UE_LOG(LogSTUWeaponFXComp, Warning,
                    TEXT("%s - One or more elements corresponding to the physical material %s in ImpactData is NULL"),  //
                    *GetOwner()->GetName(), *PhysMat->GetName());
            }
        }
    }

    // Niagara
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),  //
        ImpactData.NiagaraEffect,                               //
        Hit.ImpactPoint,                                        //
        Hit.ImpactNormal.Rotation());

    // Decal
    auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(),  //
        ImpactData.DacalData.Material,                                        //
        ImpactData.DacalData.Size,                                            //
        Hit.ImpactPoint,                                                      //
        Hit.ImpactNormal.Rotation());

    if (DecalComponent)
    {
        DecalComponent->SetFadeOut(ImpactData.DacalData.LifeTime, ImpactData.DacalData.FadeOutTime);
    }

    // Sound
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactData.ImpactSound, Hit.ImpactPoint);
}

void USTUWeaponFXComponent::PlayMuzzleFX(USkeletalMeshComponent* WeaponMesh, const FName MuzzleSocketName)
{
    // UNiagaraFunctionLibrary::SpawnSystemAttached();

    UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFX,  //
        WeaponMesh,                                         //
        MuzzleSocketName,                                   //
        FVector::ZeroVector,                                //
        FRotator::ZeroRotator,                              //
        EAttachLocation::SnapToTarget,                      //
        true);
}

void USTUWeaponFXComponent::PlayTraceFX(const FVector& TraceStart, const FVector& TraceEnd)
{
    const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart);
    if (TraceFXComponent)
    {
        TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
    }
}