#pragma once
enum DirectionMode {
  Fixed,
  Gradient
};

class BrushSettings {
	double lineWidth;
	double opacity;
	int size;
	double brushDirection;
  DirectionMode directionMode;

public:
	BrushSettings();

	double getLineWidthAsDouble() const;
	float getLineWidthAsFloat() const;
	void setLineWidth(const double lineWidth);

	char getOpacityAsChar() const;
	double getOpacityAsDouble() const;
	void setOpacity(const double opacity);

	int getSizeAsInteger() const;
	double getSizeAsDouble() const;
	float getSizeAsFloat() const;
	void setSize(const int size);

	double getBrushDirectionAsDouble() const;
	void setBrushDirection(const double brushDirection);

  DirectionMode getBrushDirectionMode() const;
  void setBrushDirectionMode(const DirectionMode directionMode);
};

