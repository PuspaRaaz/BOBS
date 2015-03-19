#include "gui.h"

void menuResponse(GtkWidget *menuItems, gpointer data){
	const char* items = gtk_menu_item_get_label(GTK_MENU_ITEM(menuItems));

	if ( strcmp ( items, "New" ) == 0 )		{		newFile(menuItems, data);		}
	if ( strcmp ( items, "Open" ) == 0 )	{		openFile(menuItems, data);		}
	if ( strcmp ( items, "Save" ) == 0 )	{		saveFile(menuItems, data);		}
	if ( strcmp ( items, "Quit" ) == 0 )	{		gtk_main_quit();				}
	if ( strcmp ( items, "Build" ) == 0 )	{		buildMenu(menuItems, data);		}
	if ( strcmp ( items, "Run" ) == 0 )		{		runMenu(menuItems, data);		}
	if ( strcmp ( items, "Help" ) == 0 )	{		helpDialog(menuItems, data);	}
	if ( strcmp ( items, "About" ) == 0 )	{		aboutDialog(menuItems, data);	}
	if ( strcmp ( items, "Convert" ) == 0 )	{		convertMenu(menuItems, data);	}
	if ( strcmp ( items, "Preferences" ) == 0 )		{		preferencesMenu(menuItems, data);	}
	if ( strcmp ( items, " Single Step" ) == 0 )	{		singleStepMenu(menuItems, data);	}
	if ( strcmp ( items, "Instructions" ) == 0 )	{		instructionDialog(menuItems, data);	}
}

GtkWidget* drawMenuItems(GtkWidget* window){
	int i, j;
	GtkWidget *menuBar, *vbox, *sep, *items;
	GtkAccelGroup *accelGroup;

	GtkWidget* menu[4];
	for (i = 0; i < 4; i++) menu[i] = gtk_menu_new();

	const gchar* menuName[] = {"_File", "E_xecute", "_Help"};

	const gchar* fileMenuItemNames[] = {"New", "Open", "Save", "Preferences", "Quit"};
	const guint fileMenuAccelGroup[] = {GDK_n, GDK_o, GDK_s, GDK_p, GDK_q};

	const gchar* executeMenuItemNames[] = {"Build", "Run", "Single Step", "Convert"};
	const guint executeMenuAccelGroup[] = {GDK_F5, GDK_F9, GDK_F10, GDK_F11};

	const gchar* helpMenuItemNames[] = {"Instructions", "Help", "About"};
	const guint helpMenuAccelGroup[] = {GDK_F3, GDK_F1, GDK_F12};

	vbox = gtk_vbox_new(0, 0);
	menuBar = gtk_menu_bar_new();
	sep = gtk_separator_menu_item_new();
	accelGroup = gtk_accel_group_new();

	gtk_window_add_accel_group(GTK_WINDOW(window), accelGroup);

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

	//execute menu items
	length = sizeof(executeMenuItemNames) / sizeof(*executeMenuItemNames);
	for (i = 0; i < length; i++){
		items = gtk_menu_item_new_with_label(executeMenuItemNames[i]);
		gtk_menu_shell_append(GTK_MENU_SHELL(menu[1]), items);
		gtk_widget_add_accelerator(items, "activate", accelGroup, executeMenuAccelGroup[i], (GdkModifierType)0, GTK_ACCEL_VISIBLE);
		g_signal_connect(items, "activate", G_CALLBACK(menuResponse), (gpointer) window);
	}

	//help menu items
	length = sizeof(helpMenuItemNames) / sizeof(*helpMenuItemNames);
	for (i = 0; i < length; i++){
		items = gtk_menu_item_new_with_label(helpMenuItemNames[i]);
		gtk_menu_shell_append(GTK_MENU_SHELL(menu[2]), items);
		gtk_widget_add_accelerator(items, "activate", accelGroup, helpMenuAccelGroup[i], (GdkModifierType)0, GTK_ACCEL_VISIBLE);
		g_signal_connect(items, "activate", G_CALLBACK(menuResponse), (gpointer) window);
	}

	gtk_box_pack_start(GTK_BOX(vbox), menuBar, 0,0,0);
	return vbox;
}

GtkWidget* drawToolbar(GtkWidget* window){
	GtkWidget *toolbar, *icon, *hbox;

	toolbar = gtk_toolbar_new();
	gtk_container_set_border_width(GTK_CONTAINER(toolbar), 5);
    gtk_toolbar_set_style(GTK_TOOLBAR ( toolbar ), GTK_TOOLBAR_ICONS);

	icon = gtk_image_new_from_icon_name("gtk-add", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "New", "New", "Private", icon, G_CALLBACK(newFile), NULL);
	icon = gtk_image_new_from_icon_name("gtk-open", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "Open", "Open", "Private", icon, G_CALLBACK(openFile), NULL);
	icon = gtk_image_new_from_icon_name("gtk-save", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "Save", "Save", "Private", icon, G_CALLBACK(saveFile), NULL);
	
	gtk_toolbar_append_space(GTK_TOOLBAR(toolbar));

	icon = gtk_image_new_from_icon_name("gtk-yes", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "Build", "Build", "Private", icon, G_CALLBACK(buildMenu), NULL);
	icon = gtk_image_new_from_icon_name("gtk-media-play", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "Run", "Run", "Private", icon, G_CALLBACK(runMenu), NULL);
	icon = gtk_image_new_from_icon_name("gtk-goto-last", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "SS", "Single Step", "Private", icon, G_CALLBACK(singleStepMenu), NULL);
	icon = gtk_image_new_from_icon_name("gtk-convert", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "Convert", "Convert Code", "Private", icon, G_CALLBACK(convertMenu), NULL);
	
	gtk_toolbar_append_space(GTK_TOOLBAR(toolbar));

	icon = gtk_image_new_from_icon_name(GTK_STOCK_INFO, GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "Ins", "Instructions", "Private", icon, G_CALLBACK(instructionDialog), NULL);
	icon = gtk_image_new_from_icon_name("gtk-help", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "Help", "Help", "Private", icon, G_CALLBACK(helpDialog), NULL);
	icon = gtk_image_new_from_icon_name("gtk-about", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "About", "About", "Private", icon, G_CALLBACK(aboutDialog), NULL);
	
	gtk_toolbar_append_space(GTK_TOOLBAR(toolbar));

	icon = gtk_image_new_from_icon_name("gtk-preferences", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "Setting", "Setting", "Private", icon, G_CALLBACK(preferencesMenu), NULL);
	
	gtk_toolbar_append_space(GTK_TOOLBAR(toolbar));

	icon = gtk_image_new_from_icon_name("gtk-close", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "Quit", "Quit", "Private", icon, G_CALLBACK(gtk_main_quit), NULL);
	
	hbox = gtk_hbox_new(0,0);
	gtk_box_pack_start(GTK_BOX(hbox), toolbar, 0,0,0);

	return hbox;
}

GtkWidget* getMicroprocessor(GtkWidget* window){
	int i, j;
	GtkWidget *micro, *hbox, *vbox, *frame, *table, *align, *label, *entry;
	micro = gtk_hbox_new(0, 0);
	hbox = gtk_hbox_new(0, 0);
	vbox = gtk_vbox_new(0, 0);
	entry = gtk_entry_new();
	textAreaYourCode = gtk_text_view_new();
	textAreaConvertedCode = gtk_text_view_new();
}