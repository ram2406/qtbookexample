#ifndef PLOTTER_H
#define PLOTTER_H

#include <QMap>
#include <QPixmap>
#include <QVector>
#include <QWidget>
#include <QThread>
#include <QTimer>


class QToolButton;
class PlotSettings;
class DrawPixmapThread;


class Plotter : public QWidget
{
    Q_OBJECT
public:
    explicit Plotter(QWidget *parent = 0);
    
    void setPlotSettings(const PlotSettings &settings);
    void setCurveData(int id, const QVector<QPointF> &data);
    void clearCurve(int id);
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void setTitle(const QString& title);
    void setVisibleCurve(int id, bool value);
    void setDrawNode(bool value);
    void setAxisName(const QString& nameX, const QString& nameY) { this->nameX = nameX; this->nameY = nameY;}
public slots:
    void zoomIn();
    void zoomOut();
    void setFastMode(bool value);
    void forceRefresh() {refreshPixmap(true);}
    void draw();
protected:
    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent *e);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);
    void wheelEvent(QWheelEvent *);

private:
    void updateRubberBandRegion();
    void refreshPixmap(bool force = false);
    void drawGrid(QPainter *painter);
    void drawCurves(QPainter *painter);

    QString title;
    QString nameX;
    QString nameY;

    void drawTitle(QPainter* painter);

    QToolButton *zoomInButton;
    QToolButton *zoomOutButton;
    QMap<int, QVector<QPointF> > curveMap;
    QMap<int, bool > curveMapVisible;
    QVector<PlotSettings> zoomStack;
    int curZoom;
    bool rubberBandIsShown;
    QRect rubberBandRect;
    QPixmap pixmap;

    bool drawNode, fastMode;

    enum { Margin = 50 };

    struct {
        QTimer *timer;
        bool timerEnable;
    };
    DrawPixmapThread *thread;

signals:
    
private slots:
    void timerEnd() { forceRefresh(); timer->stop();}

};

class PlotSettings
{
public:
    PlotSettings();

    void scroll(int dx, int dy);
    void adjust();
    double spanX() const { return maxX - minX ; }
    double spanY() const { return maxY - minY ; }
    double minX;
    double maxX;
    int numXTicks;
    double minY;
    double maxY;
    int numYTicks;

private :
    static void adjustAxis(double &min, double &max, int &numTicks);
};


#endif // PLOTTER_H
