// Shoot Them Game, All Right Reserved


#include "UI/STHealthBarWidget.h"
#include "Components/ProgressBar.h"

void USTHealthBarWidget::SetHealthPercent(float Percent)
{
	if (!HealthProgressbar) return;

	const auto HealthBarVisibility = (Percent > PercentVisibilityThreshold || FMath::IsNearlyZero(Percent))
		                                 ? ESlateVisibility::Hidden
		                                 : ESlateVisibility::Visible;
	HealthProgressbar->SetVisibility(HealthBarVisibility);

	const auto HealthBarColor = Percent > PercentColorThreshold ? GoodColor :BadColor;
	HealthProgressbar->SetFillColorAndOpacity(HealthBarColor);

	HealthProgressbar->SetPercent(Percent); 
}
