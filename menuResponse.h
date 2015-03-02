#ifndef _MENURESPONSE_H_
#define _MENURESPONSE_H_

#include "menuActions.h"
#include "string.h"
#include <gtk/gtk.h>

static void menuResponse(GtkWidget *menuItems, gpointer data){
	const char* items = gtk_menu_item_get_label(GTK_MENU_ITEM(menuItems));
	if(strcmp(items,"New") == 0){
		newFile(window);
		g_print("New\n");
	}
	if(strcmp(items,"Open") == 0){
		g_print("Open\n");
	}
	if(strcmp(items,"Save") == 0){
		g_print("Save\n");
	}
	if(strcmp(items,"Quit") == 0){
		gtk_main_quit();
		g_print("Quit\n");
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
	if(strcmp(items,"Instructions") == 0){
		g_print("Instructions\n");
	}
	if(strcmp(items,"Help") == 0){
		g_print("Help\n");
	}
	if(strcmp(items,"About") == 0){
		g_print("About\n");
	}
}


#endif
