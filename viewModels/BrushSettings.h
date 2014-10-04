#pragma once
class BrushSettings
{
	int size;

public:
	BrushSettings();

	int GetSizeAsInteger() const;
	double GetSizeAsDouble() const;
	float GetSizeAsFloat() const;
	void SetSize(const int size);
};

