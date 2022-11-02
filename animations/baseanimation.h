#ifndef BASEANIMATION_H
#define BASEANIMATION_H

#include "graphics/graphicbinarytree.h"


class BaseAnimation: public GraphicBinaryTree {
    Q_OBJECT

public:
    BaseAnimation(MainWindow *parent, GraphicBinaryTree *graphicBinaryTree);
    ~BaseAnimation();

    void setGraphicBinaryTree(GraphicBinaryTree *newGraphicBinaryTree);

protected:
    void setRoot(GraphicBinaryTree *graphicBinaryTree);

protected:
    GraphicBinaryTree *_graphicBinaryTree;
};

#endif // BASEANIMATION_H
