#ifndef _PPI_H_
#define _PPI_H_

GtkWidget* getPPI(GtkWidget* window){
	int i, j;
	GtkWidget* registers = gtk_vbox_new(0,0);
	GtkWidget *hbox, *frame, *entry, *container;

	const gchar* memory[0xf*0xf];
	for (i = 0; i < 0xf*0xf; i++)
		memory[i] = "ppi";

	frame = gtk_frame_new("\t8255 PPI\t");
	gtk_frame_set_label_align(GTK_FRAME(frame), 0.5, 0.5);

	GtkWidget* table = gtk_table_new(0xf, 0xf, 1);
	registers = gtk_vbox_new(0,0);
	for (i = 0; i < 0x8; i++){
		hbox = gtk_hbox_new(0,0);
		for (j = 0; j < 0xe; j++){
			entry = gtk_entry_new();
			gtk_entry_set_max_length(GTK_ENTRY(entry), 3);
			gtk_entry_set_text(GTK_ENTRY(entry), memory[0xf * i + j]);
			gtk_entry_set_editable(GTK_ENTRY(entry), FALSE);
			gtk_widget_set_size_request(entry, 35, 25);
			gtk_box_pack_start(GTK_BOX(hbox), entry, 0, 0, 0);
		}
		gtk_box_pack_start(GTK_BOX(registers), hbox, 0, 0, 0);
	}
	entry = gtk_label_new("This area is for 8255 PPI.\n It is under construction.\nMemory block is placed only to have distinguishable area.");
	hbox = gtk_hbox_new(0,0);
	gtk_box_pack_start(GTK_BOX(hbox), registers, 0, 0, 0);
	gtk_box_pack_start(GTK_BOX(hbox), entry, 0, 0, 0);

	gtk_container_add(GTK_CONTAINER(frame), hbox);

	container = gtk_hbox_new(0, 0);
	gtk_box_pack_start(GTK_BOX(container), frame, 1, 1, 5);

	return container;
}

#endif
