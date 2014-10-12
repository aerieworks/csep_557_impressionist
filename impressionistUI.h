//
// impressionistUI.h
//
// The header file for the UI part
//

#ifndef ImpressionistUI_h
#define ImpressionistUI_h

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_File_Chooser.H>		// FLTK file chooser
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Color_Chooser.H>

#include "impressionist.h"
#include "originalView.h"
#include "paintView.h"
#include "FltDesignUI.h"

#include "impBrush.h"
#include "KernelFilter.h"

const int FLT_WIDTH = 5;
const int FLT_HEIGHT = 5;

class ImpressionistUI {
public:
  ImpressionistUI();
  ~ImpressionistUI();

  // The FLTK widgets
  Fl_Window*			m_mainWindow;
  Fl_Menu_Bar*		m_menubar;
  const Fl_Menu_Item*	m_undoMenuItem;
  const Fl_Menu_Item*	m_redoMenuItem;

  PaintView*			m_paintView;
  OriginalView*		m_origView;
  Fl_File_Chooser*	m_chooser;

  // filter kernel dialog
  FltDesignUI*		fltDesignUI;

  // for brush dialog
  Fl_Window*			m_brushDialog;
  Fl_Choice*			m_BrushTypeChoice;

  Fl_Slider*			m_BrushSizeSlider;
  Fl_Slider*			m_BrushOpacitySlider;
  Fl_Slider*			m_BrushLineWidthSlider;
  Fl_Slider*			m_BrushDirectionSlider;
  Fl_Button*          m_ClearCanvasButton;

  // Member functions
  void				setDocument(ImpressionistDoc* doc);
  ImpressionistDoc*	getDocument();

  void				show();
  void				resize_windows(int w, int h);

  // Callbacks for the image filter dialogue (different from
  // the other callbacks because they aren't static)
  void				initFltDesignUI(void);
  void				updateFilter(void);

  void				cancelFilter(void);
  void				applyFilter(void);
  void				previewFilter(void);


private:
  BrushSettings* getCurrentBrushSettings();
  void updateBrushControls();
  void updateUndoRedoMenus();

  ImpressionistDoc*	m_pDoc;		// pointer to document to communicate with the document

  KernelFilter filter;

  // Static class members
  static Fl_Menu_Item		menuitems[];
  static Fl_Menu_Item		brushTypeMenu[NUM_BRUSH_TYPE + 1];

  static ImpressionistUI*	whoami(Fl_Menu_* o);
  static ImpressionistUI* whoami(Fl_Widget* o);

  // All callbacks here.  Callbacks are declared 
  // static
  static void	cb_load_image(Fl_Menu_* o, void* v);
  static void	cb_save_image(Fl_Menu_* o, void* v);
  static void	cb_brushes(Fl_Menu_* o, void* v);
  static void	cb_filter_kernel(Fl_Menu_* o, void* v);
  static void	cb_clear_canvas(Fl_Menu_* o, void* v);
  static void	cb_exit(Fl_Menu_* o, void* v);
  static void cb_undo(Fl_Menu_* o, void* v);
  static void cb_redo(Fl_Menu_* o, void* v);
  static void	cb_about(Fl_Menu_* o, void* v);
  static void	cb_brushChoice(Fl_Widget* o, void* v);
  static void	cb_clear_canvas_button(Fl_Widget* o, void* v);
  static void	cb_sizeSlides(Fl_Widget* o, void* v);
  static void cb_opacitySlides(Fl_Widget* o, void* v);
  static void cb_lineWidthSlides(Fl_Widget* o, void* v);
  static void cb_brushDirectionSlides(Fl_Widget* o, void* v);
};

#endif

