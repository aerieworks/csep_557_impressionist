//
// impressionistUI.cpp
//
// The user interface part for the program.
//

#include <string>

#include <FL/fl_ask.H>

#include <algorithm>

#include <math.h>

#include "impressionistUI.h"
#include "impressionistDoc.h"
#include "Log.h"

#include "dialog.h"

/*
//------------------------------ Widget Examples -------------------------------------------------
Here is some example code for all of the widgets that you may need to add to the
project.  You can copy and paste these into your code and then change them to
make them look how you want.  Descriptions for all of the widgets here can be found
in links on the fltk help session page.

//---------Window/Dialog and Menubar-----------------------------------

//----To install a window--------------------------
Fl_Window* myWindow = new Fl_Window(600, 300, "MyWindow");
myWindow->user_data((void*)(this));	// record self to be used by static callback functions

// install menu bar
myMenubar = new Fl_Menu_Bar(0, 0, 600, 25);
Fl_Menu_Item ImpressionistUI::myMenuItems[] = {
{ "&File",		0, 0, 0, FL_SUBMENU },
{ "&Load...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load },
{ "&Save...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save }.
{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
{ 0 },
{ "&Edit",		0, 0, 0, FL_SUBMENU },
{ "&Copy",FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_copy, (void *)COPY },
{ "&Cut",	FL_ALT + 'x', (Fl_Callback *)ImpressionistUI::cb_cut, (void *)CUT },
{ "&Paste",	FL_ALT + 'v', (Fl_Callback *)ImpressionistUI::cb_paste, (void *)PASTE },
{ 0 },
{ "&Help",		0, 0, 0, FL_SUBMENU },
{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
{ 0 },
{ 0 }
};
myMenubar->menu(myMenuItems);
m_mainWindow->end();

//----The window callback--------------------------
// One of the callbacks
void ImpressionistUI::cb_load(Fl_Menu_* o, void* v)
{
ImpressionistDoc *pDoc=whoami(o)->getDocument();

char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
if (newfile != NULL) {
pDoc->loadImage(newfile);
}
}


//------------Slider---------------------------------------

//----To install a slider--------------------------
Fl_Value_Slider * mySlider = new Fl_Value_Slider(10, 80, 300, 20, "My Value");
mySlider->user_data((void*)(this));	// record self to be used by static callback functions
mySlider->type(FL_HOR_NICE_SLIDER);
mySlider->labelfont(FL_COURIER);
mySlider->labelsize(12);
mySlider->minimum(1);
mySlider->maximum(40);
mySlider->step(1);
mySlider->value(m_nMyValue);
mySlider->align(FL_ALIGN_RIGHT);
mySlider->callback(cb_MyValueSlides);

//----The slider callback--------------------------
void ImpressionistUI::cb_MyValueSlides(Fl_Widget* o, void* v)
{
((ImpressionistUI*)(o->user_data()))->m_nMyValue=int( ((Fl_Slider *)o)->value() ) ;
}


//------------Choice---------------------------------------

//----To install a choice--------------------------
Fl_Choice * myChoice = new Fl_Choice(50,10,150,25,"&myChoiceLabel");
myChoice->user_data((void*)(this));	 // record self to be used by static callback functions
Fl_Menu_Item ImpressionistUI::myChoiceMenu[3+1] = {
{"one",FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)ONE},
{"two",FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)TWO},
{"three",FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)THREE},
{0}
};
myChoice->menu(myChoiceMenu);
myChoice->callback(cb_myChoice);

//-----The choice callback-------------------------
void ImpressionistUI::cb_myChoice(Fl_Widget* o, void* v)
{
ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
ImpressionistDoc* pDoc=pUI->getDocument();

int type=(int)v;

pDoc->setMyType(type);
}


//------------Button---------------------------------------

//---To install a button---------------------------
Fl_Button* myButton = new Fl_Button(330,220,50,20,"&myButtonLabel");
myButton->user_data((void*)(this));   // record self to be used by static callback functions
myButton->callback(cb_myButton);

//---The button callback---------------------------
void ImpressionistUI::cb_myButton(Fl_Widget* o, void* v)
{
ImpressionistUI* pUI=((ImpressionistUI*)(o->user_data()));
ImpressionistDoc* pDoc = pUI->getDocument();
pDoc->startPainting();
}


//---------Light Button------------------------------------

//---To install a light button---------------------
Fl_Light_Button* myLightButton = new Fl_Light_Button(240,10,150,25,"&myLightButtonLabel");
myLightButton->user_data((void*)(this));   // record self to be used by static callback functions
myLightButton->callback(cb_myLightButton);

//---The light button callback---------------------
void ImpressionistUI::cb_myLightButton(Fl_Widget* o, void* v)
{
ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));

if (pUI->myBool==TRUE) pUI->myBool=FALSE;
else pUI->myBool=TRUE;
}

//----------Int Input--------------------------------------

//---To install an int input-----------------------
Fl_Int_Input* myInput = new Fl_Int_Input(200, 50, 5, 5, "&My Input");
myInput->user_data((void*)(this));   // record self to be used by static callback functions
myInput->callback(cb_myInput);

//---The int input callback------------------------
void ImpressionistUI::cb_myInput(Fl_Widget* o, void* v)
{
((ImpressionistUI*)(o->user_data()))->m_nMyInputValue=int( ((Fl_Int_Input *)o)->value() );
}

//------------------------------------------------------------------------------------------------
*/

