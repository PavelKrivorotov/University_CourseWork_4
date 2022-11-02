#include "balancetreeanimation.h"

#include "mainwindow.h"
#include "graphics/graphicbinarytree.h"

#include <QTimer>

BalanceTreeAnimation::BalanceTreeAnimation(MainWindow *parent, GraphicBinaryTree *graphicBinaryTree):
    DifferenceHeightAnimation(parent, graphicBinaryTree) {

    _graphicBinaryTree = graphicBinaryTree;

    //

    setStartGraphicNode(graphicBinaryTree->getRoot());

    //

//    _minimalCoordY0 = 0;
//    _maximalCoordY0 = maximalCoordY0(_startGraphicNode);

    setDefaultMinimalCoordY0();
    setDefaultMaximalCoordY0();

    _currentIndexDownBalanceTreeAnimation = 0;
    _listDownBalanceTreeAnimation = new QList<GraphicNode*>;

    _currentIndexUpBalanceTreeAnimation = 0;
    _listUpBalanceTreeAnimation = new QList<GraphicNode*>;

    _templateList = new QList<GraphicNode*>;

    _deltaDownCoordY0 = 10;
    _deltaUpCoordY0 = 10;

    _timerDownUpdate = 30;
    _timerDown = new QTimer();

    _timerUpUpdate = 30;
    _timerUp = new QTimer();

    connect(_timerDown, &QTimer::timeout, this, &BalanceTreeAnimation::renderDownGraphicNodeAnimation);
    connect(_timerUp, &QTimer::timeout, this, &BalanceTreeAnimation::renderUpGraphicNodeAnimation);

    connect(this, &BalanceTreeAnimation::completeRenderDownGraphicTreeAnimation,
            this, &BalanceTreeAnimation::secondPart);
}


BalanceTreeAnimation::~BalanceTreeAnimation() {
    delete _timerDown;
    delete _timerUp;
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
//    _minimalCoordY0 = minimalCoordY0(_startGraphicNode);

    _minimalCoordY0 = _graphicBinaryTree->minimalCoordY0(_startGraphicNode);
}


void BalanceTreeAnimation::setDefaultMaximalCoordY0() {
//    _maximalCoordY0 = maximalCoordY0(_startGraphicNode);

    _maximalCoordY0 = _graphicBinaryTree->maximalCoordY0(_startGraphicNode);
}


void BalanceTreeAnimation::firstPart() {
    setRoot(_graphicBinaryTree);

    setDefaultMinimalCoordY0();
    setDefaultMaximalCoordY0();

    buildListDownAnimation(_startGraphicNode);
    renderDownGraphicTreeAnimation();
}


void BalanceTreeAnimation::secondPart() {
    _templateList->clear();

    buildTemplateList(_root);
    rebuildGraphicTree(0, nullptr, 0, _templateList->size());


    setStartGraphicNode(_root);
    buildListUpAnimation(_startGraphicNode);
    renderUpGraphicTreeAnimation();
}


void BalanceTreeAnimation::thridPart() {

}


void BalanceTreeAnimation::show() {
    firstPart();
}


void BalanceTreeAnimation::showGraphicDown() {
    setRoot(_graphicBinaryTree);

    setDefaultMinimalCoordY0();
    setDefaultMaximalCoordY0();

    buildListDownAnimation(_startGraphicNode);
    renderDownGraphicTreeAnimation();
}


void BalanceTreeAnimation::showGraphicUp() {
    setRoot(_graphicBinaryTree);

    setDefaultMinimalCoordY0();
    setDefaultMaximalCoordY0();

    _templateList->clear();

    buildTemplateList(_root);
    rebuildGraphicTree(0, nullptr, 0, _templateList->size());


    setStartGraphicNode(_root);
    buildListUpAnimation(_startGraphicNode);
    renderUpGraphicTreeAnimation();
}


void BalanceTreeAnimation::buildListDownAnimation(GraphicNode *currentGraphicNode) {
    if (!currentGraphicNode) { return; }

    buildListDownAnimation(currentGraphicNode->getLeftChild());
    buildListDownAnimation(currentGraphicNode->getRightChild());

    _listDownBalanceTreeAnimation->append(currentGraphicNode);
}


void BalanceTreeAnimation::buildTemplateList(GraphicNode *currentGraphicNode) {
    if (!currentGraphicNode) { return; }

    buildTemplateList(currentGraphicNode->getLeftChild());

    _templateList->append(currentGraphicNode);

    buildTemplateList(currentGraphicNode->getRightChild());
}


void BalanceTreeAnimation::buildListUpAnimation(GraphicNode *currentGraphicNode) {
    if (!currentGraphicNode) { return; }

    _listUpBalanceTreeAnimation->append(currentGraphicNode);

    buildListUpAnimation(currentGraphicNode->getLeftChild());
    buildListUpAnimation(currentGraphicNode->getRightChild());
}


