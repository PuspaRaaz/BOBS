#ifndef _GUI_H
#define _GUI_H

#include "MicroInstruction.h"
#include "MicroProcessor.h"
#include "menuActions.h"
#include <ctype.h>
#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STARTOFCODE 0x8000

char* getCodedText();					//returns input text
int nofile();							//checks if file exists or not
void displayConverted();				//calls displaySource/Output and refresh
void displayErrorMessage(char*, int);	//display messages
void displayFlag();						//display flag values
void displayIOPort();					//display output ports values
void displayOutput();					//displays generated opcode
void displayPPIPort();					//displays PPI port values
void displayRegister();					//displays register values
void displaySource(char*);				//display source code from the file
void nextMemory();						//shows next memory address and its value
void previousMemory();					//shows next memory address and its value
void refresh();							//displays updated value of register/ports/flags
void setMemory();						//sets value to respective memory address
void strobeOne();						//produces strobe 1 (RST 5.5) signal
void strobeTwo();						//produces strobe 2 (RST 6.5) signal
void toBinary(int, char*);				//converts integer value to respective binary
void viewMemory();						//gives the data at specified memory location

GtkWidget *flagEntry[5], *registerEntry[9], *ioPortEntry[3], *ppiEntry[3];
GtkWidget *textAreaYourCode, *textAreaConvertedCode, *errorArea, *notebook, *memLocation, *memValue;
PangoFontDescription* font_desc;

GtkWidget* drawMenuItems(GtkWidget*);	//draws the title-bar menus
GtkWidget* drawToolbar(GtkWidget*);		//draw toolbar menus
GtkWidget* getError(GtkWidget*);		//gives the message area
GtkWidget* getMicroprocessor(GtkWidget*);//gives the main microprocessor & ppi components
void menuResponse(GtkWidget*, gpointer);//receives menu actions/clicks and redirects to respective function

#endif
