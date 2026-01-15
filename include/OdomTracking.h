#pragma once

double GetX();
double GetY();
double GetHeading();

void ResetOdom(double startX = 0.0, double startY = 0.0, double startHeading = 0.0);
void UpdateOdom();