//------------------------------------- Help Functions --------------------------------------------

//------------------------------------------------------------
// This returns the UI, given the menu item.  It provides a
// link from the menu items to the UI
//------------------------------------------------------------
ImpressionistUI* ImpressionistUI::whoami(Fl_Menu_* o) {
  return ((ImpressionistUI*)(o->parent()->user_data()));
}

//------------------------------------------------------------
// This returns the UI, given the menu item.  It is a
// convenience method for use in FLTK callbacks.
//------------------------------------------------------------
ImpressionistUI* ImpressionistUI::whoami(Fl_Widget* o) {
  return (ImpressionistUI*)(o->user_data());
}

//--------------------------------- Callback Functions --------------------------------------------

//------------------------------------------------------------------
// Brings up a file chooser and then loads the chosen image
// This is called by the UI when the load image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_load_image(Fl_Menu_* o, void* v) {
  ImpressionistDoc *pDoc = whoami(o)->getDocument();
  pDoc->m_pUI->m_chooser = new Fl_File_Chooser(".", "*.{png,jpg,bmp}", 0, "Open File?");
  pDoc->m_pUI->m_chooser->show();
  while (pDoc->m_pUI->m_chooser->shown()) {
    Fl::wait();
  }
  const char *filename = pDoc->m_pUI->m_chooser->value();
  while (pDoc->m_pUI->m_chooser->visible()) {
    pDoc->m_pUI->m_chooser->preview(0);
    Fl::wait();
  }
  if (filename) {
    pDoc->loadImage(filename);
  }
}


//------------------------------------------------------------------
// Brings up a file chooser and then saves the painted image
// This is called by the UI when the save image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_save_image(Fl_Menu_* o, void* v) {
  ImpressionistDoc *pDoc = whoami(o)->getDocument();
  pDoc->m_pUI->m_chooser = new Fl_File_Chooser(".", "*.png\t*.jpg", Fl_File_Chooser::CREATE, "Save");
  pDoc->m_pUI->m_chooser->show();
  while (pDoc->m_pUI->m_chooser->shown()) {
    Fl::wait();
  }
  const char *szFileName = pDoc->m_pUI->m_chooser->value();
  if (szFileName) {
    std::string strFileName = szFileName;
    std::string ext = (std::string)pDoc->m_pUI->m_chooser->filter();
    ext = ext.substr(1, ext.length() - 1);
#ifdef WIN32
    char szExt[_MAX_EXT];
    _splitpath_s(strFileName.c_str(), NULL, 0, NULL, 0, NULL, 0, szExt, _MAX_EXT);
    // If user didn't type supported ext, add default one.
    if (_stricmp(szExt, ".jpg") && _stricmp(szExt, ".png")) {
      strFileName += ext;
    } else
      ext = szExt;
#endif
    int quality = 95;
    if (!strcmp(ext.c_str(), ".jpg")) {
      Dialog2 x(0, 0, 0, 0, "ok");
      quality = x.getValue();
    }
    pDoc->saveImage(strFileName.c_str(), ext.c_str(), quality);
  }
}

