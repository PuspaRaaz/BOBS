#ifndef _BASIC_H_
#define _BASIC_H_

#include <gtk/gtk.h>

static GdkPixbuf *createPixbuf(const gchar* filename){
	GError *error = NULL;
	GdkPixbuf* pixbuf = gdk_pixbuf_new_from_file(filename, &error);
	if(!pixbuf){
		fprintf(stderr, "%s\n", error->message);
		g_error_free(error);
	}
	return pixbuf;
}

void toBinary(int value, char* output)
{
    int i;
    output[9] = '\0';
    for (i = 7; i >= 0; --i, value >>= 1)
    {
        output[i] = (value & 1) + '0';
    }
}

#endif
