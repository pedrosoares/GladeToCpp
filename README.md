## Glade to GTKmm/C++

Tranform Glade XML into C++ Class using GTKmm.

## How Use

### 1 Build the Project

Build this project to get the binary file.

### 2 Install the Binary

Install the builded binary into the ```/usr/local/bin``` of your system.
OBS: Windows is on msys2 folder.

### 3 Generate Yours Views

Use the command bellow into your cmake file to generate the view.
Remember, the file name aways start with ui_ and lower case,
the name is the ID of the toppest item of View (QWidget/QWindow...) in lower case too.

```
#generate UI files
set(GLADE_UI ExampleWindow.glade views/anotherWindow.glade)
set (generator "GladeToCPP")
execute_process(
        COMMAND ${generator} ${GLADE_UI}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
include_directories(${CMAKE_BINARY_DIR}/include_ui)
```

### 4 Integrate with your Class

To integrate with your class you need include the header generated and Instantiate as attribute.
Example:

```
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
```

## License

Copyright 2017 <Pedro Augusto da Silva Soares>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