void BalanceTreeAnimation::rebuildGraphicTree(int state, GraphicNode *parentGraphicNode, int startIndex, int stopIndex) {
    if (!(stopIndex - startIndex)) { return; }

    int currentIndex = (startIndex + stopIndex) / 2;

    GraphicNode *currentGraphicNode = _templateList->value(currentIndex);
    currentGraphicNode->setLeftChild(nullptr);
    currentGraphicNode->setRightChild(nullptr);

    // Test
//    currentGraphicNode->setBalanceCoordinate(true);
//    currentGraphicNode->setDrawLine(true);

    currentGraphicNode->setBalanceCoordinate(false);
    currentGraphicNode->setDrawLine(false);


    switch (state) {
        case 0:
            currentGraphicNode->setParent(nullptr);
            currentGraphicNode->setCoordX0(_graphicBinaryTree->getRootCoordX0());
            currentGraphicNode->setCoordY0(_graphicBinaryTree->getRootCoordY0());
            currentGraphicNode->setAngle(_graphicBinaryTree->getStartAngle());
            currentGraphicNode->setLengthLine(_graphicBinaryTree->getStartLengthLine());
            currentGraphicNode->setIndex(0);
            currentGraphicNode->setMinimalHeight(0);
            currentGraphicNode->setMaximalHeight(0);

            _root = currentGraphicNode;

            // Set new root in GraphicBinaryTree _root
             _graphicBinaryTree->setRoot(currentGraphicNode);
            break;

        case -1:
            parentGraphicNode->setLeftChild(currentGraphicNode);

            currentGraphicNode->setParent(parentGraphicNode);
            currentGraphicNode->setIndex(parentGraphicNode->getIndex() + 1);


//            qDebug() << "By Parent: X0 =" << parentGraphicNode->getCoordLeftChildX0()
//                     << ". Y0 =" << parentGraphicNode->getCoordLeftChildY0();


            currentGraphicNode->setCoordX0(parentGraphicNode->getCoordLeftChildX0());
//            currentGraphicNode->setCoordY0(parentGraphicNode->getCoordLeftChildY0());

//            currentGraphicNode->makeBalanceCoordinate();
            break;

        case 1:
            parentGraphicNode->setRightChild(currentGraphicNode);

            currentGraphicNode->setParent(parentGraphicNode);
            currentGraphicNode->setIndex(parentGraphicNode->getIndex() + 1);


//            qDebug() << "By Parent: X0 =" << parentGraphicNode->getCoordRightChildX0()
//                     << ". Y0 =" << parentGraphicNode->getCoordRightChildY0();


            currentGraphicNode->setCoordX0(parentGraphicNode->getCoordRightChildX0());
//            currentGraphicNode->setCoordY0(parentGraphicNode->getCoordRightChildY0());

//            currentGraphicNode->makeBalanceCoordinate();
            break;

        default:
            break;
    }

    currentGraphicNode->setCoordY0(_maximalCoordY0);

//    balanceHeight(currentGraphicNode);

    _graphicBinaryTree->balanceHeight(currentGraphicNode);


//    qDebug() << "Index =" << currentIndex << ". Current Node:" << currentGraphicNode->getValue()
//             << ". X0 =" << currentGraphicNode->getCoordX0()
//             << ". Y0 =" << currentGraphicNode->getCoordY0()
//             << ". Angle =" << currentGraphicNode->getAngle()
//             << ". LEngth Line =" << currentGraphicNode->getLengthLine() << "\n";


    rebuildGraphicTree(-1, currentGraphicNode, startIndex, currentIndex);
    rebuildGraphicTree(1, currentGraphicNode, currentIndex + 1, stopIndex);
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
        currentGraphicNode->setBrush(QBrush(QColor(255, 255, 255)));

        _currentScene->update();

        _currentIndexDownBalanceTreeAnimation += 1;

        _timerDown->stop();

        completeRenderDownGraphicNodeAnimation();

        renderDownGraphicTreeAnimation();
        return;
    }

    currentGraphicNode->setCoordY0(startCoordY0);
    currentGraphicNode->setBrush(QBrush(QColor(255, 255, 0)));

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
        currentGraphicNode->setBrush(QBrush(QColor(255, 255, 255)));

        currentGraphicNode->setDrawLine(true);
        currentGraphicNode->setBalanceCoordinate(true);

        _currentScene->update();

        _currentIndexUpBalanceTreeAnimation += 1;

        _timerUp->stop();

        completeRenderUpGraphicNodeAnimation();

        renderUpGraphicTreeAnimation();
        return;
    }

    currentGraphicNode->setCoordY0(startCoordY0);
    currentGraphicNode->setBrush(QBrush(QColor(255, 255, 0)));

    _currentScene->update();
}

