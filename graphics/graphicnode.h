#ifndef GRAPHICNODE_H
#define GRAPHICNODE_H

#include <QGraphicsItem>
#include <QBrush>


class GraphicNode : public QGraphicsItem {

public:
    GraphicNode(int value, GraphicNode *parent = nullptr, bool drawLine = false, bool balanceCoordinate = false,
                int minimalHeight = 0,int maximalheight = 0, int index = 0,double radius = 20,
                QBrush brushColor = QBrush());

    ~GraphicNode();

    void setParent(GraphicNode *newParent);

    void setDrawLine(bool newState);

    void setBalanceCoordinate(bool newState);

    void setMinimalHeight(int newHeight);

    void setMaximalHeight(int newHeight);

    void setIndex(int newIndex);

    void setAngle(double newAngle);

    void setDefaultAngle();

    void setLengthLine(double newLength);

    void setDefaultLineLength();

    void setRadius(double newRadius);

    void setBrush(QBrush brushColor);

    void setLeftChild(GraphicNode *newLeftChild, bool defaultLineLength = true, bool defaultAngle = true);

    void setRightChild(GraphicNode *newRightChild, bool defaultLineLength = true, bool defaultAngle = true);

    void setCoordX0(double newCoordX0);

    void setCoordY0(double newCoordY0);

    int getValue();

    bool getDrawLine();

    bool getBalanceCoordinate();

    int getMinimalHeight();

    int getMaximalHeight();

    int getIndex();

    double getAngle();

    double getLengthLine();

    double getRadius();

    double getCoordX0();

    double getCoordY0();

    double getCoordLeftChildX0();

    double getCoordLeftChildY0();

    double getCoordRightChildX0();

    double getCoordRightChildY0();

    GraphicNode * getParent();

    GraphicNode * getLeftChild();

    GraphicNode * getRightChild();

    void makeBalanceCoordinate();


private:
    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                       QWidget *widget = nullptr) override;

private:
    int _value;
    int _minimalHeight;
    int _maximalHeight;
    int _index;

    bool _drawLine;
    bool _balanceCoordinate;

    double _angle;
    double _lengthLine;

    double _radius;

    double _coordX0;
    double _coordY0;

    QBrush _brushColor;

    GraphicNode *_parent;
    GraphicNode *_leftChild;
    GraphicNode *_rightChild;
};

#endif // GRAPHICNODE_H
