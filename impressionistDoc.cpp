// 
// impressionistDoc.cpp
//
// It basically maintain the Image for answering the color query from the brush.
// It also acts as the bridge between brushes and UI (including views)
//


#include <FL/fl_ask.H>

#include <algorithm>
#include <sstream>
#include "impressionistDoc.h"
#include "impressionistUI.h"

#include "impBrush.h"

// Include individual brush headers here.
#include "CircleBrush.h"
#include "LineBrush.h"
#include "Log.h"
#include "pointBrush.h"
#include "ScatteredCircleBrush.h"
#include "ScatteredLineBrush.h"
#include "ScatteredPointBrush.h"


#define DESTROY(p)	{  if ((p)!=NULL) {delete [] p; p=NULL; } }

ImpressionistDoc::ImpressionistDoc() 
{
	// Set NULL image name as init. 
	m_imageName[0]	='\0';	

	m_nWidth		= -1;
	m_ucImage		= NULL;
	m_ucPainting	= NULL;
	m_ucPreviewBackup = NULL;


	// create one instance of each brush
	ImpBrush::c_nBrushCount	= NUM_BRUSH_TYPE;
	ImpBrush::c_pBrushes	= new ImpBrush* [ImpBrush::c_nBrushCount];

	ImpBrush::c_pBrushes[BRUSH_POINTS]	= new PointBrush( this, "Points" );

	// Note: You should implement these 5 brushes.  They are set the same (PointBrush) for now
	ImpBrush::c_pBrushes[BRUSH_LINES]				
		= new LineBrush( this, "Lines" );
	ImpBrush::c_pBrushes[BRUSH_CIRCLES]				
		= new CircleBrush( this, "Circles" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_POINTS]	
		= new ScatteredPointBrush( this, "Scattered Points" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_LINES]		
		= new ScatteredLineBrush( this, "Scattered Lines" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_CIRCLES]	
		= new ScatteredCircleBrush( this, "Scattered Circles" );

	// make one of the brushes current
	m_pCurrentBrush	= ImpBrush::c_pBrushes[0];

}

ImpressionistDoc::~ImpressionistDoc()
{
	// Empty and deallocate the undo and redo stacks.
	ClearStack(m_undoStack);
	ClearStack(m_redoStack);
}

//---------------------------------------------------------
// Set the current UI 
//---------------------------------------------------------
void ImpressionistDoc::setUI(ImpressionistUI* ui) 
{
	m_pUI	= ui;
}

//---------------------------------------------------------
// Returns the active picture/painting name
//---------------------------------------------------------
char* ImpressionistDoc::getImageName() 
{
	return m_imageName;
}

//---------------------------------------------------------
// Called by the UI when the user changes the brush type.
// type: one of the defined brush types.
//---------------------------------------------------------
void ImpressionistDoc::setBrushType(int type)
{
	m_pCurrentBrush	= ImpBrush::c_pBrushes[type];
}

//---------------------------------------------------------
// Load the specified image
// This is called by the UI when the load image button is 
// pressed.
//---------------------------------------------------------
int ImpressionistDoc::loadImage(const char *iname) 
{
	// try to open the image to read
	unsigned char*	data;
	int				width, 
					height;

	if ( (data=load(iname, width, height))==NULL ) 
	{
		fl_alert("Can't load image file");
		return 0;
	}

	// reflect the fact of loading the new image
	m_nWidth		= width;
	m_nPaintWidth	= width;
	m_nHeight		= height;
	m_nPaintHeight	= height;

	// release old storage
	delete [] m_ucImage;
	delete [] m_ucPainting;
	delete [] m_ucPreviewBackup;

	m_ucImage		= data;

	// allocate space for draw view
	m_ucPainting		= new unsigned char [width*height*3];
	m_ucPreviewBackup	= new unsigned char [width*height*3];
	memset(m_ucPainting, 0, width*height*3);

	m_pUI->m_mainWindow->resize(m_pUI->m_mainWindow->x(), 
								m_pUI->m_mainWindow->y(), 
								width*2, 
								height+25);

	// display it on origView
	m_pUI->m_origView->resizeWindow(width, height);	
	m_pUI->m_origView->refresh();

	// refresh paint view as well
	m_pUI->m_paintView->resizeWindow(width, height);	
	m_pUI->m_paintView->refresh();


	return 1;
}


