#include "baseanimation.h"

#include "mainwindow.h"
#include "graphics/graphicbinarytree.h"

BaseAnimation::BaseAnimation(MainWindow *parent, GraphicBinaryTree *graphicBinaryTree) {
    _graphicBinaryTree = graphicBinaryTree;

    setRoot(_graphicBinaryTree);

    _currentScene = parent->getScene();
}


BaseAnimation::~BaseAnimation() {
    // Complete the problem of destructions!
    // setRoot(nullptr);
}


void BaseAnimation::setGraphicBinaryTree(GraphicBinaryTree *newGraphicBinaryTree) {
    _graphicBinaryTree = newGraphicBinaryTree;
}


void BaseAnimation::setRoot(GraphicBinaryTree *graphicBinaryTree) {
    if (graphicBinaryTree) { _root = graphicBinaryTree->getRoot(); }
    else { _root = nullptr; }
}


void BaseAnimation::showTree() {
    renderTree(_root);
}


void BaseAnimation::renderTree(GraphicNode *currentGraphicNode) {
    if (!currentGraphicNode) { return; }

    _currentScene->addItem(currentGraphicNode);
    _currentScene->update();

    renderTree(currentGraphicNode->getLeftChild());
    renderTree(currentGraphicNode->getRightChild());
}

