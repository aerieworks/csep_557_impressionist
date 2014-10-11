#include <math.h>
#include <Windows.h>
#include "KernelFilter.h"


KernelFilter::KernelFilter(const int width, const int height)
	: kernelWidth(width), kernelHeight(height), divisor(1), offset(0)
{
	kernel = new double[kernelWidth * kernelHeight];
	for (int i = 0; i < kernelWidth * kernelHeight; i++)
	{
		kernel[i] = 0;
	}
	kernel[(kernelHeight / 2 * kernelWidth) + kernelWidth / 2] = 1;
}

KernelFilter::~KernelFilter()
{
	delete[] kernel;
}

/*
 *	INPUT: 
 *		source:		the original image buffer, 
 *		dest:		the image buffer to put the resulting
 *					image in.  It is always the same size
 *					as the source buffer.
 *		width:		the width of the image buffer
 *		height:		the height of the image buffer
 *					the buffer is arranged such that 
 *					origImg[3*(row*srcBufferWidth+column)+0], 
 *					origImg[3*(row*srcBufferWidth+column)+1], 
 *					origImg[3*(row*srcBufferWidth+column)+2]
 *					are R, G, B values for pixel at (column, row).
 */
void KernelFilter::Apply(const unsigned char* source, unsigned char* dest, const int width, const int height) const
{
	// Calculate the row and column offset for the (0, 0) kernel value (i.e. (-2, -2) for a 5x5 kernel).
	// Note that this has an interesting effect if kernel dimensions are even: it would ignore the current pixel's row/column.
	const int knlRowOffset = -(int)floor(kernelHeight / 2.0);
	const int knlColOffset = -(int)floor(kernelWidth / 2.0);
	for (int destRow = 0; destRow < height; destRow++)
	{
		for (int destCol = 0; destCol < width; destCol++)
		{
			// Calculate where in the destination buffer to write this pixel's value.
			const int destPixelStart = 3 * (destRow * width + destCol);

			// We apply the filter to a pixel 3 times, once for each color channel.
			for (int color = 0; color < 3; color++)
			{
				double combinedValue = 0;
				for (int knlRow = 0; knlRow < kernelHeight; knlRow++)
				{
					// Calculate the source row to look at, given this position in the kernel.
					// Note that the kernel offset is subtracted, to account for OpenGL storing images upside down.
					// So the (-2, -2) offset becomes effectively (-2, 2).
					const int sourceRow = max(0, min(height - 1, destRow - (knlRowOffset + knlRow)));
					for (int knlCol = 0; knlCol < kernelWidth; knlCol++)
					{
						// Calculate the destination row to look at, given this position in the kernel.
						// The kernel offset is added for columns, since the image is stored normally on the X axis.
						const int sourceCol = max(0, min(width - 1, destCol + knlColOffset + knlCol));

						unsigned char sourceValue = source[3 * (sourceRow * width + sourceCol) + color];
						const double knlValue = kernel[knlRow * kernelWidth + knlCol];

						// Apply the kernel value to the source value and add it to the cumulative value.
						combinedValue += sourceValue * knlValue;
					}
				}

				// Adjust filter output and make sure it fits within the bounds of an RGB color value.
				const double adjustedValue = (double)combinedValue / divisor + offset;
				dest[destPixelStart + color] = FitFilterOutput(adjustedValue);
			}
		}
	}
}

//------------------------------------------------------------------
// Fits the value output by a filter to the range allowed within an
// image.  Values will be rounded and truncated to fit within the
// inclusive range [0, 255].
//------------------------------------------------------------------
unsigned char KernelFilter::FitFilterOutput(const double value) const
{
	return (unsigned char)max(0, min(255, round(value)));
}

double KernelFilter::GetKernelValue(const int row, const int col) const
{
	return kernel[row * kernelWidth + col];
}

void KernelFilter::SetKernelValue(const int row, const int col, const double value)
{
	kernel[row * kernelWidth + col] = value;
}

double KernelFilter::GetDivisor() const
{
	return divisor;
}

void KernelFilter::SetDivisor(const double divisor)
{
	this->divisor = divisor;
}

double KernelFilter::GetOffset() const
{
	return offset;
}

void KernelFilter::SetOffset(const double offset)
{
	this->offset = offset;
}
