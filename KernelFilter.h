#pragma once
class KernelFilter
{
public:
	KernelFilter(const int width, const int height);
	~KernelFilter();

	void Apply(const unsigned char* source, unsigned char* dest, const int width, const int height) const;

	double GetKernelValue(const int row, const int col) const;
	void SetKernelValue(const int row, const int col, const double value);

	double GetDivisor() const;
	void SetDivisor(const double value);

	double GetOffset() const;
	void SetOffset(const double offset);
private:
	unsigned char FitFilterOutput(const double value) const;
	const int kernelWidth;
	const int kernelHeight;
	double* kernel;
	double divisor;
	double offset;
};

