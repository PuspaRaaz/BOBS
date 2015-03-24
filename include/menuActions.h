#ifndef _MENUACTIONS_H_
#define _MENUACTIONS_H_

#include "gui.h"
#include "MicroInstruction.h"
#include "MicroProcessor.h"
#include <ctype.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int built;

void aboutDialog(GtkWidget*, gpointer);		//draws ABOUT dialog box
void buildMenu(GtkWidget*, gpointer);		//builds the source code
void convertMenu(GtkWidget*, gpointer);		//converts the mnemonics into opcode
void getOpcode(GtkWidget*, gpointer);		//generates an opcode file for user
void helpDialog(GtkWidget*, gpointer);		//draws HELP dialog box
void newFile();			//creates new file
void openFile(GtkWidget*, gpointer);		//opens OPEN dialog box
void runMenu(GtkWidget*, gpointer);			//runs the program
void saveAsFile(GtkWidget*, gpointer);		//opens SAVE AS dialog box
void saveFile(GtkWidget*, gpointer);		//saves the changes
void singleStepMenu(GtkWidget*, gpointer);	//runs the program stepwise

#endif
