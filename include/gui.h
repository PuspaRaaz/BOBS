#ifndef _GUI_H
#define _GUI_H

#include "menuActions.h"
#include "MicroProcessor.h"
#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>

GtkWidget *textAreaYourCode, *textAreaConvertedCode, *errorArea, *notebook, *memLocation, *memValue;
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
