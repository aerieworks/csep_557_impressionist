#pragma once
class KernelFilter
{
public:
	KernelFilter(const int width, const int height);
	~KernelFilter();

	void apply(const unsigned char* source, unsigned char* dest, const int width, const int height) const;

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
	double* kernel;
	double divisor;
	double offset;
};

