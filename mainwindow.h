#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include <QVector>
#include <QTimer>
#include <QResizeEvent>
#include "gamemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void coordinatesUpdater();
private:
    Ui::MainWindow *ui;
    GameManager *game;
    QTimer *hunterTimer;
    QLabel *resultOverlay;
    bool gameFinished;
    QVector<QLabel*> hunterWidgets;
    QVector<QLabel*> visionWidgets;
    QVector<QLabel*> itemWidgets;
    void actualizarUI();
    void crearWidgetsEntidades();
    void verificarEstadoJuego();
    void mostrarResultado(const QString& mensaje);
};
#endif // MAINWINDOW_H
