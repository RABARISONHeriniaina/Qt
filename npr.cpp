#include "npr.h"
#include "ui_npr.h"

#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDebug>
#include <QUrl>
#include <QFileDialog>
#include <QMessageBox>
npr::npr(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::npr)
{
    ui->setupUi(this);

    player = new QMediaPlayer;
    QVideoWidget *vw = new QVideoWidget(this);

    player->setVideoOutput(vw); //for the video

    this->setCentralWidget(vw);
    vw->setStyleSheet("background-color:black");

    qDebug()<< (player->state());

    connect(ui->horizontalSlider,&QSlider::sliderMoved,player,&QMediaPlayer::setPosition);

    connect(player,&QMediaPlayer::positionChanged,ui->horizontalSlider,&QSlider::setValue);

    connect(player,&QMediaPlayer::durationChanged,ui->horizontalSlider,&QSlider::setMaximum);

    ui->statusbar->addPermanentWidget(ui->label);
    ui->statusbar->addPermanentWidget(ui->horizontalSlider,1);
    ui->statusbar->addPermanentWidget(ui->label_2);

    ui->label_3->setText(QString::number(100) + "% Volume");

    maxTemps = 0;
    ui->toolBar->addWidget(ui->label_3);

    //pour le volume

    volume = 100;

    this->setWindowFlag(Qt::WindowStaysOnTopHint);

    ui->verticalSlider->setValue(player->volume());
    connect(ui->verticalSlider,&QSlider::valueChanged,player,&QMediaPlayer::setVolume);

}

npr::~npr()
{
    delete ui;
}

QString npr::calculeSeconde(int sec)
{
    QString text,minutee,secondee;
    int minute = sec / 60;
    int seconde = sec % 60;

    if(minute >= 0 && minute < 10)
    {
        minutee = "0" + QString::number(minute);
    }
    else
    {
        minutee = QString::number(minute);
    }

    if(seconde >= 0 && seconde < 10)
    {
        secondee = "0" + QString::number(seconde);
    }
    else
    {
        secondee = QString::number(seconde);
    }



    text = minutee +":"+ secondee;
    return text;
}


void npr::on_actionOuvrir_triggered()
{
    QString fileName  = QFileDialog::getOpenFileName(this,"Choisissez votre chanson","C:/","Tout les fichiers (*.*) ;;Tout les mp4 (*.mp4) ;;Tout les mkv (*.mkv)");
    player->setMedia(QUrl(fileName));
    player->play();
    volume = player->volume();
    QStringList lt = fileName.split("/");
    this->setWindowTitle(lt[lt.length()-1]);
    ui->label->setText(QString::number(player->position()));
    qDebug()<< (player->state());
    maxTemps = ui->horizontalSlider->maximum();
    ui->label_2->setText(QString::number(maxTemps));

}

void npr::on_actionStop_triggered()
{
    player->stop();
}

void npr::on_actionPlay_triggered()
{
    player->play();
}

void npr::on_actionPrev_triggered()
{
    player->setPosition(ui->horizontalSlider->value() - 10000);
}

void npr::on_actionPause_triggered()
{
    player->pause();
}

void npr::on_actionNext_triggered()
{
    player->setPosition(ui->horizontalSlider->value() + 10000);
}

void npr::on_actionMute_triggered()
{
    volume = 0;
    player->setVolume(volume);
    ui->label_3->setText(QString::number(volume) + "% Volume");
}

void npr::on_actionAugmenter_triggered()
{
    volume+=10;
    player->setVolume(volume);
    ui->label_3->setText(QString::number(volume) + "% Volume");
}

void npr::on_actionDiminuer_triggered()
{
    volume-=10;
    player->setVolume(volume);
    ui->label_3->setText(QString::number(volume) + "% Volume");
}

void npr::on_actionNormal_triggered()
{

    volume = 50;
    player->setVolume(volume);
    ui->label_3->setText(QString::number(volume) + "% Volume");
}

void npr::on_horizontalSlider_valueChanged(int value)
{
    ui->label->setText(calculeSeconde(value/1000));
}

void npr::on_horizontalSlider_rangeChanged(int min, int max)
{
    min++;
    ui->label_2->setText(calculeSeconde(max/1000));
}


void npr::on_actionNPR_triggered()
{
    player->pause();
    QMessageBox::about(this,"NPR","NPR<br/>Niah PlayeR(2020)");
    player->play();
}

void npr::on_actionRABARISON_Heriniaina_triggered()
{
    player->pause();
    QMessageBox::about(this,"RABARISON Heriniaina","Nom : RABARISON<br/>Prenom : Heriniaina<br/>Age : -- ans<br/>Developpeur<br/>Sns......");
    player->play();
}
