// RedRuins Softworks (c)


#include "Redruins_TT_2024/Task04/ObjectForReplication.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "Runtime/Launch/Resources/Version.h"
#include "UObject/Package.h"
#include "Engine/NetDriver.h"
#include "Engine/Engine.h"

UWorld* UObjectForReplication::GetWorld() const
{
	if (GetOuter() == nullptr)
	{
		return nullptr;
	}
		
	if (Cast<UPackage>(GetOuter()) != nullptr)
	{
		return Cast<UWorld>(GetOuter()->GetOuter());
	}
		
	return GetOwningActor()->GetWorld();
}

void UObjectForReplication::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	if (UBlueprintGeneratedClass* BPCClass = Cast<UBlueprintGeneratedClass>(GetClass()))
	{
		BPCClass->GetLifetimeBlueprintReplicationList(OutLifetimeProps);
	}
}

bool UObjectForReplication::IsSupportedForNetworking() const
{
	return ReplicationState == EReplicationState::Replicates;
}

int32 UObjectForReplication::GetFunctionCallspace(UFunction* Function, FFrame* Stack)
{
	if (HasAnyFlags(RF_ClassDefaultObject) || !IsSupportedForNetworking())
	{
		return GEngine->GetGlobalFunctionCallspace(Function, this, Stack);
	}
	
	return GetOuter()->GetFunctionCallspace(Function, Stack);
}

bool UObjectForReplication::CallRemoteFunction(UFunction* Function, void* Parms, FOutParmRec* OutParms, FFrame* Stack)
{
	AActor* Owner = GetOwningActor();
	if (UNetDriver* NetDriver = Owner->GetNetDriver())
	{
		NetDriver->ProcessRemoteFunction(Owner, Function, Parms, OutParms, Stack, this);
		return true;
	}
	return false;
}

AActor* UObjectForReplication::GetOwningActor() const
{
	return GetTypedOuter<AActor>();
}

void UObjectForReplication::DestroyObject()
{
	if (IsValid(this))
	{
#if ENGINE_MAJOR_VERSION == 5
		MarkAsGarbage();
#endif

#if ENGINE_MAJOR_VERSION == 4
		MarkPendingKill();
#endif
		
		OnDestroyed();
	}
}