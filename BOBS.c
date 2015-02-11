#include "menu.h"
#include "textarea.h"
#include "registerAndOutput.h"
#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv); //initialize gtk

	//initialize variables
	GtkWidget *window, *hbox, *vbox, *registerAndOutput, *textarea;
	gchar *rA = "7",*rB = "0", *rC = "1", *rD = "2", *rE = "3", *rF = "0", *rH = "4", *rL = "5", *rM = "6";
	
	//initialize window and set its titla
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "BOBS' Simulator");

	//set close (x) button to perform its default function, quiting the program
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	vbox = drawMenu(window);
	hbox = gtk_hbox_new(FALSE, 0);
	registerAndOutput = registerOutput(window, rA, rB, rC, rD, rE, rF, rH, rL, rM);
	gtk_box_pack_start(GTK_BOX(hbox), registerAndOutput, 0, 0, 0);
	textarea = drawTextarea(window);
	gtk_box_pack_start(GTK_BOX(hbox), textarea, 1, 1, 1);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 1);

	//add the box containing menu bar to the window
	gtk_container_add(GTK_CONTAINER(window), vbox);

	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}