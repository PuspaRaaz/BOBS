#ifndef _TEXTAREA_H
#define _TEXTAREA_H

#define GTK_ENABLE_BROKEN
#include <gtk/gtk.h>
#include <gtk/gtktext.h>

GtkWidget* drawTextarea(GtkWidget* window){
	GtkWidget *vbox, *hbox, *entry;

	hbox = gtk_hbox_new(FALSE, 0);
	entry = (GtkWidget*) gtk_text_view_new(NULL, NULL);
	gtk_text_set_editable(GTK_TEXT(entry), TRUE);
	gtk_box_pack_start(GTK_BOX(hbox), entry, TRUE, TRUE, 0);
	return hbox;
}


#endif