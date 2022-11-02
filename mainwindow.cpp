#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "animations/getitemanimation.h"
#include "animations/algorithmanimation.h"
#include "animations/differenceheightanimation.h"
#include "animations/balancetreeanimation.h"


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    _getDialog = new ConfirmDialog(this);
    _addDialog = new ConfirmDialog(this);
    _removeDialog = new ConfirmDialog(this);

    _scene = new QGraphicsScene(parent);
    ui->graphicView->setScene(_scene);

    _graphicBinaryTree = new GraphicBinaryTree(this);

    _graphicBinaryTree->add(0);
    _graphicBinaryTree->add(-9);
    _graphicBinaryTree->add(12);
    _graphicBinaryTree->add(100);
    _graphicBinaryTree->add(10);
    _graphicBinaryTree->add(256);
    _graphicBinaryTree->add(-89);
    _graphicBinaryTree->add(-67);
    _graphicBinaryTree->add(-5);
    _graphicBinaryTree->add(-95);
    _graphicBinaryTree->add(50);
    _graphicBinaryTree->add(9);
    _graphicBinaryTree->add(11);
    _graphicBinaryTree->add(-4);
    _graphicBinaryTree->add(-7);


    _getItemAnimation = new GetItemAnimation(this, _graphicBinaryTree);
    _algorithmAnimation = new AlgorithmAnimation(this, _graphicBinaryTree);
    _differenceHeightAnimation = new DifferenceHeightAnimation(this, _graphicBinaryTree);
    _balanceTreeAnimation = new BalanceTreeAnimation(this, _graphicBinaryTree);


    connect(ui->getBtn, &QPushButton::clicked, _getDialog, &ConfirmDialog::show);
    connect(ui->addBtn, &QPushButton::clicked, _addDialog, &ConfirmDialog::show);
    connect(ui->removeBtn, &QPushButton::clicked, _removeDialog, &ConfirmDialog::show);

    connect(_getDialog, &ConfirmDialog::dataConfirmed, this, &MainWindow::getItem);
    connect(_addDialog, &ConfirmDialog::dataConfirmed, this, &MainWindow::addItem);
    connect(_removeDialog, &ConfirmDialog::dataConfirmed, this, &MainWindow::removeItem);

    connect(ui->showAlgorithmBtn, &QPushButton::clicked, this, &MainWindow::showAlgorithm);
    connect(ui->showTreeBtn, &QPushButton::clicked, this, &MainWindow::showTree);
}


MainWindow::~MainWindow() {
    delete ui;

    delete _getDialog;
    delete _addDialog;
    delete _removeDialog;

    delete _graphicBinaryTree;

    delete _getItemAnimation;
    delete _algorithmAnimation;
    delete _differenceHeightAnimation;
    delete _balanceTreeAnimation;

    delete _scene;
}


QGraphicsScene * MainWindow::getScene() {
    return _scene;
}


void MainWindow::getItem(int value) {
    _getItemAnimation->show(value);
}


void MainWindow::addItem(int value) {
    _differenceHeightAnimation->show();
}


void MainWindow::removeItem(int value) {
    _balanceTreeAnimation->show();

//    _balanceTreeAnimation->showGraphicDown();

//    _balanceTreeAnimation->showGraphicUp();
}


void MainWindow::showAlgorithm() {
    _algorithmAnimation->show();
}


void MainWindow::showTree() {
    _graphicBinaryTree->render(_graphicBinaryTree->getRoot());
}

