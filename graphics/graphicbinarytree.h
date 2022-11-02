#ifndef GRAPHICBINARYTREE_H
#define GRAPHICBINARYTREE_H

#include "graphics/graphicnode.h"

#include <QTimer>

class MainWindow;

class GraphicBinaryTree: public QObject {
    Q_OBJECT

public:
    explicit GraphicBinaryTree(MainWindow *parent = nullptr);
    ~GraphicBinaryTree();

    GraphicNode * get(int value);

    void add(int value);

    void remove(int value);

    int minimalIndex(GraphicNode *currentGraphicNode);

    int maximalIndex(GraphicNode *currentGraphicNode);

    double minimalCoordY0(GraphicNode *currentGraphicNode);

    double maximalCoordY0(GraphicNode *currentGraphicNode);

    GraphicNode * getRoot();

    int getRootCoordX0();

    int getRootCoordY0();

    double getStartAngle();

    double getStartLengthLine();

    void setRoot(GraphicNode *newRoot);

    void setRootCoordX0(int newRootCoordX0);

    void setRootCoordY0(int newRootCoordY0);

    void setStartAngle(double newAngle);

    void setStartLengthLine(double newLengthLine);

private:
    void deleteGraphBinaryTree(GraphicNode *currentGraphicNode);

protected:
    void balanceHeight(GraphicNode *currentGraphicNode);

private:
    int _rootCoordX0;
    int _rootCoordY0;

    double _startAngle;
    double _startLengthLine;

protected:
    GraphicNode *_root;

    QGraphicsScene *_currentScene;

public slots:
    void render(GraphicNode *currentGraphicNode);
};

#endif // GRAPHICBINARYTREE_H
