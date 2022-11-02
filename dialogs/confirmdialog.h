#ifndef CONFIRMDIALOG_H
#define CONFIRMDIALOG_H

#include <QDialog>

namespace Ui {
class ConfirmDialog;
}

class ConfirmDialog : public QDialog {
    Q_OBJECT

public:
    explicit ConfirmDialog(QWidget *parent = nullptr);
    ~ConfirmDialog();

private:
    void onYesBtnClicked();

protected:
        virtual void closeEvent(QCloseEvent *e);

private:
    Ui::ConfirmDialog *ui;

signals:
    void dataConfirmed(int value);
};

#endif // CONFIRMDIALOG_H
