// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Module/GameInstanceModule.h"

#include "UniversalSwatchSlotsDefinitions.h"

#include "UniversalSwatchSlotsGIModule.generated.h"



/**
 *
 */
UCLASS()
class UNIVERSALSWATCHSLOTS_API UUniversalSwatchSlotsGIModule : public UGameInstanceModule
{
	GENERATED_BODY()

	/**
	 * Create a new swatch descriptor using the desired swatch group, name and ID.
	 *
	 * @param	SlotID					The slot ID used by swatch descriptor.
	 * @param	SwapID					The ID to give to the potential present swatch at slot ID. Be sure that Swap slot ID is available as it will be overwritten.
	 * @param	DisplayName				The name to give to the swatch descriptor.
	 * @param	DisplayName				The generated name to give to the swatch descriptor class.
	 * @param	Priority				The priority to give to this swatch.
	 * @param   PrimaryColor			The primary color used to generate the swatch icon.
	 * @param	SecondaryColor			The secondary color used to generate the swatch icon.
	 * @param	SwatchGroup				The swatch group to use.
	 * @param	HasSwapped				Tells if a swap has occured.
	 *
	 * @warning Be sure that the desired swatch descriptor doesn't exist otherwise its CDO will be modified.
	 *
	 * @return The newly generated swatch descriptor, nullptr otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category = "Swatch")
	UUSSSwatchDesc* GenerateDynamicSwatchDescriptor(int32 UniqueID);

	/**
	 * Create a new swatch recipe using the desired swatch descriptor.
	 *
	 * @param	SwatchDescriptor		The swatch descriptor to use.
	 *
	 * @warning Be sure that a recipe for the given swatch descriptor doesn't exist otherwise its CDO will be modified.
	 *
	 * @return The newly generated swatch recipe, nullptr otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category = "Swatch")
	UUSSSwatchRecipe* GenerateDynamicSwatchRecipe(int32 UniqueID);

	/**
	 * Create a new swatch using the desired group ID and swatch name.
	 *
* Note: This function will create a new swatch group if the given group ID doensn't exist in the SwatchGroupArray and call GenerateDynamicSwatchGroup -> GenerateDynamicSwatchDescriptor -> GenerateDynamicSwatchRecipe functions. This function does nothing if the swatch descriptor / recipe already exist.
	 *
	 * @param	UniqueGroupID				The swatch group ID to use. If the group doesn't exist it will be created.
	 * @param	GroupDisplayName			The name to give to the swatch group. If the group already exist its name will be changed.
	 * @param	GroupPriority				The priority to give to the swatch group. If the group already exist its priority will be changed.
	 * @param	SwatchPriority				The priority to give to this swatch.
	 * @param	SwatchUniqueID				The swatch descriptor ID to use. If the descriptor ID is already in use this function will exit without doing anything.
	 * @param	SwatchDisplayName			The name to give to the swatch descriptor.
	 * @param   PrimaryColor				The primary color of the swatch.
	 * @param	SecondaryColor				The secondary color of the swatch.
	 * @param	SwatchGroup					The used swatch group. NULL if the function was aborted.
	 * @param	SwatchDescriptor			The generated swatch descriptor. NULL if the function was aborted.
	 * @param	SwatchRecipe				The generated swatch recipe. NULL if the function was aborted.
	 *
	 * @return True if the swatch was created, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category = "Swatch")
	void GenerateDynamicSwatchClasses();

public:

	/* The list of all generated swatch descriptors. This array is modified when the GenerateDynamicSwatchDescriptor function is called.  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Swatch")
	TMap<int32, UClass*> SwatchDescriptorArray;
	UPROPERTY()
	TArray<UClass*> tmpSwatchDescriptorArray;

	/* The build gun blueprint class that will be used by the dynamically created swatch recipes. This array is modified when the GenerateDynamicSwatchRecipe function is called. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Swatch")
	TMap<int32, UClass*> SwatchRecipeArray;

protected:

	UPROPERTY()
	TArray<UClass*> GeneratedClasses;

	UClass* GenerateDynamicClass(UClass* TemplateClass, FName GeneratedClassName);

	FString PackageName = "/UniversalSwatchSlots";
};
