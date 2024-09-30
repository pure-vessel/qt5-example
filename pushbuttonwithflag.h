#ifndef PUSHBUTTONWITHFLAG_H
#define PUSHBUTTONWITHFLAG_H

#include <QPushButton>

class PushButtonWithFlag : public QPushButton
{
    Q_OBJECT

public:
    PushButtonWithFlag(QWidget* parent = nullptr);

    bool flag = false;

    void set();
};

#endif // PUSHBUTTONWITHFLAG_H
