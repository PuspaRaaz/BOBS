#ifndef _TEXTAREA_H_
#define _TEXTAREA_H_

static void clear(GtkWidget* button, GtkTextView* textView){
	GtkTextBuffer* textBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
	gtk_text_buffer_set_text(textBuffer, "", 0);
}

GtkWidget* drawTextarea(GtkWidget* window){
	GtkWidget* hbox = gtk_hbox_new(0,0);
	GtkWidget* editableBox = gtk_vbox_new(0,0); //box to hold edit area
	GtkWidget* frame = gtk_frame_new(" Your Code...\t");
	GtkWidget* textArea = gtk_text_view_new(); //the gtk textarea
	GtkTextBuffer* textBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textArea));
    GtkWidget* scrolledwindow = gtk_scrolled_window_new(NULL,NULL);
    gtk_widget_set_size_request(scrolledwindow, 250,300);

    gtk_container_add(GTK_CONTAINER(scrolledwindow), textArea); //set the textarea within scrolled window
	gtk_box_pack_start(GTK_BOX(editableBox), scrolledwindow, 1, 1, 3);

    GtkWidget* clipboardBox = gtk_hbox_new(0,0); //box to hold clipboard action buttons
    GtkWidget* button = gtk_button_new_with_label("Cut");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(cutMenu), (gpointer) textArea);
    gtk_box_pack_start(GTK_BOX(clipboardBox), button, 0,0,0); //cut (ctrl+x)

    button = gtk_button_new_with_label("Copy");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(copyMenu), (gpointer) textArea);
    gtk_box_pack_start(GTK_BOX(clipboardBox), button, 0,0,0); //copy (ctrl+c)

	gtk_box_pack_start(GTK_BOX(editableBox), clipboardBox, 0,0,0);
	gtk_container_add(GTK_CONTAINER(frame), editableBox);
	gtk_box_pack_start(GTK_BOX(hbox), frame, 0, 0, 1);

	editableBox = gtk_vbox_new(0,0); //box to hold edit area
	frame = gtk_frame_new("\tConverted Code... ");
	gtk_frame_set_label_align(GTK_FRAME(frame), 1.0, 0.5);
	textArea = gtk_text_view_new(); //the gtk textarea
	textBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textArea));
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textArea), FALSE); //this is to display changed view of the input (opcode) ? mnemonics : opcode
    scrolledwindow = gtk_scrolled_window_new(NULL,NULL);
    gtk_widget_set_size_request(scrolledwindow, 250,300);

    gtk_container_add(GTK_CONTAINER(scrolledwindow), textArea); //set the textarea within scrolled window
	gtk_box_pack_start(GTK_BOX(editableBox), scrolledwindow, 1, 1, 3);

    clipboardBox = gtk_hbox_new(0,0); //box to hold clipboard action buttons
    button = gtk_button_new_with_label("Clear");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(clear), (gpointer) textArea);
    gtk_box_pack_end(GTK_BOX(clipboardBox), button, 0,0,0); //cut (ctrl+x)

    button = gtk_button_new_with_label("Paste");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(pasteMenu), (gpointer) textArea);
    gtk_box_pack_end(GTK_BOX(clipboardBox), button, 0,0,0); //copy (ctrl+c)

	gtk_box_pack_start(GTK_BOX(editableBox), clipboardBox, 0,0,0);
	gtk_container_add(GTK_CONTAINER(frame), editableBox);

	gtk_box_pack_start(GTK_BOX(hbox), frame, 0, 0, 1);

	return hbox;
}

#endif
