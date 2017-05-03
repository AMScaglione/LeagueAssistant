#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <datagather.h>
#include <jsonfmcpp/nlohmann_json.hpp>
#include <champion.h>

bool gameWin = true;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    getMasterPlayerIDs();
}

void MainWindow::on_pushButton_4_clicked()
{
    getSeedPlayers();
}

void MainWindow::on_pushButton_5_clicked()
{
    getMatchData();
}

void MainWindow::on_pushButton_3_clicked()
{
    createBlank();
}

void MainWindow::on_pushButton_2_clicked()
{
    parseRawData();
}

//displays stats for given searched champion
void MainWindow::on_testbutton_clicked()
{
    json champions;
    std::ifstream i("./data/champion/champMatchStats.json");
    i >> champions;
    bool found = false;
    QString Qsearch = ui->lineEdit->text();
    std::string search = Qsearch.toStdString();
    search.erase(remove_if(search.begin(), search.end(), isspace), search.end()); //remove spaces
    search.erase(remove_if(search.begin(), search.end(), ispunct), search.end()); //remove punctuation
    for (json::iterator it = champions.begin(); it != champions.end(); ++it) {
        json temp = it.value();
        if(temp["id"] == search){
            found = true;
            break;
        }
    }
    if(found){
        champion current(search);
        std::string label = search + ": " + current.getTitle();
        ui->searchResultLabel->setText(QString::fromStdString(label));
        ui->armorLabel->setText(QString::fromStdString(current.getArmor()));
        ui->armorlevellabel->setText(QString::fromStdString(current.getArmorPerLevel()));
        ui->ADlabel->setText(QString::fromStdString(current.getAttackDamage()));
        ui->ADPLlabel->setText(QString::fromStdString(current.getAttackDamagePerLevel()));
        ui->rangelabel->setText(QString::fromStdString(current.getAttackRange()));
        ui->ASlabel->setText(QString::fromStdString(current.getAttackSpeedOffset()));
        ui->ASPLlabel->setText(QString::fromStdString(current.getAttackSpeedPerLevel()));
        ui->HPlabel->setText(QString::fromStdString(current.getHP()));
        ui->HPPLlabel->setText(QString::fromStdString(current.getHPPerLevel()));
        ui->HPRlabel->setText(QString::fromStdString(current.getHPRegen()));
        ui->HPRPLlabel->setText(QString::fromStdString(current.getHPRegenPerLevel()));
        ui->speedlabel->setText(QString::fromStdString(current.getMoveSpeed()));
        ui->manalabel->setText(QString::fromStdString(current.getMP()));
        ui->MPLlabel->setText(QString::fromStdString(current.getMPPerLevel()));
        ui->MRegenlabel->setText(QString::fromStdString(current.getMPRegen()));
        ui->MRPLlabel->setText(QString::fromStdString(current.getMPRegenPerLevel()));
        ui->MRlabel->setText(QString::fromStdString(current.getSpellBlock()));
        ui->MResistPLlabel->setText(QString::fromStdString(current.getSpellBlockPerLevel()));
        ui->winratelabel->setText(QString::fromStdString(current.getWinRate()));
        ui->playratelabel->setText(QString::fromStdString(current.getPlayRate()));
        ui->banratelabel->setText(QString::fromStdString(current.getBanRate()));
        ui->killlabel->setText(QString::fromStdString(current.getKills()));
        ui->deathlabel->setText(QString::fromStdString(current.getDeaths()));
        ui->assistlabel->setText(QString::fromStdString(current.getAssists()));
        ui->minionlabel->setText(QString::fromStdString(current.getMinionKills()));
        ui->towerlabel->setText(QString::fromStdString(current.getTowerKills()));
        ui->wardlabel->setText(QString::fromStdString(current.getWardsKilled()));
        ui->wardplacelabel->setText(QString::fromStdString(current.getWardsPlaced()));
        ui->goldlabel->setText(QString::fromStdString(current.getGoldEarned()));
        ui->PDDlabel->setText(QString::fromStdString(current.getPhysicalDamageDealt()));
        ui->PDTClabel->setText(QString::fromStdString(current.getPhysicalDamageDealtToChamps()));
        ui->PDTlabel->setText(QString::fromStdString(current.getPhysicalDamageTaken()));
        ui->MDDlabel->setText(QString::fromStdString(current.getMagicDamageDealt()));
        ui->MDTClabel->setText(QString::fromStdString(current.getMagicDamageDealtToChamps()));
        ui->MDTlabel->setText(QString::fromStdString(current.getMagicDamageTaken()));
        ui->TDDlabel->setText(QString::fromStdString(current.getTrueDamageDealt()));
        ui->TDTClabel->setText(QString::fromStdString(current.getTrueDamageDealtToChamps()));
        ui->TDTlabel->setText(QString::fromStdString(current.getTrueDamageTaken()));
        ui->LCSlabel->setText(QString::fromStdString(current.getLargestCriticalStrike()));
        ui->CCDlabel->setText(QString::fromStdString(current.getCrowdControlDealt()));
        ui->HDlabel->setText(QString::fromStdString(current.getHealingDone()));
        ui->DKlabel->setText(QString::fromStdString(current.getDoubleKills()));
        ui->TKlabel->setText(QString::fromStdString(current.getTripleKills()));
        ui->QKlabel->setText(QString::fromStdString(current.getQuadraKills()));
        ui->PKlabel->setText(QString::fromStdString(current.getPentaKills()));
    }else{
        ui->searchResultLabel->setText("Champion Not Found!");
    }
}


//saves note into json file
void MainWindow::on_pushButton_8_clicked()
{
    json notes;
    std::ifstream i("./data/Notes/notes.json");
    i >> notes;
    json tempNote;
    tempNote["win"] = gameWin;
    std::string name = ui->champNameEdit->text().toStdString();
    tempNote["champion"] = ui->champNameEdit->text().toStdString();
    std::string note = ui->plainTextEdit->toPlainText().toStdString();
    tempNote["note"] = ui->plainTextEdit->toPlainText().toStdString();
    notes["notes"][IntToString(notes["currentIndex"])] = tempNote;
    notes["currentIndex"] = notes["currentIndex"].get<int>() + 1;

    std::ofstream o("./data/Notes/notes.json");
    o << std::setw(4) << notes << std::endl;
}

void MainWindow::on_pushButton_6_clicked()
{
    gameWin = true;
}

void MainWindow::on_pushButton_7_clicked()
{
    gameWin = false;
}
