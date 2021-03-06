#include "gui.h"

char* getCodedText(){
    GtkTextIter start, end;
	GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(textAreaYourCode));
	gchar *text;
	gtk_text_buffer_get_bounds (buffer, &start, &end);
	text = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);
	return text;
}

int nofile(){
    if(!sourceFile.saved && sourceFile.filename == NULL){
        displayErrorMessage("No file selected.", 0);
    	return TRUE;
    }
    return FALSE;
}

void clearConvertedCode(){
	GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(textAreaConvertedCode));
	gtk_text_buffer_set_text(buffer, "", 0);
}

void displayConverted(){
	if (nofile()) return;
	displaySource(sourceFile.filename);
	displayOutput();
    gtk_notebook_next_page (GTK_NOTEBOOK(notebook));
    refresh();
    displayErrorMessage("Mnemonics converted to opcode.", start_of_code+PC);
}

void displayErrorMessage(char* message, int pos){
	char position[200];
	sprintf(position, "%X :\t", pos);
	strcat(position, message);
	GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(errorArea));
    gtk_text_buffer_set_text(buffer, position, -1);
}
void displayFlag(){
	int flag[] = {getsign(), getzero(), getAF(), getparity(), getcarry()};
	int i;
	for (i = 0; i < 5; i++){
		char value[2];
		sprintf(value, "%d", flag[i]);
		gtk_entry_set_text(GTK_ENTRY(flagEntry[i]), value);
	}
}
void displayIOPort(){
	int outputValue[] = {mPort.pa.val, mPort.pb.val, mPort.pc.val};
	int i; char binaryOutputValue[8];
	for (i = 0; i < 3; i++){
		toBinary(outputValue[i], binaryOutputValue);
		gtk_entry_set_text(GTK_ENTRY(ioPortEntry[i]), binaryOutputValue);
	}
}
void displayOutput(){
    const size_t total_size = 0x1000;
    const size_t line_size = 0x50;
    char* opcode = malloc(total_size);
    char* cline = malloc(line_size);
    strcpy(opcode, " ");
    FILE* ofile = fopen(OUTPUTFILENAME,"r");
    if (!ofile){
        displayErrorMessage("File could not be located", 0);
        return;
    }
    while (fgets(cline, line_size, ofile) != NULL){
        strcat(opcode,cline);
        strcat(opcode," ");
    }

    GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textAreaConvertedCode));
    gtk_text_buffer_set_text(buffer, opcode, -1);
    fclose(ofile);
    free(opcode);
    free(cline);
}
void displayPPIPort(){
	int outputValue[] = {pPort.pa.val, pPort.pb.val, pPort.pc.val};
	int i; char binaryOutputValue[8];
	for (i = 0; i < 3; i++){
		toBinary(outputValue[i], binaryOutputValue);
		gtk_entry_set_text(GTK_ENTRY(ppiEntry[i]), binaryOutputValue);
	}
}
void displayRegister(){
	int registerIntValue[] = {A, B, C, D, E, H, L, PC+STARTOFCODE, SP};
	int i;
	for (i = 0; i < 9; i++){
		char value[2];
		sprintf(value, "%X", registerIntValue[i]);
		gtk_entry_set_text(GTK_ENTRY(registerEntry[i]), value);
	}
}
void displaySource(char* filename){
	if(nofile()){
	    GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textAreaYourCode));
	    gtk_text_buffer_set_text(buffer, "", 0);
	    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textAreaConvertedCode));
	    gtk_text_buffer_set_text(buffer, "", 0);
	    gtk_notebook_prev_page (GTK_NOTEBOOK(notebook));
	    return;
	}
    const size_t total_size = 0x1000;
    const size_t line_size = 0x50;
    char* mnemonics = malloc(total_size);
    char* cline = malloc(line_size);
    strcpy(mnemonics, " ");
    FILE* mfile = fopen(filename,"r");

    if (!mfile){
        displayErrorMessage("File could not be located", 0);
        return;
    }
    while (fgets(cline, line_size, mfile) != NULL){
        strcat(mnemonics,cline);
        strcat(mnemonics," ");
    }

    GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textAreaYourCode));
    gtk_text_buffer_set_text(buffer, mnemonics, -1);
    fclose(mfile);
    free(mnemonics);
    free(cline);
}
void nextMemory(){
	setMemory();
	int memAddress, memoryValueInt;
	char memoryValue[5], memoryAddress[4];

	GtkEntryBuffer *buffer = gtk_entry_get_buffer (GTK_ENTRY(memLocation));
	const char* memoryAddressConst = gtk_entry_buffer_get_text (buffer);

    memAddress = (int) strtol(memoryAddressConst, NULL, 16);

    if (memAddress >= 0x8000 && memAddress < STARTOFCODE+MAX_OP_LEN-1) memAddress++;
    else memAddress = STARTOFCODE;

    memoryValueInt = Op[memAddress - STARTOFCODE].value;

    sprintf(memoryAddress, "%X", memAddress);
    sprintf(memoryValue, "%X", memoryValueInt);

    gtk_entry_set_text (GTK_ENTRY (memLocation), memoryAddress);
    gtk_entry_set_text (GTK_ENTRY (memValue), memoryValue);
}
void previousMemory(){
	int memAddress, memoryValueInt;
	char memoryValue[5], memoryAddress[4];

	GtkEntryBuffer *buffer = gtk_entry_get_buffer (GTK_ENTRY(memLocation));
	const char* memoryAddressConst = gtk_entry_buffer_get_text (buffer);

    memAddress = (int) strtol(memoryAddressConst, NULL, 16);

    if (memAddress > 0x8000 && memAddress < STARTOFCODE+MAX_OP_LEN) memAddress--;
    else memAddress = STARTOFCODE;

    memoryValueInt = Op[memAddress - STARTOFCODE].value;

    sprintf(memoryAddress, "%X", memAddress);
    sprintf(memoryValue, "%X", memoryValueInt);

    gtk_entry_set_text (GTK_ENTRY (memLocation), memoryAddress);
    gtk_entry_set_text (GTK_ENTRY (memValue), memoryValue);
}
void refresh(){
    displayFlag();
    displayRegister();
    displayIOPort();
    displayPPIPort();

	char memoryValue[4];
    int memoryValueInt = Op[0].value;
    sprintf(memoryValue, "%X", memoryValueInt);
    gtk_entry_set_text (GTK_ENTRY (memLocation), "8000");
    gtk_entry_set_text (GTK_ENTRY (memValue), memoryValue);
}
void setMemory(){
	char memoryAddress[4], memoryValue[4];

	GtkEntryBuffer *buffer = gtk_entry_get_buffer (GTK_ENTRY(memLocation));
	const char* memoryAddressConst = gtk_entry_buffer_get_text (buffer);

	buffer = gtk_entry_get_buffer (GTK_ENTRY(memValue));
	const char* memoryValueConst = gtk_entry_buffer_get_text (buffer);

    int memAddressInt = (int) strtol(memoryAddressConst, NULL, 16);
    int memValueInt = (int) strtol(memoryValueConst, NULL, 16);
    sprintf(memoryAddress, "%X", memAddressInt);
    sprintf(memoryValue, "%X", memValueInt);

    Op[memAddressInt - STARTOFCODE].value = memValueInt;

    gtk_entry_set_text (GTK_ENTRY (memLocation), memoryAddress);
    gtk_entry_set_text (GTK_ENTRY (memValue), memoryValue);
}
void stroneOne(){	pPort.strA = 1;	}
void strobeTwo(){	pPort.strB = 1;	}
void toBinary(int value, char* output)
{
    int i;
    output[8] = '\0';
    for (i = 7; i >= 0; --i, value >>= 1){
        output[i] = (value & 1) + '0';
    }
}
void viewMemory(){
	int memAddress, memoryValueInt;
	char memoryValue[5], memoryAddress[4];

	GtkEntryBuffer *buffer = gtk_entry_get_buffer (GTK_ENTRY(memLocation));
	const char* memoryAddressConst = gtk_entry_buffer_get_text (buffer);

    memAddress = (int) strtol(memoryAddressConst, NULL, 16);

    if (memAddress < 0x8000 && memAddress >= STARTOFCODE+MAX_OP_LEN) memAddress = STARTOFCODE;

    memoryValueInt = Op[memAddress - STARTOFCODE].value;

    sprintf(memoryAddress, "%X", memAddress);
    sprintf(memoryValue, "%X", memoryValueInt);

    gtk_entry_set_text (GTK_ENTRY (memLocation), memoryAddress);
    gtk_entry_set_text (GTK_ENTRY (memValue), memoryValue);
}
void menuResponse(GtkWidget *menuItems, gpointer data){
	const char* items = gtk_menu_item_get_label(GTK_MENU_ITEM(menuItems));

	if ( strcmp ( items, "About"	) == 0 )	{	aboutDialog(menuItems, data);		}
	if ( strcmp ( items, "Build"	) == 0 )	{	buildMenu(menuItems, data);			}
	if ( strcmp ( items, "Convert"	) == 0 )	{	convertMenu(menuItems, data);		}
	if ( strcmp ( items, "Get Opcode") == 0)	{	getOpcode(menuItems, data);			}
	if ( strcmp ( items, "Help"		) == 0 )	{	helpDialog(menuItems, data);		}
	if ( strcmp ( items, "New"		) == 0 )	{	newFile(menuItems, data);			}
	if ( strcmp ( items, "Open"		) == 0 )	{	openFile(menuItems, data);			}
	if ( strcmp ( items, "Quit"		) == 0 )	{	gtk_main_quit();					}
	if ( strcmp ( items, "Run"		) == 0 )	{	runMenu(menuItems, data);			}
	if ( strcmp ( items, "Save As"	) == 0 )	{	saveAsFile(menuItems, data);		}
	if ( strcmp ( items, "Save"		) == 0 )	{	saveFile(menuItems, data);			}
	if ( strcmp ( items, "Single Step" ) == 0 )	{	singleStepMenu(menuItems, data);	}
}

