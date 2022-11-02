#include "graphicbinarytree.h"
#include "mainwindow.h"


GraphicBinaryTree::GraphicBinaryTree() {
    _root = nullptr;

    _rootCoordX0 = 0;
    _rootCoordY0 = 0;

    _startAngle = 15;
    _startLengthLine = 256;
}


GraphicBinaryTree::~GraphicBinaryTree() {
    deleteGraphBinaryTree(_root);
}


GraphicNode * GraphicBinaryTree::get(int value) {
    GraphicNode *currentGraphicNode = _root;

    while (true) {
        if (!currentGraphicNode) { break; }

        int currentValue = currentGraphicNode->getValue();

        if (value < currentValue) { currentGraphicNode = currentGraphicNode->getLeftChild(); }
        else if (value > currentValue) { currentGraphicNode = currentGraphicNode->getRightChild(); }
        else { return currentGraphicNode; }
    }

    return nullptr;
}


void GraphicBinaryTree::add(int value) {
    if (!_root) {
        GraphicNode *rootGraphicNode = new GraphicNode(value, nullptr, false, true);
        rootGraphicNode->setCoordX0(_rootCoordX0);
        rootGraphicNode->setCoordY0(_rootCoordY0);
        rootGraphicNode->setAngle(_startAngle);
        rootGraphicNode->setLengthLine(_startLengthLine);

//        qDebug() << "Node:" << rootGraphicNode->getValue() << ". X0 =" << rootGraphicNode->getCoordX0()
//                 << ". Y0 =" << rootGraphicNode->getCoordY0();

        _root = rootGraphicNode;
        return;
    }

    GraphicNode *previousGraphicNode = nullptr;
    GraphicNode *currentGraphicNode = _root;

    while (currentGraphicNode) {
        previousGraphicNode = currentGraphicNode;

        if (value < currentGraphicNode->getValue()) { currentGraphicNode = currentGraphicNode->getLeftChild(); }
        else { currentGraphicNode = currentGraphicNode->getRightChild(); }
    }

    GraphicNode *newGraphicNode = new GraphicNode(value);
    newGraphicNode->setBalanceCoordinate(true);
    newGraphicNode->setParent(previousGraphicNode);
    newGraphicNode->setIndex(previousGraphicNode->getIndex() + 1);
    newGraphicNode->setDrawLine(true);
    newGraphicNode->setBalanceCoordinate(true);
//    newGraphicNode->setVisible(false);

    if (value < previousGraphicNode->getValue()) {
        previousGraphicNode->setLeftChild(newGraphicNode);
    }

    else {
        previousGraphicNode->setRightChild(newGraphicNode);
    }

    newGraphicNode->makeBalanceCoordinate();

//    qDebug() << "Node:" << newGraphicNode->getValue() << ". X0 =" << newGraphicNode->getCoordX0()
//             << ". Y0 =" << newGraphicNode->getCoordY0();

    balanceHeight(_root);
}


void GraphicBinaryTree::remove(int value) {

}


int GraphicBinaryTree::minimalIndex(GraphicNode *currentGraphicNode) {
    if (!currentGraphicNode) { return -1; }

    int currentIndex = currentGraphicNode->getIndex();

    int currentLeftIndex = minimalIndex(currentGraphicNode->getLeftChild());
    int currentRightIndex = minimalIndex(currentGraphicNode->getRightChild());

    if (currentLeftIndex == -1) { currentLeftIndex = currentIndex; }
    if (currentRightIndex == -1) { currentRightIndex = currentIndex; }

    if (!currentGraphicNode->getLeftChild() && !currentGraphicNode->getRightChild()) { return currentIndex; }
    else {
        if (currentLeftIndex < currentRightIndex) { return currentLeftIndex; }
        else { return currentRightIndex; }
    }
}


int GraphicBinaryTree::maximalIndex(GraphicNode *currentGraphicNode) {
    if (!currentGraphicNode) { return -1; }

    int currentIndex = currentGraphicNode->getIndex();

    int currentLeftIndex = maximalIndex(currentGraphicNode->getLeftChild());
    int currentRightIndex = maximalIndex(currentGraphicNode->getRightChild());

    if ((currentIndex > currentLeftIndex) && (currentIndex > currentRightIndex)) { return currentIndex; }
    else {
        if (currentLeftIndex > currentRightIndex) { return currentLeftIndex; }
        else { return currentRightIndex; }
    }
}



double GraphicBinaryTree::minimalCoordY0(GraphicNode *currentGraphicNode) {
   if (!currentGraphicNode) { return 0; }

   return currentGraphicNode->getCoordY0();
}


