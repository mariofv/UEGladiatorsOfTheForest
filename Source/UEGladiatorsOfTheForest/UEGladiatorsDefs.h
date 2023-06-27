

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class UEGLADIATORSOFTHEFOREST_API UEGladiatorsDefs
{
public:
	enum class RotationMode : uint8
	{
		Looking = 0u,
		Velocity = 1u,
		Aim = 2u
	};

	struct SetRotationModeParams
	{
		RotationMode m_RotationMode;
	};
};
