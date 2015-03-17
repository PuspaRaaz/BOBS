#ifndef _BASIC_H_
#define _BASIC_H_

static GtkWidget *window, *container;
static GtkWidget *hbox, *vbox, *items;

static GtkWidget *menuBar, *sep;
static GtkAccelGroup *accelGroup;

static GtkWidget *toolbar, *icon;

static GtkWidget *ppiContainer, *ppiFrame;

static GtkWidget *micro;
static GtkWidget *textAreaYourCode = gtk_text_view_new();
static GtkWidget *textAreaConvertedCode = gtk_text_view_new();

GdkPixbuf *createPixbuf(const gchar* filename){
	GError *error = NULL;
	GdkPixbuf* pixbuf = gdk_pixbuf_new_from_file(filename, &error);
	if(!pixbuf){
		fprintf(stderr, "%s\n", error->message);
		g_error_free(error);
	}
	return pixbuf;
}

#endif
