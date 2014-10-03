#ifndef GTKMM_GRIDWINDOW_H
#define GTKMM_GRIDWINDOW_H

#include <gtkmm.h>
//#include "sudoku.h"

// Custom entry class to enforce requirements
class SudokuEntry : public Gtk::Entry
{
	public:
		SudokuEntry();
		virtual ~SudokuEntry();

	protected:
		void on_cell_edited();
};

// Child area of the popup window MapWindow
class GridWindow : public Gtk::Window
{
	public:
		GridWindow();
		virtual ~GridWindow();
		Glib::ustring IntToUString(int intVal);
		//sudoku git;
	protected:
		Gtk::Grid m_guiGrid;
		Gtk::Button m_solveButton;
		Gtk::Button m_clearButton;
		SudokuEntry m_entry[9][9];

		// Button handlers
		void on_button_solve_clicked();
		void on_button_clear_clicked();
};

#endif //GTKMM_MENUWINDOW_H