GtkWidget* drawMenuItems(GtkWidget* window){
	int i, j;
	GtkWidget *menuBar, *vbox, *sep, *items;
	GtkAccelGroup *accelGroup;

	GtkWidget* menu[4];
	for (i = 0; i < 4; i++) menu[i] = gtk_menu_new();

	const gchar* menuName[] = {"_File", "E_xecute", "_Help"};

	const gchar* fileMenuItemNames[] = {"New", "Open", "Save", "Save As", "Get Opcode", "Quit"};
	const guint fileMenuAccelGroup[] = {GDK_n, GDK_o, GDK_s, GDK_d, GDK_g, GDK_q};

	const gchar* executeMenuItemNames[] = {"Build", "Run", "Single Step", "Convert"};
	const guint executeMenuAccelGroup[] = {GDK_F5, GDK_F9, GDK_F10, GDK_F11};

	const gchar* helpMenuItemNames[] = {"Help", "About"};
	const guint helpMenuAccelGroup[] = {GDK_F1, GDK_F12};

	vbox = gtk_vbox_new(0, 0);
	menuBar = gtk_menu_bar_new();
	sep = gtk_separator_menu_item_new();
	accelGroup = gtk_accel_group_new();

	textAreaConvertedCode = gtk_text_view_new();
	textAreaYourCode = gtk_text_view_new();
	errorArea = gtk_text_view_new();
	notebook = gtk_notebook_new();

	gtk_window_add_accel_group(GTK_WINDOW(window), accelGroup);

	int length = sizeof(menuName) / sizeof(*menuName);
	for(i = 0; i < length; i++){
		items = gtk_menu_item_new_with_mnemonic(menuName[i]);
		gtk_menu_item_set_submenu(GTK_MENU_ITEM(items), menu[i]);
		gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), items);
	}

