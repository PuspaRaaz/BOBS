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

	GtkWidget* editableBox = gtk_vbox_new(0,0); //box to hold edit area
	GtkWidget* textArea = gtk_text_view_new(); //the gtk textarea
	GtkTextBuffer* textBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textArea));
	gtk_text_buffer_set_text(textBuffer, "Place your code here...\0", -1);
    GtkWidget* scrolledwindow = gtk_scrolled_window_new(NULL,NULL);
    gtk_widget_set_size_request(scrolledwindow, 250,300);

    gtk_container_add(GTK_CONTAINER(scrolledwindow), textArea); //set the textarea within scrolled window
	gtk_box_pack_start(GTK_BOX(editableBox), scrolledwindow, 1, 1, 3);

    GtkWidget* clipboardBox = gtk_hbox_new(0,0); //box to hold clipboard action buttons
    GtkWidget* button = gtk_button_new_with_label("Cut");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(cutMenu), (gpointer) textArea);
    gtk_box_pack_start(GTK_BOX(clipboardBox), button, 0,0,0); //cut (ctrl+x)

    button = gtk_button_new_with_label("Copy");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(copyMenu), (gpointer) textArea);
    gtk_box_pack_start(GTK_BOX(clipboardBox), button, 0,0,0); //copy (ctrl+c)

	textArea = gtk_text_view_new(); //text area without edit access
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textArea), FALSE); //this is to display changed view of the input (opcode) ? mnemonics : opcode
	textBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textArea));
	gtk_text_buffer_set_text(textBuffer, "Converted code...\0", -1);
    scrolledwindow = gtk_scrolled_window_new(NULL,NULL);
    gtk_widget_set_size_request(scrolledwindow, 250,300);

    button = gtk_button_new_with_label("Paste");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(pasteMenu), (gpointer) textArea);
    gtk_box_pack_start(GTK_BOX(clipboardBox), button, 0,0,0);

    button = gtk_button_new_with_label("Clear");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(clear), (gpointer) textArea);
    gtk_box_pack_start(GTK_BOX(clipboardBox), button, 0,0,0);

    gtk_box_pack_start(GTK_BOX(editableBox), clipboardBox, 0,0,0);
    gtk_box_pack_start(GTK_BOX(registers), editableBox, 0, 0, 0);

    gtk_container_add(GTK_CONTAINER(scrolledwindow), textArea);
	gtk_box_pack_start(GTK_BOX(registers), scrolledwindow, 0, 0, 3);
>>>>>>> 054193b9220d8769625444e02c1cb1bddde4bcc7

	gtk_box_pack_start(GTK_BOX(container), getPPI(window), 0, 0, 5); //ppi frame is loaded with ppi components

	gtk_container_add(GTK_CONTAINER(window), container); //container is added to the window
	gtk_widget_show_all(window); //all components/widgets are shown
	gtk_main(); //hold on gtkMain until quit
	return 0;
}
