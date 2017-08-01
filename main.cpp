#include <iostream>
#include <sys/stat.h>
#include <gtkmm.h>
#include "GtkMap.cpp"
#include "Tigre/String.h"
#include "Parse.cpp"

static int varCount = 0;

std::string renderUi(std::string &ui_init, Parse::Object* item, std::string &proprety){
    std::string name = item->name.length() > 0 ? item->name : item->type+"_item"+std::to_string(varCount);
    varCount++;
    proprety += "                "+GtkMap::typeToGtkmmClass(item->type)+" "+name+";\n";
    for(auto const &propety : item->properties) {
        std::string command = GtkMap::propertyToGtkmm(propety.first);
        ui_init += "                this->"+name+"."+command+"("+GtkMap::propetyValueToString(propety.second, command)+");\n";
    }
    for(auto item_ : item->childrens) {
        std::string child_name = renderUi(ui_init, item_, proprety);

        if(item_->attach == NULL){
            if(item_->isSubmenu == false){
                ui_init += "                this->"+name+".add("+child_name+");\n\n";
            }else{
                ui_init += "                this->"+name+".set_submenu("+child_name+");\n\n";
            }
        }else{
            ui_init += "                this->"+name+".attach("+child_name+","+item_->attach->left+","+item_->attach->top+", 1, 1);\n\n";
        }
    }
    return name;
}

void Generate(Parse::Window * window){
    Tigre::String ui_template = GtkMap::ui_template;
    window->name = window->name.length() > 0 ? window->name : "MainWindow";
    ui_template.replace("{className}", window->name);
    ui_template.replace("{windowType}", GtkMap::typeToGtkmmClass(window->type));

    std::string proprety = "";
    std::string ui_init = "";
    for(auto const &propety : window->properties) {
        std::string command = GtkMap::propertyToGtkmm(propety.first);
        ui_init += "window->"+command+"("+GtkMap::propetyValueToString(propety.second, command)+");\n";
    }

    for(auto item : window->childrens) {
        std::string child_name = renderUi(ui_init, item, proprety);
        if(item->attach == NULL){
            ui_init += "                window->add("+child_name+");\n\n";
        }else{
            ui_init += "                window->attach("+child_name+","+item->attach->left+","+item->attach->top+", 1, 1);\n\n";
        }
    }
    ui_template.replace("{UI_Initializer}", ui_init);
    ui_template.replace("{childrens}", proprety);

    mode_t mask = umask(0);
    umask (mask);
    mkdir("include_ui", 0777 - mask);

    std::string filename = "include_ui/ui_"+(window->name)+".h";
    std::transform(filename.begin(), filename.end(), filename.begin(), ::tolower);

    std::fstream myfile;
    myfile = std::fstream(filename.c_str(), std::ios::out | std::ios::binary);
    myfile.write(ui_template.getValue().c_str(), ui_template.getValue().length());
    myfile.close();
}

int main(int argc, char *argv[]){
    for (int i = 1; i < argc; ++i) {
        std::string file = "../";
        file += argv[i];

        struct stat buffer;
        if(!(stat (file.c_str(), &buffer) == 0)){
            file = argv[i];
            if(!(stat (file.c_str(), &buffer) == 0)){
                continue;
            }
        }

        Parse::Window * window = new Parse::Window();
        Parse::parseMe(window, file);
        Generate(window);
        delete window;
    }
    return 0;
}
