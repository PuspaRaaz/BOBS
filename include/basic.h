#ifndef _BASIC_H_
#define _BASIC_H_

#include <gtk/gtk.h>

static GtkWidget* textAreaYourCode;
static GtkWidget* textAreaConvertedCode;

static GdkPixbuf *createPixbuf(const gchar* filename){
	GError *error = NULL;
	GdkPixbuf* pixbuf = gdk_pixbuf_new_from_file(filename, &error);
	if(!pixbuf){
		fprintf(stderr, "%s\n", error->message);
		g_error_free(error);
	}
	return pixbuf;
}

#endif
