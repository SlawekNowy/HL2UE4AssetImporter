// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HL2EntityData.h"

#include "BaseEntity.generated.h"

USTRUCT(BlueprintType)
struct HL2RUNTIME_API FEntityLogicOutput
{
	GENERATED_BODY()

public:

	// The targetname of the target. May be a wildcard or special targetname.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HL2")
	FName TargetName;

	// The name of the output.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HL2")
	FName OutputName;

	// The name of the input of the target to fire.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HL2")
	FName InputName;

	// How long to wait before firing (s).
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HL2")
	float Delay;

	// Whether to only fire once.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HL2")
	bool Once;

	// Parameters.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HL2")
	TArray<FString> Params;
};

UCLASS()
class HL2RUNTIME_API ABaseEntity : public AActor
{
	GENERATED_BODY()
	
public:

	/** The raw entity data straight from the vbsp entities lump. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HL2")
	FHL2EntityData EntityData;

	/** The world model, if any, for this entity. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HL2")
	UStaticMesh* WorldModel;

	/** The targetname, if any, for this entity. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HL2")
	FName TargetName;

protected:

	/** All current logic outputs, valid or not, on this entity. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HL2")
	TArray<FEntityLogicOutput> LogicOutputs;

public:

	/**
	 * Fires a logic input on this entity.
	 * Returns true if the logic input was successfully handled.
	 * The caller is the entity which is directly responsible for firing the input. For example, if the player walked into a trigger that has fired this input, the trigger is the caller.
	 * The activator is the entity which is indirectly responsible for firing the input. For example, if the player walked into a trigger that has fired this input, the player is the activator.
	 * Either caller or activator, or both, may be null.
	 */
	UFUNCTION(BlueprintCallable, Category = "HL2")
	bool FireInput(const FName inputName, const TArray<FString>& args, ABaseEntity* caller = nullptr, ABaseEntity* activator = nullptr);

	/**
	 * Fires a logic output on this entity.
	 * Returns the number of entities that succesfully handled the output.
	 */
	UFUNCTION(BlueprintCallable, Category = "HL2")
	int FireOutput(const FName outputName, const TArray<FString>& args, ABaseEntity* caller = nullptr, ABaseEntity* activator = nullptr);

	/**
	 * Resets all logic outputs to their initial state.
	 */
	UFUNCTION(BlueprintCallable, Category = "HL2")
	void ResetLogicOutputs();

protected:

	/**
	 * Published when an input has been fired on this entity.
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "HL2")
	void OnInputFired(const FName inputName, const TArray<FString>& args, ABaseEntity* caller, ABaseEntity* activator);

	void OnInputFired_Implementation(const FName inputName, const TArray<FString>& args, ABaseEntity* caller, ABaseEntity* activator);

};
