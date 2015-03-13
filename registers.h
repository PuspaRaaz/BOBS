#ifndef _REGISTERS_H_
#define _REGISTERS_H_

GtkWidget* drawRegisters(GtkWidget* window){
	GtkWidget* registers = gtk_hbox_new(0,0);
	GtkWidget* container = gtk_vbox_new(0,0);

	const gchar* regNames[] = {"B:", "C:", "D:", "E:", "H:", "L:", "M:", "A:", "F:", "PC:"};
	const gchar* portNames[] = {"Flag:", "Port A:", "Port B:", "Port C:"};

	const gchar* regValues[] = {"95", "b8", "d2", "e1", "f5", "a0", "46", "39", "12", "8000"};
	const gchar* portValues[] = {"1 0 1 0 1", "0 1 0 0 0 1 0 0", "1 0 0 1 1 0 1 0", "0 0 0 1 0 1 1 0"};

	GtkWidget *align, *label;
	GtkWidget* frame;

	int i, j;
	GtkWidget* table = gtk_table_new(5,4,1);
	frame = gtk_frame_new("Registers");
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
	gtk_box_pack_start(GTK_BOX(container), frame, 0, 0, 5);

	table = gtk_table_new(4, 2, 1);
	frame = gtk_frame_new("Outputs");
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
	gtk_box_pack_start(GTK_BOX(container), frame, 0, 0, 5);

	gtk_box_pack_start(GTK_BOX(registers), container, 0, 0, 10);
	return registers;
}

#endif
