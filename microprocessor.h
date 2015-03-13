#ifndef _MICROPROCESSOR_H_
#define _MICROPROCESSOR_H_

GtkWidget* getMicroprocessor(GtkWidget* window){
	int i, j;
	GtkWidget* micro = gtk_hbox_new(0,0);
	GtkWidget* hbox = gtk_hbox_new(0,0);
	GtkWidget* vbox = gtk_vbox_new(0,0);

	const gchar* regNames[] = {"B:", "C:", "D:", "E:", "H:", "L:", "M:", "A:", "F:", "PC:"};
	const gchar* portNames[] = {"Flag:", "Port A:", "Port B:", "Port C:"};

	const gchar* regValues[] = {"95", "b8", "d2", "e1", "f5", "a0", "46", "39", "12", "8000"};
	const gchar* portValues[] = {"1 0 1 0 1", "0 1 0 0 0 1 0 0", "1 0 0 1 1 0 1 0", "0 0 0 1 0 1 1 0"};

	GtkWidget *align, *label, *entry, *frame;

	GtkWidget* table = gtk_table_new(5,4,1);
	frame = gtk_frame_new(" Registers\t");
	for (i = 0; i < 5; i++){
		for (j = 0; j < 2; j++){
			label = gtk_label_new(regNames[2*i+j]);
			align = gtk_alignment_new(0.0, 0.5, 0.0, 0.0);
			gtk_container_add(GTK_CONTAINER(align), label);
			gtk_table_attach(GTK_TABLE(table), align, 2*j, 2*j+1, i, i+1, GTK_FILL,GTK_FILL,5,5);

			label = gtk_label_new(regValues[2*i+j]);
			align = gtk_alignment_new(0.0, 0.0, 0.0, 0.5);
			gtk_container_add(GTK_CONTAINER(align), label);
			gtk_table_attach(GTK_TABLE(table), align, 2*j+1, 2*j+2, i, i+1, GTK_FILL,GTK_FILL,5,5);
		}
	}

	gtk_container_add(GTK_CONTAINER(frame), table);
	gtk_box_pack_start(GTK_BOX(vbox), frame, 0, 0, 5);

	table = gtk_table_new(4, 2, 1);
	frame = gtk_frame_new(" Outputs\t");
	for (i = 0; i < 4; i++){
		label = gtk_label_new(portNames[i]);
		align = gtk_alignment_new(0.0, 0.5, 0.0, 0.0);
		gtk_container_add(GTK_CONTAINER(align), label);
		gtk_table_attach(GTK_TABLE(table), align, 0, 1, i, i+1, GTK_FILL,GTK_FILL,5,5);

		label = gtk_label_new(portValues[i]);
		align = gtk_alignment_new(0.0, 1.0, 0.0, 1.0);
		gtk_container_add(GTK_CONTAINER(align), label);
		gtk_table_attach(GTK_TABLE(table), align, 1, 2, i, i+1, GTK_FILL,GTK_FILL,5,5);
	}
	gtk_container_add(GTK_CONTAINER(frame), table);
	gtk_box_pack_start(GTK_BOX(vbox), frame, 0, 0, 5);

	entry = gtk_label_new("Set memory: ");
	gtk_box_pack_start(GTK_BOX(hbox), entry, 0, 0, 5);

	entry = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(entry), 4);
	gtk_entry_set_text(GTK_ENTRY(entry), "8000");
	gtk_widget_set_size_request(entry, 45, 25);
	gtk_box_pack_start(GTK_BOX(hbox), entry, 0, 0, 0);

	entry = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(entry), 2);
	gtk_entry_set_text(GTK_ENTRY(entry), "00");
	gtk_widget_set_size_request(entry, 25, 25);
	gtk_box_pack_start(GTK_BOX(hbox), entry, 0, 0, 0);

	gtk_box_pack_start(GTK_BOX(vbox), hbox, 0, 0, 5);

	gtk_box_pack_start(GTK_BOX(micro), vbox, 0, 0, 10); 

	//registers and outputs finished
	//now started textarea

	vbox = gtk_vbox_new(0,0);
	frame = gtk_frame_new("  Your code\t");
	gtk_frame_set_label_align(GTK_FRAME(frame), 0.0, 1.0);
	gtk_container_add(GTK_CONTAINER(frame), vbox);
	gtk_box_pack_start(GTK_BOX(micro), frame, 0, 0, 1);

	GtkWidget* textArea = gtk_text_view_new();
	GtkWidget* scrolledWindow = gtk_scrolled_window_new(NULL,NULL);
    gtk_widget_set_size_request(scrolledWindow, 250,300);

    gtk_container_add(GTK_CONTAINER(scrolledWindow), textArea);
    gtk_box_pack_start(GTK_BOX(vbox), scrolledWindow, 1, 1, 3);

	vbox = gtk_vbox_new(0,0);
	frame = gtk_frame_new("\tConverted code  ");
	gtk_frame_set_label_align(GTK_FRAME(frame), 1.0, 1.0);
	gtk_container_add(GTK_CONTAINER(frame), vbox);
	gtk_box_pack_start(GTK_BOX(micro), frame, 0, 0, 1);

	textArea = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textArea), FALSE);
	scrolledWindow = gtk_scrolled_window_new(NULL,NULL);
    gtk_widget_set_size_request(scrolledWindow, 250,300);

    gtk_container_add(GTK_CONTAINER(scrolledWindow), textArea);
    gtk_box_pack_start(GTK_BOX(vbox), scrolledWindow, 1, 1, 3);

	//textarea finished
	//now started memory block

	const gchar* memory[0x10*0x10];
	for (i = 0; i < 0x10*0x10; i++)
		memory[i] = "00";

	vbox = gtk_vbox_new(0,0);
	frame = gtk_frame_new("\tMemory Block ");
	gtk_frame_set_label_align(GTK_FRAME(frame), 0.5, 0.5);

	for (i = 0; i < 0x10; i++){
		hbox = gtk_hbox_new(0,0);
		for (j = 0; j < 0x10; j++){
			entry = gtk_entry_new();
			gtk_entry_set_max_length(GTK_ENTRY(entry), 2);
			gtk_entry_set_text(GTK_ENTRY(entry), memory[0xf * i + j]);
			gtk_entry_set_editable(GTK_ENTRY(entry), FALSE);
			gtk_widget_set_size_request(entry, 25, 25);
			gtk_box_pack_start(GTK_BOX(hbox), entry, 0, 0, 0);
			if((j+1) % 4 == 0)
				gtk_box_pack_start(GTK_BOX(hbox), gtk_vseparator_new(), 0, 0, 1);
		}
		gtk_box_pack_start(GTK_BOX(vbox), hbox, 0, 0, 0);
	}
	gtk_container_add(GTK_CONTAINER(frame), vbox);

	gtk_box_pack_start(GTK_BOX(micro), frame, 0, 0, 10);

	//memory block finished
	return micro;
}

#endif
