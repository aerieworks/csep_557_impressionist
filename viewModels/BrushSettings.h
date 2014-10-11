#pragma once
class BrushSettings
{
	double lineWidth;
	double opacity;
	int size;
	double brushDirection;

public:
	BrushSettings();

	double GetLineWidthAsDouble() const;
	float GetLineWidthAsFloat() const;
	void SetLineWidth(const double lineWidth);

	char GetOpacityAsChar() const;
	double GetOpacityAsDouble() const;
	void SetOpacity(const double opacity);

	int GetSizeAsInteger() const;
	double GetSizeAsDouble() const;
	float GetSizeAsFloat() const;
	void SetSize(const int size);

	double GetBrushDirectionAsDouble() const;
	void SetBrushDirection(const double brushDirection);
};

