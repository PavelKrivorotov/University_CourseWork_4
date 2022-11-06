#include "removeitemanimation.h"

#include "graphics/graphicbinarytree.h"
#include "animations/differenceheightanimation.h"
#include "animations/balancetreeanimation.h"
#include "animations/getitemanimation.h"

RemoveItemAnimation::RemoveItemAnimation(MainWindow *parent, GraphicBinaryTree *graphicBinaryTree):
    BaseAnimation(parent, graphicBinaryTree) {

    _removeValue = 0;

    _childrenState = 0;
    _parentRemoveGraphicNode = nullptr;

    _differenceHeightAnimation = new DifferenceHeightAnimation(parent, graphicBinaryTree);
    _balanceTreeAnimation = new BalanceTreeAnimation(parent, graphicBinaryTree);
    _getItemAnimation = new GetItemAnimation(parent, graphicBinaryTree);

    connect(_getItemAnimation, &GetItemAnimation::completeRenderGetAnimation,
            this, &RemoveItemAnimation::removeItem);

    connect(_balanceTreeAnimation, &BalanceTreeAnimation::completeRenderDownGraphicTreeAnimation,
            this, &RemoveItemAnimation::balanceTree1);

    connect(_balanceTreeAnimation, &BalanceTreeAnimation::completeRenderUpGraphicTreeAnimation,
            this, &RemoveItemAnimation::checkCurrentDifferenceHeight);

    connect(_differenceHeightAnimation, &DifferenceHeightAnimation::completeDifferenceHeightAnimation,
            this, &RemoveItemAnimation::balanceTree2);
}


RemoveItemAnimation::~RemoveItemAnimation() {
    delete _differenceHeightAnimation;
    delete _balanceTreeAnimation;
    delete _getItemAnimation;
}


void RemoveItemAnimation::show(int value) {
    _getItemAnimation->show(value);
}


void RemoveItemAnimation::removeItem(bool itemExists, int value) {
    if (itemExists) {
        _removeValue = value;

        GraphicNode *removeGraphicNode = _graphicBinaryTree->get(value);

        _parentRemoveGraphicNode = removeGraphicNode->getParent();

        if (!_parentRemoveGraphicNode) { _childrenState = 0; }
        else if (removeGraphicNode == _parentRemoveGraphicNode->getLeftChild()) { _childrenState = -1; }
        else { _childrenState = 1; }

        _balanceTreeAnimation->setStartGraphicNode(removeGraphicNode);
        _balanceTreeAnimation->showGraphicDown();
    }
}


void RemoveItemAnimation::balanceTree1() {
    _graphicBinaryTree->remove(_removeValue);

    if (!_childrenState) { _balanceTreeAnimation->setStartGraphicNode(_graphicBinaryTree->getRoot()); }
    else if (_childrenState == -1) { _balanceTreeAnimation->setStartGraphicNode(_parentRemoveGraphicNode->getLeftChild()); }
    else { _balanceTreeAnimation->setStartGraphicNode(_parentRemoveGraphicNode->getRightChild()); }

    _balanceTreeAnimation->showGraphicUp();
}


void RemoveItemAnimation::checkCurrentDifferenceHeight() {
    _differenceHeightAnimation->setStartGraphicNode(_parentRemoveGraphicNode);
    _differenceHeightAnimation->show();
}


void RemoveItemAnimation::balanceTree2(bool makeBalance) {
//    if (makeBalance) { _balanceTreeAnimation->showGraphicDown(); qDebug() << "Neew Balance!";}
    if (_parentRemoveGraphicNode) {
        _parentRemoveGraphicNode = _parentRemoveGraphicNode->getParent();

        checkCurrentDifferenceHeight();
    }
}

