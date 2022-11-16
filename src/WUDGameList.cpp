#include <adwaita.h>
#include <cstdlib>
#include <gtk/gtk.h>
#include <gtkmm.h>
#include <iostream>

#include <WUDGameList.h>
#include <WUDTitle.h>
#include <downloader.h>
#include <gtitles.h>

GameList::GameList(
        GtkApplication *app,
        Glib::RefPtr<Gtk::Builder> builder,
        const TitleEntry *titleEntries) {

    this->app = app;
    this->builder = builder;
    this->titleEntries = titleEntries;

    this->setupWindow();
}

GameList::~GameList() {
}

void GameList::setupWindow() {
    mainWindow = GTK_WIDGET(gtk_builder_get_object(builder->gobj(), "mainWindow"));

    auto headerbar = gtk_builder_get_object(builder->gobj(), "main_headerbar");
    auto category_box = gtk_builder_get_object(builder->gobj(), "categoryBox");

    adw_header_bar_pack_start(ADW_HEADER_BAR(headerbar), GTK_WIDGET(category_box));

    gtk_application_add_window(app, GTK_WINDOW(mainWindow));
    gtk_widget_show(mainWindow);


    /*
    this->setupColumns();

    // Show window

    // Setup games button
    gamesButton = builder->get_widget<Gtk::ToggleButton>("gamesButton");
    gamesButton->set_active();
    gamesButton->set_group(*gamesButton);
    gamesButton->signal_toggled().connect(
            sigc::bind(sigc::mem_fun(*this, &GameList::on_button_selected), TITLE_CATEGORY_GAME));

    // Setup updates button
    updatesButton = builder->get_widget<Gtk::ToggleButton>("updatesButton");
    updatesButton->signal_toggled().connect(
            sigc::bind(sigc::mem_fun(*this, &GameList::on_button_selected), TITLE_CATEGORY_UPDATE));

    // Setup DLC button
    dlcsButton = builder->get_widget<Gtk::ToggleButton>("dlcsButton");
    dlcsButton->signal_toggled().connect(
            sigc::bind(sigc::mem_fun(*this, &GameList::on_button_selected), TITLE_CATEGORY_DLC));


    // Setup Demo Button
    demosButton = builder->get_widget<Gtk::ToggleButton>("demoButton");
    demosButton->signal_toggled().connect(
            sigc::bind(sigc::mem_fun(*this, &GameList::on_button_selected), TITLE_CATEGORY_DEMO));

    allButton = builder->get_widget<Gtk::ToggleButton>("allButton");
    allButton->signal_toggled().connect(
            sigc::bind(sigc::mem_fun(*this, &GameList::on_button_selected), TITLE_CATEGORY_ALL));

    // Setup Queue Add Button
    addToQueueButton = builder->get_widget<Gtk::Button>("addToQueueButton");
    addToQueueButton->signal_clicked().connect(sigc::mem_fun(*this, &GameList::on_add_to_queue));

    // Setup Download Button
    downloadQueueButton = builder->get_widget<Gtk::Button>("downloadQueueButton");
    downloadQueueButton->signal_clicked().connect(sigc::mem_fun(*this, &GameList::on_download_queue));

    //- Region Buttons -//
    // Setup Japan Button
    japanButton = builder->get_widget<Gtk::CheckButton>("japanButton");
    japanButton->signal_toggled().connect(
            sigc::bind(sigc::mem_fun(*this, &GameList::on_region_selected), japanButton, MCP_REGION_JAPAN));

    // Setup USA Button
    usaButton = builder->get_widget<Gtk::CheckButton>("usaButton");
    usaButton->signal_toggled().connect(
            sigc::bind(sigc::mem_fun(*this, &GameList::on_region_selected), usaButton, MCP_REGION_USA));

    // Setup Europe Button
    europeButton = builder->get_widget<Gtk::CheckButton>("europeButton");
    europeButton->signal_toggled().connect(
            sigc::bind(sigc::mem_fun(*this, &GameList::on_region_selected), europeButton, MCP_REGION_EUROPE));

    // Setup Decrypt Contents Toggle
    decryptContentsButton = builder->get_widget<Gtk::CheckButton>("decryptContentsButton");
    decryptContentsButton->signal_toggled().connect(
            sigc::bind(sigc::mem_fun(*this, &GameList::on_decrypt_selected), decryptContentsButton));
    decryptContentsButton->set_active();

    // Setup View
    columnView = builder->get_widget<Gtk::ColumnView>("columnView");

    columnView->signal_activate().connect(
            sigc::mem_fun(*this, &GameList::on_gamelist_row_activated));

    columnView->get_model()->signal_selection_changed().connect(
            sigc::mem_fun(*this, &GameList::on_selection_changed));

    // Initial Title list sorting
    updateTitles(currentCategory, selectedRegion);

    //    Gtk::CellRendererToggle *renderer = Gtk::manage(new Gtk::CellRendererToggle());

    //  columnView->append_column("Queue", *renderer);

    //   Gtk::ListStore *columns = columnView->get_columns();

    columns->add_attribute(*renderer, "active", columns.toQueue);

    columnView->append_column("TitleID", columns.titleId);
    columnView->get_column(1)->set_sort_column(columns.titleId);

    columnView->append_column("Kind", columns.kind);

    columnView->append_column("Region", columns.region);

    columnView->append_column("Name", columns.name);
    columnView->get_column(4)->set_sort_column(columns.name);
    

    // Search for name
    columnView->set_search_column(5);

    // Sort by name by default
    columnModel->set_sort_column(GTK_TREE_SORTABLE_UNSORTED_SORT_COLUMN_ID, Gtk::SortType::SORT_ASCENDING);
    columnModel->set_sort_column(5, Gtk::SortType::SORT_ASCENDING);

    columnView->set_search_equal_func(sigc::mem_fun(*this, &GameList::on_search_equal));
     */
}