// file menu items
	length = sizeof(fileMenuItemNames) / sizeof(*fileMenuItemNames);
	for (i = 0; i < length; i++){
		items = gtk_menu_item_new_with_label(fileMenuItemNames[i]);
		gtk_menu_shell_append(GTK_MENU_SHELL(menu[0]), items);
		gtk_widget_add_accelerator(items, "activate", accelGroup, fileMenuAccelGroup[i], GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
		g_signal_connect(items, "activate", G_CALLBACK(menuResponse), (gpointer) window);
	}

// execute menu items
	length = sizeof(executeMenuItemNames) / sizeof(*executeMenuItemNames);
	for (i = 0; i < length; i++){
		items = gtk_menu_item_new_with_label(executeMenuItemNames[i]);
		gtk_menu_shell_append(GTK_MENU_SHELL(menu[1]), items);
		gtk_widget_add_accelerator(items, "activate", accelGroup, executeMenuAccelGroup[i], (GdkModifierType)0, GTK_ACCEL_VISIBLE);
		g_signal_connect(items, "activate", G_CALLBACK(menuResponse), (gpointer) window);
	}

// help menu items
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

	gtk_toolbar_append_space(GTK_TOOLBAR(toolbar));

	icon = gtk_image_new_from_icon_name("gtk-add", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "New", "New", "Private", icon, G_CALLBACK(newFile), NULL);
	icon = gtk_image_new_from_icon_name("gtk-open", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "Open", "Open", "Private", icon, G_CALLBACK(openFile), NULL);
	icon = gtk_image_new_from_icon_name("gtk-save", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "Save", "Save", "Private", icon, G_CALLBACK(saveFile), NULL);

	gtk_toolbar_append_space(GTK_TOOLBAR(toolbar));

	icon = gtk_image_new_from_icon_name("gtk-media-record", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "Build", "Build", "Private", icon, G_CALLBACK(buildMenu), NULL);
	icon = gtk_image_new_from_icon_name("gtk-yes", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "Run", "Run", "Private", icon, G_CALLBACK(runMenu), NULL);
	icon = gtk_image_new_from_icon_name("gtk-media-pause", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "SS", "Single Step", "Private", icon, G_CALLBACK(singleStepMenu), NULL);
	icon = gtk_image_new_from_icon_name("gtk-convert", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "Convert", "Convert Code", "Private", icon, G_CALLBACK(convertMenu), NULL);

	gtk_toolbar_append_space(GTK_TOOLBAR(toolbar));

	icon = gtk_image_new_from_icon_name("gtk-info", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "Help", "Help", "Private", icon, G_CALLBACK(helpDialog), NULL);
	icon = gtk_image_new_from_icon_name("gtk-about", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "About", "About", "Private", icon, G_CALLBACK(aboutDialog), NULL);

	gtk_toolbar_append_space(GTK_TOOLBAR(toolbar));

	icon = gtk_image_new_from_icon_name("gtk-close", GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_append_item(GTK_TOOLBAR(toolbar), "Quit", "Quit", "Private", icon, G_CALLBACK(gtk_main_quit), NULL);

	gtk_toolbar_append_space(GTK_TOOLBAR(toolbar));

	hbox = gtk_hbox_new(0,0);
	gtk_box_pack_start(GTK_BOX(hbox), toolbar, 0,0,0);

	return hbox;
}

GtkWidget* getError(GtkWidget* window){
	gtk_text_view_set_editable(GTK_TEXT_VIEW(errorArea), FALSE);
    gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW(errorArea), FALSE);

    GtkWidget* scrolledWindow = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(scrolledWindow, 250, 70);
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(errorArea), 15);
    gtk_container_add(GTK_CONTAINER(scrolledWindow), errorArea);
	gtk_text_view_set_pixels_above_lines (GTK_TEXT_VIEW(errorArea), 2);
	gtk_text_view_set_pixels_below_lines (GTK_TEXT_VIEW(errorArea), 2);
    GtkWidget* frame = gtk_frame_new(" Message\t");
    gtk_container_add(GTK_CONTAINER(frame), scrolledWindow);

    return frame;
}

