#ifndef _MENU_H_
#define _MENU_H_

#include "menuActions.h"
#include "menuResponse.h"
#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>
#include <string.h>

GtkWidget* drawMenuItems(GtkWidget* window){
	int i, j;
	const gchar* menuName[] = {"_File", "_Edit", "E_xecute", "_Help"};

	GtkWidget* menu[4];
	for (i = 0; i < 4; i++) menu[i] = gtk_menu_new();

	GtkWidget* menuBox = gtk_vbox_new(0, 0);
	GtkWidget* menuBar = gtk_menu_bar_new();
	GtkWidget* sep = gtk_separator_menu_item_new();
	GtkAccelGroup* accelGroup = gtk_accel_group_new();
	GtkWidget* items;

	gtk_window_add_accel_group(GTK_WINDOW(window), accelGroup);

	int length = sizeof(menuName) / sizeof(*menuName);
	for(i = 0; i < length; i++){
		items = gtk_menu_item_new_with_mnemonic(menuName[i]);
		gtk_menu_item_set_submenu(GTK_MENU_ITEM(items), menu[i]);
		gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), items);
	}
	
	//File menu
	items = gtk_menu_item_new_with_label("New");
	gtk_menu_shell_append(GTK_MENU_SHELL(menu[0]), items);
	gtk_widget_add_accelerator(items, "activate", accelGroup, GDK_n, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	g_signal_connect(items, "activate", G_CALLBACK(newFile), NULL);

	items = gtk_menu_item_new_with_label("Open");
	gtk_menu_shell_append(GTK_MENU_SHELL(menu[0]), items);
	gtk_widget_add_accelerator(items, "activate", accelGroup, GDK_o, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	g_signal_connect(items, "activate", G_CALLBACK(openFile), NULL);

	items = gtk_menu_item_new_with_label("Save");
	gtk_menu_shell_append(GTK_MENU_SHELL(menu[0]), items);
	gtk_widget_add_accelerator(items, "activate", accelGroup, GDK_s, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	g_signal_connect(items, "activate", G_CALLBACK(saveFile), NULL);

	gtk_menu_shell_append(GTK_MENU_SHELL(menu[0]), sep);

	items = gtk_menu_item_new_with_label("Quit");
	gtk_menu_shell_append(GTK_MENU_SHELL(menu[0]), items);
	gtk_widget_add_accelerator(items, "activate", accelGroup, GDK_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	g_signal_connect(items, "activate", G_CALLBACK(gtk_main_quit), NULL);

	//Edit menu
	items = gtk_menu_item_new_with_label("Undo");
	gtk_menu_shell_append(GTK_MENU_SHELL(menu[1]), items);
	gtk_widget_add_accelerator(items, "activate", accelGroup, GDK_z, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	g_signal_connect(items, "activate", G_CALLBACK(undoMenu), NULL);

	items = gtk_menu_item_new_with_label("Redo");
	gtk_menu_shell_append(GTK_MENU_SHELL(menu[1]), items);
	gtk_widget_add_accelerator(items, "activate", accelGroup, GDK_y, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	g_signal_connect(items, "activate", G_CALLBACK(redoMenu), NULL);

	sep = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(menu[1]), sep);

	items = gtk_menu_item_new_with_label("Preferences");
	gtk_menu_shell_append(GTK_MENU_SHELL(menu[1]), items);
	gtk_widget_add_accelerator(items, "activate", accelGroup, GDK_P, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	g_signal_connect(items, "activate", G_CALLBACK(preferencesMenu), NULL);

	//Execute menu
	items = gtk_menu_item_new_with_label("Build");
	gtk_menu_shell_append(GTK_MENU_SHELL(menu[2]), items);
	gtk_widget_add_accelerator(items, "activate", accelGroup, GDK_F5, GdkModifierType(NULL), GTK_ACCEL_VISIBLE);
	g_signal_connect(items, "activate", G_CALLBACK(buildMenu), NULL);

	items = gtk_menu_item_new_with_label("Run");
	gtk_menu_shell_append(GTK_MENU_SHELL(menu[2]), items);
	gtk_widget_add_accelerator(items, "activate", accelGroup, GDK_F9, GdkModifierType(NULL), GTK_ACCEL_VISIBLE);
	g_signal_connect(items, "activate", G_CALLBACK(runMenu), NULL);

	items = gtk_menu_item_new_with_label("Single Step");
	gtk_menu_shell_append(GTK_MENU_SHELL(menu[2]), items);
	gtk_widget_add_accelerator(items, "activate", accelGroup, GDK_F10, GdkModifierType(NULL), GTK_ACCEL_VISIBLE);
	g_signal_connect(items, "activate", G_CALLBACK(singleStepMenu), NULL);

	//Help menu
	items = gtk_menu_item_new_with_label("Instructions");
	gtk_menu_shell_append(GTK_MENU_SHELL(menu[3]), items);
	gtk_widget_add_accelerator(items, "activate", accelGroup, GDK_F3, GdkModifierType(NULL), GTK_ACCEL_VISIBLE);
	g_signal_connect(items, "activate", G_CALLBACK(instructionDialog), NULL);

	items = gtk_menu_item_new_with_label("Help");
	gtk_menu_shell_append(GTK_MENU_SHELL(menu[3]), items);
	gtk_widget_add_accelerator(items, "activate", accelGroup, GDK_F1, GdkModifierType(NULL), GTK_ACCEL_VISIBLE);
	g_signal_connect(items, "activate", G_CALLBACK(helpDialog), NULL);

	sep = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(menu[3]), sep);

	items = gtk_menu_item_new_with_label("About");
	gtk_menu_shell_append(GTK_MENU_SHELL(menu[3]), items);
	g_signal_connect(items, "activate", G_CALLBACK(aboutDialog), NULL);

	gtk_box_pack_start(GTK_BOX(menuBox), menuBar, 0,0,0);
	return menuBox;
}

#endif