void GameList::updateTitles(TITLE_CATEGORY title_category, MCPRegion region) {
    /*     // Create empty titles model
    auto titlesList = Gio::ListStore<Title>::create();
    auto titlesModel = Gtk::MultiSelection::create();

    titlesModel->set_model(titlesList);
    // Set empty model
    columnView->set_model(titlesModel);

    // Append titles to model
    for (unsigned int i = 0; i < getTitleEntriesSize(title_category); i++) {
        if (!(region & titleEntries[i].region))
            continue;

        // Setup Title ID
        char id[128];
        hex(titleEntries[i].tid, 16, id);

        titlesList->append(Glib::make_refptr_for_instance(new Title(i)));

        // Check if queued
        // row[1] = queueVector.empty() ? false : std::binary_search(queueVector.begin(), queueVector.end(), titleEntries[i].tid);

        // Title ID
        // row[2] = Glib::ustring::format(id);

        // Type
        // row[3] = Glib::ustring::format(getFormattedKind(titleEntries[i].tid));

        // Region
        // row[4] = Glib::ustring::format(getFormattedRegion((MCPRegion) titleEntries[i].region));

        // Name
        // row[5] = titleEntries[i].name;
    } */
}


void GameList::setupColumns() {
    /*     columnView->append_column(
            Gtk::ColumnViewColumn::create("Queued"));

    columnView->append_column(
            Gtk::ColumnViewColumn::create("Title ID"));

    columnView->append_column(
            Gtk::ColumnViewColumn::create("Kind"));

    columnView->append_column(
            Gtk::ColumnViewColumn::create("Region"));

    columnView->append_column(
            Gtk::ColumnViewColumn::create("Index")); */
}

void GameList::on_decrypt_selected(Gtk::ToggleButton *button) {
    /*     decryptContents = !decryptContents;
    return; */
}

void GameList::on_download_queue(Gdk::Event *ev) {
    /*     if (queueVector.empty())
        return;

    mainWindow->set_sensitive(false);

    for (auto queuedItem: queueVector) {
        char tid[128];
        sprintf(tid, "%016lx", queuedItem);
        download_title(tid, decryptContents);
    }

    queueVector.clear();
    mainWindow->set_sensitive(true); */
}

void GameList::on_selection_changed() {
    /*     Glib::RefPtr <Gtk::SelectionModel> selection = columnView->get_model();
    //    Gtk::TreeModel::Row row = *selection->get_selection();
 */
    /*if (row) {
        if (row[columns.toQueue] == true) {
            addToQueueButton->set_label("Remove from queue");
        } else {
            addToQueueButton->set_label("Add to queue");
        }
    }*/
}

void GameList::on_add_to_queue(Gdk::Event *ev) {
    /*     Glib::RefPtr <Gtk::SelectionModel> selection = columnView->get_model(); */
    // Gtk::TreeModel::Row row = *selection->get_selection();

    /*if (row) {
        row[columns.toQueue] = !row[columns.toQueue];
        if (row[columns.toQueue]) {
            queueVector.push_back(titleEntries[row[columns.index]].tid);
            addToQueueButton->set_label("Remove from queue");
        } else {
            queueVector.erase(std::remove(queueVector.begin(), queueVector.end(), titleEntries[row[columns.index]].tid), queueVector.end());
            addToQueueButton->set_label("Add to queue");
        }
    }*/
}

void GameList::on_button_selected(Gdk::Event *ev, TITLE_CATEGORY title_category) {
    /*     currentCategory = title_category;
    titleEntries = getTitleEntries(currentCategory);
    updateTitles(currentCategory, selectedRegion);
    return; */
}

void GameList::on_region_selected(Gtk::ToggleButton *button, MCPRegion reg) {
    /*     if (button->get_active())
        selectedRegion = (MCPRegion)(selectedRegion | reg);
    else
        selectedRegion = (MCPRegion)(selectedRegion & ~reg);
    updateTitles(currentCategory, selectedRegion);
    return; */
}

void GameList::on_gamelist_row_activated(guint position) {
    /*     Glib::RefPtr <Gtk::SelectionModel> selection = columnView->get_model();

    selection->get_selection(position, 1); */

    /* if () {
        mainWindow->set_sensitive(false);
        char selectedTID[128];
        sprintf(selectedTID, "%016llx", titleEntries[title->id].tid);
        download_title(selectedTID, decryptContents);
        mainWindow->set_sensitive(true);
    }*/
}

bool GameList::on_search_equal(
        const Glib::RefPtr<Gtk::SelectionModel> &model,
        int column,
        const Glib::ustring &key,
        const Gtk::TreeModel::iterator &iter) {
    /*
    Gtk::TreeModel::Row row = *iter;
    if (row) {
        Glib::ustring name = row[columns.name];
        std::string string_name(name.lowercase());
        std::string string_key(key.lowercase());
        if (string_name.find(string_key) != std::string::npos) {
            return false;
        }

        Glib::ustring titleId = row[columns.titleId];
        if (strcmp(titleId.c_str(), key.c_str()) == 0) {
            return false;
        }
    }
    */
    return true;
}