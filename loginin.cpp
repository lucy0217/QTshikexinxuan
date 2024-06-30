#include "loginin.h"
#include "ui_loginin.h"

loginin::loginin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::loginin)
{
    ui->setupUi(this);
}

loginin::~loginin()
{
    delete ui;
}
