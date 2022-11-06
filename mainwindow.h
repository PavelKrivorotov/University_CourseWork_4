#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ConfirmDialog;

class BaseAnimation;
class GraphicBinaryTree;
class GetItemAnimation;
class AlgorithmAnimation;
class DifferenceHeightAnimation;
class BalanceTreeAnimation;

class AddItemAnimation;
class RemoveItemAnimation;

class QGraphicsScene;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QGraphicsScene * getScene();

private:
    Ui::MainWindow *ui;

    ConfirmDialog *_getDialog, *_addDialog, *_removeDialog;

    QGraphicsScene *_scene;

    GraphicBinaryTree *_graphicBinaryTree;

    BaseAnimation *_baseAnimation;
    GetItemAnimation *_getItemAnimation;
    AlgorithmAnimation *_algorithmAnimation;
    DifferenceHeightAnimation *_differenceHeightAnimation;
    BalanceTreeAnimation *_balanceTreeAnimation;

    AddItemAnimation *_addItemAnimation;
    RemoveItemAnimation *_removeItemAnimation;

private slots:
    void getItem(int value);

    void addItem(int value);

    void removeItem(int value);

    void showAlgorithm();

    void showTree();
};
#endif // MAINWINDOW_H
