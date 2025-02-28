// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAvatarAnimInstance.h"
#include "PlayerAvatar.h"

void UPlayerAvatarAnimInstance::OnStateAnimationEnds()
{
	if (State == EPlayerState::Attack)
	{
		State = EPlayerState::Locomotion;
	}
	else
	{
		const auto OwnerActor = this->GetOwningActor();
		const auto PlayerAvatar = Cast<APlayerAvatar>(OwnerActor);
		if (PlayerAvatar == nullptr)
		{
			return;
		}
		if (State == EPlayerState::Hit)
		{
			if (PlayerAvatar->GetHealthPoints() > 0.0f)
			{
				State = EPlayerState::Locomotion;
			}
			else
			{
				State = EPlayerState::Die;
			}
		}
		else if (State == EPlayerState::Die)
		{
			PlayerAvatar->DieProcess();
		}
	}
}
