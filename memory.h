#ifndef _MEMORY_H_
#define _MEMORY_H_

GtkWidget* drawMemory(GtkWidget* window){
	int i, j;
	GtkWidget* registers = gtk_vbox_new(0,0);
	GtkWidget *hbox, *separator, *frame, *label;

	const gchar* memory[0xf*0xf];
	for (i = 0; i < 0xf*0xf; i++)
		memory[i] = "ff";

	separator = gtk_hseparator_new();
	gtk_box_pack_start(GTK_BOX(registers), separator, 0, 0, 1);
	for (i = 0; i < 0xf; i++){
		hbox = gtk_hbox_new(0,0);
		separator = gtk_vseparator_new();
		gtk_box_pack_start(GTK_BOX(hbox), separator, 0, 0, 1);
		for (j = 0; j < 0xf; j++){
			label = gtk_label_new(memory[0xf*i+j]);
			gtk_box_pack_start(GTK_BOX(hbox), label, 0,0,5);
			separator = gtk_vseparator_new();
			gtk_box_pack_start(GTK_BOX(hbox), separator, 0, 0, 1);
		}
		gtk_box_pack_start(GTK_BOX(registers), hbox, 0, 0, 5);
		separator = gtk_hseparator_new();
		gtk_box_pack_start(GTK_BOX(registers), separator, 0, 0, 1);
	}
	frame = gtk_frame_new("Memory Block");
	gtk_container_add(GTK_CONTAINER(frame), registers);
	return frame;
}

#endif
