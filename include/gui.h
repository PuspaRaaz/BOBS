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

int STARTOFCODE = 0x8000;
GtkWidget *textAreaYourCode, *textAreaConvertedCode, *errorArea, *notebook, *memLocation, *memValue;
GtkWidget *flagEntry[5], *registerEntry[9], *ioPortEntry[3];
PangoFontDescription* font_desc;

void menuResponse(GtkWidget*, gpointer);

GtkWidget* drawMenuItems(GtkWidget*);

GtkWidget* drawToolbar(GtkWidget*);

GtkWidget* getMicroprocessor(GtkWidget*);

GtkWidget* getError(GtkWidget*);

void displayConverted(char*, char*);

char* getCodedText();

void toBinary(int, char*);

#endif
