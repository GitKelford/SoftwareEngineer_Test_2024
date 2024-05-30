// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_2.generated.h"


class UDA_1;

UENUM(BlueprintType)
enum class EDAEnum : uint8
{
    Value_True UMETA(DisplayName = "Value True"),
    Value_False UMETA(DisplayName = "Value False"),
    Value_N UMETA(DisplayName = "Value N")
};

UCLASS()
class REDRUINS_TT_2024_API UDA_2 : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DA_2")
	EDAEnum EnumValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DA_2", meta = (EditCondition = "EnumValue == EDAEnum::Value_True", EditConditionHides))
	UDA_1* DA1Reference;
};
