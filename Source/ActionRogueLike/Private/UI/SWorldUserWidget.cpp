// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SWorldUserWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"

void USWorldUserWidget::SetAttachedActor(AActor* InActor)
{
	AttachedActor = InActor;
}

void USWorldUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	FVector2D ScreenPosition;

	if(AttachedActor == nullptr)
	{
		RemoveFromParent();

		UE_LOG(LogTemp,Warning,TEXT("AttachedActor is no longer valid, removing health widget"));
		return;
	}
	
	if(UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(),AttachedActor->GetActorLocation() + WorldOffset,ScreenPosition))
	{
		float Scale = UWidgetLayoutLibrary::GetViewportScale(this);

		ScreenPosition /= Scale;

		if(ParentSizeBox)
		{
			ParentSizeBox->SetRenderTranslation(ScreenPosition);
		}
		
	}
}