//----------------------------------------------------------------
// Save the specified image
// This is called by the UI when the save image menu button is 
// pressed.
//----------------------------------------------------------------
int ImpressionistDoc::saveImage(const char *iname, const char * type, int quality) 
{

	save(iname, m_ucPainting, m_nPaintWidth, m_nPaintHeight, type, quality);

	return 1;
}

//----------------------------------------------------------------
// Clear the drawing canvas
// This is called by the UI when the clear canvas menu item is 
// chosen
//-----------------------------------------------------------------
int ImpressionistDoc::clearCanvas() 
{

	// Release old storage
	if ( m_ucPainting ) 
	{
		delete [] m_ucPainting;

		// allocate space for draw view
		m_ucPainting	= new unsigned char [m_nPaintWidth*m_nPaintHeight*3];
		memset(m_ucPainting, 0, m_nPaintWidth*m_nPaintHeight*3);

		// refresh paint view as well	
		m_pUI->m_paintView->refresh();
	}
	
	return 0;
}

// Apply the filter specified by filter_kernel to the 
// each pixel in the source buffer and place the resulting
// pixel in the destination buffer.  

// This is called from the UI when the
// "preview" or "apply" button is pressed in the filter dialog.



/*
 *	INPUT: 
 *		sourceBuffer:		the original image buffer, 
 *		srcBufferWidth:		the width of the image buffer
 *		srcBufferHeight:	the height of the image buffer
 *							the buffer is arranged such that 
 *							origImg[3*(row*srcBufferWidth+column)+0], 
 *							origImg[3*(row*srcBufferWidth+column)+1], 
 *							origImg[3*(row*srcBufferWidth+column)+2]
 *							are R, G, B values for pixel at (column, row).
 *		destBuffer:			the image buffer to put the resulting
 *							image in.  It is always the same size
 *							as the source buffer.
 *
 *      filterKernel:		the 2D filter kernel,
 *		knlWidth:			the width of the kernel
 *		knlHeight:			the height of the kernel
 *
 *		divisor, offset:	each pixel after filtering should be
 *							divided by divisor and then added by offset
 */
void ImpressionistDoc::applyFilter( const unsigned char* sourceBuffer,
		int srcBufferWidth, int srcBufferHeight,
		unsigned char* destBuffer,
		const double *filterKernel, 
		int knlWidth, int knlHeight, 
		double divisor, double offset )
{
	// Calculate the row and column offset for the (0, 0) kernel value (i.e. (-2, -2) for a 5x5 kernel).
	// Note that this has an interesting effect if kernel dimensions are even: it would ignore the current pixel's row/column.
	const int knlRowOffset = -floor(knlHeight / 2);
	const int knlColOffset = -floor(knlWidth / 2);
	for (int destRow = 0; destRow < srcBufferHeight; destRow++)
	{
		for (int destCol = 0; destCol < srcBufferWidth; destCol++)
		{
			// Calculate where in the destination buffer to write this pixel's value.
			const int destPixelStart = 3 * (destRow * srcBufferWidth + destCol);

			// We apply the filter to a pixel 3 times, once for each color channel.
			for (int color = 0; color < 3; color++)
			{
				int combinedValue = 0;
				for (int knlRow = 0; knlRow < knlHeight; knlRow++)
				{
					// Calculate the source row to look at, given this position in the kernel.
					// Note that the kernel offset is subtracted, to account for OpenGL storing images upside down.
					// So the (-2, -2) offset becomes effectively (-2, 2).
					const int sourceRow = max(0, min(srcBufferHeight - 1, destRow - (knlRowOffset + knlRow)));
					for (int knlCol = 0; knlCol < knlWidth; knlCol++)
					{
						// Calculate the destination row to look at, given this position in the kernel.
						// The kernel offset is added for columns, since the image is stored normally on the X axis.
						const int sourceCol = max(0, min(srcBufferWidth - 1, destCol + knlColOffset + knlCol));
						unsigned char sourceValue;
						if (m_pUI->fltDesignUI->applyToPainting->value() == 1)
						{
							// If applying to the painting, get the source value from the preview buffer.
							sourceValue = sourceBuffer[3 * (sourceRow * srcBufferWidth + sourceCol) + color];
						}
						else
						{
							// If applying to the source image, get the source value from the source image.
							sourceValue = GetOriginalPixel(sourceCol, sourceRow)[color];
						}

						const double knlValue = filterKernel[knlRow * knlWidth + knlCol];
						// Apply the kernel value to the source value and add it to the cumulative value.
						combinedValue += sourceValue * knlValue;
					}
				}

				// Adjust filter output and make sure it fits within the bounds of an RGB color value.
				const double adjustedValue = (double)combinedValue / divisor + offset;
				destBuffer[destPixelStart + color] = FitFilterOutput(adjustedValue);
			}
		}
	}
}

