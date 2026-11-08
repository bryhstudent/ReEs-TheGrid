#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <algorithm> // Necesario para std::clamp
#include <QPixmap>
#include "commonhunter.h"
#include "elitehunter.h"
#include "frag.h"
#include "pem.h"

using namespace std;

const int ESCALA = 40;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    game = new GameManager();
    hunterTimer = nullptr;
    resultOverlay = nullptr;
    gameFinished = false;
    ui->player->setFixedSize(28, 42);
    game->getPlayer()->setWidth(static_cast<float>(ui->player->width()) / ESCALA);
    game->getPlayer()->setHeight(static_cast<float>(ui->player->height()) / ESCALA);
    this->setFocusPolicy(Qt::StrongFocus);
    crearWidgetsEntidades();
    actualizarUI(); // Sincroniza imagen y CoordinatesLabel al iniciar
    hunterTimer = new QTimer(this);
    connect(hunterTimer, &QTimer::timeout, this, [this]() {
        game->updateHunters(0.04f);
        game->checkCollisions();
        actualizarUI();
        verificarEstadoJuego();
    });
    hunterTimer->start(40);
}

MainWindow::~MainWindow()
{
    delete game;
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (gameFinished) return;
    float dx = 0.0f;
    float dy = 0.0f;

    switch (event->key()) {
    case Qt::Key_W: dy = -0.5f; break;
    case Qt::Key_S: dy =  0.5f; break;
    case Qt::Key_A: dx = -0.5f; break;
    case Qt::Key_D: dx =  0.5f; break;
    case Qt::Key_Up: dy = -0.5f; break;
    case Qt::Key_Down: dy = 0.5f; break;
    case Qt::Key_Left: dx = -0.5f; break;
    case Qt::Key_Right: dx = 0.5f; break;
    default:
        QMainWindow::keyPressEvent(event);
        return;
    }

    // 1. Mueve el objeto lógico
    game->processPlayerMovement(dx, dy);

    // 2. Calcula los límites máximos en coordenadas lógicas
    float maxX = static_cast<float>(ui->centralwidget->width() - ui->player->width()) / ESCALA;
    float maxY = static_cast<float>(ui->centralwidget->height() - ui->player->height()) / ESCALA;

    // 3. Restringe (clamp) la posición del jugador entre 0 y el máximo
    Player* p = game->getPlayer();
    p->setPosX(std::clamp(p->getPosX(), 0.0f, std::max(0.0f, maxX)));
    p->setPosY(std::clamp(p->getPosY(), 0.0f, std::max(0.0f, maxY)));

    game->checkCollisions();

    // 4. Actualiza la UI con las coordenadas ya corregidas
    actualizarUI();
    verificarEstadoJuego();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    if (resultOverlay) resultOverlay->setGeometry(ui->centralwidget->rect());
}

void MainWindow::actualizarUI()
{
    float x = game->getPlayer()->getPosX();
    float y = game->getPlayer()->getPosY();

    // 1. Mueve el sprite/imagen
    int pixelX = static_cast<int>(x * ESCALA);
    int pixelY = static_cast<int>(y * ESCALA);
    ui->player->move(pixelX, pixelY);

    // 2. Actualiza el texto de CoordinatesLabel
    const auto& hunters = game->getHunters();
    bool eliteDetecting = false;
    const bool huntersFrozen = game->getHuntersFreezeRemaining() > 0.0f;
    for (int i = 0; i < hunters.size(); ++i) {
        hunterWidgets[i]->move(qRound(hunters[i]->getPosX() * ESCALA),
                               qRound(hunters[i]->getPosY() * ESCALA));
        if (huntersFrozen) {
            hunterWidgets[i]->setStyleSheet("background:#145067;border:3px solid #32dcff;border-radius:7px;");
        } else if (dynamic_cast<EliteHunter*>(hunters[i])) {
            hunterWidgets[i]->setStyleSheet("border:3px solid #713bd1;border-radius:8px;");
        } else {
            hunterWidgets[i]->setStyleSheet("border:2px solid #a72f2f;border-radius:5px;");
        }
        if (visionWidgets[i]) {
            EliteHunter *elite = static_cast<EliteHunter*>(hunters[i]);
            const float radius = elite->getVisionRadius();
            const int diameter = qRound(radius * 2.0f * ESCALA);
            visionWidgets[i]->setGeometry(qRound((elite->getPosX() + elite->getWidth() / 2.0f) * ESCALA - diameter / 2.0f),
                                          qRound((elite->getPosY() + elite->getHeight() / 2.0f) * ESCALA - diameter / 2.0f),
                                          diameter, diameter);
            const bool detected = elite->drawRadius(x + game->getPlayer()->getWidth() / 2.0f,
                                                    y + game->getPlayer()->getHeight() / 2.0f);
            eliteDetecting = eliteDetecting || detected;
            const QString radiusStyle = QString("border-radius:%1px;").arg(diameter / 2);
            visionWidgets[i]->setStyleSheet(detected
                ? "background:rgba(220,70,70,35);border:2px dashed rgba(220,50,50,200);" + radiusStyle
                : "background:rgba(110,70,220,20);border:2px dashed rgba(110,70,220,150);" + radiusStyle);
            visionWidgets[i]->lower();
        }
    }
    const auto& items = game->getItems();
    for (int i = 0; i < items.size(); ++i) {
        itemWidgets[i]->move(qRound(items[i]->getPosX() * ESCALA),
                             qRound(items[i]->getPosY() * ESCALA));
        itemWidgets[i]->setVisible(!items[i]->getIsCollected());
    }
    const QString detectionStatus = eliteDetecting ? "   ¡Elite te detectó!" : "";
    const QString freezeStatus = huntersFrozen
        ? QString("   Cazadores congelados: %1 s").arg(game->getHuntersFreezeRemaining(), 0, 'f', 1)
        : QString();
    ui->CoordinatesLabel->setText(QString("Posición: (%1, %2)   Vidas: %3   Puntos: %4%5%6")
                                      .arg(x, 0, 'f', 1).arg(y, 0, 'f', 1)
                                      .arg(game->getPlayer()->getRemainingLifes())
                                      .arg(game->getPlayer()->getScore())
                                      .arg(detectionStatus).arg(freezeStatus));
    ui->CoordinatesLabel->adjustSize();
}

