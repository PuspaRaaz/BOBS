#include "gtk/gtk.h"

void destroy(GtkWidget *widget, gpointer data){
	gtk_main_quit();
}
//returns box with icon followed by label
static GtkWidget *label_box_with_image(gchar *filename, gchar *label_text){
	GtkWidget *box;
	GtkWidget *label;
	GtkWidget *image;

	box = gtk_hbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(box), 2);
	image = gtk_image_new_from_file(filename);
	label = gtk_label_new(label_text);
	gtk_box_pack_start(GTK_BOX(box), image, FALSE, FALSE, 3);
	gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 3);
	gtk_widget_show(image);
	gtk_widget_show(label);

	return box;
}

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	GtkWidget *window;
	GtkWidget *box;
	GtkWidget *box1;
	GtkWidget *box2;
	GtkWidget *button;
	GtkWidget *radiobutton;
	GSList *modeGroup;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "8085 Simulator");
	gtk_widget_show(window);

	button = gtk_button_new();
	box = label_box_with_image("icon/new.xpm", "New");
	gtk_widget_show(box);
	gtk_container_add(GTK_CONTAINER(button), box);
	// gtk_widget_show(button);
	// gtk_container_add(GTK_CONTAINER(window), button);
	// gtk_widget_show(window);

	//input mode selector between opcode and instruction starts

	box1 = gtk_hbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), box1);
	gtk_widget_show(box1);
	box2 = gtk_hbox_new(FALSE, 10);
	gtk_container_set_border_width(GTK_CONTAINER(box2), 10);
	gtk_box_pack_start(GTK_BOX(box1), box2, TRUE, TRUE, 0);
	gtk_widget_show(box2);
	radiobutton = gtk_radio_button_new_with_label(NULL, "Opcode Mode");
	gtk_box_pack_start(GTK_BOX(box2), radiobutton, TRUE, TRUE, 0);
	gtk_widget_show(radiobutton);
	modeGroup = gtk_radio_button_get_group(GTK_RADIO_BUTTON(radiobutton));
	radiobutton = gtk_radio_button_new_with_label(modeGroup, "Instruction Mode");
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton), TRUE);
	gtk_box_pack_start(GTK_BOX(box2), radiobutton, TRUE, TRUE, 0);
	gtk_widget_show(radiobutton);
	gtk_box_pack_start(GTK_BUTTON(radiobutton), button, TRUE, TRUE, 0);
	gtk_widget_show(button);

	//input mode selector ends

	gtk_widget_show(window);
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(destroy), NULL);
	gtk_main();
	return 0;
}