
#include "FollowSwitchAnimInst.h"
#include "FollowSwitchCharacter.h"

void UFollowSwitchAnimInst::SetVelocity(float _velocity)
{
	velocity = _velocity;
}

void UFollowSwitchAnimInst::NativeBeginPlay()
{
	AFollowSwitchCharacter* _character = Cast<AFollowSwitchCharacter>(TryGetPawnOwner());

	if (!_character)
		return;

	_character->OnMoveForward().AddDynamic(this, &UFollowSwitchAnimInst::SetVelocity);
}