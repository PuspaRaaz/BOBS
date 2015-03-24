#include "menuActions.h"

void aboutDialog(GtkWidget* button, gpointer window){
    GtkWidget* dialog, *label, *image, *vbox;
    vbox = gtk_vbox_new(0,0);

    dialog = gtk_dialog_new_with_buttons("About", GTK_WINDOW(window), GTK_DIALOG_MODAL, NULL);
    gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);

    image = gtk_image_new_from_stock(GTK_STOCK_INFO, GTK_ICON_SIZE_DIALOG);
    gtk_box_pack_start(GTK_BOX(vbox), image, 0, 0, 0);

    label = gtk_label_new("BOBS' Simulator");
    gtk_box_pack_start(GTK_BOX(vbox), label, 0, 0, 0);

    GtkWidget* sep = gtk_separator_menu_item_new();
    gtk_box_pack_start(GTK_BOX(vbox), sep, 0, 0, 0);

    label = gtk_label_new("\nBOBS' Simulator is a completely GUI implemented and\nfully functioning simulator for 8085 microprocessor\nprogramming with both opcode and instruction mode\ninput, conversion of codes from one mode to another,\nattached 8255 PPI and hardware interrupts.\n");
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(vbox), label, 0, 0, 0);
    
    label = gtk_label_new("\nDevelopers");
    gtk_box_pack_start(GTK_BOX(vbox), label, 0, 0, 0);

    sep = gtk_separator_menu_item_new();
    gtk_box_pack_start(GTK_BOX(vbox), sep, 0, 0, 0);
    
    label = gtk_label_new("\nPrabesh Pathak, Pramod Maharjan");
    gtk_box_pack_start(GTK_BOX(vbox), label, 0, 0, 0);
    
    label = gtk_label_new("Prasanna Koirala, Pusparaj Bhattarai\n");
    gtk_box_pack_start(GTK_BOX(vbox), label, 0, 0, 0);
    
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), vbox, 0, 0, 0);

    gtk_widget_show_all(dialog);
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void buildMenu(GtkWidget* button, gpointer window){
    if (nofile()) return;
    saveFile(button, window);
    if(!sourceFile.saved) return;
    microMain();
    if (!haltFound) return;
    built = 1;
    displayErrorMessage("Program successfully built.", start_of_code+PC);
}

void convertMenu(GtkWidget* button, gpointer window){
    buildMenu(button, window);
    if (nofile() || !haltFound) return;
    displayConverted();
}
void getOpcode(GtkWidget* button, gpointer window){
    const size_t total_size = 0x1000;
    const size_t line_size = 0x50;
    char* opcode = malloc(total_size);
    char* cline = malloc(line_size);
    char* opcodeOutputFileName;
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

    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new("Save Opcode", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_SAVE, GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
    gtk_widget_show_all(dialog);
    gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER(dialog), TRUE);
    gint resp = gtk_dialog_run(GTK_DIALOG(dialog));
    if(resp == GTK_RESPONSE_OK){
        opcodeOutputFileName = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        FILE* ifile = fopen(opcodeOutputFileName,"w");
        fprintf(ifile, "%s\n", opcode);
        fclose(ifile);
        displayErrorMessage("Opcode file generated", 0);
    }
    gtk_widget_destroy(dialog);

    fclose(ofile);
    free(opcode);
    free(cline);
}

void helpDialog(GtkWidget* button, gpointer window){
    GtkWidget* dialog, *label, *image, *vbox;
    vbox = gtk_vbox_new(0,0);

    dialog = gtk_dialog_new_with_buttons("Help", GTK_WINDOW(window), GTK_DIALOG_MODAL, NULL);
    gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);

    image = gtk_image_new_from_stock(GTK_STOCK_INFO, GTK_ICON_SIZE_DIALOG);
    gtk_box_pack_start(GTK_BOX(vbox), image, 0, 0, 0);

    label = gtk_label_new("BOBS' Simulator");
    gtk_box_pack_start(GTK_BOX(vbox), label, 0, 0, 0);

    GtkWidget* sep = gtk_separator_menu_item_new();
    gtk_box_pack_start(GTK_BOX(vbox), sep, 0, 0, 0);

    label = gtk_label_new("\n \n");
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(vbox), label, 0, 0, 0);
    
    label = gtk_label_new("\nDevelopers");
    gtk_box_pack_start(GTK_BOX(vbox), label, 0, 0, 0);

    sep = gtk_separator_menu_item_new();
    gtk_box_pack_start(GTK_BOX(vbox), sep, 0, 0, 0);
    
    label = gtk_label_new("\nPrabesh Pathak, Pramod Maharjan");
    gtk_box_pack_start(GTK_BOX(vbox), label, 0, 0, 0);
    
    label = gtk_label_new("Prasanna Koirala, Pusparaj Bhattarai\n");
    gtk_box_pack_start(GTK_BOX(vbox), label, 0, 0, 0);
    
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), vbox, 0, 0, 0);

    gtk_widget_show_all(dialog);
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void newFile(){
    sourceFile.filename = "Untitled.txt";
    sourceFile.saved = 0;
    displayErrorMessage("New file created.", 0);
    gtk_notebook_prev_page (GTK_NOTEBOOK(notebook));
}

void openFile(GtkWidget* button, gpointer window){
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new("Choose a file", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
    gtk_widget_show_all(dialog);
    gint resp = gtk_dialog_run(GTK_DIALOG(dialog));
    if(resp == GTK_RESPONSE_OK){
        sourceFile.filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        displaySource(sourceFile.filename);
        sourceFile.saved = 1;
        displayErrorMessage("File opened successful.", start_of_code+PC);
        gtk_notebook_prev_page (GTK_NOTEBOOK(notebook));
    }
    gtk_widget_destroy(dialog);    
}

void runMenu(GtkWidget* button, gpointer window){
    buildMenu(button, window);
    if(nofile() || !haltFound) return;
    while(!hasHalted){
        singleStepMenu(button, window);
    }
    refresh();
    built = 0;
    displayErrorMessage("Program successfully executed.", start_of_code+PC);
}

void saveAsFile(GtkWidget* button, gpointer window){
    sourceFile.saved = 0;
    saveFile(button, window);
}

void saveFile(GtkWidget* button, gpointer window){
    if (nofile()) return;
    char* code = getCodedText();
    if (sourceFile.saved){
        FILE* ifile = fopen(sourceFile.filename,"w");
        fprintf(ifile, "%s\n", code);
        fclose(ifile);
        displayErrorMessage("File saved successful.", start_of_code+PC);
    }else{
        GtkWidget *dialog;
        dialog = gtk_file_chooser_dialog_new("Save file", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_SAVE, GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
        gtk_widget_show_all(dialog);
        gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER(dialog), TRUE);
        gint resp = gtk_dialog_run(GTK_DIALOG(dialog));
        if(resp == GTK_RESPONSE_OK){
            sourceFile.filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
            FILE* ifile = fopen(sourceFile.filename,"w");
            fprintf(ifile, "%s\n", code);
            fclose(ifile);
            sourceFile.saved = 1;
            displayErrorMessage("File saved successful.", start_of_code+PC);
        }
        gtk_widget_destroy(dialog);
    }
}

void singleStepMenu(GtkWidget* button, gpointer window){
    if (nofile()) return;
    if (!built) buildMenu(button, window);
    if (!haltFound) return;
    SingleStep();
    refresh();
    if (hasHalted) return;
}