void MainWindow::crearWidgetsEntidades()
{
    const auto& hunters = game->getHunters();
    for (int i = 0; i < hunters.size(); ++i) {
        EliteHunter *elite = dynamic_cast<EliteHunter*>(hunters[i]);
        QLabel *vision = nullptr;
        if (elite) {
            vision = new QLabel(ui->centralwidget);
            vision->setObjectName(QString("eliteVision_%1").arg(i));
            const int diameter = qRound(elite->getVisionRadius() * 2.0f * ESCALA);
            vision->setFixedSize(diameter, diameter);
            vision->setStyleSheet(QString("background:rgba(110,70,220,20);border:2px dashed rgba(110,70,220,150);border-radius:%1px;")
                                      .arg(diameter / 2));
            vision->setAttribute(Qt::WA_TransparentForMouseEvents);
            vision->show();
        }
        visionWidgets.append(vision);

        QLabel *sprite = new QLabel(ui->centralwidget);
        sprite->setObjectName(QString("hunter_%1").arg(i));
        sprite->setGeometry(0, 0, 26, 26);
        QPixmap pixmap(":/images/hunter");
        if (!pixmap.isNull()) {
            sprite->setPixmap(pixmap);
            sprite->setScaledContents(true);
        } else {
            sprite->setText("H");
            sprite->setAlignment(Qt::AlignCenter);
            sprite->setStyleSheet("background:#b23b3b;color:white;font-weight:bold;");
        }
        if (elite) {
            sprite->setStyleSheet("border:3px solid #713bd1;border-radius:8px;");
            sprite->setToolTip("Elite Hunter: rango de visión " + QString::number(elite->getVisionRadius(), 'f', 1));
        } else if (dynamic_cast<CommonHunter*>(hunters[i])) {
            sprite->setStyleSheet("border:2px solid #a72f2f;border-radius:5px;");
            sprite->setToolTip("Common Hunter");
        }
        sprite->show();
        hunterWidgets.append(sprite);
    }

    const auto& items = game->getItems();
    for (int i = 0; i < items.size(); ++i) {
        QLabel *sprite = new QLabel(ui->centralwidget);
        sprite->setObjectName(QString("item_%1").arg(i));
        sprite->setGeometry(0, 0, 18, 18);
        sprite->setAlignment(Qt::AlignCenter);
        if (dynamic_cast<Frag*>(items[i])) {
            sprite->setText("F");
            sprite->setStyleSheet("background:#57c765;color:#102d13;border:2px solid #277a32;border-radius:20px;font-weight:bold;");
            sprite->setToolTip("Frag: +" + QString::number(items[i]->getPointValue()) + " puntos");
        } else if (dynamic_cast<PEM*>(items[i])) {
            sprite->setText("P");
            sprite->setStyleSheet("background:#42c8d8;color:#10343a;border:2px solid #187b88;border-radius:20px;font-weight:bold;");
            sprite->setToolTip("PEM: +" + QString::number(items[i]->getPointValue())
                               + " puntos y congela a los cazadores por 5 segundos");
        }
        sprite->show();
        itemWidgets.append(sprite);
    }
}

void MainWindow::verificarEstadoJuego()
{
    if (gameFinished) return;
    if (game->getPlayer()->getRemainingLifes() <= 0) {
        mostrarResultado("GAME OVER");
    } else if (game->allItemsCollected()) {
        mostrarResultado("¡Ganaste!");
    }
}

void MainWindow::mostrarResultado(const QString& mensaje)
{
    if (gameFinished) return;
    gameFinished = true;
    hunterTimer->stop();

    resultOverlay = new QLabel(mensaje, ui->centralwidget);
    resultOverlay->setObjectName("resultOverlay");
    resultOverlay->setGeometry(ui->centralwidget->rect());
    resultOverlay->setAlignment(Qt::AlignCenter);
    resultOverlay->setStyleSheet("background:rgba(0,0,0,190);color:white;font-size:48px;font-weight:bold;");
    resultOverlay->raise();
    resultOverlay->show();
}