//-------------------------------------------------------------
// Brings up the paint dialog
// This is called by the UI when the brushes menu item
// is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_brushes(Fl_Menu_* o, void* v) {
  ImpressionistUI* self = whoami(o);
  GLfloat lineWidthRange[2];
  glGetFloatv(GL_LINE_WIDTH_RANGE, lineWidthRange);
  self->m_BrushLineWidthSlider->minimum(max(1, lineWidthRange[0]));
  self->m_BrushLineWidthSlider->maximum(lineWidthRange[1]);
  GLfloat lineWidthGranularity[1];
  glGetFloatv(GL_LINE_WIDTH_GRANULARITY, lineWidthGranularity);
  self->m_BrushLineWidthSlider->step(lineWidthGranularity[0]);

  self->m_brushDialog->show();
}

void ImpressionistUI::cb_filter_kernel(Fl_Menu_* o, void* v) {
  ImpressionistDoc* pDoc = whoami(o)->getDocument();

  // Need to back up the current paint view status
  // so we can easily preview filters
  //If no image has been loaded, do not open filter kernel
  if (pDoc->m_ucPainting != NULL) {
    memcpy(pDoc->m_ucPreviewBackup, pDoc->m_ucPainting,
      pDoc->m_nPaintWidth * pDoc->m_nPaintHeight * 3);
    whoami(o)->fltDesignUI->show();
  } else
    fl_alert("Must load an image first!");
}



//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas(Fl_Menu_* o, void* v) {
  ImpressionistDoc* pDoc = whoami(o)->getDocument();

  pDoc->clearCanvas();
}

//------------------------------------------------------------
// Causes the Impressionist program to exit
// Called by the UI when the quit menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_exit(Fl_Menu_* o, void* v) {
  whoami(o)->m_mainWindow->hide();
  whoami(o)->m_brushDialog->hide();

}

//-----------------------------------------------------------
// Undoes the most recent action.
//-----------------------------------------------------------
void ImpressionistUI::cb_undo(Fl_Menu_* o, void* v) {
  Log::Debug << "UI: Undo" << Log::end;
  whoami(o)->getDocument()->undo();
}

//-----------------------------------------------------------
// Redoes the most recent action.
//-----------------------------------------------------------
void ImpressionistUI::cb_redo(Fl_Menu_* o, void* v) {
  Log::Debug << "UI: Redo" << Log::end;
  whoami(o)->getDocument()->redo();
}

//-----------------------------------------------------------
// Brings up an about dialog box
// Called by the UI when the about menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_about(Fl_Menu_* o, void* v) {
  fl_message("Impressionist FLTK version for CSE 557, by Annabelle Richard");
}

//------- UI should keep track of the current for all the controls for answering the query from Doc ---------
//-------------------------------------------------------------
// Sets the type of brush to use to the one chosen in the brush 
// choice.  
// Called by the UI when a brush is chosen in the brush choice
//-------------------------------------------------------------
void ImpressionistUI::cb_brushChoice(Fl_Widget* o, void* v) {
  ImpressionistUI* pUI = whoami(o);
  ImpressionistDoc* pDoc = pUI->getDocument();

  int type = (int)v;


  pDoc->setBrushType(type);
  pUI->updateBrushControls();
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas button is pushed
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas_button(Fl_Widget* o, void* v) {
  ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

  pDoc->clearCanvas();
}


//-----------------------------------------------------------
// Updates the brush direction to use from the value of the
// line width slider.
// Called by the UI when the brush direction slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_brushDirectionSlides(Fl_Widget* o, void* v) {
  const double newDirection = ((Fl_Slider*)o)->value();
  whoami(o)->getCurrentBrushSettings()->setBrushDirection(newDirection);
}

