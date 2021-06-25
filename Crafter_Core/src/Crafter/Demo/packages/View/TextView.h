//
// Created by Matthew Good on 25/6/21.
//

#ifndef CRAFTER_TEXTVIEW_H
#define CRAFTER_TEXTVIEW_H


#include "View.h"
#include "GLIS_FONT.h"

class TextView : public View {
public:
    virtual void init();

    virtual void onDraw();

    void setText(const std::string &string);
    void setTextSize(const int &size);
};


#endif //CRAFTER_TEXTVIEW_H
