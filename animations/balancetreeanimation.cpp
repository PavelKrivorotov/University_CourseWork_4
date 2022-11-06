#include "balancetreeanimation.h"

#include "graphics/graphicbinarytree.h"

#include <QTimer>

BalanceTreeAnimation::BalanceTreeAnimation(MainWindow *parent, GraphicBinaryTree *graphicBinaryTree):
    BaseAnimation(parent, graphicBinaryTree) {

    //

//    setStartGraphicNode(graphicBinaryTree->getRoot());

    _startGraphicNode = nullptr;

    //


    setDefaultMinimalCoordY0();
    setDefaultMaximalCoordY0();

    _currentIndexDownBalanceTreeAnimation = 0;
    _listDownBalanceTreeAnimation = new QList<GraphicNode*>;

    _currentIndexUpBalanceTreeAnimation = 0;
    _listUpBalanceTreeAnimation = new QList<GraphicNode*>;

    _brushPreviousNode = QBrush(QColor(255, 255, 255));
    _brushCurrentNode = QBrush(QColor(255, 255, 0));

    _deltaDownCoordY0 = 10;
    _deltaUpCoordY0 = 10;

    _timerDownUpdate = 30;
    _timerDown = new QTimer();

    _timerUpUpdate = 30;
    _timerUp = new QTimer();

    connect(_timerDown, &QTimer::timeout, this, &BalanceTreeAnimation::renderDownGraphicNodeAnimation);
    connect(_timerUp, &QTimer::timeout, this, &BalanceTreeAnimation::renderUpGraphicNodeAnimation);
}


BalanceTreeAnimation::~BalanceTreeAnimation() {
    delete _timerDown;
    delete _timerUp;
}


void BalanceTreeAnimation::setStartGraphicNode(GraphicNode *newStartGraphicNode) {
    if (newStartGraphicNode) { _startGraphicNode = newStartGraphicNode; }
    else { _startGraphicNode = nullptr; }
}


void BalanceTreeAnimation::setDeltaDownCoordY0(int newDeltaDownCoordY0) {
    _deltaDownCoordY0 = newDeltaDownCoordY0;
}


void BalanceTreeAnimation::setDeltaUpCoordY0(int newDeltaUpCoordY0) {
    _deltaUpCoordY0 = newDeltaUpCoordY0;
}


void BalanceTreeAnimation::setTimerDownUpdate(int milliSeconds) {
    _timerDownUpdate = milliSeconds;
}


void BalanceTreeAnimation::setTimerUpUpdate(int milliSeconds) {
    _timerUpUpdate = milliSeconds;
}


void BalanceTreeAnimation::setDefaultMinimalCoordY0() {
    _minimalCoordY0 = _graphicBinaryTree->minimalCoordY0(_startGraphicNode);
}


void BalanceTreeAnimation::setDefaultMaximalCoordY0() {
    _maximalCoordY0 = _graphicBinaryTree->maximalCoordY0(_startGraphicNode);
}


void BalanceTreeAnimation::showGraphicDown() {
    setDefaultMinimalCoordY0();
    setDefaultMaximalCoordY0();

    buildListDownAnimation(_startGraphicNode);
    renderDownGraphicTreeAnimation();
}


void BalanceTreeAnimation::showGraphicUp() {
    buildListUpAnimation(_startGraphicNode);
    renderUpGraphicTreeAnimation();
}


void BalanceTreeAnimation::buildListDownAnimation(GraphicNode *currentGraphicNode) {
    if (!currentGraphicNode) { return; }

    buildListDownAnimation(currentGraphicNode->getLeftChild());
    buildListDownAnimation(currentGraphicNode->getRightChild());

    _listDownBalanceTreeAnimation->append(currentGraphicNode);
}


void BalanceTreeAnimation::buildListUpAnimation(GraphicNode *currentGraphicNode) {
    if (!currentGraphicNode) { return; }

    currentGraphicNode->setCoordY0(_maximalCoordY0);

    _listUpBalanceTreeAnimation->append(currentGraphicNode);

    buildListUpAnimation(currentGraphicNode->getLeftChild());
    buildListUpAnimation(currentGraphicNode->getRightChild());
}


void BalanceTreeAnimation::renderDownGraphicTreeAnimation() {
    if (_currentIndexDownBalanceTreeAnimation < _listDownBalanceTreeAnimation->size()) {
        GraphicNode *currentGraphicNode = _listDownBalanceTreeAnimation->value(_currentIndexDownBalanceTreeAnimation);

        currentGraphicNode->setDrawLine(false);
        currentGraphicNode->setBalanceCoordinate(false);

        _currentScene->update();

        _timerDown->start(_timerDownUpdate);
        return;
    }

    _currentIndexDownBalanceTreeAnimation = 0;
    _listDownBalanceTreeAnimation->clear();

    completeRenderDownGraphicTreeAnimation();
}


void BalanceTreeAnimation::renderUpGraphicTreeAnimation() {
    if (_currentIndexUpBalanceTreeAnimation < _listUpBalanceTreeAnimation->size()) {
        _timerUp->start(_timerUpUpdate);
        return;
    }

    _currentIndexUpBalanceTreeAnimation = 0;
    _listUpBalanceTreeAnimation->clear();

    completeRenderUpGraphicTreeAnimation();
}


void BalanceTreeAnimation::renderDownGraphicNodeAnimation() {
    GraphicNode *currentGraphicNode = _listDownBalanceTreeAnimation->value(_currentIndexDownBalanceTreeAnimation);

    // Constant 10
    double startCoordY0 = currentGraphicNode->getCoordY0() + _deltaDownCoordY0;
    double endCoordY0 = _maximalCoordY0;

    if (startCoordY0 > endCoordY0) {
        currentGraphicNode->setCoordY0(endCoordY0);
        currentGraphicNode->setBrush(_brushPreviousNode);

        _currentScene->update();

        _currentIndexDownBalanceTreeAnimation += 1;

        _timerDown->stop();

        renderDownGraphicTreeAnimation();
        return;
    }

    currentGraphicNode->setCoordY0(startCoordY0);
    currentGraphicNode->setBrush(_brushCurrentNode);

    _currentScene->update();
}


void BalanceTreeAnimation::renderUpGraphicNodeAnimation() {
    GraphicNode *currentGraphicNode = _listUpBalanceTreeAnimation->value(_currentIndexUpBalanceTreeAnimation);

    // Constant 10
    double startCoordY0 = currentGraphicNode->getCoordY0() - _deltaUpCoordY0;
    double endCoordY0;

    GraphicNode *parentGraphicNode = currentGraphicNode->getParent();

    if (!parentGraphicNode) { endCoordY0 = _minimalCoordY0; }
    else { endCoordY0 = parentGraphicNode->getCoordLeftChildY0(); }


    if (startCoordY0 < endCoordY0) {
        currentGraphicNode->setCoordY0(endCoordY0);
        currentGraphicNode->setBrush(_brushPreviousNode);

        currentGraphicNode->setDrawLine(true);
        currentGraphicNode->setBalanceCoordinate(true);

        _currentScene->update();

        _currentIndexUpBalanceTreeAnimation += 1;

        _timerUp->stop();

        renderUpGraphicTreeAnimation();
        return;
    }

    currentGraphicNode->setCoordY0(startCoordY0);
    currentGraphicNode->setBrush(_brushCurrentNode);

    _currentScene->update();
}

