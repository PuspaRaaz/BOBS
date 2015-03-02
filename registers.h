#ifndef _REGISTERS_H_
#define _REGISTERS_H_

GtkWidget* drawRegisters(GtkWidget* window){
	GtkWidget* registers = gtk_hbox_new(0,0);
	GtkWidget* container = gtk_vbox_new(0,0);

	GtkWidget* table = gtk_table_new(10,4,1);

	const gchar* regNames[10] = {"B:", "C:", "D:", "E:", "H:", "L:", "M:", "A:", "F:", "PC:"};
	const gchar* regValues[10] = {"b", "c", "d", "e", "h", "l", "m", "a", "f", "pc"};

	const gchar* portNames[4] = {"Flag:", "Port A:", "Port B:", "Port C:"};
	const gchar* portValues[4] = {"1 0 1 1 0", "0 1 0 0 0 1 0 0", "port b", "port c"};

	GtkWidget* label; int i, j;
	for (i = 0; i < 5; i++){
		for (j = 0; j < 2; j++){
			label = gtk_label_new(regNames[2*i+j]);
			gtk_table_attach(GTK_TABLE(table), label, 2*j, 2*j+1, i, i+1, GTK_FILL,GTK_FILL,5,5);
			label = gtk_label_new(regValues[2*i+j]);
			gtk_table_attach(GTK_TABLE(table), label, 2*j+1, 2*j+2, i, i+1, GTK_FILL,GTK_FILL,5,5);
		}
	}

	for (i = 5; i < 9; i++){
		label = gtk_label_new(portNames[i-5]);
		gtk_table_attach(GTK_TABLE(table), label, 0, 2, i, i+1, GTK_FILL,GTK_FILL,5,5);
		label = gtk_label_new(portValues[i-5]);
		gtk_table_attach(GTK_TABLE(table), label, 2, 4, i, i+1, GTK_FILL,GTK_FILL,5,5);
	}

	gtk_box_pack_start(GTK_BOX(registers), table, 0, 0, 10);
	return registers;
}

#endif
