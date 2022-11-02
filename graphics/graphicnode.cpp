#include "graphicnode.h"
#include "math.h"

#include <QPainter>

GraphicNode::GraphicNode(int value, GraphicNode *parent, bool drawLine, bool balanceCoordinate,
                         int minimalHeight, int maximalHeight, int index, double radius,
                         QBrush brushColor) {

    _value = value;
    _parent = parent;

    _drawLine = drawLine;
    _balanceCoordinate = balanceCoordinate;

    _minimalHeight = minimalHeight;
    _maximalHeight = maximalHeight;
    _index = index;

    _angle = 0;
    _lengthLine = 0;

    _radius = radius;

    _coordX0 = 0;
    _coordY0 = 0;

    _brushColor = brushColor;

    _rightChild = nullptr;
    _leftChild = nullptr;;

    setDefaultLineLength();
    setDefaultAngle();

//    makeBalanceCoordinate();
}


GraphicNode::~GraphicNode() {

}


QRectF GraphicNode::boundingRect() const {
    return QRectF(-_radius, - _radius, _radius * 2, _radius * 2);
}


void GraphicNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
//    if (_parent && _balanceCoordinate) { makeBalanceCoordinate(); }

    painter->setPen(QPen(QBrush(QColor(0, 0, 0)), 2));
    painter->setFont(QFont("Helvetica", _radius / 1.25));
    painter->setBrush(_brushColor);

    if (_parent && _balanceCoordinate) {
        double lengthLine = _parent->getLengthLine();
        double angle = _parent->getAngle();

        painter->translate(_parent->getCoordX0(), _parent->getCoordY0());

        if (this == _parent->getLeftChild()) { angle = 180 - angle; }

        painter->rotate(angle);

        if (_drawLine) { painter->drawLine(_parent->getRadius(), 0, lengthLine - _radius, 0); }

        painter->translate(lengthLine, 0);
        painter->rotate(-angle);
    }

    else { painter->translate(_coordX0, _coordY0); }

    painter->drawEllipse(-_radius, - _radius, _radius * 2, _radius * 2);

    QRectF rect = QRectF(-_radius, - _radius, _radius * 2, _radius * 2);
    painter->drawText(rect, Qt::AlignCenter, QString::number(_value));
}


void GraphicNode::setParent(GraphicNode *newParent) {
    _parent = newParent;
}


void GraphicNode::setDrawLine(bool newState) {
    _drawLine = newState;
}


void GraphicNode::setBalanceCoordinate(bool newState) {
    _balanceCoordinate = newState;

//    if (_parent && newState) { makeBalanceCoordinate(); }
}


void GraphicNode::setAngle(double newAngle) {
    _angle = newAngle;
}


void GraphicNode::setLengthLine(double newLength) {
    _lengthLine = newLength;;
}


void GraphicNode::setRadius(double newRadius) {
    _radius = newRadius;
}


void GraphicNode::setMinimalHeight(int newHeight) {
    _minimalHeight = newHeight;
}


void GraphicNode::setMaximalHeight(int newHeight) {
    _maximalHeight = newHeight;
}


void GraphicNode::setIndex(int newIndex) {
    _index = newIndex;
}


void GraphicNode::setBrush(QBrush brushColor) {
    _brushColor = brushColor;
}


void GraphicNode::setLeftChild(GraphicNode *newLeftChild, bool defaultLineLength, bool defaultAngle) {
    _leftChild = newLeftChild;

//    if (defaultLineLength) { setDefaultLineLength(); }
//    if (defaultAngle) { setDefaultAngle(); }


//    if (newLeftChild) {
//        if (defaultLineLength) { _leftChild->setDefaultLineLength(); }
//        if (defaultAngle) { _leftChild->setDefaultAngle(); }
//    }


    if (newLeftChild) {
        if (defaultLineLength) { _leftChild->setLengthLine(_lengthLine / 2); }
        if (defaultAngle) { _leftChild->setAngle(_angle + 15); }
    }
}


void GraphicNode::setRightChild(GraphicNode *newRightChild, bool defaultLineLength, bool defaultAngle) {
    _rightChild = newRightChild;

//    if (defaultLineLength) { setDefaultLineLength(); }
//    if (defaultAngle) { setDefaultAngle(); }


//    if (newRightChild) {
//        if (defaultLineLength) { _rightChild->setDefaultLineLength(); }
//        if (defaultAngle) { _rightChild->setDefaultAngle(); }
//    }


    if (newRightChild) {
        if (defaultLineLength) { _rightChild->setLengthLine(_lengthLine / 2); }
        if (defaultAngle) { _rightChild->setAngle(_angle + 15); }
    }
}


void GraphicNode::setCoordX0(double newCoordX0) {
    _coordX0 = newCoordX0;
}


void GraphicNode::setCoordY0(double newCoordY0) {
    _coordY0 = newCoordY0;
}


int GraphicNode::getValue() {
    return _value;
}


bool GraphicNode::getDrawLine() {
    return _drawLine;
}


bool GraphicNode::getBalanceCoordinate() {
    return _balanceCoordinate;
}


int GraphicNode::getMinimalHeight() {
    return _minimalHeight;
}


int GraphicNode::getMaximalHeight() {
    return _maximalHeight;
}


int GraphicNode::getIndex() {
    return _index;
}


double GraphicNode::getAngle() {
    return _angle;
}


double GraphicNode::getLengthLine() {
    return _lengthLine;
}


double GraphicNode::getRadius() {
    return _radius;
}


double GraphicNode::getCoordX0() {
    return _coordX0;
}


double GraphicNode::getCoordY0() {
    return _coordY0;
}


double GraphicNode::getCoordLeftChildX0() {
    double x0 = _coordX0 + _lengthLine * cos((180 - _angle) * (M_PI/180));
    return x0;
}


double GraphicNode::getCoordLeftChildY0() {
    double y0 = _coordY0 + _lengthLine * sin((180 - _angle) * (M_PI/180));
    return y0;
}


double GraphicNode::getCoordRightChildX0() {
    double x0 = _coordX0 + _lengthLine * cos(_angle * (M_PI/180));
    return x0;
}


double GraphicNode::getCoordRightChildY0() {
    double y0 = _coordY0 + _lengthLine * sin(_angle * (M_PI/180));
    return y0;
}


GraphicNode * GraphicNode::getParent() {
    return _parent;
}


GraphicNode * GraphicNode::getLeftChild() {
    return _leftChild;
}


GraphicNode * GraphicNode::getRightChild() {
    return _rightChild;
}


void GraphicNode::makeBalanceCoordinate() {
    if (_parent) {
        double angle = _parent->getAngle();

        if (this == _parent->getLeftChild()) { angle = 180 - angle; }
        else if (this == _parent->getRightChild()) { }
        else { return; }

        double x0, y0;
        x0 = _parent->getCoordX0() + _parent->getLengthLine() * cos(angle * (M_PI/180));
        y0 = _parent->getCoordY0() + _parent->getLengthLine() * sin(angle * (M_PI/180));

        _coordX0 = x0;
        _coordY0 = y0;
    }
}


void GraphicNode::setDefaultLineLength() {
    if (_parent) {
        double lengthLine = _parent->getLengthLine();

        // Constant!
        _lengthLine = lengthLine / 2;
    }
}


void GraphicNode::setDefaultAngle() {
    if (_parent) {
        double angle = _parent->getAngle();

        // Constant!
        _angle = angle + 15;
    }
}

