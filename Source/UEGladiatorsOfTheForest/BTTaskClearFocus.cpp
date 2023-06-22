


#include "AIController.h"
#include "BTTaskClearFocus.h"


EBTNodeResult::Type UBTTaskClearFocus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetAIOwner()->ClearFocus(EAIFocusPriority::Gameplay);
	return EBTNodeResult::Succeeded;
}