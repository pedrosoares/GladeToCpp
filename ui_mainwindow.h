#ifndef UI_MainWindow_H_GENERATED
#define UI_MainWindow_H_GENERATED

#include <gtkmm.h>
#include <gtkmm/lockbutton.h>

namespace Ui {
    class MainWindow {

    public:
        void setupUi(Gtk::Window *window) {
            window->set_can_focus(false);
            this->gride1.set_can_focus(false);
            this->gride1.set_column_homogeneous(true);
            this->gride1.set_hexpand(true);
            this->gride1.set_vexpand(true);
            this->gride1.set_visible(true);
            this->gride2.set_can_focus(false);
            this->gride2.set_column_homogeneous(true);
            this->gride2.set_row_homogeneous(true);
            this->gride2.set_visible(true);
            this->GtkButton_item.set_can_focus(true);
            this->GtkButton_item.set_label("button");
            this->GtkButton_item.set_receives_default(true);
            this->GtkButton_item.set_visible(true);
            this->gride2.attach(GtkButton_item,0,0, 1, 1);
            this->GtkToggleButton_item.set_can_focus(true);
            this->GtkToggleButton_item.set_label("togglebutton");
            this->GtkToggleButton_item.set_receives_default(true);
            this->GtkToggleButton_item.set_visible(true);
            this->gride2.attach(GtkToggleButton_item,1,0, 1, 1);
            this->GtkLockButton_item.set_can_focus(true);
            this->GtkLockButton_item.set_visible(true);
            this->gride2.attach(GtkLockButton_item,2,0, 1, 1);
            this->gride1.attach(gride2,0,0, 1, 1);
            this->GtkFixed_item.set_can_focus(false);
            this->GtkFixed_item.set_hexpand(true);
            this->GtkFixed_item.set_vexpand(true);
            this->GtkFixed_item.set_visible(true);
            this->GtkLabel_item.set_can_focus(false);
            this->GtkLabel_item.set_label("Oi abiguinhos");
            this->GtkLabel_item.set_visible(true);
            this->GtkFixed_item.add(GtkLabel_item);
            this->gride1.attach(GtkFixed_item,0,1, 1, 1);
            window->add(gride1);

        }

    private:
        Gtk::Grid gride1;
        Gtk::Grid gride2;
        Gtk::Button GtkButton_item;
        Gtk::ToggleButton GtkToggleButton_item;
        Gtk::LockButton GtkLockButton_item;
        Gtk::Fixed GtkFixed_item;
        Gtk::Label GtkLabel_item;


    };
}

#endif