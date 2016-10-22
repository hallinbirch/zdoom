/*
#include "actor.h"
#include "info.h"
#include "m_random.h"
#include "p_local.h"
#include "p_enemy.h"
#include "gstrings.h"
#include "a_action.h"
#include "s_sound.h"
#include "vm.h"
*/

static FRandom pr_headattack ("HeadAttack");

DEFINE_ACTION_FUNCTION(AActor, A_HeadAttack)
{
	PARAM_SELF_PROLOGUE(AActor);

	if (!self->target)
		return 0;
				
	A_FaceTarget (self);
	if (self->CheckMeleeRange ())
	{
		int damage = (pr_headattack()%6+1)*10;
		S_Sound (self, CHAN_WEAPON, self->AttackSound, 1, ATTN_NORM);
		int newdam = P_DamageMobj (self->target, self, self, damage, NAME_Melee);
		P_TraceBleed (newdam > 0 ? newdam : damage, self->target, self);
		return 0;
	}
	
	// launch a missile
	P_SpawnMissile (self, self->target, PClass::FindActor("CacodemonBall"));
	return 0;
}
