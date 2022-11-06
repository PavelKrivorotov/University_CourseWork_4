#include "differenceheightanimation.h"

#include "graphics/graphicbinarytree.h"

#include <QTimer>

DifferenceHeightAnimation::DifferenceHeightAnimation(MainWindow *parent, GraphicBinaryTree *graphicBinaryTree):
    BaseAnimation(parent, graphicBinaryTree) {

    //

//    setStartGraphicNode(graphicBinaryTree->getRoot());

    _startGraphicNode = nullptr;

    //


    setDefaultMinimalIndex();
    setDefaultMaximalIndex();

    _currentIndexDifferenceHeightAnimation = 0;
    _listDifferenceHeightAnimation = new QList<GraphicNode*>;

    _brushStartGraphicNode = QBrush(QColor(48, 213, 200));
    _brushPreviousGraphicNode = QBrush(QColor(255, 255, 255));
    _brushHighLevelNode = QBrush(QColor(0, 255, 0));
    _brushMiddleLevelNode = QBrush(QColor(255, 255, 0));
    _brushLowLevelNode = QBrush(QColor(255, 0, 0));

    _timerUpdate = 300;
    _timer = new QTimer();

    connect(_timer, &QTimer::timeout, this, &DifferenceHeightAnimation::renderDifferenceHeightAnimation);
}


DifferenceHeightAnimation::~DifferenceHeightAnimation() {
    delete _timer;
}


void DifferenceHeightAnimation::setStartGraphicNode(GraphicNode *newStartGraphicNode) {
    if (newStartGraphicNode) { _startGraphicNode = newStartGraphicNode; }
    else { _startGraphicNode = nullptr; }
}


void DifferenceHeightAnimation::setBrushPreviousGraphicNode(QBrush newBrush) {
    _brushPreviousGraphicNode = newBrush;
}


void DifferenceHeightAnimation::setBrushHighLevelNode(QBrush newBrush) {
    _brushHighLevelNode = newBrush;
}


void DifferenceHeightAnimation::setBrushMiddleLevelNode(QBrush newBrush) {
    _brushMiddleLevelNode = newBrush;
}


void DifferenceHeightAnimation::setBrushLowLevelNode(QBrush newBrush) {
    _brushLowLevelNode = newBrush;
}


void DifferenceHeightAnimation::setTimerUpdate(int milliSeconds) {
    if (milliSeconds < 30) { _timerUpdate = 30; }
    else if (milliSeconds > 1000) { _timerUpdate = 1000; }
    else { _timerUpdate = milliSeconds; }
}


void DifferenceHeightAnimation::setDefaultMinimalIndex() {
    _minimalIndex = _graphicBinaryTree->minimalIndex(_startGraphicNode);
}


void DifferenceHeightAnimation::setDefaultMaximalIndex() {
    _maximalIndex = _graphicBinaryTree->maximalIndex(_startGraphicNode);
}


void DifferenceHeightAnimation::show() {
    setDefaultMinimalIndex();
    setDefaultMaximalIndex();

    buildListDifferenceHeightAnimation(_startGraphicNode);

    _timer->start(_timerUpdate);
}


void DifferenceHeightAnimation::buildListDifferenceHeightAnimation(GraphicNode *currentGraphicNode) {
    if (!currentGraphicNode) { return; }

    GraphicNode *currentGraphicLeftChild = currentGraphicNode->getLeftChild();
    GraphicNode *currentGraphicRightChild = currentGraphicNode->getRightChild();

    if (!currentGraphicLeftChild || !currentGraphicRightChild) {
        _listDifferenceHeightAnimation->append(currentGraphicNode);
    }

    buildListDifferenceHeightAnimation(currentGraphicLeftChild);
    buildListDifferenceHeightAnimation(currentGraphicRightChild);
}


void DifferenceHeightAnimation::renderDifferenceHeightAnimation() {
    if (_startGraphicNode) { _startGraphicNode->setBrush(_brushStartGraphicNode); }

    if (_currentIndexDifferenceHeightAnimation < _listDifferenceHeightAnimation->size()) {
        GraphicNode *currentGraphicNode = _listDifferenceHeightAnimation->value(_currentIndexDifferenceHeightAnimation);

        if ((_maximalIndex - _minimalIndex) > 1) {
            if (currentGraphicNode->getIndex() == _minimalIndex) {
                currentGraphicNode->setBrush(_brushHighLevelNode);
            }

            else if (currentGraphicNode->getIndex() == _maximalIndex) {
                    currentGraphicNode->setBrush(_brushLowLevelNode);
            }

            else { currentGraphicNode->setBrush(_brushMiddleLevelNode); }
        }

        else {
            if (currentGraphicNode->getIndex() == _minimalIndex) {
                currentGraphicNode->setBrush(_brushHighLevelNode);
            }

            else if (currentGraphicNode->getIndex() == _maximalIndex) {
                    currentGraphicNode->setBrush(_brushMiddleLevelNode);
            }
        }

        _currentScene->update();

        _currentIndexDifferenceHeightAnimation += 1;
        return;
    }


    for (int index = 0; index < _listDifferenceHeightAnimation->size(); index++) {
        GraphicNode *currentGraphicNode = _listDifferenceHeightAnimation->value(index);

        currentGraphicNode->setBrush(_brushPreviousGraphicNode);
    }

    _currentScene->update();

    _currentIndexDifferenceHeightAnimation = 0;
    _listDifferenceHeightAnimation->clear();

    if (_startGraphicNode) { _startGraphicNode->setBrush(_brushPreviousGraphicNode); }

    _timer->stop();


    GraphicNode *rootGraphicNode = _graphicBinaryTree->getRoot();

    if (_graphicBinaryTree->differenceHeight(rootGraphicNode) < 2) { completeDifferenceHeightAnimation(false); }
    else { completeDifferenceHeightAnimation(true); };
}

