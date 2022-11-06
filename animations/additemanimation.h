#ifndef ADDITEMANIMATION_H
#define ADDITEMANIMATION_H

#include "baseanimation.h"


class DifferenceHeightAnimation;
class BalanceTreeAnimation;
class GetItemAnimation;

class AddItemAnimation: public BaseAnimation {
    Q_OBJECT

public:
    AddItemAnimation(MainWindow *parent, GraphicBinaryTree *graphicBinaryTree);
    ~AddItemAnimation();

private:
    void addItem(bool itemExists, int value);

    void checkCurrentDifferenceHeight();

    void balanceTree1(bool makeBalance);

    void balanceTree2();

    void checkNewDifferenceHeight();

private:
    DifferenceHeightAnimation *_differenceHeightAnimation;
    BalanceTreeAnimation *_balanceTreeAnimation;
    GetItemAnimation *_getItemAnimation;

public slots:
    void show(int value);
};

#endif // ADDITEMANIMATION_H
