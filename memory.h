#ifndef _MEMORY_H_
#define _MEMORY_H_

GtkWidget* drawMemory(GtkWidget* window){
	GtkWidget* registers = gtk_vbox_new(0,0);
	GtkWidget* label = gtk_label_new("Memory Block here...");
	gtk_box_pack_start(GTK_BOX(registers), label, 0,0,3);

	GtkWidget* table = gtk_table_new(0xf, 0xf, 1);
	gtk_box_pack_start(GTK_BOX(registers), table, 0, 0, 3);

	int i, j;
	for (i = 0; i < 0xf; i++){
		for (j = 0; j < 0xf; j++){
			label = gtk_label_new("ff");
			gtk_table_attach(GTK_TABLE(table), label, j, j+1, i, i+1, GTK_FILL,GTK_FILL,5,5);
		}
	}
	return registers;
}

#endif
