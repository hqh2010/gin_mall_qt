#include "register.h"
#include "ui_register.h"

Register::Register(QWidget *parent) : QMainWindow(parent),
                                      ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}
