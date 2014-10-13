#pragma once
enum ColorMode {
  FixedColor,
  FromSource
};

enum DirectionMode {
  FixedDirection,
  Gradient,
  Random
};

class BrushSettings {
  ColorMode colorMode;
  unsigned char color[4];
	double lineWidth;
	double opacity;
	int size;
	double brushDirection;
  double scatterMinSize;
  double scatterMaxSize;
  int scatterMinCount;
  int scatterMaxCount;
  DirectionMode directionMode;

public:
	BrushSettings();
  BrushSettings(const BrushSettings& settings);

  ColorMode getColorMode() const;
  void setColorMode(ColorMode mode);

  const unsigned char* getColor() const;
  void setColor(const unsigned char* color);

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

  double getScatterMinSizeAsDouble() const;
  void setScatterMinSize(const double size);
  double getScatterMaxSizeAsDouble() const;
  void setScatterMaxSize(const double size);

  int getScatterMinCountAsInteger() const;
  void setScatterMinCount(const int count);
  int getScatterMaxCountAsInteger() const;
  void setScatterMaxCount(const int count);
};

