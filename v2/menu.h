#ifndef _MENU_H_
#define _MENU_H_

// #include "editMenu.h"
// #include "executeMenu.h"
// #include "fileMenu.h"
// #include "helpMenu.h"
#include "menuResponse.h"
#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>
#include <string.h>

GtkWidget* drawMenuItems(GtkWidget* window){
	GtkWidget* menuBox = gtk_vbox_new(0, 0);
	GtkWidget* menuBar = gtk_menu_bar_new();
	GtkWidget* fileMenu = gtk_menu_new();
	GtkWidget* editMenu = gtk_menu_new();
	GtkWidget* executeMenu = gtk_menu_new();
	GtkWidget* helpMenu = gtk_menu_new();
	GtkWidget* toolsMenu = gtk_menu_new();
	GtkWidget* sep = gtk_separator_menu_item_new();
	GtkAccelGroup* accelGroup = gtk_accel_group_new();

	gtk_window_add_accel_group(GTK_WINDOW(window), accelGroup);

	GtkWidget* menuItems = gtk_menu_item_new_with_mnemonic("_File");
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
	
	//File menu
	menuItems = gtk_menu_item_new_with_label("New");
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), menuItems);
	gtk_widget_add_accelerator(menuItems, "activate", accelGroup, GDK_n, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	g_signal_connect(menuItems, "activate", G_CALLBACK(newFile), NULL);

	menuItems = gtk_menu_item_new_with_label("Open");
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), menuItems);
	gtk_widget_add_accelerator(menuItems, "activate", accelGroup, GDK_o, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	g_signal_connect(menuItems, "activate", G_CALLBACK(openFile), NULL);

	menuItems = gtk_menu_item_new_with_label("Save");
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), menuItems);
	gtk_widget_add_accelerator(menuItems, "activate", accelGroup, GDK_s, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	g_signal_connect(menuItems, "activate", G_CALLBACK(saveFile), NULL);

	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), sep);

	menuItems = gtk_menu_item_new_with_label("Quit");
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), menuItems);
	gtk_widget_add_accelerator(menuItems, "activate", accelGroup, GDK_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	g_signal_connect(menuItems, "activate", G_CALLBACK(gtk_main_quit), NULL);

	//Edit menu
	menuItems = gtk_menu_item_new_with_label("Undo");
	gtk_menu_shell_append(GTK_MENU_SHELL(editMenu), menuItems);
	gtk_widget_add_accelerator(menuItems, "activate", accelGroup, GDK_z, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	g_signal_connect(menuItems, "activate", G_CALLBACK(undoMenu), NULL);

	menuItems = gtk_menu_item_new_with_label("Redo");
	gtk_menu_shell_append(GTK_MENU_SHELL(editMenu), menuItems);
	gtk_widget_add_accelerator(menuItems, "activate", accelGroup, GDK_y, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	g_signal_connect(menuItems, "activate", G_CALLBACK(redoMenu), NULL);

	sep = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(editMenu), sep);

	menuItems = gtk_menu_item_new_with_label("Preferences");
	gtk_menu_shell_append(GTK_MENU_SHELL(editMenu), menuItems);
	gtk_widget_add_accelerator(menuItems, "activate", accelGroup, GDK_P, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	g_signal_connect(menuItems, "activate", G_CALLBACK(preferencesMenu), NULL);

	//Execute menu
	menuItems = gtk_menu_item_new_with_label("Build");
	gtk_menu_shell_append(GTK_MENU_SHELL(executeMenu), menuItems);
	gtk_widget_add_accelerator(menuItems, "activate", accelGroup, GDK_F5, GdkModifierType(NULL), GTK_ACCEL_VISIBLE);
	g_signal_connect(menuItems, "activate", G_CALLBACK(buildMenu), NULL);

	menuItems = gtk_menu_item_new_with_label("Run");
	gtk_menu_shell_append(GTK_MENU_SHELL(executeMenu), menuItems);
	gtk_widget_add_accelerator(menuItems, "activate", accelGroup, GDK_F9, GdkModifierType(NULL), GTK_ACCEL_VISIBLE);
	g_signal_connect(menuItems, "activate", G_CALLBACK(runMenu), NULL);

	menuItems = gtk_menu_item_new_with_label("Single Step");
	gtk_menu_shell_append(GTK_MENU_SHELL(executeMenu), menuItems);
	gtk_widget_add_accelerator(menuItems, "activate", accelGroup, GDK_F10, GdkModifierType(NULL), GTK_ACCEL_VISIBLE);
	g_signal_connect(menuItems, "activate", G_CALLBACK(singleStepMenu), NULL);

	//Help menu
	menuItems = gtk_menu_item_new_with_label("Instructions");
	gtk_menu_shell_append(GTK_MENU_SHELL(helpMenu), menuItems);
	gtk_widget_add_accelerator(menuItems, "activate", accelGroup, GDK_F3, GdkModifierType(NULL), GTK_ACCEL_VISIBLE);
	g_signal_connect(menuItems, "activate", G_CALLBACK(instructionDialog), NULL);

	menuItems = gtk_menu_item_new_with_label("Help");
	gtk_menu_shell_append(GTK_MENU_SHELL(helpMenu), menuItems);
	gtk_widget_add_accelerator(menuItems, "activate", accelGroup, GDK_F1, GdkModifierType(NULL), GTK_ACCEL_VISIBLE);
	g_signal_connect(menuItems, "activate", G_CALLBACK(helpDialog), NULL);

	sep = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(helpMenu), sep);

	menuItems = gtk_menu_item_new_with_label("About");
	gtk_menu_shell_append(GTK_MENU_SHELL(helpMenu), menuItems);
	g_signal_connect(menuItems, "activate", G_CALLBACK(aboutDialog), NULL);

	gtk_box_pack_start(GTK_BOX(menuBox), menuBar, 0,0,0);
	return menuBox;
}

#endif
