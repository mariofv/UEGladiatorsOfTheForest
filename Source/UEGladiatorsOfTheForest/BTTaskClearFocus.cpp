#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UEGladiatorsDefs.h"

#include "BTTaskClearFocus.h"


EBTNodeResult::Type UBTTaskClearFocus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetAIOwner()->ClearFocus(EAIFocusPriority::Gameplay);

	UObject* selfActorObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("SelfActor"));
	AActor* selfActor = static_cast<AActor*>(selfActorObject);

	UFunction* setRotationModeFunction = selfActor->FindFunction(TEXT("BPI_Set_RotationMode"));
	if (setRotationModeFunction == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	UEGladiatorsDefs::SetRotationModeParams setRotationModeParams;
	setRotationModeParams.m_RotationMode = UEGladiatorsDefs::RotationMode::Looking;
	selfActor->ProcessEvent(setRotationModeFunction, &setRotationModeParams);

	return EBTNodeResult::Succeeded;
}