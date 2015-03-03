#ifndef _MEMORY_H_
#define _MEMORY_H_

GtkWidget* drawMemory(GtkWidget* window){
	int i, j;
	GtkWidget* registers = gtk_vbox_new(0,0);
	GtkWidget *hbox, *frame, *entry;

	const gchar* memory[0xf*0xf];
	for (i = 0; i < 0xf*0xf; i++)
		memory[i] = "ff";

	frame = gtk_frame_new("\tMemory Block\t");
	gtk_frame_set_label_align(GTK_FRAME(frame), 0.5, 0.5);

	GtkWidget* table = gtk_table_new(0xf, 0xf, 1);
	registers = gtk_vbox_new(0,0);
	for (i = 0; i < 0xf; i++){
		hbox = gtk_hbox_new(0,0);
		for (j = 0; j < 0xf; j++){
			entry = gtk_entry_new();
			gtk_entry_set_max_length(GTK_ENTRY(entry), 2);
			gtk_entry_set_text(GTK_ENTRY(entry), memory[0xf * i + j]);
			gtk_entry_set_editable(GTK_ENTRY(entry), FALSE);
			gtk_widget_set_size_request(entry, 25, 25);
			gtk_box_pack_start(GTK_BOX(hbox), entry, 0, 0, 0);
		}
		gtk_box_pack_start(GTK_BOX(registers), hbox, 0, 0, 0);
	}
	gtk_container_add(GTK_CONTAINER(frame), registers);

	return frame;
}

#endif
