#include "gridwindow.h"
#include <iostream>
#include <sys/time.h>
#include "sudoku.h"

GridWindow::GridWindow()
: m_solveButton("Solve"),
  m_clearButton("Clear"),
  m_entry()
{
	set_title("Sudoku");

	// Add the grid child widget
	add(m_guiGrid);

	// Add the entries to the grid
	for(unsigned int ii=0;ii<9;ii++)
	{
		for(unsigned int jj=0;jj<9;jj++)
		{
			m_guiGrid.attach(m_entry[ii][jj],ii,jj,1,1);
			m_entry[ii][jj].set_max_length(1);
			m_entry[ii][jj].set_width_chars(1);
		}
	}

	// Add the button to the grid
	m_guiGrid.attach(m_solveButton,9,1,1,2);
	m_guiGrid.attach(m_clearButton,9,5,1,2);

	// Connect a signal handler to the buttons
	m_solveButton.signal_clicked().connect(sigc::mem_fun(*this,
			  &GridWindow::on_button_solve_clicked) );
	m_clearButton.signal_clicked().connect(sigc::mem_fun(*this,
			  &GridWindow::on_button_clear_clicked) );

	show_all_children();
}

GridWindow::~GridWindow()
{
}

void GridWindow::on_button_solve_clicked()
{
	// Attempt to solve the puzzle

	// Read the contents of the entries
	sudoku sudokuPuzzle;
	sudokuPuzzle.initPuzzle(m_entry);
	bool result = sudokuPuzzle.SolvePuzzle();

	if(result)
	{
		Glib::ustring finalValue;

		Gdk::RGBA solutionColor;
		solutionColor.set_rgba(1.0,0.0,0.0,1.0); 	// red for the solution

		for(unsigned int ii=0;ii<9;ii++)
		{
			for(unsigned int jj=0;jj<9;jj++)
			{
				// Fill in the remaining cells
				if( m_entry[ii][jj].get_text().empty() )
				{
					Glib::ustring finalValue = IntToUString(sudokuPuzzle.getPuzzleValue(jj,ii));
					m_entry[ii][jj].override_color(solutionColor);
					m_entry[ii][jj].set_text(finalValue);
					m_entry[ii][jj].set_editable(false);
				}
			}
		}
	}
	else
	{
		// Input is not solvable
		// Inform the user of the error
		Gtk::MessageDialog dlg("Puzzle cannot be solved. Check the input.");
		dlg.run();
	}

}

void GridWindow::on_button_clear_clicked()
{
	// Clear the contents of the grid
	for(unsigned int ii=0;ii<9;ii++)
	{
		for(unsigned int jj=0;jj<9;jj++)
		{
				m_entry[ii][jj].set_text("");
				m_entry[ii][jj].set_editable(true);
		}
	}
}


void SudokuEntry::on_cell_edited()
{
	// Check to make sure the entry is a number between 1 and 9
	Glib::ustring raw = get_text().raw();
	std::stringstream raw_stream;
	raw_stream << raw;

	int value;
	raw_stream >> value;

	// Reset the value to the
	if( (value < 1 || value > 9) && raw != "")
	{
		// Inform the user of the error
		Gtk::MessageDialog dlg("Invalid entry. Be sure to enter a number between 1 and 9");
		dlg.run();
		set_text("");
	}
}

SudokuEntry::SudokuEntry()
{
	// Connect the editing of each entry to the method to check if it is a valid value
	signal_changed().connect(sigc::mem_fun(*this,
			&SudokuEntry::on_cell_edited) );
}

SudokuEntry::~SudokuEntry()
{
}

// Convert integer to Glib::ustring
Glib::ustring GridWindow::IntToUString(int intVal)
{
	std::ostringstream streamValue;
	streamValue << intVal;
	Glib::ustring sOut = streamValue.str();
	return sOut;
}

