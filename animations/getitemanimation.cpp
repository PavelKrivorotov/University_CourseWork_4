#include "getitemanimation.h"

#include "mainwindow.h"

GetItemAnimation::GetItemAnimation(MainWindow *parent, GraphicBinaryTree *graphicBinaryTree):
    BaseAnimation(parent, graphicBinaryTree) {

    _graphicBinaryTree = graphicBinaryTree;

    _currentIndexListGetAnimation = 0;
    _listGetAnimation = new QList<GraphicNode*>;

    _brushSearchNode = QBrush(QColor(255, 255, 0));
    _brushPreviousNode= QBrush(QColor(255, 255, 255));
    _brushDetectedNode = QBrush(QColor(0, 255, 0));

    _timerUpdate = 350;
    _timer = new QTimer();

    connect(_timer, &QTimer::timeout, this, &GetItemAnimation::renderGetAnimation);
}


GetItemAnimation::~GetItemAnimation() {
    delete _listGetAnimation;

    delete _timer;
}


void GetItemAnimation::setBrushSearchNode(QBrush newBrush) {
    _brushSearchNode = newBrush;
}


void GetItemAnimation::setBrushPreviousNode(QBrush newBrush) {
    _brushPreviousNode = newBrush;
}


void GetItemAnimation::setBrushDetectedNode(QBrush newBrush) {
    _brushDetectedNode = newBrush;
}


void GetItemAnimation::setTimerUpdate(int milliSeconds) {
    if (milliSeconds < 30) { _timerUpdate = 30; }
    else if (milliSeconds > 1000) { _timerUpdate = 1000; }
    else { _timerUpdate = milliSeconds; }
}


void GetItemAnimation::show(int value) {
    setRoot(_graphicBinaryTree);
    buildListGetAnimation(value);

    _timer->start(_timerUpdate);
}


void GetItemAnimation::buildListGetAnimation(int value) {
    GraphicNode *currentGraphicNode = _root;

    _listGetAnimation->clear();
    _currentIndexListGetAnimation = 0;

    while (true) {
        _listGetAnimation->append(currentGraphicNode);

        if (!currentGraphicNode) { break; }

        int currentValue = currentGraphicNode->getValue();

        if (value < currentValue) { currentGraphicNode = currentGraphicNode->getLeftChild(); }
        else if (value > currentValue) { currentGraphicNode = currentGraphicNode->getRightChild(); }
        else { break; }
    }
}


void GetItemAnimation::renderGetAnimation() {
    if (_currentIndexListGetAnimation > 0) {
        GraphicNode *previousGraphicNode = _listGetAnimation->value(_currentIndexListGetAnimation - 1);

        if (previousGraphicNode) {
            previousGraphicNode->setBrush(_brushPreviousNode);
        }
    }

    if (_currentIndexListGetAnimation < _listGetAnimation->size()) {
        GraphicNode *currentGraphicNode = _listGetAnimation->value(_currentIndexListGetAnimation);

        if (currentGraphicNode) {
            if (_currentIndexListGetAnimation == _listGetAnimation->size() - 1) {
                currentGraphicNode->setBrush(_brushDetectedNode);
            }

            else { currentGraphicNode->setBrush(_brushSearchNode); }

        _currentScene->update();

        _currentIndexListGetAnimation += 1;
        return;
        }
    }

    _currentScene->update();

    _listGetAnimation->clear();
    _currentIndexListGetAnimation = 0;

    _timer->stop();

    completeRenderGetAnimation();
}

