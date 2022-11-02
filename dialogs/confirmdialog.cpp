#include "confirmdialog.h"
#include "ui_confirmdialog.h"

ConfirmDialog::ConfirmDialog(QWidget *parent): QDialog(parent), ui(new Ui::ConfirmDialog) {
    ui->setupUi(this);

    connect(ui->yesBtn, &QPushButton::clicked, this, &ConfirmDialog::onYesBtnClicked);
    connect(ui->noBtn, &QPushButton::clicked, this, &ConfirmDialog::close);
}


ConfirmDialog::~ConfirmDialog() {
    delete ui;
}


void ConfirmDialog::closeEvent(QCloseEvent *e) {
    ui->valueSB->setValue(0);
}


void ConfirmDialog::onYesBtnClicked() {
    int value = ui->valueSB->value();
    dataConfirmed(value);

    close();
}

