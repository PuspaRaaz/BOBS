#ifndef _GUI_H
#define _GUI_H

#include "basic.h"
#include "menuActions.h"
#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>

GtkWidget *textAreaYourCode, *textAreaConvertedCode, *errorArea, *notebook;

void menuResponse(GtkWidget*, gpointer);

GtkWidget* drawMenuItems(GtkWidget*);

GtkWidget* drawToolbar(GtkWidget*);

GtkWidget* getMicroprocessor(GtkWidget*);

GtkWidget* getError(GtkWidget*);

void displayConverted(char*);

char* getCodedText();

#endif
