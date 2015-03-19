#ifndef _GUI_H
#define _GUI_H

#include "basic.h"
#include "menuActions.h"
#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>
#include <string.h>

void menuResponse(GtkWidget*, gpointer);

GtkWidget* drawMenuItems(GtkWidget*);

GtkWidget* drawToolbar(GtkWidget*);

GtkWidget* getMicroprocessor(GtkWidget*);

#endif
