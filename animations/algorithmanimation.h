#ifndef ALGORITHMANIMATION_H
#define ALGORITHMANIMATION_H

#include "animations/baseanimation.h"


class AlgorithmAnimation: public BaseAnimation {
    Q_OBJECT

public:
    AlgorithmAnimation(MainWindow *parent, GraphicBinaryTree *graphicBinaryTree);
    ~AlgorithmAnimation();

    void setBrushPreviousNode(QBrush newBrush);

    void setBrushParentNode(QBrush newBrush);

    void setBrushLeftChildNode(QBrush newBrush);

    void setBrushRightChildNode(QBrush newBrush);

    void setTimerUpdate(int milliSeconds);

protected:
    void buildListElements();

    void renderAlgorithmAnimation();

private:
    int _currentIndexAlgorithmAnimation;
    QList<GraphicNode*> *_listAlgorithmAnimation;

    QBrush _brushPreviousNode;
    QBrush _brushParentNode;
    QBrush _brushLeftChildNode;
    QBrush _brushRightChildNode;

    int _timerUpdate;
    QTimer *_timer;

public slots:
    virtual void show();

signals:
    void completeAlgorithmAnimation();
};

#endif // ALGORITHMANIMATION_H