//------------------------------------------------------------------
// Fits the value output by a filter to the range allowed within an
// image.  Values will be rounded and truncated to fit within the
// inclusive range [0, 255].
//------------------------------------------------------------------
unsigned char ImpressionistDoc::FitFilterOutput(const double value) const
{
	return max(0, min(255, round(value)));
}

//------------------------------------------------------------------
// Get the color of the pixel in the original image at coord x and y
//------------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( int x, int y )
{
	if ( x < 0 ) 
		x = 0;
	else if ( x >= m_nWidth ) 
		x = m_nWidth-1;

	if ( y < 0 ) 
		y = 0;
	else if ( y >= m_nHeight ) 
		y = m_nHeight-1;

	return (GLubyte*)(m_ucImage + 3 * (y*m_nWidth + x));
}

//----------------------------------------------------------------
// Get the color of the pixel in the original image at point p
//----------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( const Point p )
{
	return GetOriginalPixel( p.x, p.y );
}


//----------------------------------------------------------------
// Applies the specified pixels to the painting at the specified
// location.  Pixels are assumed to be ordered upside down, like
// OpenGL orders them.
//----------------------------------------------------------------
void ImpressionistDoc::ApplyToPainting(const Point location, const int width, const int height, const unsigned char* pixels)
{
	Log::Debug << "Applying to painting: " << width << " x " << height << " area starting at (" << location.x << ", " << location.y << ")." << Log::end;
	glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	m_pUI->m_paintView->refresh();
}

void ImpressionistDoc::ClearStack(std::stack<UndoItem*>& st)
{
	while (!st.empty())
	{
		UndoItem* item = st.top();
		delete item;
		st.pop();
	}
}

//----------------------------------------------------------------
// Performs the action and adds it to the undo queue.
//----------------------------------------------------------------
void ImpressionistDoc::AddUndoItem(UndoItem* item)
{
	m_undoStack.push(item);
	// Clear the redo stack when new actions are performed.
	ClearStack(m_redoStack);
	Log::Debug << "Undo item added: " << item->GetName() << ", can undo? " << CanUndo() << Log::end;
}

//----------------------------------------------------------------
// Gets whether or not there is an action that can be undone.
//----------------------------------------------------------------
bool ImpressionistDoc::CanUndo() const
{
	return !m_undoStack.empty();
}

//----------------------------------------------------------------
// Gets whether or not there is an action that can be redone.
//----------------------------------------------------------------
bool ImpressionistDoc::CanRedo() const
{
	return !m_redoStack.empty();
}

//----------------------------------------------------------------
// Undoes the most recent action.
//----------------------------------------------------------------
void ImpressionistDoc::Undo()
{
	if (CanUndo())
	{
		UndoItem* item = m_undoStack.top();
		Log::Debug << "Doc: Undoing " << item->GetName() << Log::end;
		m_pUI->m_paintView->HandleAction(item->GetUndoAction());
		m_redoStack.push(item);
		m_undoStack.pop();
	}
	else
	{
		Log::Debug << "Nothing to undo." << Log::end;
	}
}

//----------------------------------------------------------------
// Redoes the most recent action.
//----------------------------------------------------------------
void ImpressionistDoc::Redo()
{
	if (CanRedo())
	{
		UndoItem* item = m_redoStack.top();
		Log::Debug << "Doc: Redoing " << item->GetName() << Log::end;
		m_pUI->m_paintView->HandleAction(item->GetRedoAction());
		m_undoStack.push(item);
		m_redoStack.pop();
	}
	else
	{
		Log::Debug << "Nothing to redo." << Log::end;
	}
}
