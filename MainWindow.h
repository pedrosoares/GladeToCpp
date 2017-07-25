//
// Created by pedrosoares on 24/07/17.
//

#ifndef GLADETOCPP_MAINWINDOW_H
#define GLADETOCPP_MAINWINDOW_H

#include <iostream>
#include <gtkmm.h>
#include "ui_mainwindow.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public Gtk::Window {

    public:
        MainWindow() : Gtk::Window(), ui(new Ui::MainWindow()) {
            ui->setupUi(this);
        }

        ~MainWindow(){
            delete ui;
        }

    private:
        Ui::MainWindow *ui;

};

#endif //GLADETOCPP_MAINWINDOW_H