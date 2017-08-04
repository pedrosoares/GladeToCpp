//
// Created by Pedro Soares on 24/07/17.
//

#ifndef PARSE__
#define PARSE__

#include <iostream>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <string>
#include <map>
#include <vector>


using namespace std;

namespace Parse {

    class Attach {
        public:
            string top;
            string bottom;
            string left;
            string right;
    };

    class Size {
        public:
            string width;
            string height;
    };

    class Position {
        public:
            string x;
            string y;
    };

    class Object {
        public:
            virtual ~Object() {}
            string type;
            string name;
            map<string, string> properties;
            vector<Object *> childrens;
            // ===== Specials Attributes ===== //
            Size *dimencions = NULL;
            Attach *attach = NULL;
            Position *position = NULL;
            bool isSubmenu = false;

            void setPosition(std::string anchor, std::string coordN) {
                if (position == NULL) {
                    position = new Position();
                }
                if (anchor == "x") {
                    position->x = (coordN.c_str());
                }
                if (anchor == "y") {
                    position->x = (coordN.c_str());
                }
            }

            void setAttach(std::string anchor, std::string coordN) {
                if (attach == NULL) {
                    attach = new Attach();
                }
                if (anchor == "left_attach") {
                    attach->left = (coordN.c_str());
                }
                if (anchor == "right_attach") {
                    attach->right = (coordN.c_str());
                }
                if (anchor == "top_attach") {
                    attach->top = (coordN.c_str());
                }
                if (anchor == "bottom_attach") {
                    attach->bottom = (coordN.c_str());
                }
            }

            void setDimencionRequest(std::string anchor, std::string size) {
                if (dimencions == NULL) {
                    dimencions = new Size();
                }
                if (anchor == "width_request") {
                    dimencions->width = (size.c_str());
                }
                if (anchor == "width_request") {
                    dimencions->height = (size.c_str());
                }
            }

    };

    class Window : public Object {

        public:
            bool isTemplate = false;

    };


    static void weNeedGoDeeper(xmlNodePtr cur, Object *actual) {
        while (cur != NULL) {
            std::string name = (char *) cur->name;
            if(name == "placeholder"){
                cur = cur->next;
                continue;
            }
            if (name != "text") {
                auto properties = cur->properties;
                while (properties != NULL) {
                    cout << cur->name << " || " << properties->name << " || " << properties->children->content << endl;

                    if (name == "object" && string((char *) properties->name) == "class") {
                        actual->type = (char *) properties->children->content;
                    }

                    if (name == "template" && string((char *) properties->name) == "parent") {
                        actual->type = (char *) properties->children->content;
                        if(Parse::Window* v = dynamic_cast<Parse::Window*>(actual)) {
                            // old was safely casted to NewType
                            v->isTemplate = true;
                        }
                    }

                    if (
                        (name == "object" && string((char *) properties->name) == "id") or
                        (name == "template" && string((char *) properties->name) == "class")
                    ) {
                        actual->name = (char *) properties->children->content;
                    }
                    std::string parent_name = (char *) cur->parent->name;
                    if (parent_name == "object") {
                        if (name == "property" && string((char *) properties->name) == "name") {
                            std::string type_ = (char *) properties->children->content;
                            if (type_ == "width_request" || type_ == "height_request") {
                                actual->setDimencionRequest(type_, (char *) cur->children->content);
                            } else {
                                actual->properties[type_] = (char *) cur->children->content;
                            }
                        }
                    }
                    if (parent_name == "packing") {
                        if (name == "property" && string((char *) properties->name) == "name") {
                            std::string type_ = (char *) properties->children->content;
                            if (type_ == "x" || type_ == "y") {
                                actual->setPosition(type_, (char *) cur->children->content);
                            }
                            if (type_ == "left_attach" || type_ == "right_attach" || type_ == "top_attach" || type_ == "bottom_attach") {
                                actual->setAttach(type_, (char *) cur->children->content);
                            }
                        }
                    }

                    properties = properties->next;
                }

                if (cur->children != NULL) {
                    Object *child = actual;
                    if (name == "child") {
                        if(string((char *) cur->children->next->name) != "placeholder") {
                            child = new Object();
                            if (cur->properties != NULL && string((char *) cur->properties->name) == "type") {
                                if (string((char *) cur->properties->children->content) == "submenu") {
                                    child->isSubmenu = true;
                                }
                            }
                            actual->childrens.push_back(child);
                        }
                    }
                    weNeedGoDeeper(cur->children, child);
                }
            }
            cur = cur->next;
        }
    }

    static int parseMe(Object *actual, std::string filename) {
        xmlDocPtr doc;
        xmlNodePtr cur;

        doc = xmlParseFile(filename.c_str());

        if (doc == NULL) {
            fprintf(stderr, "Document not parsed successfully. \n");
            return -3;
        }

        cur = xmlDocGetRootElement(doc);

        if (cur == NULL) {
            fprintf(stderr, "empty document\n");
            xmlFreeDoc(doc);
            return -2;
        }

        if (xmlStrcmp(cur->name, (const xmlChar *) "interface")) {
            fprintf(stderr, "document of the wrong type, root node != story");
            xmlFreeDoc(doc);
            return -1;
        }

        weNeedGoDeeper(cur->xmlChildrenNode, actual);

        xmlFreeDoc(doc);
        return 0;
    }


}

#endif
