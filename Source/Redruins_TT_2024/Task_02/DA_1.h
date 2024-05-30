// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_1.generated.h"


class UDA_2;
class UTexture2D;

USTRUCT(BlueprintType)
struct FDataStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Struct")
	UDA_2* DA2Reference;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Struct")
	FString Name = "Man";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Struct")
	FString ReleaseDate = "25 Feb 2021";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Struct")
	UTexture2D* Texture;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Struct")
	FVector Vector;
};

UCLASS()
class REDRUINS_TT_2024_API UDA_1 : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DA_1")
	FDataStruct Sample_DataStruct;
};
