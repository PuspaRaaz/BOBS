#include <gtk/gtk.h>
#include <stdio.h>
#include "basic.h"
#include "memory.h"
#include "menu.h"
#include "registers.h"
#include "toolbar.h"







static void cutTextToClipboard(GtkButton* cut, GtkTextView* textView){
	g_print("cut...\t");
	GtkClipboard* clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
	GtkTextBuffer* buffer = gtk_text_view_get_buffer(textView);

	gtk_text_buffer_cut_clipboard(buffer, clipboard, TRUE);
}
static void copyTextToClipboard(GtkButton* cut, GtkTextView* textView){
	GtkClipboard* clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
	GtkTextBuffer* buffer = gtk_text_view_get_buffer(textView);

	gtk_text_buffer_copy_clipboard(buffer, clipboard);
}
static void pasteTextFromClipboard(GtkButton* cut, GtkTextView* textView){
	GtkClipboard* clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
	GtkTextBuffer* buffer = gtk_text_view_get_buffer(textView);

	gtk_text_buffer_paste_clipboard(buffer, clipboard, NULL, TRUE);
}






int main(int argc, char ** argv){
	gtk_init(&argc, &argv); //initialize gtkMain

	GtkWidget *window, *container; //define basic variables

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL); //construct window on toplevel
	gtk_window_set_title(GTK_WINDOW(window), "BOBS' Simulator - a 8085 microprocessor simulator"); //set window title
	gtk_window_set_default_size(GTK_WINDOW(window), 600, 480); //set window default size
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_icon(GTK_WINDOW(window), createPixbuf("BOBS'.jpg"));
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL); //provision to quit with 'Alt+f4' or 'X' from title bar

	container = drawMenuItems(window); //container gets menus located at title bar

	GtkWidget* toolbar = drawToolbar(window);
	gtk_box_pack_start(GTK_BOX(container), toolbar, 0,1,0); //toolbar is added to container

	GtkWidget* sep = gtk_separator_menu_item_new(); //place a separator to separate toolbar with the main container
	gtk_box_pack_start(GTK_BOX(container), sep, 0, 0, 0);

	GtkWidget* registers = drawRegisters(window); //gets registers and their dependencies widget
	gtk_box_pack_start(GTK_BOX(container), registers, 0,0,5); //add register row to container

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
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(cutTextToClipboard), (gpointer) textArea);
    gtk_box_pack_start(GTK_BOX(clipboardBox), button, 0,0,0); //cut (ctrl+x)

    button = gtk_button_new_with_label("Copy");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(copyTextToClipboard), (gpointer) textArea);
    gtk_box_pack_start(GTK_BOX(clipboardBox), button, 0,0,0); //copy (ctrl+c)

	textArea = gtk_text_view_new(); //text area without edit access
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textArea), FALSE); //this is to display changed view of the input (opcode) ? mnemonics : opcode
	textBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textArea));
	gtk_text_buffer_set_text(textBuffer, "Converted code...\0", -1);
    scrolledwindow = gtk_scrolled_window_new(NULL,NULL);
    gtk_widget_set_size_request(scrolledwindow, 250,300);

    button = gtk_button_new_with_label("Paste");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(pasteTextFromClipboard), (gpointer) textArea);
    gtk_box_pack_start(GTK_BOX(clipboardBox), button, 0,0,0);

    gtk_box_pack_start(GTK_BOX(editableBox), clipboardBox, 0,0,0);
    gtk_box_pack_start(GTK_BOX(registers), editableBox, 0, 0, 0);

    gtk_container_add(GTK_CONTAINER(scrolledwindow), textArea);
	gtk_box_pack_start(GTK_BOX(registers), scrolledwindow, 0, 0, 3);

	GtkWidget* memory = drawMemory(window); //gets memory and their dependencies widget
	gtk_box_pack_start(GTK_BOX(registers), memory, 0,0,5); //keep memory block horizontal to register block

	gtk_container_add(GTK_CONTAINER(window), container); //container is added to the window
	gtk_widget_show_all(window); //all components/widgets are shown
	gtk_main(); //hold on gtkMain until quit
	return 0;
}