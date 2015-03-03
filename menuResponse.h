#ifndef _MENURESPONSE_H_
#define _MENURESPONSE_H_

#include "menuActions.h"
#include "string.h"
#include <gtk/gtk.h>

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


#endif
