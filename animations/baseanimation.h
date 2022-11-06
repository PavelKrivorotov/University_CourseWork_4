#ifndef BASEANIMATION_H
#define BASEANIMATION_H

#include <QObject>
#include <QGraphicsScene>


class MainWindow;
class GraphicBinaryTree;
class GraphicNode;

class BaseAnimation: public QObject {
    Q_OBJECT

public:
    BaseAnimation(MainWindow *parent, GraphicBinaryTree *graphicBinaryTree);
    ~BaseAnimation();

    void setGraphicBinaryTree(GraphicBinaryTree *newGraphicBinaryTree);

protected:
    void renderTree(GraphicNode *currentGraphicNode);

protected:
    GraphicBinaryTree *_graphicBinaryTree;

    QGraphicsScene *_currentScene;

public slots:
    void showTree();
};

#endif // BASEANIMATION_H
