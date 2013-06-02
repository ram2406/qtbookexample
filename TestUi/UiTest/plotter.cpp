#include "plotter.h"
#include <QToolButton>
#include <QStylePainter>
#include <QStyleOptionFocusRect>
#include <QMouseEvent>
#include <cmath>
#include <QMapIterator>
#include <QDebug>
#include <QTimer>




Plotter::Plotter(QWidget *parent)
    : QWidget(parent), drawNode(false), fastMode(false)
    , timer(new QTimer(this)) , timerEnable(true)
{
    title = tr("График движения фрезы");
    setBackgroundRole(QPalette::Dark);
    setAutoFillBackground(true);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setFocusPolicy(Qt::StrongFocus);
    rubberBandIsShown = false;

    zoomInButton = new QToolButton(this);
    zoomInButton->setIcon(QIcon(":/images/zoomIn.png"));
    zoomInButton->adjustSize();
    connect(zoomInButton, SIGNAL(clicked()), this, SLOT(zoomIn()));

    zoomOutButton = new QToolButton(this);
    zoomOutButton->setIcon(QIcon(":/images/zoomout.png"));
    zoomOutButton->adjustSize();
    connect(zoomOutButton, SIGNAL(clicked()), this, SLOT(zoomOut()));

    setPlotSettings(PlotSettings());

    connect(timer, SIGNAL(timeout()) , this , SLOT(timerEnd()));

}



void Plotter::setPlotSettings(const PlotSettings &settings)
{
    zoomStack.clear();
    zoomStack.append(settings);
    curZoom = 0;
    zoomInButton->hide();
    zoomOutButton->hide();
    refreshPixmap();
}

void Plotter::setCurveData(int id, const QVector<QPointF> &data)
{
    curveMap[id] = data;

    refreshPixmap();
}

void Plotter::clearCurve(int id)
{
    curveMap.remove(id);
    refreshPixmap();
}

QSize Plotter::minimumSizeHint() const
{
    return QSize(6*Margin, 4 * Margin);
}

QSize Plotter::sizeHint() const
{
    return QSize(12* Margin, 8* Margin);
}

void Plotter::setTitle(const QString &title)
{
    this->title = title;
}

void Plotter::setVisibleCurve(int id, bool value)
{
    curveMapVisible[id] = value;
    refreshPixmap();
}

void Plotter::setDrawNode( bool value)
{
    drawNode = value;
    refreshPixmap();
}

void Plotter::setFastMode(bool value)
{
    this->fastMode = value;
    refreshPixmap();
}

void Plotter::zoomIn()
{
    if(curZoom < zoomStack.count() - 1) {
        ++curZoom;
        zoomInButton->setEnabled(curZoom < zoomStack.count() - 1);
        zoomOutButton->setEnabled(true);
        zoomOutButton->show();
        refreshPixmap();
    }
}

void Plotter::zoomOut()
{
    if(curZoom > 0){
        --curZoom;
        zoomOutButton->setEnabled(curZoom > 0);
        zoomInButton->setEnabled(true);
        zoomInButton->show();
        refreshPixmap();
    }
}

void Plotter::paintEvent(QPaintEvent *e)
{
    QStylePainter painter(this);
    painter.drawPixmap(0,0,pixmap);
    if(rubberBandIsShown) {
        painter.setPen(palette().light().color());
        painter.drawRect(rubberBandRect
                         .normalized()
                         .adjusted(0,0,-1,-1)
                         );
    }
    if(hasFocus()) {
        QStyleOptionFocusRect option;
        option.initFrom(this);
        option.backgroundColor = palette().dark().color();
        painter.drawPrimitive(QStyle::PE_FrameFocusRect, option);
    }
}

void Plotter::resizeEvent(QResizeEvent *e)
{
    int x = width() - (zoomInButton->width() + zoomOutButton->width() + 10);
    zoomInButton->move(x, 5);
    zoomOutButton->move(x + zoomInButton->width() + 5 , 5);
    refreshPixmap();
}

void Plotter::mousePressEvent(QMouseEvent *e)
{
    QRect rect(Margin, Margin, width() - 2*Margin, height() - 2*Margin);
    if(e->button() == Qt::LeftButton) {
        if(rect.contains(e->pos())) {
            rubberBandIsShown = true;
            rubberBandRect.setTopLeft(e->pos());
            rubberBandRect.setBottomRight(e->pos());
            updateRubberBandRegion();
            setCursor(Qt::CrossCursor);
        }
    }
}

void Plotter::mouseMoveEvent(QMouseEvent *e)
{
    if(rubberBandIsShown) {
        updateRubberBandRegion();
        rubberBandRect.setBottomRight(e->pos());
        updateRubberBandRegion();
    }
}