GtkWidget* getMicroprocessor(GtkWidget* window){
	int i, j;
	GtkWidget *micro, *hbox, *vbox, *frame, *table, *align, *label, *entry;
	micro = gtk_hbox_new(0, 0);
	hbox = gtk_hbox_new(0, 0);
	vbox = gtk_vbox_new(0, 0);
	font_desc = pango_font_description_from_string ("Serif 15");

// registers
	gchar* regNames[] = {"A", "BC", "DE", "HL", "PC", "SP"};
	table = gtk_table_new(6, 4, 0);
	for (i = 0; i < 9; i++){
		registerEntry[i] = gtk_entry_new();
		gtk_editable_set_editable(GTK_EDITABLE(registerEntry[i]), FALSE);
		gtk_entry_set_max_length(GTK_ENTRY(registerEntry[i]), 4);
		gtk_widget_set_size_request(registerEntry[i], 25, 25);
	}
	int pos = 0;
	for (i = 0; i < 6; i++){
		label = gtk_label_new(regNames[i]);
		gtk_table_attach(GTK_TABLE(table), label, 0, 1, i, i+1, GTK_FILL, GTK_FILL, 5, 5);
		for (j = 0; j < 2; j++){
			if (i != 1 && i != 2 && i !=3){
				gtk_table_attach(GTK_TABLE(table), registerEntry[pos], 2, 4, i, i+1, GTK_FILL, GTK_FILL, 2, 2);
				pos++;
				j++;
			}else{
				gtk_table_attach(GTK_TABLE(table), registerEntry[pos], j+2, j+3, i, i+1, GTK_FILL, GTK_FILL, 2, 2);
				pos++;
			}
		}
	}
    displayRegister();
	frame = gtk_frame_new(" Registers\t");
	gtk_container_add(GTK_CONTAINER(frame), table);
	gtk_box_pack_start(GTK_BOX(hbox), frame, 1, 0, 5);

// flags
	gchar* flagNames[] = {"S", "Z", "AC", "P", "C"};
	for (i = 0; i < 5; i++){
		flagEntry[i] = gtk_entry_new();
		gtk_editable_set_editable(GTK_EDITABLE(flagEntry[i]), FALSE);
		gtk_entry_set_max_length(GTK_ENTRY(flagEntry[i]), 1);
		gtk_widget_set_size_request(flagEntry[i], 15, 25);
	}
	table = gtk_table_new(5, 2, 1);
	for (i = 0; i < 5; i++){
		label = gtk_label_new(flagNames[i]);
		gtk_table_attach(GTK_TABLE(table), label, 0, 1, i, i+1, GTK_FILL, GTK_FILL, 5, 5);

		gtk_table_attach(GTK_TABLE(table), flagEntry[i], 1, 2, i, i+1, GTK_FILL, GTK_FILL, 2, 2);
	}
    displayFlag();
	frame = gtk_frame_new(" Flags\t");
	gtk_container_add(GTK_CONTAINER(frame), table);
	gtk_box_pack_start(GTK_BOX(hbox), frame, 0, 0, 5);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, 0, 0, 5);

