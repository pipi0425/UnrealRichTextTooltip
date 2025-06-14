// Fill out your copyright notice in the Description page of Project Settings.


#include "RichTextBlockTooltipDecorator.h"

#include "Blueprint/UserWidget.h"
#include "Components/RichTextBlock.h"

class FRichInlineTooltip : public FRichTextDecorator
{
public:
	FRichInlineTooltip(URichTextBlock* InOwner, URichTextBlockTooltipDecorator* InDecorator)
		: FRichTextDecorator(InOwner)
		, Decorator(InDecorator)
	{
	}

	// Only valid if text is: <tooltip id="Some infos">Some text</>
	virtual bool Supports(const FTextRunParseResults& RunParseResult, const FString& Text) const override
	{
		return RunParseResult.Name == TEXT("tooltip") && RunParseResult.MetaData.Contains(TEXT("id"));
	}

protected:
	virtual TSharedPtr<SWidget> CreateDecoratorWidget(const FTextRunInfo& InRunInfo, const FTextBlockStyle& InTextStyle) const override
	{
		auto widget = SNew(STextBlock).Text(InRunInfo.Content).TextStyle(&Decorator->TextStyle);

		if (Decorator->IsValidLowLevel() && Owner->GetWorld())
		{
			if (UUserWidget* TooltipWidget = Decorator->CreateTooltipWidget(Owner->GetWorld()->GetFirstPlayerController(), InRunInfo.MetaData[TEXT("id")]))
			{
				widget->SetToolTip(SNew(SToolTip).Content()[TooltipWidget->TakeWidget()]);
			}
		}

		return widget;
	}

private:
	URichTextBlockTooltipDecorator* Decorator;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

URichTextBlockTooltipDecorator::URichTextBlockTooltipDecorator(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

TSharedPtr<ITextDecorator> URichTextBlockTooltipDecorator::CreateDecorator(URichTextBlock* InOwner)
{
	return MakeShareable(new FRichInlineTooltip(InOwner, this));
}
