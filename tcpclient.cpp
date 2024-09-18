#include "tcpclient.h"
#include "ui_tcpclient.h"
#include <QByteArray>
#include <QDebug>
#include <QMessageBox>

TcpClient::TcpClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TcpClient)
{
    ui->setupUi(this);
    loadConfig();
}

TcpClient::~TcpClient()
{
    delete ui;
}

void TcpClient::loadConfig()
{
    // Load the file.
    QFile file(":/client.config");

    // Open file.
    if (file.open(QIODevice::ReadOnly))
    {
        // Read the file into string.
        QByteArray baData = file.readAll();
        QString strData = baData.toStdString().c_str();

        // Close file.
        file.close();

        // Split the string.
        strData.replace("\r\n", " ");
        qDebug() << strData;
        QStringList strList = strData.split(" ");

        m_strIP = strList.at(0);
        m_usPort = strList.at(1).toUShort();
        qDebug() << "ip: " << m_strIP << " port: " << m_usPort;
    }
    else
    {
        QMessageBox::critical(this, "open config", "open config failed");
    }
}