void Plotter::mouseReleaseEvent(QMouseEvent *e)
{
    if ((e->button() == Qt::LeftButton) && rubberBandIsShown) {
        rubberBandIsShown = false;
        updateRubberBandRegion();
        unsetCursor();
        QRect rect = rubberBandRect.normalized();
        if(rect.width() < 4 || rect.height() < 4)
            return;
        rect.translate(-Margin, -Margin);
        PlotSettings prevSettings = zoomStack[curZoom];
        PlotSettings settings;
        double dx = prevSettings.spanX() / (width() - 2*Margin);
        double dy = prevSettings.spanY() / (height() - 2*Margin);
        settings.minX = prevSettings.minX + dx * rect.left();
        settings.maxX = prevSettings.minX + dx * rect.right();
        settings.minY = prevSettings.maxY - dy * rect.bottom();
        settings.maxY = prevSettings.maxY - dy * rect.top();
        settings.adjust();
        zoomStack.resize(curZoom + 1);
        zoomStack.append(settings);
        zoomIn();
    }
}

void Plotter::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Left:
        zoomStack[curZoom].scroll(-1, 0);
        refreshPixmap();
        break;
    case Qt::Key_Right:
        zoomStack[curZoom].scroll(+1, 0);
        refreshPixmap();
        break;
    case Qt::Key_Down:
        zoomStack[curZoom].scroll(0, -1);
        refreshPixmap();
        break;
    case Qt::Key_Up:
        zoomStack[curZoom].scroll(0, +1);
        refreshPixmap();
        break;
    default:
        QWidget::keyPressEvent(e);
        break;
    }
}

void Plotter::wheelEvent(QWheelEvent *e)
{
    int numDegres = e->delta() / 8;
    int numTicks  = numDegres / 15;
    if (e->orientation() == Qt::Horizontal) {
        zoomStack[curZoom].scroll(numTicks , 0);
    }
    else {
        zoomStack[curZoom].scroll(0 , numTicks);
    }
    refreshPixmap();
}

void Plotter::updateRubberBandRegion()
{
    QRect rect = rubberBandRect.normalized();
    update(rect.left(), rect.top(), rect.width(), 1);
    update(rect.left(), rect.top(), 1, rect.height() );
    update(rect.left(), rect.bottom(), rect.width(), 1);
    update(rect.right(), rect.top(), 1, rect.height());
}

void Plotter::refreshPixmap(bool force)
{
    pixmap = QPixmap(size());
    pixmap.fill(Qt::darkGray);


    if(!force) {

        QPainter painter(&pixmap);
        painter.initFrom(this);
        painter.setOpacity(0.1);
        painter.drawImage(QPoint( width()/2 - 128 , height()/2 - 128), QImage(tr(":/images/refresh.png")) );
        timer->start(500);

        return;
    }

    draw();



}

void Plotter::drawGrid(QPainter *painter)
{
    QRect rect(Margin, Margin , width() - 2 * Margin, height() - 2*Margin);
    if (!rect.isValid()) {
        return;
    }
    PlotSettings settings = zoomStack[curZoom];
    QPen quiteDark = palette().dark().color().light();
    QPen light = palette().light().color();


    for (int ti = 0; ti < settings.numXTicks; ++ti) {
        int x  = rect.left() + (ti *(rect.width() - 1)
                               / settings.numXTicks);
        double label = settings.minX + (ti * settings.spanX()
                                        / settings.numXTicks);
        painter->setPen(quiteDark);
        painter->drawLine(x, rect.top(), x, rect.bottom());
        painter->setPen(light);
        painter->drawLine(x, rect.bottom(), x, rect.bottom() +3);
        painter->drawText(x - 50, rect.bottom() + 5, 100, 20
                          , Qt::AlignCenter | Qt::AlignTop
                          ,  QString::number(label));


    }

{
    QRect axisXrect = pixmap.rect();
    axisXrect.setTop(axisXrect.bottom() - Margin+3);
    axisXrect.setLeft(axisXrect.left() + Margin );
    //axisXrect.setSize(QSize(axisXrect.width(), Margin));
    painter->drawText(axisXrect
                      ,Qt::AlignLeft | Qt::AlignVCenter
                      ,  nameX);
}
    for (int ti = 0; ti < settings.numYTicks; ++ti) {
        int y = rect.bottom() -(ti * ( rect.height() -1)
                                / settings.numYTicks);
        double label = settings.minY + (ti* settings.spanY()
                                        / settings.numYTicks);

        painter->setPen(quiteDark);
        painter->drawLine(rect.left(), y, rect.right() , y);
        painter->setPen(light);
        painter->drawLine(rect.left()-3, y , rect.left(), y);
        painter->drawText(rect.left() - Margin, y -10, Margin -5, 20
                          , Qt::AlignRight | Qt::AlignVCenter
                          , QString::number(label));
    }
{
    QRect axisYrect = pixmap.rect();
    axisYrect.setTop(axisYrect.top() - Margin);

    axisYrect.setSize(QSize( Margin, axisYrect.height() - Margin));

    painter->save();
    QPoint p = axisYrect.topLeft();
    p.setX(p.x() + Margin/2 - 16);
    p.setY(p.y() + axisYrect.height());
    painter->translate(p);

    painter->rotate(-90);
    painter->drawText(0,0 ,  nameY);

    painter->restore();

}
    painter->drawRect(rect.adjusted(0,0,-1,-1));
}

