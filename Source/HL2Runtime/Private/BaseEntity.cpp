#include "HL2RuntimePrivatePCH.h"

#include "BaseEntity.h"
#include "IHL2Runtime.h"

// The entity that began the current I / O chain.If a player walks into a trigger that fires a logic_relay, the player is the !activator of the relay's output(s).
static const FName tnActivator(TEXT("!activator"));

// The previous entity in the current I / O chain.If a player walks into a trigger that that fires a logic_relay, the trigger is the !caller of the relay's output(s).
static const FName tnCaller(TEXT("!caller"));

// The entity from which the current output originates.If a player walks into a trigger that that fires a logic_relay, the relay is the !self of its output(s).
static const FName tnSelf(TEXT("!self"));

// The player.Only useful in singleplayer.
static const FName tnPlayer(TEXT("!player"));

// The first player found in the entity's Potential Visibility Set. The PVS used is taken from the entity doing the searching, or the activator if no searching entity exists. If no activator exists either, the first player in the game is returned (i.e. !player).
static const FName tnPVSPlayer(TEXT("!pvsplayer"));

// The entity at which the !caller is looking due to a Look At Actor or Face Actor choreography event.
static const FName tnSpeechTarget(TEXT("!speechtarget"));
	
// The first entity under the player's crosshair. Only useful in single-player, and mostly only for debugging. Entities without collision can only be selected by aiming at their origin.
static const FName tnPicker(TEXT("!picker"));
	

/**
 * Fires a logic input on this entity.
 * Returns true if the logic input was successfully handled.
 * The caller is the entity which is directly responsible for firing the input. For example, if the player walked into a trigger that has fired this input, the trigger is the caller.
 * The activator is the entity which is indirectly responsible for firing the input. For example, if the player walked into a trigger that has fired this input, the player is the activator.
 * Either caller or activator, or both, may be null.
 */
bool ABaseEntity::FireInput(const FName inputName, const TArray<FString>& args, ABaseEntity* caller, ABaseEntity* activator)
{
	// Handle basic inputs
	static const FName inKill(TEXT("Kill"));
	static const FName inKillHierarchy(TEXT("KillHierarchy"));
	static const FName inAddOutput(TEXT("AddOutput"));
	static const FName inFireUser1(TEXT("FireUser1"));
	static const FName inFireUser2(TEXT("FireUser2"));
	static const FName inFireUser3(TEXT("FireUser3"));
	static const FName inFireUser4(TEXT("FireUser4"));
	static const FName onFireUser1(TEXT("OnUser1"));
	static const FName onFireUser2(TEXT("OnUser2"));
	static const FName onFireUser3(TEXT("OnUser3"));
	static const FName onFireUser4(TEXT("OnUser4"));
	if (inputName == inKill || inputName == inKillHierarchy)
	{
		Destroy();
		return true;
	}
	else if (inputName == inAddOutput)
	{
		// Not yet supported!
		return false;
	}
	else if (inputName == inFireUser1)
	{
		FireOutput(onFireUser1, args, this, caller);
		return true;
	}
	else if (inputName == inFireUser2)
	{
		FireOutput(onFireUser2, args, this, caller);
		return true;
	}
	else if (inputName == inFireUser3)
	{
		FireOutput(onFireUser3, args, this, caller);
		return true;
	}
	else if (inputName == inFireUser4)
	{
		FireOutput(onFireUser4, args, this, caller);
		return true;
	}
	else
	{
		OnInputFired(inputName, args, caller, activator);
		return true;
	}
}

/**
 * Fires a logic output on this entity.
 * Returns the number of entities that succesfully handled the output.
 */
int ABaseEntity::FireOutput(const FName outputName, const TArray<FString>& args, ABaseEntity* caller = nullptr, ABaseEntity* activator = nullptr)
{
	// Gather all relevant outputs to fire
	TArray<const FEntityLogicOutput&> toFire;
	for (int i = LogicOutputs.Num() - 1; i >= 0; --i)
	{
		const FEntityLogicOutput& logicOutput = LogicOutputs[i];
		if (logicOutput.InputName == outputName)
		{
			toFire.Add(logicOutput);
			if (logicOutput.Once)
			{
				LogicOutputs.RemoveAt(i);
			}
		}
	}

	// TODO: Deal with delay somehow...
	// Timers?

	// Iterate all and fire them
	int result = 0;
	for (const FEntityLogicOutput& logicOutput : toFire)
	{
		TArray<ABaseEntity*> targets;

		// Test for special targetnames
		if (logicOutput.TargetName == tnActivator)
		{
			if (activator != nullptr) { targets.Add(activator); }
		}
		else if (logicOutput.TargetName == tnCaller)
		{
			if (caller != nullptr) { targets.Add(caller); }
		}
		else if (logicOutput.TargetName == tnSelf)
		{
			targets.Add(this);
		}
		else
		{
			IHL2Runtime::Get().FindEntitiesByTargetName(GetWorld(), logicOutput.TargetName, targets);
		}

		// Prepare arguments
		TArray<FString> arguments = logicOutput.Params;
		arguments.Reserve(args.Num());
		for (int i = 0; i < args.Num(); ++i)
		{
			if (i > arguments.Num())
			{
				arguments.Add(args[i]);
			}
			else if (arguments[i].IsEmpty())
			{
				arguments[i] = args[i];
			}
		}
		arguments.Reserve(FMath::Max(args.Num(), logicOutput.Params.Num()));

		// Iterate all entities
		for (ABaseEntity* targetEntity : targets)
		{
			// Fire the input!
			if (targetEntity->FireInput(logicOutput.InputName, arguments, this, caller))
			{
				++result;
			}
		}
	}

	return result;
}

/**
 * Resets all logic outputs to their initial state.
 */
void ABaseEntity::ResetLogicOutputs()
{
	LogicOutputs.Empty();
	for (const auto& pair : EntityData.KeyValues)
	{
		TArray<FString> logicArgs;
		pair.Value.ParseIntoArray(logicArgs, TEXT(","), false);
		if (logicArgs.Num() >= 4)
		{
			FEntityLogicOutput logicOutput;
			logicOutput.TargetName = FName(*logicArgs[0].Trim());
			logicOutput.OutputName = pair.Key;
			logicOutput.InputName = FName(*logicArgs[1].Trim());
			logicOutput.Delay = FCString::Atof(*logicArgs.Last(1));
			logicOutput.Once = FCString::Atoi(*logicArgs.Last(0)) != -1;
			logicArgs.RemoveAt(logicArgs.Num() - 2, 2);
			logicArgs.RemoveAt(0, 2);
			logicOutput.Params = logicArgs;
			LogicOutputs.Add(logicOutput);
		}
	}
}


void ABaseEntity::OnInputFired_Implementation(const FName inputName, const TArray<FString>& args, ABaseEntity* caller, ABaseEntity* activator)
{
	// Left for blueprint to override and handle custom inputs
}