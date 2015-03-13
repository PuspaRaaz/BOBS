#ifndef _MENU_H_
#define _MENU_H_

#include "menuActions.h"
#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>
#include <string.h>

static void menuResponse(GtkWidget *menuItems, gpointer data){
	const char* items = gtk_menu_item_get_label(GTK_MENU_ITEM(menuItems));
	if(strcmp(items,"New") == 0){
		newFile(menuItems, data);
		g_print("New\n");
	}
	if(strcmp(items,"Open") == 0){
		openFile(menuItems, data);
		g_print("Open\n");
	}
	if(strcmp(items,"Save") == 0){
		saveFile(menuItems, data);
		g_print("Save\n");
	}
	if(strcmp(items,"Quit") == 0){
		gtk_main_quit();
	}
	if(strcmp(items,"Undo") == 0){
		undoMenu(menuItems, data);
		g_print("Undo\n");
	}
	if(strcmp(items,"Redo") == 0){
		redoMenu(menuItems, data);
		g_print("Redo\n");
	}
	if(strcmp(items,"Preferences") == 0){
		preferencesMenu(menuItems, data);
		g_print("Preferences\n");
	}
	if(strcmp(items,"Build") == 0){
		buildMenu(menuItems, data);
		g_print("Build\n");
	}
	if(strcmp(items,"Run") == 0){
		runMenu(menuItems, data);
		g_print("Run\n");
	}
	if(strcmp(items,"Single Step") == 0){
		singleStepMenu(menuItems, data);
		g_print("Single Step\n");
	}
	if(strcmp(items,"Convert") == 0){
		convertMenu(menuItems, data);
		g_print("Converted\n");
	}
	if(strcmp(items,"Instructions") == 0){
		instructionDialog(menuItems, data);
	}
	if(strcmp(items,"Help") == 0){
		helpDialog(menuItems, data);
	}
	if(strcmp(items,"About") == 0){
		aboutDialog(menuItems, data);
	}
}

GtkWidget* drawMenuItems(GtkWidget* window){
	int i, j;

	GtkWidget* menu[4];
	for (i = 0; i < 4; i++) menu[i] = gtk_menu_new();

	const gchar* menuName[] = {"_File", "_Edit", "E_xecute", "_Help"};

	const gchar* fileMenuItemNames[] = {"New", "Open", "Save", "Quit"};
	const guint fileMenuAccelGroup[] = {GDK_n, GDK_o, GDK_s, GDK_q};

	const gchar* editMenuItemNames[] = {"Undo", "Redo", "Preferences"};
	const guint editMenuAccelGroup[] = {GDK_z, GDK_y, GDK_p};

	const gchar* executeMenuItemNames[] = {"Build", "Run", "Single Step"};
	const guint executeMenuAccelGroup[] = {GDK_F5, GDK_F9, GDK_F10};

	const gchar* helpMenuItemNames[] = {"Instructions", "Help", "About"};
	const guint helpMenuAccelGroup[] = {GDK_F3, GDK_F1, GDK_F12};

	GtkWidget* menuBox = gtk_vbox_new(0, 0);
	GtkWidget* menuBar = gtk_menu_bar_new();
	GtkWidget* sep = gtk_separator_menu_item_new();
	GtkAccelGroup* accelGroup = gtk_accel_group_new();
	GtkWidget* items;

	gtk_window_add_accel_group(GTK_WINDOW(window), accelGroup);

//menu items
	int length = sizeof(menuName) / sizeof(*menuName);
	for(i = 0; i < length; i++){
		items = gtk_menu_item_new_with_mnemonic(menuName[i]);
		gtk_menu_item_set_submenu(GTK_MENU_ITEM(items), menu[i]);
		gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), items);
	}

//file menu items
	length = sizeof(fileMenuItemNames) / sizeof(*fileMenuItemNames);
	for (i = 0; i < length; i++){
		items = gtk_menu_item_new_with_label(fileMenuItemNames[i]);
		gtk_menu_shell_append(GTK_MENU_SHELL(menu[0]), items);
		gtk_widget_add_accelerator(items, "activate", accelGroup, fileMenuAccelGroup[i], GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
		g_signal_connect(items, "activate", G_CALLBACK(menuResponse), (gpointer) window);
	}

//edit menu items
	length = sizeof(editMenuItemNames) / sizeof(*editMenuItemNames);
	for (i = 0; i < length; i++){
		items = gtk_menu_item_new_with_label(editMenuItemNames[i]);
		gtk_menu_shell_append(GTK_MENU_SHELL(menu[1]), items);
		gtk_widget_add_accelerator(items, "activate", accelGroup, editMenuAccelGroup[i], GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
		g_signal_connect(items, "activate", G_CALLBACK(menuResponse), (gpointer) window);
	}

//execute menu items
	length = sizeof(executeMenuItemNames) / sizeof(*executeMenuItemNames);
	for (i = 0; i < length; i++){
		items = gtk_menu_item_new_with_label(executeMenuItemNames[i]);
		gtk_menu_shell_append(GTK_MENU_SHELL(menu[2]), items);
		gtk_widget_add_accelerator(items, "activate", accelGroup, executeMenuAccelGroup[i], GdkModifierType(NULL), GTK_ACCEL_VISIBLE);
		g_signal_connect(items, "activate", G_CALLBACK(menuResponse), (gpointer) window);
	}

//help menu items
	length = sizeof(helpMenuItemNames) / sizeof(*helpMenuItemNames);
	for (i = 0; i < length; i++){
		items = gtk_menu_item_new_with_label(helpMenuItemNames[i]);
		gtk_menu_shell_append(GTK_MENU_SHELL(menu[3]), items);
		gtk_widget_add_accelerator(items, "activate", accelGroup, helpMenuAccelGroup[i], GdkModifierType(NULL), GTK_ACCEL_VISIBLE);
		g_signal_connect(items, "activate", G_CALLBACK(menuResponse), (gpointer) window);
	}

	gtk_box_pack_start(GTK_BOX(menuBox), menuBar, 0,0,0);
	return menuBox;
}

#endif
