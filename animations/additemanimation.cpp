#include "additemanimation.h"

#include "graphics/graphicbinarytree.h"
#include "animations/differenceheightanimation.h"
#include "animations/balancetreeanimation.h"
#include "animations/getitemanimation.h"

#include <QGraphicsScene>

AddItemAnimation::AddItemAnimation(MainWindow *parent, GraphicBinaryTree *graphicBinaryTree):
    BaseAnimation(parent, graphicBinaryTree) {

    _differenceHeightAnimation = new DifferenceHeightAnimation(parent, graphicBinaryTree);
    _balanceTreeAnimation = new BalanceTreeAnimation(parent, graphicBinaryTree);
    _getItemAnimation = new GetItemAnimation(parent, graphicBinaryTree);

    connect(_getItemAnimation, &GetItemAnimation::completeRenderGetAnimation,
            this, &AddItemAnimation::addItem);

    connect(_differenceHeightAnimation, &DifferenceHeightAnimation::completeDifferenceHeightAnimation,
            this, &AddItemAnimation::balanceTree1);

    connect(_balanceTreeAnimation, &BalanceTreeAnimation::completeRenderDownGraphicTreeAnimation,
            this, &AddItemAnimation::balanceTree2);

    connect(_balanceTreeAnimation, &BalanceTreeAnimation::completeRenderUpGraphicTreeAnimation,
            this, &AddItemAnimation::checkNewDifferenceHeight);
}


AddItemAnimation::~AddItemAnimation() {
    delete _differenceHeightAnimation;
    delete _balanceTreeAnimation;
    delete _getItemAnimation;
}


void AddItemAnimation::show(int value) {
    _getItemAnimation->show(value);
}


void AddItemAnimation::addItem(bool itemExists, int value) {
    if (!itemExists) {
        GraphicNode *addGraphicNode = _graphicBinaryTree->add(value);

        _currentScene->addItem(addGraphicNode);
        _currentScene->update();

        checkCurrentDifferenceHeight();
    }
}


void AddItemAnimation::checkCurrentDifferenceHeight() {
    _differenceHeightAnimation->setStartGraphicNode(_graphicBinaryTree->getRoot());
    _differenceHeightAnimation->show();
}


void AddItemAnimation::balanceTree1(bool makeBalance) {
    if (makeBalance) {
        _balanceTreeAnimation->setStartGraphicNode(_graphicBinaryTree->getRoot());
        _balanceTreeAnimation->showGraphicDown();
    }
}


void AddItemAnimation::balanceTree2() {
    _graphicBinaryTree->balanceTree(0, _graphicBinaryTree->getRoot());

    _balanceTreeAnimation->setStartGraphicNode(_graphicBinaryTree->getRoot());
    _balanceTreeAnimation->showGraphicUp();
}


void AddItemAnimation::checkNewDifferenceHeight() {
    _differenceHeightAnimation->setStartGraphicNode(_graphicBinaryTree->getRoot());
    _differenceHeightAnimation->show();
}

