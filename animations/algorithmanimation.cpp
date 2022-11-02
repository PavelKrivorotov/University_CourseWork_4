#include "algorithmanimation.h"

#include "mainwindow.h"
#include "graphics/graphicnode.h"

#include <QTimer>

AlgorithmAnimation::AlgorithmAnimation(MainWindow *parent, GraphicBinaryTree *graphicBinaryTree):
    BaseAnimation(parent, graphicBinaryTree) {

    _graphicBinaryTree = graphicBinaryTree;

    _currentIndexAlgorithmAnimation = 0;
    _listAlgorithmAnimation = new QList<GraphicNode*>;

    _brushPreviousNode = QBrush(QColor(255, 255, 255));
    _brushParentNode = QBrush(QColor(0, 255, 0));
    _brushLeftChildNode = QBrush(QColor(255, 255, 0));
    _brushRightChildNode = QBrush(QColor(255, 255, 0));

    _timerUpdate = 350;
    _timer = new QTimer();

    connect(_timer, &QTimer::timeout, this, &AlgorithmAnimation::renderAlgorithmAnimation);
}


AlgorithmAnimation::~AlgorithmAnimation() {
    delete _timer;
}


void AlgorithmAnimation::setBrushPreviousNode(QBrush newBrush) {
    _brushPreviousNode = newBrush;
}


void AlgorithmAnimation::setBrushParentNode(QBrush newBrush) {
    _brushParentNode = newBrush;
}


void AlgorithmAnimation::setBrushLeftChildNode(QBrush newBrush) {
    _brushLeftChildNode = newBrush;
}


void AlgorithmAnimation::setBrushRightChildNode(QBrush newBrush) {
    _brushRightChildNode = newBrush;
}


void AlgorithmAnimation::setTimerUpdate(int milliSeconds) {
    if (milliSeconds < 30) { _timerUpdate = 30; }
    else if (milliSeconds > 1000) { _timerUpdate = 1000; }
    else { _timerUpdate = milliSeconds; }
}


void AlgorithmAnimation::show() {
    setRoot(_graphicBinaryTree);
    buildListElements();

    _timer->start(_timerUpdate);
}


void AlgorithmAnimation::buildListElements() {
    _listAlgorithmAnimation->clear();
    _currentIndexAlgorithmAnimation = 0;

    if (!_root) { return; }

    QList<GraphicNode*> *queue1, *queue2, *currentQueue, *waitingQueue;
    queue1 = new QList<GraphicNode*>;
    queue2 = new QList<GraphicNode*>;

    _listAlgorithmAnimation->append(_root);

    GraphicNode *graphicNodeLeft = _root->getLeftChild();
    GraphicNode *graphicNodeRight = _root->getRightChild();

    if (graphicNodeLeft) { queue1->append(graphicNodeLeft); }
    if (graphicNodeRight) { queue1->append(graphicNodeRight); }


    bool state = false;
    while (queue1->size() || queue2->size()) {
        if (!state) { currentQueue = queue1; waitingQueue = queue2; }
        else { currentQueue = queue2; waitingQueue = queue1; }

        for (int index = 0; index < currentQueue->size(); index++) {
            GraphicNode *currentGraphicNode = currentQueue->value(index);

            _listAlgorithmAnimation->append(currentGraphicNode);

            GraphicNode *graphicNodeLeft = currentGraphicNode->getLeftChild();
            GraphicNode *graphicNodeRight = currentGraphicNode->getRightChild();

            if (graphicNodeLeft) { waitingQueue->append(graphicNodeLeft); }
            if (graphicNodeRight) { waitingQueue->append(graphicNodeRight); }
        }

        currentQueue->clear();
        state = !state;
    }


    delete queue1;
    delete queue2;
}


void AlgorithmAnimation::renderAlgorithmAnimation() {
    if (_currentIndexAlgorithmAnimation > 0) {
        GraphicNode *previousGraphicNode = _listAlgorithmAnimation->value(_currentIndexAlgorithmAnimation - 1);

        if (previousGraphicNode) {
            previousGraphicNode->setBrush(_brushPreviousNode);

            GraphicNode *leftGraphicNode = previousGraphicNode->getLeftChild();
            GraphicNode *rightGraphicNode = previousGraphicNode->getRightChild();

            if (leftGraphicNode) { leftGraphicNode->setBrush(_brushPreviousNode); }
            if (rightGraphicNode) { rightGraphicNode->setBrush(_brushPreviousNode); }
        }
    }

    if (_currentIndexAlgorithmAnimation < _listAlgorithmAnimation->size()) {
        GraphicNode *currentGraphicNode = _listAlgorithmAnimation->value(_currentIndexAlgorithmAnimation);

        if (currentGraphicNode) {
            currentGraphicNode->setBrush(_brushParentNode);

            GraphicNode *leftGraphicNode = currentGraphicNode->getLeftChild();
            GraphicNode *rightGraphicNode = currentGraphicNode->getRightChild();

            if (leftGraphicNode) { leftGraphicNode->setBrush(_brushLeftChildNode); }
            if (rightGraphicNode) { rightGraphicNode->setBrush(_brushRightChildNode); }

            _currentScene->update();

            _currentIndexAlgorithmAnimation += 1;
            return;
        }
    }

    _currentScene->update();

    _listAlgorithmAnimation->clear();
    _currentIndexAlgorithmAnimation = 0;

    _timer->stop();

    completeAlgorithmAnimation();
}

