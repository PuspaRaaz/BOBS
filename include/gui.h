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

GtkWidget *timerEntry[4];
GtkWidget *flagEntry[5], *registerEntry[9], *ioPortEntry[3];
GtkWidget *textAreaYourCode, *textAreaConvertedCode, *errorArea, *notebook, *memLocation, *memValue;
PangoFontDescription* font_desc;

GtkWidget* drawMenuItems(GtkWidget*);
GtkWidget* drawToolbar(GtkWidget*);
GtkWidget* getError(GtkWidget*);
GtkWidget* getMicroprocessor(GtkWidget*);
char* getCodedText();
void displayConverted(char*, char*);
void menuResponse(GtkWidget*, gpointer);
void timerStart();
void timerPause();
void timerStop();
void timerReset();
void toBinary(int, char*);

#endif
