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
    }
}
