#include "mainwindow.h"

#include <QApplication>
#include <QCoreApplication>
#include <QMqttClient>
#include <QMqttSubscription>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QMqttClient client;
    client.setHostname("mqtt://192.168.0.11");
    client.setPort(1883);
    client.setUsername("VPJ");
    client.setPassword("R462");
    client.connectToHost();

    QMqttTopicFilter topic("$SYS/broker/messages");
    client.subscribe(topic, 0);

    QObject::connect(&client, &QMqttClient::messageReceived, [](const QByteArray &message, const QMqttTopicName &topic) {
        qDebug() << "Message received:" << message << "on topic" << topic;
    });

    if (client.state() == QMqttClient::Connected) {
            qDebug() << "Successfully connected to the broker!";
        } else {
            qDebug() << "Failed to connect to the broker.";
        }

    qDebug() << "Debug check";

    const QByteArray payload = "Hello, MQTT!";
    const quint8 qos = 0;
    const bool retain = true;
    const QMqttTopicName topicname = QMqttTopicName("$SYS/broker/messages");

    auto publishResult = client.publish(topicname, payload, qos, retain);

    //w.show();
    // teeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeest
    // loooooooool
    // check
    return a.exec();
}