//-----------------------------------------------------------
// Updates the brush line width to use from the value of the
// line width slider.
// Called by the UI when the line width slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_lineWidthSlides(Fl_Widget* o, void* v) {
  const int newLineWidth = int(((Fl_Slider*)o)->value());
  whoami(o)->getCurrentBrushSettings()->setLineWidth(newLineWidth);
}

//-----------------------------------------------------------
// Updates the brush opacity to use from the value of the
// opacity slider.
// Called by the UI when the opacity slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_opacitySlides(Fl_Widget* o, void* v) {
  const int newOpacity = int(((Fl_Slider*)o)->value());
  whoami(o)->getCurrentBrushSettings()->setOpacity(newOpacity);
}

//-----------------------------------------------------------
// Updates the brush size to use from the value of the size
// slider
// Called by the UI when the size slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_sizeSlides(Fl_Widget* o, void* v) {
  const int newSize = int(((Fl_Slider*)o)->value());
  whoami(o)->getCurrentBrushSettings()->setSize(newSize);
}

//---------------------------------- per instance functions --------------------------------------

//------------------------------------------------
// Return the ImpressionistDoc used
//------------------------------------------------
ImpressionistDoc* ImpressionistUI::getDocument() {
  return m_pDoc;
}

//------------------------------------------------
// Draw the main window
//------------------------------------------------
void ImpressionistUI::show() {
  m_mainWindow->show();
  m_paintView->show();
  m_origView->show();
}

//------------------------------------------------
// Change the paint and original window sizes to 
// w by h
//------------------------------------------------
void ImpressionistUI::resize_windows(int w, int h) {
  m_paintView->size(w, h);
  m_origView->size(w, h);
}

//------------------------------------------------ 
// Set the ImpressionistDoc used by the UI to 
// communicate with the brushes 
//------------------------------------------------
void ImpressionistUI::setDocument(ImpressionistDoc* doc) {
  m_pDoc = doc;

  m_origView->m_pDoc = doc;
  m_paintView->m_pDoc = doc;
  doc->setUI(this);
  this->updateBrushControls();
}

// Getting/setting methods for the filter design UI
void ImpressionistUI::initFltDesignUI(void) {
  fltDesignUI->ele0->value(filter.getKernelValue(0, 0));
  fltDesignUI->ele1->value(filter.getKernelValue(0, 1));
  fltDesignUI->ele2->value(filter.getKernelValue(0, 2));
  fltDesignUI->ele3->value(filter.getKernelValue(0, 3));
  fltDesignUI->ele4->value(filter.getKernelValue(0, 4));
  fltDesignUI->ele5->value(filter.getKernelValue(1, 0));
  fltDesignUI->ele6->value(filter.getKernelValue(1, 1));
  fltDesignUI->ele7->value(filter.getKernelValue(1, 2));
  fltDesignUI->ele8->value(filter.getKernelValue(1, 3));
  fltDesignUI->ele9->value(filter.getKernelValue(1, 4));
  fltDesignUI->ele10->value(filter.getKernelValue(2, 0));
  fltDesignUI->ele11->value(filter.getKernelValue(2, 1));
  fltDesignUI->ele12->value(filter.getKernelValue(2, 2));
  fltDesignUI->ele13->value(filter.getKernelValue(2, 3));
  fltDesignUI->ele14->value(filter.getKernelValue(2, 4));
  fltDesignUI->ele15->value(filter.getKernelValue(3, 0));
  fltDesignUI->ele16->value(filter.getKernelValue(3, 1));
  fltDesignUI->ele17->value(filter.getKernelValue(3, 2));
  fltDesignUI->ele18->value(filter.getKernelValue(3, 3));
  fltDesignUI->ele19->value(filter.getKernelValue(3, 4));
  fltDesignUI->ele20->value(filter.getKernelValue(4, 0));
  fltDesignUI->ele21->value(filter.getKernelValue(4, 1));
  fltDesignUI->ele22->value(filter.getKernelValue(4, 2));
  fltDesignUI->ele23->value(filter.getKernelValue(4, 3));
  fltDesignUI->ele24->value(filter.getKernelValue(4, 4));

  fltDesignUI->scale->value(filter.getDivisor());
  fltDesignUI->offset->value(filter.getOffset());
}

