// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/RichTextBlockDecorator.h"
#include "RichTextBlockTooltipDecorator.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class YOURPROJECT_API URichTextBlockTooltipDecorator : public URichTextBlockDecorator
{
	GENERATED_BODY()
	
public:

	URichTextBlockTooltipDecorator(const FObjectInitializer& ObjectInitializer);

	virtual TSharedPtr<ITextDecorator> CreateDecorator(URichTextBlock* InOwner) override;

	UFUNCTION(BlueprintImplementableEvent)
	UUserWidget* CreateTooltipWidget(APlayerController* playerController, const FString& id);

	// Style used for text
	UPROPERTY(EditAnywhere, Category = Appearance)
	FTextBlockStyle TextStyle;
};
