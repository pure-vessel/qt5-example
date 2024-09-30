#include "pushbuttonwithflag.h"

PushButtonWithFlag::PushButtonWithFlag(QWidget* parent) : QPushButton(parent) {}

void PushButtonWithFlag::set()
{
    flag = true;
}
