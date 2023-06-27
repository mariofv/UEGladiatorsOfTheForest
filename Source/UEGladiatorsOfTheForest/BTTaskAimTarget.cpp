#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UEGladiatorsDefs.h"

#include "BTTaskAimTarget.h"

EBTNodeResult::Type UBTTaskAimTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UObject* targetActorObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("TargetActor"));
	AActor* targetActor = static_cast<AActor*>(targetActorObject);

	AAIController* owenrController = OwnerComp.GetAIOwner();
	owenrController->SetFocus(targetActor);

	UObject* selfActorObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("SelfActor"));
	AActor* selfActor = static_cast<AActor*>(selfActorObject);

	UFunction* setRotationModeFunction = selfActor->FindFunction(TEXT("BPI_Set_RotationMode"));
	if (setRotationModeFunction == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	UEGladiatorsDefs::SetRotationModeParams setRotationModeParams;
	setRotationModeParams.m_RotationMode = UEGladiatorsDefs::RotationMode::Aim;
	selfActor->ProcessEvent(setRotationModeFunction, &setRotationModeParams);

	return EBTNodeResult::Succeeded;
}