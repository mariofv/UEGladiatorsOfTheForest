

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskClearFocus.generated.h"

/**
 * 
 */
UCLASS()
class UEGLADIATORSOFTHEFOREST_API UBTTaskClearFocus : public UBTTaskNode
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
