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
    void buildListDifferenceHeightAnimation(GraphicNode *currentGraphicNode);

    void renderDifferenceHeightAnimation();

private:
    GraphicNode *_startGraphicNode;

    int _minimalIndex;
    int _maximalIndex;

    int _currentIndexDifferenceHeightAnimation;
    QList<GraphicNode*> *_listDifferenceHeightAnimation;

    QBrush _brushStartGraphicNode;
    QBrush _brushPreviousGraphicNode;
    QBrush _brushHighLevelNode;
    QBrush _brushMiddleLevelNode;
    QBrush _brushLowLevelNode;

    int _timerUpdate;
    QTimer *_timer;

public slots:
    virtual void show();

signals:
    void completeDifferenceHeightAnimation(bool makeBalance);
};

#endif // DIFFERENCEHEIGHTANIMATION_H
