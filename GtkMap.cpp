//
// Created by pedrosoares on 24/07/17.
//

#ifndef GTKMAP__
#define GTKMAP__

#include <iostream>
#include <cstring>
#include "Tigre/String.h"

namespace GtkMap {

    static bool is_number(std::string str);

    static std::string ui_template =
            "#ifndef UI_{className}_H_GENERATED\n"
            "#define UI_{className}_H_GENERATED\n"
            "\n"
            "#include <gtkmm.h>\n"
            "#include <gtkmm/lockbutton.h>\n"
            "\n"
            "namespace Ui {\n"
            "    class {className} {\n"
            "\n"
            "        public:\n"
            "            void setupUi({windowType} *{windowParamether}) {\n"
            "{UI_Initializer}\n"
            "            }\n"
            "\n"
            "        private:\n"
            "{childrens}\n"
            "\n"
            "    };\n"
            "}\n"
            "\n"
            "#endif";

    static std::string propertyToGtkmm(std::string propety){
        //=================== BOOL PARAMETHER ========================
        if(propety == "car_focus"){
            return "set_can_focus";
        }
        if(propety == "visible"){
            return "set_visible";
        }
        if(propety == "hexpand"){
            return "set_hexpand";
        }
        if(propety == "vexpand"){
            return "set_vexpand";
        }
        if(propety == "column_homogeneous"){
            return "set_column_homogeneous";
        }
        if(propety == "row_homogeneous"){
            return "set_row_homogeneous";
        }
        //=================== STRING PARAMETHER ========================

        if(propety == "label"){
            return "set_label";
        }

        if(propety == "left_attach"){
            return "set_margin_left";
        }
        if(propety == "top_attach"){
            return "set_margin_top";
        }
        if(propety == "right_attach"){
            return "set_margin_right";
        }
        if(propety == "bottom_attach"){
            return "set_margin_bottom";
        }
        if(propety == "width_request"){
            return "set_size_request";
        }
        if(propety == "width_request"){
            return "height_request";
        }

        return "set_"+propety;
    }

    static std::string propetyValueToString(std::string value, std::string command = ""){
        if(value == "True"){
            return "true";
        }
        if(value == "False"){
            return "false";
        }
        if(is_number(value)){
            return value;
        }
        if(command != ""){
            if(command == "set_shadow_type"){
                std::transform(value.begin(), value.end(),value.begin(), ::toupper);
                return "Gtk::SHADOW_"+value;
            }
        }
        return "\""+value+"\"";
    }

    static bool is_number(std::string str) {
        for(int i = 0;i < (str.length() - 1); i++) {

            char  char_[] = " ";
            char_[0] = str[i];

            if(isdigit(str[i]) || std::string(char_) == ".") {
                //it's ok so far
            } else {
                return false;
            }
        }
        return true;
    }

    static std::string typeToGtkmmClass(std::string type){
        if(type == "GtkWindow"){
            return "Gtk::Window";
        }
        if(type == "GtkGrid"){
            return "Gtk::Grid";
        }
        if(type == "GtkButton"){
            return "Gtk::Button";
        }
        if(type == "GtkToggleButton"){
            return "Gtk::ToggleButton";
        }
        if(type == "GtkLockButton"){
            return "Gtk::LockButton";
        }
        if(type == "GtkFixed"){
            return "Gtk::Fixed";
        }
        if(type == "GtkLabel"){
            return "Gtk::Label";
        }
        Tigre::String classname = type;
        auto pieaces = classname.explode("Gtk");
        if(pieaces.size() <= 1)
            return "NotFound";
        else{
            return "Gtk::"+pieaces[1].getValue();
        }
    }

}

#endif
