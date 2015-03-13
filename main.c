#include <gtk/gtk.h>
#include <stdio.h>
#include "basic.h"
#include "menu.h"
#include "microprocessor.h"
#include "ppi.h"
#include "toolbar.h"

int main(int argc, char ** argv){
	gtk_init(&argc, &argv); //initialize gtkMain

	GtkWidget *window, *container; //define basic variables

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL); //construct window on toplevel
	gtk_window_set_title(GTK_WINDOW(window), "BOBS' Simulator - a 8085 microprocessor simulator"); //set window title
	gtk_window_set_default_size(GTK_WINDOW(window), 600, 480); //set window default size
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE); //set program window size fixed
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); //place program at center on first use
	gtk_window_set_icon(GTK_WINDOW(window), createPixbuf("BOBS'.jpg")); //program icon
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL); //provision to quit with 'Alt+f4' or 'X' from title bar

	container = drawMenuItems(window); //container gets menus located at title bar. As GtkWidget* is returned, container is not as any widget

	gtk_box_pack_start(GTK_BOX(container), drawToolbar(window), 0, 1, 0); //toolbar is added to container

	gtk_box_pack_start(GTK_BOX(container), gtk_hseparator_new(), 0, 0, 0); //horizontal separator is added

	gtk_box_pack_start(GTK_BOX(container), getMicroprocessor(window), 0, 0, 5); //microprocessor components are added

	gtk_box_pack_start(GTK_BOX(container), gtk_hseparator_new(), 0, 0, 0); //horizontal separator is added

	gtk_box_pack_start(GTK_BOX(container), getPPI(window), 0, 0, 5); //ppi frame is loaded with ppi components

	gtk_container_add(GTK_CONTAINER(window), container); //container is added to the window
	gtk_widget_show_all(window); //all components/widgets are shown
	gtk_main(); //hold on gtkMain until quit
	return 0;
}