void Plotter::drawCurves(QPainter *painter)
{
    static const QColor colorForIds[6] = {
        Qt::red  , Qt::green   , Qt::blue  ,
        Qt::cyan , Qt::magenta , Qt::yellow
    };
    PlotSettings settings= zoomStack[curZoom];
    QRect rect(Margin, Margin,
               width() - 2*Margin, height() - 2*Margin);
    if(!rect.isValid())
        return;

    painter->setClipRect(rect.adjusted(+1,+1,-1,-1));
    QMapIterator<int, QVector<QPointF> > i(curveMap);
    while(i.hasNext()) {
        i.next();
        int id =i.key();

        if(!curveMapVisible[id])
            continue;

        QVector<QPointF> data = i.value();
        QPolygonF polyline;
        polyline.reserve(data.count());

        for(int j = 0; j < data.count(); ++j) {
            double dx = data[j].x() - settings.minX;
            double dy = data[j].y() - settings.minY;
            double x = rect.left() + (dx *(rect.width() - 1)
                                      / settings.spanX());
            double y = rect.bottom() - (dy * (rect.height() -1)
                                      /settings.spanY());

            bool ignorePoint = !rect.contains(x,y);

            if(fastMode && ignorePoint)  continue;
            polyline.append(QPointF(x,y));

            if(drawNode && !ignorePoint) { //show points

                QPen pen(colorForIds[uint(id) % 6]);
                QBrush brush(pen.color());
                //pen.setWidth(10);

                painter->setPen(pen);

                painter->setBrush(brush);
                //painter->setOpacity(0.6);
                painter->drawEllipse(QPointF(x,y), 2,2);

            }

        }
        painter->setOpacity(1);
        painter->setPen(colorForIds[uint(id) % 6]);
        painter->drawPolyline(polyline);
    }
}

void Plotter::drawTitle(QPainter *painter)
{

    QPen quiteDark = palette().dark().color().light();
    qDebug() << title;
    painter->setFont(QFont("Arial", 16));
    painter->setPen(quiteDark);
    QRect rect =  pixmap.rect();
    rect.setHeight(Margin);
    painter->drawText(rect, Qt::AlignHCenter|Qt::AlignVCenter  , tr("%1" ).arg(title));



}

void Plotter::draw()
{
    QPainter painter(&pixmap);
    painter.initFrom(this);

    drawGrid(&painter);
    drawTitle(&painter);
    drawCurves(&painter);
    update();
}


PlotSettings::PlotSettings()
{
    minX = 0.0;
    maxX = 2000.0;
    numXTicks = 5;

    minY = 0.0;
    maxY = 2000.0;
    numYTicks = 5;
}

void PlotSettings::scroll(int dx, int dy)
{
    double stepX = spanX() / numXTicks;
    minX += dx * stepX;
    maxX += dx * stepX;

    double stepY = spanY() / numYTicks;
    minY += dy * stepY;
    maxY += dy * stepY;

}

void PlotSettings::adjust()
{
    adjustAxis(minX, maxX, numXTicks);
    adjustAxis(minY, maxY, numYTicks);
}

void PlotSettings::adjustAxis(double &min, double &max, int &numTicks)
{
    const int MinTicks = 4;
    double grossStep = (max - min) / MinTicks;
    double step =std::pow(10.0 , std::floor(std::log10(grossStep)));

    if(5* step < grossStep) {
        step *= 5;
    }
    else if(2 * step < grossStep) {
        step *= 2;
    }

    numTicks = int(std::ceil(max / step) - std::floor(min / step));
    if(numTicks < MinTicks)
        numTicks = MinTicks;

    min = std::floor(min / step) * step;
    max = std::ceil(max / step) * step;
}
