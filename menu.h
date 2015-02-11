#ifndef _MENU_H
#define _MENU_H

#include <gtk/gtk.h>

static void openFileDialog(GtkWidget* button, gpointer window)
{
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new("Chosse a file", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
    gtk_widget_show_all(dialog);
    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), g_get_home_dir());
    gint resp = gtk_dialog_run(GTK_DIALOG(dialog));
    if(resp == GTK_RESPONSE_OK)
            g_print("%s\n", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
    else
            g_print("You pressed Cancel\n");
    gtk_widget_destroy(dialog);
}     
static void openAboutDialog(GtkWidget* button, gpointer window)
{
    GtkWidget *dialog, *label;
    dialog = gtk_dialog_new_with_buttons("About", GTK_WINDOW(window), GTK_DIALOG_MODAL, NULL);
    gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);
    label = gtk_label_new("8085 Simulator\n");
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog) -> vbox), label, 0,0,0);
    label = gtk_label_new("'8085 Simulator' is a completely GUI implemented and\nfully functioning simulator for 8085 microprocessor\nprogramming with both opcode and instruction mode\ninput, conversion of codes from one mode to another,\nattached 8255 PPI and hardware interrupts.\n");
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog) -> vbox), label, 0,0,0);
    label = gtk_label_new("Developers:");
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog) -> vbox), label, 0,0,0);
    label = gtk_label_new("Prabesh Pathak, Pramod Maharjan");
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog) -> vbox), label, 0,0,0);
    label = gtk_label_new("Prasanna Koirala, Puspa Raaz...\n");
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog) -> vbox), label, 0,0,0);
    label = gtk_label_new("Copyright: Developers");
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog) -> vbox), label, 0,0,0);
    label = gtk_label_new("All right reserved");
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog) -> vbox), label, 0,0,0);
    gtk_widget_show_all(dialog);
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}    
static void openInstructionSetDialog(GtkWidget* button, gpointer window)
{
    int i, j;
	const gchar* instruction[50] = {"ACI", "ADC A", "ADC B", "ADC C",
								"ADC D", "ADC E", "ADC H", "ADC L",
								"ADC M", "ADD A", "ADD B", "ADD C",
								"ADC D", "ADD E", "ADD H", "ADD L",
								"ADD M", "ADI", "ANA A", "ANA B",
								"ANA C", "ANA D", "ANA E", "ANA H",
								"ANA L", "ANA M", "ANI", "CALL",
								"CMA", "CMC", "CMP A", "CMP B",
								"CMP C", "CMP D","CMP E", "CMP H",
								"CMP L", "CMP M"};
	const gchar* opcode[50] = {"CE", "8F", "88", "89",
								"8A", "8B", "8C","8D",
								"8E", "87", "80", "81",
								"82", "83", "84", "85",
								"86", "C6", "A6", "A0",
								"A1", "A2", "A3", "A4",
								"A5", "A6", "E6", "CD",
								"2F", "3F", "BF", "B8",
								"B9", "BA", "BB", "BC",
								"BD", "BE"};
    GtkWidget *dialog, *label, *table;
    dialog = gtk_dialog_new_with_buttons("Instruction Set", GTK_WINDOW(window), GTK_DIALOG_DESTROY_WITH_PARENT, NULL);
    gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);
    gint row = 25, col = 6, block = 2;
    table = gtk_table_new(row,col,0);
    col = col / block;
    for(i = 0; i < col; i++){
    	label = gtk_label_new("\tMnemonics\n");
	    gtk_table_attach(GTK_TABLE(table),label,i*block,i*block+1,0,1,GTK_FILL,GTK_FILL,5,0);
	    label = gtk_label_new("opcode\t\n");
	    gtk_table_attach(GTK_TABLE(table),label,i*block+1,i*block+2,0,1,GTK_FILL,GTK_FILL,0,0);
    }
    for (i = 0; i < 25; i++){
    	for (j = 0; j < col; j++){
    		label = gtk_label_new(instruction[col*i+j]);
    		gtk_table_attach(GTK_TABLE(table),label,j*block,j*block+1,i+1,i+2,GTK_FILL,GTK_FILL,0,0);
    		label = gtk_label_new(opcode[col*i+j]);
    		gtk_table_attach(GTK_TABLE(table),label,j*block+1,j*block+2,i+1,i+2,GTK_FILL,GTK_FILL,0,0);
    	}
    }

    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog) -> vbox), table, 0,0,0);
    gtk_widget_show_all(dialog);
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
static void menuResponse(GtkWidget *menuItems, gpointer data){
	const char* items = gtk_menu_item_get_label(GTK_MENU_ITEM(menuItems));
	if(strcmp(items,"New") == 0){
		g_print("New\n");
	}
	if(strcmp(items,"Save") == 0){
		g_print("Save\n");
	}
	if(strcmp(items,"Cut") == 0){
		g_print("Cut\n");
	}
	if(strcmp(items,"Copy") == 0){
		g_print("Copy\n");
	}
	if(strcmp(items,"Paste") == 0){
		g_print("Paste\n");
	}
	if(strcmp(items,"Undo") == 0){
		g_print("Undo\n");
	}
	if(strcmp(items,"Redo") == 0){
		g_print("Redo\n");
	}
	if(strcmp(items,"Build") == 0){
		g_print("Build\n");
	}
	if(strcmp(items,"Run") == 0){
		g_print("Run\n");
	}
	if(strcmp(items,"Single Step") == 0){
		g_print("Single Step\n");
	}
	if(strcmp(items,"Documentation") == 0){
		g_print("Documentation\n");
	}
}
GtkWidget* drawMenu(GtkWidget* window)
{
	//initialize variables
	GtkWidget *vbox, *button, *menuBar, *fileMenu, *editMenu, *executeMenu, *helpMenu, *menuItems;

	//set menu bar
	menuBar = gtk_menu_bar_new();
	//set menu items
	fileMenu = gtk_menu_new();
	editMenu = gtk_menu_new();
	executeMenu = gtk_menu_new();
	helpMenu = gtk_menu_new();

	//name the menu items and add them to the menu bar
	menuItems = gtk_menu_item_new_with_mnemonic("_File");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuItems), fileMenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), menuItems);
	menuItems = gtk_menu_item_new_with_mnemonic("_Edit");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuItems), editMenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), menuItems);
	menuItems = gtk_menu_item_new_with_mnemonic("E_xecute");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuItems), executeMenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), menuItems);
	menuItems = gtk_menu_item_new_with_mnemonic("_Help");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuItems), helpMenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), menuItems);

	//set sub menu items
	menuItems = gtk_menu_item_new_with_label("New");
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), menuItems);
	g_signal_connect(menuItems, "activate", G_CALLBACK(menuResponse), NULL);
	menuItems = gtk_menu_item_new_with_label("Open");
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), menuItems);
	g_signal_connect(menuItems, "activate", G_CALLBACK(openFileDialog), NULL);
	menuItems = gtk_menu_item_new_with_label("Save");
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), menuItems);
	g_signal_connect(menuItems, "activate", G_CALLBACK(menuResponse), NULL);
	menuItems = gtk_menu_item_new_with_label("Exit");
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), menuItems);
	g_signal_connect(menuItems, "activate", G_CALLBACK(gtk_main_quit), NULL);
	menuItems = gtk_menu_item_new_with_label("Cut");
	gtk_menu_shell_append(GTK_MENU_SHELL(editMenu), menuItems);
	g_signal_connect(menuItems, "activate", G_CALLBACK(menuResponse), NULL);
	menuItems = gtk_menu_item_new_with_label("Copy");
	gtk_menu_shell_append(GTK_MENU_SHELL(editMenu), menuItems);
	g_signal_connect(menuItems, "activate", G_CALLBACK(menuResponse), NULL);
	menuItems = gtk_menu_item_new_with_label("Paste");
	gtk_menu_shell_append(GTK_MENU_SHELL(editMenu), menuItems);
	g_signal_connect(menuItems, "activate", G_CALLBACK(menuResponse), NULL);
	menuItems = gtk_menu_item_new_with_label("Undo");
	gtk_menu_shell_append(GTK_MENU_SHELL(editMenu), menuItems);
	g_signal_connect(menuItems, "activate", G_CALLBACK(menuResponse), NULL);
	menuItems = gtk_menu_item_new_with_label("Redo");
	gtk_menu_shell_append(GTK_MENU_SHELL(editMenu), menuItems);
	g_signal_connect(menuItems, "activate", G_CALLBACK(menuResponse), NULL);
	menuItems = gtk_menu_item_new_with_label("Build");
	gtk_menu_shell_append(GTK_MENU_SHELL(executeMenu), menuItems);
	g_signal_connect(menuItems, "activate", G_CALLBACK(menuResponse), NULL);
	menuItems = gtk_menu_item_new_with_label("Run");
	gtk_menu_shell_append(GTK_MENU_SHELL(executeMenu), menuItems);
	g_signal_connect(menuItems, "activate", G_CALLBACK(menuResponse), NULL);
	menuItems = gtk_menu_item_new_with_label("Single Step");
	gtk_menu_shell_append(GTK_MENU_SHELL(executeMenu), menuItems);
	g_signal_connect(menuItems, "activate", G_CALLBACK(menuResponse), NULL);
	menuItems = gtk_menu_item_new_with_label("Instruction Set");
	gtk_menu_shell_append(GTK_MENU_SHELL(helpMenu), menuItems);
	g_signal_connect(menuItems, "activate", G_CALLBACK(openInstructionSetDialog), window);
	menuItems = gtk_menu_item_new_with_label("Documentation");
	gtk_menu_shell_append(GTK_MENU_SHELL(helpMenu), menuItems);
	g_signal_connect(menuItems, "activate", G_CALLBACK(menuResponse), NULL);
	menuItems = gtk_menu_item_new_with_label("About");
	gtk_menu_shell_append(GTK_MENU_SHELL(helpMenu), menuItems);
	g_signal_connect(menuItems, "activate", G_CALLBACK(openAboutDialog), NULL);

	//add menu bar
	vbox = gtk_vbox_new(0,0);
	button = gtk_button_new_with_label("Hello");
	gtk_box_pack_start(GTK_BOX(vbox), menuBar, 0, 0, 0);

	return vbox;
}

#endif