void ImpressionistUI::updateFilter() {
  filter.setKernelValue(0, 0, fltDesignUI->ele0->value());
  filter.setKernelValue(0, 1, fltDesignUI->ele1->value());
  filter.setKernelValue(0, 2, fltDesignUI->ele2->value());
  filter.setKernelValue(0, 3, fltDesignUI->ele3->value());
  filter.setKernelValue(0, 4, fltDesignUI->ele4->value());
  filter.setKernelValue(1, 0, fltDesignUI->ele5->value());
  filter.setKernelValue(1, 1, fltDesignUI->ele6->value());
  filter.setKernelValue(1, 2, fltDesignUI->ele7->value());
  filter.setKernelValue(1, 3, fltDesignUI->ele8->value());
  filter.setKernelValue(1, 4, fltDesignUI->ele9->value());
  filter.setKernelValue(2, 0, fltDesignUI->ele10->value());
  filter.setKernelValue(2, 1, fltDesignUI->ele11->value());
  filter.setKernelValue(2, 2, fltDesignUI->ele12->value());
  filter.setKernelValue(2, 3, fltDesignUI->ele13->value());
  filter.setKernelValue(2, 4, fltDesignUI->ele14->value());
  filter.setKernelValue(3, 0, fltDesignUI->ele15->value());
  filter.setKernelValue(3, 1, fltDesignUI->ele16->value());
  filter.setKernelValue(3, 2, fltDesignUI->ele17->value());
  filter.setKernelValue(3, 3, fltDesignUI->ele18->value());
  filter.setKernelValue(3, 4, fltDesignUI->ele19->value());
  filter.setKernelValue(4, 0, fltDesignUI->ele20->value());
  filter.setKernelValue(4, 1, fltDesignUI->ele21->value());
  filter.setKernelValue(4, 2, fltDesignUI->ele22->value());
  filter.setKernelValue(4, 3, fltDesignUI->ele23->value());
  filter.setKernelValue(4, 4, fltDesignUI->ele24->value());

  filter.setDivisor(fltDesignUI->scale->value());
  filter.setOffset(fltDesignUI->offset->value());
}




