#ifndef BALANCETREEANIMATION_H
#define BALANCETREEANIMATION_H

#include "animations/differenceheightanimation.h"


class BalanceTreeAnimation: public DifferenceHeightAnimation {
    Q_OBJECT

public:
    BalanceTreeAnimation(MainWindow *parent, GraphicBinaryTree *graphicBinaryTree);
    ~BalanceTreeAnimation();

    void setDeltaDownCoordY0(int newDeltaDownCoordY0);

    void setDeltaUpCoordY0(int newDeltaUpCoordY0);

    void setTimerDownUpdate(int milliSeconds);

    void setTimerUpUpdate(int milliSeconds);

private:
    void setDefaultMinimalCoordY0();

    void setDefaultMaximalCoordY0();

    void firstPart();

    void secondPart();

    void thridPart();

protected:
    void buildListDownAnimation(GraphicNode *currentGraphicNode);

    void buildTemplateList(GraphicNode *currentGraphicNode);

    void buildListUpAnimation(GraphicNode *currentGraphicNode);

    void rebuildGraphicTree(int state, GraphicNode *parentGraphicNode, int startIndex, int stopIndex);

    void renderDownGraphicTreeAnimation();

    void renderUpGraphicTreeAnimation();

    void renderDownGraphicNodeAnimation();

    void renderUpGraphicNodeAnimation();

private:
    int _minimalCoordY0;
    int _maximalCoordY0;

    int _currentIndexDownBalanceTreeAnimation;
    QList<GraphicNode*> *_listDownBalanceTreeAnimation;

    int _currentIndexUpBalanceTreeAnimation;
    QList<GraphicNode*> *_listUpBalanceTreeAnimation;

    QList<GraphicNode*> *_templateList;

    int _deltaDownCoordY0;
    int _deltaUpCoordY0;

    int _timerDownUpdate;
    QTimer *_timerDown;

    int _timerUpUpdate;
    QTimer *_timerUp;

public slots:
    virtual void show() override;

    void showGraphicDown();

    void showGraphicUp();

signals:
    void completeRenderDownGraphicTreeAnimation();

    void completeRenderUpGraphicTreeAnimation();

    void completeRenderDownGraphicNodeAnimation();

    void completeRenderUpGraphicNodeAnimation();
};

#endif // BALANCETREEANIMATION_H
