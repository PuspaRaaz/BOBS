#ifndef _REGISTER_AND_OUTPUT_H
#define _REGISTER_AND_OUTPUT_H

#define GTK_ENABLE_BROKEN
#include <gtk/gtk.h>
#include <stdio.h>

GtkWidget* registerOutput(GtkWidget* window, gchar* a, gchar* b, gchar* c, gchar* d,
				gchar* e, gchar* f, gchar* h, gchar* l, gchar* m){
	GtkWidget *vbox, *hbox, *table, *label;
    int i, j;
	gchar* registerArray[9] = {"B :", "C :", "D :", "E :", "H :", "L :", "M :", "A :"};
	gchar* registerValue[9] = {b, c, d, e, h, l, m, a};
	gchar* outputArray[3] = {"Port A :", "Port B :", "Port C :"};		
	gchar* outputValue[3][8] = {{"0", "0", "1", "1", "0", "1", "1", "0"},
								{"0", "0", "1", "1", "0", "1", "1", "0"},
								{"0", "0", "1", "1", "0", "1", "1", "0"}};
	
	gchar* flagTypes[5] = {"S", "AC", "P", "Z", "CY"};
	gchar* flagVlaue[5] = {"0", "0", "1", "1", "0"};
	gchar* programCounter = "8000";

    gint row = 13, col = 10;
    table = gtk_table_new(row,col,1);
	label = gtk_label_new("Registers: \n");
    gtk_table_attach(GTK_TABLE(table),label,0,10,0,1,GTK_FILL,GTK_FILL,10,0);

    for (i = 0; i < 4; i++){
    	for (j = 0; j < 2; j++){
	    	label = gtk_label_new(registerArray[2*i + j]);
	    	gtk_table_attach(GTK_TABLE(table),label,5*j,5*j+2, i+1,i+2,GTK_FILL,GTK_FILL,5,5);
	    	label = gtk_label_new(registerValue[2*i + j]);
	    	gtk_table_attach(GTK_TABLE(table),label,5*j+2,5*j+4, i+1,i+2,GTK_FILL,GTK_FILL,5,5);
	    }
    }

	label = gtk_label_new("\nOutputs: \n");
    gtk_table_attach(GTK_TABLE(table),label,0,10,5,6,GTK_FILL,GTK_FILL,10,0);

    for (i = 0; i < 3; i++){
    	label = gtk_label_new(outputArray[i]);
    	gtk_table_attach(GTK_TABLE(table),label,0,2, i+6,i+7,GTK_FILL,GTK_FILL,5,5);
    	for (j = 0; j < 8; j++){
	    	label = gtk_label_new(outputValue[i][j]);
	    	gtk_table_attach(GTK_TABLE(table),label,j+2,j+3, i+6,i+7,GTK_FILL,GTK_FILL,5,5);
	    }
    }

	label = gtk_label_new("\nFlag Register: \n");
    gtk_table_attach(GTK_TABLE(table),label,0,10,9,10,GTK_FILL,GTK_FILL,10,0);

    for (i = 0; i < 5; i++){
		label = gtk_label_new(flagTypes[i]);
		gtk_table_attach(GTK_TABLE(table),label,2*i,2*i+2, 10,11,GTK_FILL,GTK_FILL,5,5);
		label = gtk_label_new(flagVlaue[i]);
		gtk_table_attach(GTK_TABLE(table),label,2*i,2*i+2, 11,12,GTK_FILL,GTK_FILL,5,5);
	}

	label = gtk_label_new("\nPC: \n");
    gtk_table_attach(GTK_TABLE(table),label,0,2,12,13,GTK_FILL,GTK_FILL,10,0);
	label = gtk_label_new(programCounter);
	gtk_table_attach(GTK_TABLE(table),label,2,3, 12,13,GTK_FILL,GTK_FILL,5,5);
    
	return table;
}

#endif