// Main menu definition
Fl_Menu_Item ImpressionistUI::menuitems[] = {
    { "&File", 0, 0, 0, FL_SUBMENU },
    { "&Load Image...", FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load_image },
    { "&Save Image...", FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save_image },
    { "&Brushes...", FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_brushes },
    { "&Filter Kernel...", FL_CTRL + 'f', (Fl_Callback *)ImpressionistUI::cb_filter_kernel },
    { "&Clear Canvas", FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_clear_canvas, 0, FL_MENU_DIVIDER },

    { "&Quit", FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
    { 0 },

    { "&Edit", 0, 0, 0, FL_SUBMENU },
    { "&Undo", FL_ALT + 'z', (Fl_Callback*)ImpressionistUI::cb_undo },
    { "&Redo", FL_ALT + 'Z', (Fl_Callback*)ImpressionistUI::cb_redo },
    { 0 },

    { "&Help", 0, 0, 0, FL_SUBMENU },
    { "&About", FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
    { 0 },

    { 0 }
};

// Brush choice menu definition
Fl_Menu_Item ImpressionistUI::brushTypeMenu[NUM_BRUSH_TYPE + 1] = {
    { "Points", FL_ALT + 'p', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_POINTS },
    { "Lines", FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_LINES },
    { "Circles", FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_CIRCLES },
    { "Scattered Points", FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_POINTS },
    { "Scattered Lines", FL_ALT + 'm', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_LINES },
    { "Scattered Circles", FL_ALT + 'd', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_CIRCLES },
    { 0 }
};



//----------------------------------------------------
// Constructor.  Creates all of the widgets.
// Add new widgets here
//----------------------------------------------------
ImpressionistUI::ImpressionistUI()
  : filter(FLT_WIDTH, FLT_HEIGHT) {
  // Create the main window
  m_mainWindow = new Fl_Window(600, 300, "Impressionist");
  m_mainWindow->user_data((void*)(this));	// record self to be used by static callback functions
  // install menu bar
  m_menubar = new Fl_Menu_Bar(0, 0, 600, 25);
  m_menubar->menu(menuitems);
  m_undoMenuItem = m_menubar->find_item("&Undo");
  m_redoMenuItem = m_menubar->find_item("&Redo");

  // Create a group that will hold two sub windows inside the main
  // window
  Fl_Group* group = new Fl_Group(0, 25, 600, 275);

  // install paint view window
  m_paintView = new PaintView(300, 25, 300, 275, "This is the paint view");//0jon
  m_paintView->box(FL_DOWN_FRAME);

  // install original view window
  m_origView = new OriginalView(0, 25, 300, 275, "This is the orig view");//300jon
  m_origView->box(FL_DOWN_FRAME);
  m_origView->deactivate();

  group->end();
  Fl_Group::current()->resizable(group);
  m_mainWindow->end();

  // Create the filter kernel UI
  fltDesignUI = new FltDesignUI;
  fltDesignUI->impUI = this;

  initFltDesignUI();

  // brush dialog definition
  m_brushDialog = new Fl_Window(400, 325, "Brush Dialog");
  // Add a brush type choice to the dialog
  m_BrushTypeChoice = new Fl_Choice(50, 10, 150, 25, "&Brush");
  m_BrushTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
  m_BrushTypeChoice->menu(brushTypeMenu);
  m_BrushTypeChoice->callback(cb_brushChoice);

  m_ClearCanvasButton = new Fl_Button(240, 10, 150, 25, "&Clear Canvas");
  m_ClearCanvasButton->user_data((void*)(this));
  m_ClearCanvasButton->callback(cb_clear_canvas_button);


  // Add brush size slider to the dialog 
  m_BrushSizeSlider = new Fl_Value_Slider(10, 80, 300, 20, "Size");
  m_BrushSizeSlider->user_data((void*)(this));	// record self to be used by static callback functions
  m_BrushSizeSlider->type(FL_HOR_NICE_SLIDER);
  m_BrushSizeSlider->labelfont(FL_COURIER);
  m_BrushSizeSlider->labelsize(12);
  m_BrushSizeSlider->minimum(1);
  m_BrushSizeSlider->maximum(40);
  m_BrushSizeSlider->step(1);
  m_BrushSizeSlider->value(0);
  m_BrushSizeSlider->align(FL_ALIGN_RIGHT);
  m_BrushSizeSlider->callback(cb_sizeSlides);

  // Add brush opacity slider to the dialog
  m_BrushOpacitySlider = new Fl_Value_Slider(10, 120, 300, 20, "Opacity");
  m_BrushOpacitySlider->user_data((void*)this);
  m_BrushOpacitySlider->type(FL_HOR_NICE_SLIDER);
  m_BrushOpacitySlider->labelfont(FL_COURIER);
  m_BrushOpacitySlider->labelsize(12);
  m_BrushOpacitySlider->minimum(0);
  m_BrushOpacitySlider->maximum(255);
  m_BrushOpacitySlider->step(1);
  m_BrushOpacitySlider->value(255);
  m_BrushOpacitySlider->align(FL_ALIGN_RIGHT);
  m_BrushOpacitySlider->callback(cb_opacitySlides);

  // Add brush line width slider to the dialog
  m_BrushLineWidthSlider = new Fl_Value_Slider(10, 160, 300, 20, "Line Width");
  m_BrushLineWidthSlider->user_data((void*)this);
  m_BrushLineWidthSlider->type(FL_HOR_NICE_SLIDER);
  m_BrushLineWidthSlider->labelfont(FL_COURIER);
  m_BrushLineWidthSlider->labelsize(12);
  m_BrushLineWidthSlider->minimum(1);
  m_BrushLineWidthSlider->maximum(3);
  m_BrushLineWidthSlider->value(3);
  m_BrushLineWidthSlider->align(FL_ALIGN_RIGHT);
  m_BrushLineWidthSlider->callback(cb_lineWidthSlides);

  // Add brush direction slider to the dialog
  m_BrushDirectionSlider = new Fl_Value_Slider(10, 200, 300, 20, "Brush Direction");
  m_BrushDirectionSlider->user_data((void*)this);
  m_BrushDirectionSlider->type(FL_HOR_NICE_SLIDER);
  m_BrushDirectionSlider->labelfont(FL_COURIER);
  m_BrushDirectionSlider->labelsize(12);
  m_BrushDirectionSlider->minimum(0);
  m_BrushDirectionSlider->maximum(360);
  m_BrushDirectionSlider->value(0);
  m_BrushDirectionSlider->align(FL_ALIGN_RIGHT);
  m_BrushDirectionSlider->callback(cb_brushDirectionSlides);

  m_brushDialog->end();

}

ImpressionistUI::~ImpressionistUI() {
  delete fltDesignUI;
}

void ImpressionistUI::cancelFilter(void) {
  std::swap(m_pDoc->m_ucPainting, m_pDoc->m_ucPreviewBackup);
  fltDesignUI->hide();
  m_paintView->refresh();
}

void ImpressionistUI::applyFilter(void) {
  m_pDoc->applyFilter(filter, fltDesignUI->applyToPainting->value() == 1);
  fltDesignUI->hide();
  m_paintView->refresh();
}

void ImpressionistUI::previewFilter(void) {
  m_pDoc->applyFilter(filter, fltDesignUI->applyToPainting->value() == 1);
  m_paintView->refresh();
}

//------------------------------------------------------------
// Returns the settings for the currently selected brush.
//------------------------------------------------------------
BrushSettings* ImpressionistUI::getCurrentBrushSettings() {
  return getDocument()->m_pCurrentBrush->getSettings();
}

//------------------------------------------------------------
// Updates brush setting controls based on the currently
// selected brush.
//------------------------------------------------------------
void ImpressionistUI::updateBrushControls() {
  m_BrushDirectionSlider->value(getCurrentBrushSettings()->getBrushDirectionAsDouble());
  m_BrushLineWidthSlider->value(getCurrentBrushSettings()->getLineWidthAsDouble());
  m_BrushOpacitySlider->value(getCurrentBrushSettings()->getOpacityAsDouble());
  m_BrushSizeSlider->value(getCurrentBrushSettings()->getSizeAsDouble());

  const ImpBrush* currentBrush = getDocument()->m_pCurrentBrush;
  if (currentBrush == ImpBrush::c_pBrushes[BRUSH_LINES]
    || currentBrush == ImpBrush::c_pBrushes[BRUSH_SCATTERED_LINES]) {
    m_BrushDirectionSlider->show();
    m_BrushLineWidthSlider->show();
  } else {
    m_BrushDirectionSlider->hide();
    m_BrushLineWidthSlider->hide();
  }
}

void ImpressionistUI::updateUndoRedoMenus() {
  /*
  if (m_pDoc->CanUndo())
  {
  m_undoMenuItem->show();
  }
  else
  {
  m_undoMenuItem->hide();
  }

  if (m_pDoc->CanRedo())
  {
  m_redoMenuItem->show();
  }
  else
  {
  m_redoMenuItem->hide();
  }
  */
}