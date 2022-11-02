#include "baseanimation.h"

BaseAnimation::BaseAnimation(MainWindow *parent, GraphicBinaryTree *graphicBinaryTree):
    GraphicBinaryTree(parent) {

    _graphicBinaryTree = graphicBinaryTree;
}


BaseAnimation::~BaseAnimation() {
    // Complete the problem of destructions!
    setRoot(nullptr);
}


void BaseAnimation::setGraphicBinaryTree(GraphicBinaryTree *newGraphicBinaryTree) {
    _graphicBinaryTree = newGraphicBinaryTree;
}


void BaseAnimation::setRoot(GraphicBinaryTree *graphicBinaryTree) {
    if (graphicBinaryTree) { _root = graphicBinaryTree->getRoot(); }
    else { _root = nullptr; }
}

