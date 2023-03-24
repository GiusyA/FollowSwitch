
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FollowSwitchAnimInst.generated.h"

UCLASS()
class ATTACKEXO_API UFollowSwitchAnimInst : public UAnimInstance
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
		float velocity = 1.0f;

private:
	void SetVelocity(float _velocity);

	virtual void NativeBeginPlay() override;
};