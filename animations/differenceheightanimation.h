#ifndef DIFFERENCEHEIGHTANIMATION_H
#define DIFFERENCEHEIGHTANIMATION_H

#include "animations/baseanimation.h"


class DifferenceHeightAnimation: public BaseAnimation {
    Q_OBJECT

public:
    DifferenceHeightAnimation(MainWindow *parent, GraphicBinaryTree *graphicBinaryTree);
    ~DifferenceHeightAnimation();

    void setStartGraphicNode(GraphicNode *newStartGraphicNode = nullptr);

    void setBrushPreviousGraphicNode(QBrush newBrush);

    void setBrushHighLevelNode(QBrush newBrush);

    void setBrushMiddleLevelNode(QBrush newBrush);

    void setBrushLowLevelNode(QBrush newBrush);

    void setTimerUpdate(int milliSeconds);

private:
    void setDefaultMinimalIndex();

    void setDefaultMaximalIndex();

protected:
    void setRoot(GraphicBinaryTree *graphicBinaryTree);

    void buildListDifferenceHeightAnimation(GraphicNode *currentGraphicNode);

    void renderDifferenceHeightAnimation();

private:
    int _minimalIndex;
    int _maximalIndex;

    int _currentIndexDifferenceHeightAnimation;
    QList<GraphicNode*> *_listDifferenceHeightAnimation;

    QBrush _brushPreviousGraphicNode;
    QBrush _brushHighLevelNode;
    QBrush _brushMiddleLevelNode;
    QBrush _brushLowLevelNode;

    int _timerUpdate;
    QTimer *_timer;

protected:
    GraphicNode *_startGraphicNode;

public slots:
    virtual void show();

signals:
    void completeDifferenceHeightAnimation();
};

#endif // DIFFERENCEHEIGHTANIMATION_H
