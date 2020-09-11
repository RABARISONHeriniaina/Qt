#ifndef NPR_H
#define NPR_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QSlider>

QT_BEGIN_NAMESPACE
namespace Ui { class npr; }
QT_END_NAMESPACE

class npr : public QMainWindow
{
    Q_OBJECT

public:
    npr(QWidget *parent = nullptr);
    ~npr();
    QString calculeSeconde(int sec);

private slots:

    void on_actionOuvrir_triggered();

    void on_actionStop_triggered();

    void on_actionPlay_triggered();

    void on_actionPrev_triggered();

    void on_actionPause_triggered();

    void on_actionNext_triggered();

    void on_actionMute_triggered();

    void on_actionAugmenter_triggered();

    void on_actionDiminuer_triggered();

    void on_actionNormal_triggered();

    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_rangeChanged(int min, int max);


    void on_actionNPR_triggered();

    void on_actionRABARISON_Heriniaina_triggered();

private:
    Ui::npr *ui;
    QMediaPlayer *player;
    QSlider *slider;
    int volume;
    int maxTemps;
};
#endif // NPR_H
