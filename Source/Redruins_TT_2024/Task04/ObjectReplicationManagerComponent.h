// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectReplicationManagerComponent.generated.h"

class UObjectForReplication;

/** 
 * 
 */
UCLASS(ClassGroup=("Object Replication"), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType, DisplayName = "UObject Replication Manager")
class REDRUINS_TT_2024_API UObjectReplicationManagerComponent : public UActorComponent
{
	GENERATED_BODY()

	public:
	
	UObjectReplicationManagerComponent();

	protected:
	
	//UActorComponent interface implementation
	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;;
	//End of implementation

	public:
	
	/**
	 * Register a Replicated UObjects to replicate
	 * 
	 * @param ObjectToRegister The Replicated UObject to register.
	 */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Object Replication", DisplayName = "Register Replicated UObject")
	virtual bool RegisterReplicatedObject(UPARAM(DisplayName = "Replicated UObject") UObjectForReplication* ObjectToRegister);

	/**
	 * Unregister a Replicated UObject from replication
	 * 
	 * @param ObjectToUnregister The Replicated UObject to unregister.
	 * @param bDestroyObject If the UObject Replication Manager should mark the Replicated UObject as garbage for the garbage collector, after it has unregistered the Replicated UObject.
	 */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Object Replication", DisplayName = "Unregister Replicated UObject")
	virtual bool UnregisterReplicatedObject(UPARAM(DisplayName = "Replicated UObject") UObjectForReplication* ObjectToUnregister, UPARAM(DisplayName = "Destroy Replicated UObject") bool bDestroyObject = false);

	//Get all the replicated objects that are registered on this manager.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Object Replication", DisplayName = "Get Registered Replicated UObjects")
	virtual TArray<UObjectForReplication*> GetRegisteredReplicatedObjects()
	{
		return ReplicatedObjects;
	};

	protected:
	
	//All the currently replicated objects
	UPROPERTY()
	TArray<UObjectForReplication*> ReplicatedObjects;
};