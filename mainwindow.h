#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "workshop.h"
#include <QtWidgets/QLineEdit>
#include "statistics.h"
#include <QSound>
#include <QMediaPlayer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



    private slots:

        void on_Add_WorkShop_clicked();

        void on_edit_workshop_clicked();

        void on_reset_workshop_edit_clicked();

        void on_delete_workshop_clicked();

        void on_reset_workshop_delete_clicked();


        void on_reset_workshop_add_clicked();

        void on_yes_reservation_workshop_clicked();

        void on_no_reservation_workshop_clicked();

        void on_yes_reservation_workshop_edit_clicked();

        void on_no_reservation_workshop_edit_clicked();

        void on_rechercherf_clicked();

        void on_reafficherf_clicked();

        void on_Statistics_clicked();

        void on_ouvrir_media_clicked();

        void on_play_media_clicked();

        void on_pause_media_clicked();

        void on_stop_media_clicked();

        void on_mute_media_clicked();

        void on_volume_media_valueChanged(int value);

        void on_export2_2_clicked();

private:
    Ui::MainWindow *ui;
    Workshop W;
    QSound *son;
    QMediaPlayer musicAdd;
    QMediaPlayer *mMediaPlayer;
    QMediaPlayer *med;


};
#endif // MAINWINDOW_H
