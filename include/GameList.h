#pragma once

#include <gtkmm.h>
#include <string>
#include <vector>

#include <keygen.h>
#include <gtitles.h>

class GameList
{
public:
    class ModelColumns : public Gtk::TreeModel::ColumnRecord
    {
    public:
        ModelColumns()
        {
            add(index);
            add(titleId);
            add(kind);
            add(region);
            add(name);
        }

        Gtk::TreeModelColumn<int> index;
        Gtk::TreeModelColumn<Glib::ustring> titleId;
        Gtk::TreeModelColumn<Glib::ustring> kind;
        Gtk::TreeModelColumn<Glib::ustring> region;
        Gtk::TreeModelColumn<Glib::ustring> name;
    };

    GameList(Glib::RefPtr<Gtk::Builder> builder, const TitleEntry *infos);
    ~GameList();

    void on_gamelist_row_activated(const Gtk::TreePath& treePath, Gtk::TreeViewColumn* const& column);
    void on_dumpWindow_closed();
    bool on_search_equal(const Glib::RefPtr<Gtk::TreeModel>& model, int column, const Glib::ustring& key, const Gtk::TreeModel::iterator& iter);

    Gtk::Window* getWindow() { return gameListWindow; }

private:
    Gtk::Window* gameListWindow = nullptr;
    Glib::RefPtr<Gtk::Builder> builder;
    std::vector<uint8_t> key;

    Gtk::TreeView* treeView = nullptr;
    ModelColumns columns;
    const TitleEntry *infos;

    sigc::connection deleteConn;

    Gtk::AboutDialog* aboutDialog = nullptr;
    sigc::connection aboutConn;
};