#ifndef BALANCETREEANIMATION_H
#define BALANCETREEANIMATION_H

#include "animations/baseanimation.h"


class BalanceTreeAnimation: public BaseAnimation {
    Q_OBJECT

public:
    BalanceTreeAnimation(MainWindow *parent, GraphicBinaryTree *graphicBinaryTree);
    ~BalanceTreeAnimation();

    void setStartGraphicNode(GraphicNode *newStartGraphicNode = nullptr);

    void setDeltaDownCoordY0(int newDeltaDownCoordY0);

    void setDeltaUpCoordY0(int newDeltaUpCoordY0);

    void setTimerDownUpdate(int milliSeconds);

    void setTimerUpUpdate(int milliSeconds);

private:
    void setDefaultMinimalCoordY0();

    void setDefaultMaximalCoordY0();

protected:
    void buildListDownAnimation(GraphicNode *currentGraphicNode);

    void buildListUpAnimation(GraphicNode *currentGraphicNode);

    void renderDownGraphicTreeAnimation();

    void renderUpGraphicTreeAnimation();

    void renderDownGraphicNodeAnimation();

    void renderUpGraphicNodeAnimation();

private:
    GraphicNode *_startGraphicNode;

    int _minimalCoordY0;
    int _maximalCoordY0;

    int _currentIndexDownBalanceTreeAnimation;
    QList<GraphicNode*> *_listDownBalanceTreeAnimation;

    int _currentIndexUpBalanceTreeAnimation;
    QList<GraphicNode*> *_listUpBalanceTreeAnimation;

    int _deltaDownCoordY0;
    int _deltaUpCoordY0;

    QBrush _brushPreviousNode;
    QBrush _brushCurrentNode;

    int _timerDownUpdate;
    QTimer *_timerDown;

    int _timerUpUpdate;
    QTimer *_timerUp;

public slots:
    void showGraphicDown();

    void showGraphicUp();

signals:
    void completeRenderDownGraphicTreeAnimation();

    void completeRenderUpGraphicTreeAnimation();
};

#endif // BALANCETREEANIMATION_H
