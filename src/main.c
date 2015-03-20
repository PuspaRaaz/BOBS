#include "basic.h"
#include "gui.h"
#include <gtk/gtk.h>
#include <stdio.h>

int main(int argc, char** argv){

	GtkWidget *window, *container;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "BOBS' Simulator - a 8085 microprocessor simulator");
	// gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	// gtk_window_set_icon(GTK_WINDOW(window), createPixbuf("bin/files/BOBS'.jpg"));
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	container = drawMenuItems(window);
	gtk_box_pack_start(GTK_BOX(container), drawToolbar(window), 0, 1, 0); //toolbar is added to container
	gtk_box_pack_start(GTK_BOX(container), gtk_hseparator_new(), 0, 0, 0); //horizontal separator is added
	gtk_box_pack_start(GTK_BOX(container), getMicroprocessor(window), 0, 0, 5); //microprocessor components are added
	gtk_box_pack_start(GTK_BOX(container), gtk_hseparator_new(), 0, 0, 0); //horizontal separator is added
	gtk_box_pack_start(GTK_BOX(container), getError(window), 1, 1, 5); //microprocessor components are added

	gtk_container_add(GTK_CONTAINER(window), container);
	gtk_widget_show_all(window);

	gtk_main();
	return 0;
}