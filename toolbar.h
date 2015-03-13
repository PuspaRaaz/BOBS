#ifndef _TOOLBAR_H_
#define _TOOLBAR_H_

#include "menu.h"

GtkWidget* drawToolbar(GtkWidget* window){
	GtkWidget* toolbar = gtk_toolbar_new();
	gtk_container_set_border_width(GTK_CONTAINER(toolbar), 5);
    gtk_toolbar_set_style(GTK_TOOLBAR ( toolbar ), GTK_TOOLBAR_ICONS);

	GtkWidget* icon = gtk_image_new_from_icon_name("gtk-add", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "New", "New (Ctrl+N)", "Private", icon, G_CALLBACK(newFile), NULL);
	icon = gtk_image_new_from_icon_name("gtk-open", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "Open", "Open (Ctrl+O)", "Private", icon, G_CALLBACK(openFile), NULL);
	icon = gtk_image_new_from_icon_name("gtk-save", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "Save", "Save (Ctrl+S)", "Private", icon, G_CALLBACK(saveFile), NULL);
	
	gtk_toolbar_append_space(GTK_TOOLBAR(toolbar));

	icon = gtk_image_new_from_icon_name("gtk-go-back", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "Undo", "Undo (Ctrl+Z)", "Private", icon, G_CALLBACK(undoMenu), NULL);
	icon = gtk_image_new_from_icon_name("gtk-go-forward", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "Redo", "Redo (Ctrl+Y)", "Private", icon, G_CALLBACK(redoMenu), NULL);
	
	gtk_toolbar_append_space(GTK_TOOLBAR(toolbar));

	icon = gtk_image_new_from_icon_name("gtk-yes", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "Build", "Build (F5)", "Private", icon, G_CALLBACK(buildMenu), NULL);
	icon = gtk_image_new_from_icon_name("gtk-media-play", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "Run", "Run (F9)", "Private", icon, G_CALLBACK(runMenu), NULL);
	icon = gtk_image_new_from_icon_name("gtk-goto-last", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "SS", "Single Step (F10)", "Private", icon, G_CALLBACK(singleStepMenu), NULL);
	icon = gtk_image_new_from_icon_name("gtk-convert", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "Convert", "Convert Code (F11)", "Private", icon, G_CALLBACK(convertMenu), NULL);
	
	gtk_toolbar_append_space(GTK_TOOLBAR(toolbar));

	icon = gtk_image_new_from_icon_name("gtk-info", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "Ins", "Instructions (F3)", "Private", icon, G_CALLBACK(instructionDialog), NULL);
	icon = gtk_image_new_from_icon_name("gtk-help", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "Help", "Help (F1)", "Private", icon, G_CALLBACK(helpDialog), NULL);
	icon = gtk_image_new_from_icon_name("gtk-about", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "About", "About (F12)", "Private", icon, G_CALLBACK(aboutDialog), NULL);
	
	gtk_toolbar_append_space(GTK_TOOLBAR(toolbar));

	icon = gtk_image_new_from_icon_name("gtk-preferences", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "Setting", "Setting (Ctrl+P)", "Private", icon, G_CALLBACK(preferencesMenu), NULL);
	
	gtk_toolbar_append_space(GTK_TOOLBAR(toolbar));

	icon = gtk_image_new_from_icon_name("gtk-close", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "Quit", "Quit (Ctrl+Q)", "Private", icon, G_CALLBACK(gtk_main_quit), NULL);
	
	GtkWidget* hbox = gtk_hbox_new(0,0);
	gtk_box_pack_start(GTK_BOX(hbox), toolbar, 0,0,0);

	return hbox;
}

#endif
