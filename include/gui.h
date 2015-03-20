#ifndef _GUI_H
#define _GUI_H

#include "basic.h"
#include "menuActions.h"
#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>
#include <string.h>

GtkWidget* textAreaYourCode;
GtkWidget* textAreaConvertedCode;

void menuResponse(GtkWidget*, gpointer);

GtkWidget* drawMenuItems(GtkWidget*);

GtkWidget* drawToolbar(GtkWidget*);

GtkWidget* getMicroprocessor(GtkWidget*);

void displayConverted(char*);

char* getCodedText();

#endif
