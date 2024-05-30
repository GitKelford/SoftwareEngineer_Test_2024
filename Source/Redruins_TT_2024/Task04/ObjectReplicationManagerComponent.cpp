// RedRuins Softworks (c)


#include "ObjectReplicationManagerComponent.h"
#include "ObjectForReplication.h"
#include "Runtime/Launch/Resources/Version.h"
#include "Engine/ActorChannel.h"

/** 
 * 
 */
UObjectReplicationManagerComponent::UObjectReplicationManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);

#if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1
	bReplicateUsingRegisteredSubObjectList = true;
#endif
}

bool UObjectReplicationManagerComponent::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
#if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1
	return Super::ReplicateSubobjects(Channel, Bunch, RepFlags);
#else
	bool WroteSomething = true;

for (UORReplicatedObject* ReplicatedObject : ReplicatedObjects)
{
	if (IsValid(ReplicatedObject))
	{
		WroteSomething |= Channel->ReplicateSubobject(ReplicatedObject, *Bunch, *RepFlags);
	}
}

return WroteSomething;
#endif
}

bool UObjectReplicationManagerComponent::RegisterReplicatedObject(UObjectForReplication* ObjectToRegister)
{
	if (IsValid(ObjectToRegister))
	{
		ReplicatedObjects.AddUnique(ObjectToRegister);
#if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1
		AddReplicatedSubObject(ObjectToRegister);
#endif
		return true;
	}

	return false;
}

bool UObjectReplicationManagerComponent::UnregisterReplicatedObject(UObjectForReplication* ObjectToUnregister, bool bDestroyObject)
{
	if (IsValid(ObjectToUnregister))
	{
		ReplicatedObjects.Remove(ObjectToUnregister);
#if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 1
		RemoveReplicatedSubObject(ObjectToUnregister);
#endif

		if (bDestroyObject)
		{
			ObjectToUnregister->DestroyObject();
		}
		
		return true;
	}

	return false;
}