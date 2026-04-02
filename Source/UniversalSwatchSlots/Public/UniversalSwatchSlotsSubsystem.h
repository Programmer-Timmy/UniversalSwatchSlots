// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystem/ModSubsystem.h"
#include "FGSaveInterface.h"

#include "UniversalSwatchSlotsDefinitions.h"

#include "UniversalSwatchSlotsSubsystem.generated.h"



/**
 *
 */
UCLASS()
class UNIVERSALSWATCHSLOTS_API AUniversalSwatchSlotsSubsystem : public AModSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()

public:

	/**
	 * Get the existing of this subsystem.
	 *
	 * @param	WorldContext		The worldcontext to retrieve the subsystem from.
	 */
	UFUNCTION(BlueprintPure, Category = "Subsystem", DisplayName = "GetAUniversalSwatchSlotsSubsystem", meta = (DefaultToSelf = "WorldContext"))
	static AUniversalSwatchSlotsSubsystem* Get(UObject* WorldContext);


	/**
	 * Add new swatch color slots to the gamestate using the given swatch descriptors.
	 *
	 * @param	SwatchDescriptions		The swatch descriptors to use.
	 */
	UFUNCTION(BlueprintCallable, Category = "Swatch")
	void AddNewSwatchesColorSlotsToGameState(TArray<UUSSSwatchDesc*> SwatchDescriptions);

	/**
	 * Generate all the groups, swatches descriptor and receipes of the given palette.
	 *
	 * @param	Palette			The palette to generate.
	 */
	UFUNCTION(BlueprintCallable, Category = "Swatch")
	void GeneratePalette(FUSSPalette Palette);

	/**
	 * Create a new swatch using the desired group ID and swatch name.
	 *
	 * Note: This function will create a new swatch group if the given group ID doensn't exist in the SwatchGroupArray and call GenerateDynamicSwatchGroup -> GenerateDynamicSwatchDescriptor -> GenerateDynamicSwatchRecipe functions. This function does nothing if the swatch descriptor / recipe already exist.
	 *
	 * @param	SwatchInformation			The swatch information to use.
	 * @param	SwatchGroup					The used swatch group. NULL if the function was aborted.
	 * @param	SwatchDescriptor			The generated swatch descriptor. NULL if the function was aborted.
	 * @param	SwatchRecipe				The generated swatch recipe. NULL if the function was aborted.
	 *
	 * @return True if the swatch was created, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category = "Swatch")
	bool GenerateNewSwatchUsingInfo(UUSSSwatchGroup* SwatchGroup, FUSSSwatch SwatchInfo);

	/**
	 * Create a new swatch group using the desired ID, name and priority.
	 *
	 * Note : The newly generated swatch group will be added to the SwatchGroupArray at the given UniqueGroupID.
	 *
	 * @param	UniqueGroupID			The ID to give to the swatch group.
	 * @param	GroupInfo				The swatch group information used to build the group.
	 *
	 * @warning Be sure that the desired swatch group doesn't exist otherwise its CDO will be modified.
	 *
	 * @return The newly generated swatch group, nullptr otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category = "Swatch")
	UUSSSwatchGroup* GenerateDynamicSwatchGroup(int32 UniqueGroupID, FUSSGroup GroupInfo);

	/**
	 * Create a new swatch descriptor using the desired swatch group, name and ID.
	 *
	 * @param	SlotID					The slot ID used by swatch descriptor.
	  @param	GenName					The generated name to give to the swatch descriptor class.
	 * @param	SwatchGroup				The swatch group to use.
	 * @param	SwatchInfo				The swatch information used to build the descriptor.
	 *
	 * @warning Be sure that the desired swatch descriptor doesn't exist otherwise its CDO will be modified.
	 *
	 * @return The newly generated swatch descriptor, nullptr otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category = "Swatch")
	UUSSSwatchDesc* GenerateDynamicSwatchDescriptor(int32 SlotID, FString GenName, UFGCustomizerSubCategory* SwatchGroup, FUSSSwatch SwatchInfo);

	/**
	 * Create a new swatch recipe using the desired swatch descriptor.
	 *
	 * @param	UniqueID				The swatch receipe ID (should be the same as the swatch descriptor one).
	 * @param	SwatchDescriptor		The swatch descriptor to use.
	 *
	 * @warning Be sure that a recipe for the given swatch descriptor doesn't exist otherwise its CDO will be modified.
	 *
	 * @return The newly generated swatch recipe, nullptr otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category = "Swatch")
	UUSSSwatchRecipe* GenerateDynamicSwatchRecipe(int32 UniqueID, UUSSSwatchDesc* SwatchDescriptor);

	/**
	 * Patch existing buildings descriptor.
	 */
	UFUNCTION(BlueprintCallable, Category = "Subsystem")
	void PatchBuildingsSwatchDescriptor();

	/**
	 * Find the matching saved swatch if any.
	 *
	 * @param	GeneratedName			The swatch generated name (use the BuildSwatchGenName function to create one).
	 * @param	Out						The saved swatch info if found, NULL otherwise.
	 *
	 * @return True if the swatch was found, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category = "Swatch")
	bool FindSavedSwatch(FString GeneratedName, FUSSSwatchSaveInfo& Out);

	/**
	 * Update the saved swatches array.
	 *
	 *
	 * @param	GeneratedName			The swatch generated name (use the BuildSwatchGenName function to create one).
	 * @param	Out						The saved swatch info if found, NULL otherwise.
	 *
	 * @return True if the swatch was found, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category = "Swatch")
	void UpdateSavedSwatches(TArray<UUSSSwatchDesc*> ToSave);

	/**
	 * Update the USS version used for saving this file.
	 */
	UFUNCTION(BlueprintCallable, Category = "Subsystem")
	void UpdateSavedVersion();

	/**
	 * Update The available valid swatche slots ID.
	 */
	void RetrieveFreeColorSlotID();

