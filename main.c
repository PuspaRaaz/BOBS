#include <gtk/gtk.h>
#include <stdio.h>
#include "basic.h"
#include "memory.h"
#include "menu.h"
#include "registers.h"
#include "textarea.h"
#include "toolbar.h"

int main(int argc, char ** argv){
	gtk_init(&argc, &argv); //initialize gtkMain

	GtkWidget *window, *container; //define basic variables

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL); //construct window on toplevel
	gtk_window_set_title(GTK_WINDOW(window), "BOBS' Simulator - a 8085 microprocessor simulator"); //set window title
	gtk_window_set_default_size(GTK_WINDOW(window), 600, 480); //set window default size
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_icon(GTK_WINDOW(window), createPixbuf("BOBS'.jpg"));
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL); //provision to quit with 'Alt+f4' or 'X' from title bar

	container = drawMenuItems(window); //container gets menus located at title bar

	GtkWidget* toolbar = drawToolbar(window);
	gtk_box_pack_start(GTK_BOX(container), toolbar, 0,1,0); //toolbar is added to container

	GtkWidget* sep = gtk_hseparator_new(); //place a separator to separate toolbar with the main container
	gtk_box_pack_start(GTK_BOX(container), sep, 0, 0, 0);

	GtkWidget* registers = drawRegisters(window); //gets registers and their dependencies widget
	gtk_box_pack_start(GTK_BOX(container), registers, 0,0,5); //add register row to container

	GtkWidget* textarea = drawTextarea(window);
	gtk_box_pack_start(GTK_BOX(registers), textarea, 0, 0, 1);

	GtkWidget* memory = drawMemory(window); //gets memory and their dependencies widget
	gtk_box_pack_start(GTK_BOX(registers), memory, 0,0,10); //keep memory block horizontal to register block

	gtk_container_add(GTK_CONTAINER(window), container); //container is added to the window
	gtk_widget_show_all(window); //all components/widgets are shown
	gtk_main(); //hold on gtkMain until quit
	return 0;
}