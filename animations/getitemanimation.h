#ifndef GETITEMANIMATION_H
#define GETITEMANIMATION_H

#include "animations/baseanimation.h"


class GetItemAnimation: public BaseAnimation {
    Q_OBJECT

public:
    explicit GetItemAnimation(MainWindow *parent, GraphicBinaryTree *graphicBinaryTree);
    ~GetItemAnimation();

    void setBrushSearchNode(QBrush newBrush);

    void setBrushPreviousNode(QBrush newBrush);

    void setBrushDetectedNode(QBrush newBrush);

    void setTimerUpdate(int milliSeconds);

protected:
    void buildListGetAnimation(int value);

    void renderGetAnimation();

private:
    int _detectedValue;

    int _currentIndexListGetAnimation;
    QList<GraphicNode*> *_listGetAnimation;

    QBrush _brushSearchNode;
    QBrush _brushPreviousNode;
    QBrush _brushDetectedNode;

    int _timerUpdate;
    QTimer *_timer;

public slots:
    virtual void show(int value);

signals:
    void completeRenderGetAnimation(bool itemExists, int value);
};

#endif // GETITEMANIMATION_H