public:

	/* Tells if More Swatch slots mod is loaded. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	bool IsUsingMSS;

	/* The build gun blueprint class that will be used by the dynamically created swatch recipes. */
	UPROPERTY(EditDefaultsOnly, Category = "Swatch")
	TSoftClassPtr<UObject> BuildGunBPClass;

	/* The category under which the generated swatch group should appear. */
	UPROPERTY(EditDefaultsOnly, Category = "Swatch")
	TSubclassOf<UFGCustomizerCategory> SwatchCategory = UFGCustomizerCategory::StaticClass();

	/* The paint finish to apply to our swatches. */
	UPROPERTY(EditDefaultsOnly, Category = "Swatch")
	TArray<TSubclassOf<UFGFactoryCustomizationDescriptor_PaintFinish>>PaintFinishes;

	/* The description that should be added to all swatches. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Swatch")
	FText SwatchDescription;

	/* The list of all available swatch groups. This array is modified when the GenerateDynamicSwatchGroup function is called. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Swatch")
	TMap<int32, UUSSSwatchGroup*> SwatchGroupArray;

	/* The list of all generated swatch descriptors. This array is modified when the GenerateDynamicSwatchDescriptor function is called.  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Swatch")
	TMap<int32, UUSSSwatchDesc*> SwatchDescriptorArray;

	/* The build gun blueprint class that will be used by the dynamically created swatch recipes. This array is modified when the GenerateDynamicSwatchRecipe function is called. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Swatch")
	TMap<int32, UUSSSwatchRecipe*> SwatchRecipeArray;

	/* A detailed array that contains info about saved swatches. */
	UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Saving")
	TArray<FUSSSwatchSaveInfo> SavedSwatches;

	/* Gives the USS version used by the save file. */
	UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Saving")
	EUSSVersion SaveVersion = EUSSVersion::None;

	/* Tells is More swatch slots was installed when the game was saved. */
	UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Saving")
	bool WasUsingMSS = false;


protected:

	friend class UUniversalSwatchSlotsWorldModule;

	/* This map contains the number of time a unique swatch name appears in the configuration. */
	UPROPERTY()
	TMap<FString, int32> SwatchNameCount;

	/* This array contains all the free color slot IDs. */
	UPROPERTY()
	TArray<int32> ValidSlotIDs;

	/* The internal map to check if all previous saved swatches have a macthing loaded swatch. If a key is not equal to its value we should get all actors of FGBuilding type to re-reference the swatches. */
	TMap <int, int> InternalSwatchMatch;
};