// output ports
	table = gtk_table_new(3, 2, 0);
	for (i = 0; i < 3; i++){
		ioPortEntry[i] = gtk_entry_new();
		gtk_widget_modify_font (ioPortEntry[i], font_desc);
		gtk_editable_set_editable(GTK_EDITABLE(ioPortEntry[i]), FALSE);
		gtk_entry_set_max_length(GTK_ENTRY(ioPortEntry[i]), 8);
		gtk_widget_set_size_request(ioPortEntry[i], 120, 35);
	}
	for (i = 0; i < 3; i++){
		char port[2];
		sprintf(port, "%c :-", 'A' + i);
		label = gtk_label_new(port);
		gtk_table_attach(GTK_TABLE(table), label, 0, 1, i, i+1, GTK_FILL, GTK_FILL, 7, 7);
		gtk_table_attach(GTK_TABLE(table), ioPortEntry[i], 1, 2, i, i+1, GTK_FILL, GTK_FILL, 7, 7);
	}
    displayIOPort();
    frame = gtk_frame_new(" O/P Ports\t");
	gtk_container_add(GTK_CONTAINER(frame), table);
	gtk_box_pack_start(GTK_BOX(vbox), frame, 0, 0, 5);
	gtk_box_pack_start(GTK_BOX(micro), vbox, 0, 0, 5);

// vertical separator line
	gtk_box_pack_start(GTK_BOX(micro), gtk_vseparator_new(), 0, 0, 0);

// codearea
	vbox = gtk_vbox_new(0, 0);
	hbox = gtk_hbox_new(0, 0);
	gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_TOP);
	gtk_box_pack_start(GTK_BOX(micro), notebook, 0, 0, 5);

	GtkWidget* scrolledWindow = gtk_scrolled_window_new(NULL,NULL);
	gtk_text_view_set_pixels_below_lines (GTK_TEXT_VIEW(textAreaYourCode), 2);
	gtk_text_view_set_pixels_above_lines (GTK_TEXT_VIEW(textAreaYourCode), 2);
    gtk_widget_set_size_request(scrolledWindow, 400,500);
	gtk_widget_modify_font (textAreaYourCode, font_desc);
    gtk_container_add(GTK_CONTAINER(scrolledWindow), textAreaYourCode);
	label = gtk_label_new ("Mnemonics");
	gtk_notebook_append_page (GTK_NOTEBOOK (notebook), scrolledWindow, label);

	scrolledWindow = gtk_scrolled_window_new(NULL,NULL);
    gtk_widget_set_size_request(scrolledWindow, 400,500);
	gtk_text_view_set_pixels_above_lines (GTK_TEXT_VIEW(textAreaConvertedCode), 2);
	gtk_text_view_set_pixels_below_lines (GTK_TEXT_VIEW(textAreaConvertedCode), 2);
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(textAreaConvertedCode), 15);
	gtk_widget_modify_font (textAreaConvertedCode, font_desc);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textAreaConvertedCode), FALSE);
    gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW(textAreaConvertedCode), FALSE);
    gtk_container_add(GTK_CONTAINER(scrolledWindow), textAreaConvertedCode);
	label = gtk_label_new ("Opcode");
	gtk_notebook_append_page (GTK_NOTEBOOK (notebook), scrolledWindow, label);

