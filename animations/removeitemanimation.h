#ifndef REMOVEITEMANIMATION_H
#define REMOVEITEMANIMATION_H

#include "animations/baseanimation.h"


class DifferenceHeightAnimation;
class BalanceTreeAnimation;
class GetItemAnimation;

class RemoveItemAnimation: public BaseAnimation {
    Q_OBJECT

public:
    RemoveItemAnimation(MainWindow *parent, GraphicBinaryTree *graphicBinaryTree);
    ~RemoveItemAnimation();

private:
    void removeItem(bool itemExists, int value);

    void balanceTree1();

    void balanceTree2(bool makeBalance);

    void checkCurrentDifferenceHeight();

private:
    int _removeValue;

    int _childrenState;
    GraphicNode *_parentRemoveGraphicNode;

    DifferenceHeightAnimation *_differenceHeightAnimation;
    BalanceTreeAnimation *_balanceTreeAnimation;
    GetItemAnimation *_getItemAnimation;

public slots:
    void show(int value);
};

#endif // REMOVEITEMANIMATION_H
