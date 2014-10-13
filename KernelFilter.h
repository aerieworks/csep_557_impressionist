#pragma once
class KernelFilter
{
public:
	KernelFilter(const int width, const int height);
  KernelFilter(const int width, const int height, const double* kernel, double divisor, double offset);
	~KernelFilter();

	void apply(const unsigned char* source, unsigned char* dest, const int width, const int height) const;
  double evaluateAt(const unsigned char* source, const int x, const int y, const int width, const int height, const int channels) const;

	double getKernelValue(const int row, const int col) const;
	void setKernelValue(const int row, const int col, const double value);

	double getDivisor() const;
	void setDivisor(const double value);

	double getOffset() const;
	void setOffset(const double offset);
private:
	unsigned char fitFilterOutput(const double value) const;
	const int kernelWidth;
	const int kernelHeight;
  const int kernelXOffset;
  const int kernelYOffset;
	double* kernel;
	double divisor;
	double offset;
};

