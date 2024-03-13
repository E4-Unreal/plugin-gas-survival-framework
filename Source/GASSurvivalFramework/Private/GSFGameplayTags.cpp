#include "GSFGameplayTags.h"

namespace GSFGameplayTags
{
    namespace State
    {
        /* 기본 */
        UE_DEFINE_GAMEPLAY_TAG(ProningTag, "State.Proning") // 엎드리기
        UE_DEFINE_GAMEPLAY_TAG(CrouchingTag, "State.Crouching") // 앉기
        UE_DEFINE_GAMEPLAY_TAG(FallingTag, "State.Falling") // 점프 혹은 낙하

        /* 행동 불가 */
        UE_DEFINE_GAMEPLAY_TAG(DeadTag, "State.Dead") // 죽음
        UE_DEFINE_GAMEPLAY_TAG(StunTag, "State.Stun") // 무력화
        UE_DEFINE_GAMEPLAY_TAG(KnockdownTag, "State.Knockdown") // 기절 (부활 기회)

        /* 파쿠르 */
        UE_DEFINE_GAMEPLAY_TAG(VaultingTag, "State.Vaulting") // 낮은 파쿠르
        UE_DEFINE_GAMEPLAY_TAG(ClimbingTag, "State.Climbing") // 높은 파쿠르 혹은 사다리 타기

        /* 슈터 */
        UE_DEFINE_GAMEPLAY_TAG(ADSTag, "State.ADS") // 조준

        /* 전투 */
        UE_DEFINE_GAMEPLAY_TAG(CombatTag, "State.Combat") // 전투
    }

    namespace Input
    {
        UE_DEFINE_GAMEPLAY_TAG(PrimaryTag, "Input.Primary")
        UE_DEFINE_GAMEPLAY_TAG(SecondaryTag, "Input.Secondary")
    }

    namespace Action
    {
        /* 공격 */
        UE_DEFINE_GAMEPLAY_TAG(AttackTag, "Action.Attack") // 공격
    }

    namespace Equipment
    {
        /* 장비 슬롯 */
        UE_DEFINE_GAMEPLAY_TAG(SlotTag, "Equipment.Slot")
        UE_DEFINE_GAMEPLAY_TAG(PrimarySlotTag, "Equipment.Slot.Primary") // 주 무기 슬롯
        UE_DEFINE_GAMEPLAY_TAG(SecondarySlotTag, "Equipment.Slot.Secondary") // 보조 무기 슬롯
        UE_DEFINE_GAMEPLAY_TAG(SpecialSlotTag, "Equipment.Slot.Special") // 특수 슬롯 (아이템, 투척류 등)

        /* 장비 아이템 */
        UE_DEFINE_GAMEPLAY_TAG(EquipmentTag, "Equipment")
        UE_DEFINE_GAMEPLAY_TAG(WeaponTag, "Equipment.Weapon")
        UE_DEFINE_GAMEPLAY_TAG(ArmorTag, "Equipment.Armor")
    }
}
