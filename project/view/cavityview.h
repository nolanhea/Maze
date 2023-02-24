#ifndef CAVITYVIEW_H
#define CAVITYVIEW_H

#include <QLabel>
#include "../cavity/cavitygenerator.h"
#include <QRgb>
class CavityView : public QLabel
{
    Q_OBJECT
public:
    CavityView(QWidget *parent = nullptr);
    void setCavityGenerator(CavityGenerator *c);
    void drawCavity();
    bool nextStep();

signals:
    void cavityFinished();

private:
    CavityGenerator *cavityGenerator;
};

#endif // CAVITYVIEW_H
