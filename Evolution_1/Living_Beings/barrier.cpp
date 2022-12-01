#include "barrier.h"

Barrier::Barrier() {
    block = QRectF(-18, -22, 36, 60);
}

QRectF Barrier::boundingRect() {
    return block;
}

QPainterPath Barrier::boundingRect() {
}