// vertical separator line
	gtk_box_pack_start(GTK_BOX(micro), gtk_vseparator_new(), 0, 0, 0);

// memory access
	hbox = gtk_hbox_new(0, 0);
	GtkWidget* memVbox = gtk_vbox_new(0, 0);
	memLocation = gtk_entry_new();
	gtk_widget_modify_font (memLocation, font_desc);
    gtk_entry_set_text (GTK_ENTRY (memLocation), "8000");
	gtk_entry_set_max_length(GTK_ENTRY(memLocation), 4);
	gtk_widget_set_size_request(memLocation, 65, 40);
	gtk_box_pack_start(GTK_BOX(hbox), memLocation, 1, 1, 5);

	memValue = gtk_entry_new();
	gtk_widget_modify_font (memValue, font_desc);
    int memoryValueInt = Op[0].value;
    char memoryValue[5];
    sprintf(memoryValue, "%X", memoryValueInt);
    gtk_entry_set_text (GTK_ENTRY (memValue), memoryValue);
	gtk_entry_set_max_length(GTK_ENTRY(memValue), 2);
	gtk_widget_set_size_request(memValue, 40, 40);
	gtk_box_pack_start(GTK_BOX(hbox), memValue, 1, 1, 5);
	GtkWidget* button = gtk_button_new_with_label(" Go ");
	gtk_box_pack_start(GTK_BOX(hbox), button, 1, 1, 1);
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(viewMemory), NULL);
	gtk_box_pack_start(GTK_BOX(memVbox), hbox, 1, 1, 1);

	hbox = gtk_hbox_new(0, 0);
	button = gtk_button_new_with_label(" << Prev ");
	gtk_box_pack_start(GTK_BOX(hbox), button, 1, 1, 1);
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(previousMemory), NULL);
	button = gtk_button_new_with_label(" Next >> ");
	gtk_box_pack_start(GTK_BOX(hbox), button, 1, 1, 1);
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(nextMemory), NULL);
	gtk_box_pack_start(GTK_BOX(memVbox), hbox, 0, 0, 1);

	frame = gtk_frame_new(" Memory\t");
	gtk_container_add(GTK_CONTAINER(frame), memVbox);
	gtk_box_pack_start(GTK_BOX(vbox), frame, 0, 0, 1);

// //PPI
	GtkWidget* ppiVBox = gtk_vbox_new(0, 0);
	char* ppiName[] = {" A :-", " B :-", " C :-"};
	for (i = 0; i < 3; i++){
		ppiEntry[i] = gtk_entry_new();
		hbox = gtk_hbox_new(0, 0);
		gtk_widget_modify_font (ppiEntry[i], font_desc);
		gtk_entry_set_max_length(GTK_ENTRY(ppiEntry[i]), 8);
		gtk_widget_set_size_request(ppiEntry[i], 40, 35);
		label = gtk_label_new(ppiName[i]);
		gtk_box_pack_start(GTK_BOX(hbox), label, 0, 0, 10);
		gtk_box_pack_start(GTK_BOX(hbox), ppiEntry[i], 1, 1, 2);
		gtk_box_pack_start(GTK_BOX(ppiVBox), hbox, 0, 0, 3);
	}/*
	hbox = gtk_hbox_new(0, 0);
	button = gtk_button_new_with_label(" Strobe 1 ");
	gtk_box_pack_start(GTK_BOX(hbox), button, 1, 1, 1);
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(stroneOne), NULL);
	button = gtk_button_new_with_label(" Strobe 2 ");
	gtk_box_pack_start(GTK_BOX(hbox), button, 1, 1, 1);
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(strobeTwo), NULL);
	gtk_box_pack_start(GTK_BOX(ppiVBox), hbox, 0, 0, 3);*/

	frame = gtk_frame_new(" 8255 PPI\t");
	gtk_container_add(GTK_CONTAINER(frame), ppiVBox);
	gtk_box_pack_start(GTK_BOX(vbox), frame, 0, 0, 10);


	gtk_box_pack_start(GTK_BOX(micro), vbox, 0, 0, 5);
	pango_font_description_free (font_desc);

	newFile();

	return micro;
}

/*
GdkPixbuf *createPixbuf(const gchar* filename){
	GError *error = NULL;
	GdkPixbuf* pixbuf = gdk_pixbuf_new_from_file(filename, &error);
	if(!pixbuf){
		fprintf(stderr, "%s\n", error->message);
		g_error_free(error);
	}
	return pixbuf;
}
*/
