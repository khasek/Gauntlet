/*******************************************************************************
* GauntletPlayerController handles character selection logic. Once regular
* gameplay begins, it works just like any other PlayerController.
*
* Author: Kendal Hasek
*******************************************************************************/

#include "Kismet/GameplayStatics.h"
#include "GauntletPlayerController.h"

/// <summary>
/// Enable selection screen input handling
/// </summary>
void AGauntletPlayerController::BeginPlay()
{
	Super::BeginPlay();

	gameInstance = Cast<UGauntletGameInstance>(GetGameInstance());

	// Enable both cursor and button input
	SetInputMode(FInputModeGameAndUI());

	// Set up selection screen input
	EnableInput(this);
	SetupInputComponent();
}

/// <summary>
/// Bind character selection events
/// </summary>
void AGauntletPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SelectWarrior", IE_Pressed, this, &AGauntletPlayerController::SelectWarrior);
	InputComponent->BindAction("SelectValkyrie", IE_Pressed, this, &AGauntletPlayerController::SelectValkyrie);
	InputComponent->BindAction("SelectWizard", IE_Pressed, this, &AGauntletPlayerController::SelectWizard);
	InputComponent->BindAction("SelectElf", IE_Pressed, this, &AGauntletPlayerController::SelectElf);
}

/// <summary>
/// Disable character selection input and prepare for regular gameplay
/// </summary>
void AGauntletPlayerController::FreezeCharacterSelection()
{
	InputComponent->ClearActionBindings();
	SetInputMode(FInputModeGameOnly());
}

/// <summary>
/// Called when a player selects the Warrior character class
/// </summary>
void AGauntletPlayerController::SelectWarrior()
{
	if (gameInstance->AddCharacterAssignment("Warrior", this))
	{
		WarriorSelected.Broadcast(UGameplayStatics::GetPlayerControllerID(this));
	}
}

/// <summary>
/// Called when a player selects the Valkyrie character class
/// </summary>
void AGauntletPlayerController::SelectValkyrie()
{
	if (gameInstance->AddCharacterAssignment("Valkyrie", this))
	{
		ValkyrieSelected.Broadcast(UGameplayStatics::GetPlayerControllerID(this));
	}
}

/// <summary>
/// Called when a player selects the Wizard character class
/// </summary>
void AGauntletPlayerController::SelectWizard()
{
	if (gameInstance->AddCharacterAssignment("Wizard", this))
	{
		WizardSelected.Broadcast(UGameplayStatics::GetPlayerControllerID(this));
	}
}

/// <summary>
/// Called when a player selects the Elf character class
/// </summary>
void AGauntletPlayerController::SelectElf()
{
	if (gameInstance->AddCharacterAssignment("Elf", this))
	{
		ElfSelected.Broadcast(UGameplayStatics::GetPlayerControllerID(this));
	}
}
