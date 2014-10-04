#pragma once
class BrushSettings
{
	int size;
	double opacity;

public:
	BrushSettings();

	int GetSizeAsInteger() const;
	double GetSizeAsDouble() const;
	float GetSizeAsFloat() const;
	void SetSize(const int size);

	char GetOpacityAsChar() const;
	double GetOpacityAsDouble() const;
	void SetOpacity(const double opacity);
};

