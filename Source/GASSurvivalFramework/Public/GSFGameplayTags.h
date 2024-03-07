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
    }
}
