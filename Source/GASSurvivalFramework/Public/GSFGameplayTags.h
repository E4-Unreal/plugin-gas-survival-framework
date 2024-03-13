#pragma once

#include "NativeGameplayTags.h"

namespace GSFGameplayTags
{
    namespace State
    {
        /* 기본 */
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(ProningTag)
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(CrouchingTag)
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(FallingTag)

        /* 행동 불가 */
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(DeadTag)
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(StunTag)
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(KnockdownTag)

        /* 파쿠르 */
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(VaultingTag)
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(ClimbingTag)

        /* 슈터 */
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(ADSTag)

        /* 전투 */
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(CombatTag)
    }

    namespace Input
    {
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(PrimaryTag)
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(SecondaryTag)
    }

    namespace Action
    {
        /* 공격 */
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttackTag)
    }

    namespace Equipment
    {
        /* 장비 슬롯 */
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(SlotTag)
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(PrimarySlotTag) // 주 무기 슬롯
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(SecondarySlotTag) // 보조 무기 슬롯
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(SpecialSlotTag) // 특수 슬롯 (아이템, 투척류 등)

        /* 장비 아이템 */
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(EquipmentTag)
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(WeaponTag)
        UE_DECLARE_GAMEPLAY_TAG_EXTERN(ArmorTag)
    }
}