double GraphicBinaryTree::maximalCoordY0(GraphicNode *currentGraphicNode) {
    if (!currentGraphicNode) { return 0; }

    double maximalCoordY0Left = maximalCoordY0(currentGraphicNode->getLeftChild());
    double maximalCoordY0Right = maximalCoordY0(currentGraphicNode->getRightChild());

    double currentCoordY0 = currentGraphicNode->getCoordY0();

    if (maximalCoordY0Left < currentCoordY0) { maximalCoordY0Left = currentCoordY0; }
    if (maximalCoordY0Right < currentCoordY0) { maximalCoordY0Right = currentCoordY0; }

    if (maximalCoordY0Left > maximalCoordY0Right) { return maximalCoordY0Left; }
    else { return maximalCoordY0Right; }
}


GraphicNode * GraphicBinaryTree::getRoot() {
    return _root;
}


int GraphicBinaryTree::getRootCoordX0() {
    return _rootCoordX0;
}


int GraphicBinaryTree::getRootCoordY0() {
    return _rootCoordY0;
}


double GraphicBinaryTree::getStartAngle() {
    return _startAngle;
}


double GraphicBinaryTree::getStartLengthLine() {
    return _startLengthLine;
}


void GraphicBinaryTree::setRoot(GraphicNode *newRoot) {
    _root = newRoot;
}


void GraphicBinaryTree::setRootCoordX0(int newRootCoordX0) {
    _rootCoordX0 = newRootCoordX0;
}


void GraphicBinaryTree::setRootCoordY0(int newRootCoordY0) {
    _rootCoordY0 = newRootCoordY0;
}


void GraphicBinaryTree::setStartAngle(double newAngle) {
    _startAngle = newAngle;
}


void GraphicBinaryTree::setStartLengthLine(double newLengthLine) {
    _startLengthLine = newLengthLine;
}


void GraphicBinaryTree::balanceHeight(GraphicNode *currentGraphicNode) {
    if (!currentGraphicNode) { return; }

    if (!currentGraphicNode->getLeftChild() && !currentGraphicNode->getRightChild()) {
        currentGraphicNode->setMinimalHeight(0);
        currentGraphicNode->setMaximalHeight(0);
    }

    else if (currentGraphicNode->getLeftChild() && !currentGraphicNode->getRightChild()) {
        GraphicNode *currentGraphicNodeLeft = currentGraphicNode->getLeftChild();
        balanceHeight(currentGraphicNodeLeft);

        currentGraphicNode->setMinimalHeight(0);
        currentGraphicNode->setMaximalHeight(currentGraphicNodeLeft->getMaximalHeight() + 1);
    }

    else if (!currentGraphicNode->getLeftChild() && currentGraphicNode->getRightChild()) {
        GraphicNode *currentGraphicNodeRight = currentGraphicNode->getRightChild();
        balanceHeight(currentGraphicNodeRight);

        currentGraphicNode->setMinimalHeight(0);
        currentGraphicNode->setMaximalHeight(currentGraphicNodeRight->getMaximalHeight() + 1);
    }

    else {
        GraphicNode *currentGraphicNodeLeft = currentGraphicNode->getLeftChild();
        GraphicNode *currentGraphicNodeRight = currentGraphicNode->getRightChild();

        balanceHeight(currentGraphicNodeLeft);
        balanceHeight(currentGraphicNodeRight);

        int minimalHeightLeft = currentGraphicNodeLeft->getMinimalHeight();
        int minimalHeightRight = currentGraphicNodeRight->getMinimalHeight();
        int maximalHeightLeft = currentGraphicNodeLeft->getMaximalHeight();
        int maximalHeightRight = currentGraphicNodeRight->getMaximalHeight();

        if (minimalHeightLeft < minimalHeightRight) { currentGraphicNode->setMinimalHeight(minimalHeightLeft + 1); }
        else { currentGraphicNode->setMinimalHeight(minimalHeightRight + 1); }

        if (maximalHeightLeft > maximalHeightRight) { currentGraphicNode->setMaximalHeight(maximalHeightLeft + 1); }
        else { currentGraphicNode->setMaximalHeight(maximalHeightRight + 1); }
    }
}


void GraphicBinaryTree::deleteGraphBinaryTree(GraphicNode *currentGraphicNode) {
    if (!currentGraphicNode) { return; }

    if (currentGraphicNode == _root) {
        delete currentGraphicNode;
        _root = nullptr;
        return;
    }

    deleteGraphBinaryTree(currentGraphicNode->getLeftChild());
    deleteGraphBinaryTree(currentGraphicNode->getRightChild());

    qDebug() << currentGraphicNode->getValue() << "\n";

    delete currentGraphicNode;
}

