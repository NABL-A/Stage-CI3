#include "SensorBackend.h"
#include <QtMath>

SensorBackend::SensorBackend(QObject *parent) : QObject(parent)
{
    serial.setPortName("COM4");
    serial.setBaudRate(QSerialPort::Baud9600);

    if (serial.open(QIODevice::ReadOnly))
        qDebug() << "Serial open: true";
    else
        qDebug() << "Serial open: false";

    connect(&serial, &QSerialPort::readyRead,
            this, &SensorBackend::readSerial);
}

void SensorBackend::updateFromSensors(float c1, float c2,float c3, float c4,float c5, float c6,float c7, float c8,float c9, float c10,float c11, float c12,float c13, float c14,float c15, float c16)
{
    // Normalise les valeurs brutes Arduino (0-1023) vers 0.0-1.0
    const float MAX_VAL = 1023.0f;

    float n1 = qBound(0.0f, c1 / MAX_VAL, 1.0f);
    float n2 = qBound(0.0f, c2 / MAX_VAL, 1.0f);
    float n3 = qBound(0.0f, c3 / MAX_VAL, 1.0f);
    float n4 = qBound(0.0f, c4 / MAX_VAL, 1.0f);
    float n5 = qBound(0.0f, c5 / MAX_VAL, 1.0f);
    float n6 = qBound(0.0f, c6 / MAX_VAL, 1.0f);
    float n7 = qBound(0.0f, c7 / MAX_VAL, 1.0f);
    float n8 = qBound(0.0f, c8 / MAX_VAL, 1.0f);
    float n9 = qBound(0.0f, c9 / MAX_VAL, 1.0f);
    float n10 = qBound(0.0f, c10 / MAX_VAL, 1.0f);
    float n11 = qBound(0.0f, c11 / MAX_VAL, 1.0f);
    float n12 = qBound(0.0f, c12 / MAX_VAL, 1.0f);
    float n13 = qBound(0.0f, c13 / MAX_VAL, 1.0f);
    float n14 = qBound(0.0f, c14 / MAX_VAL, 1.0f);
    float n15 = qBound(0.0f, c15 / MAX_VAL, 1.0f);
    float n16 = qBound(0.0f, c16 / MAX_VAL, 1.0f);

    m_c1 = n1;
    m_c2 = n2;
    m_c3 = n3;
    m_c4 = n4;
    m_c5 = n5;
    m_c6 = n6;
    m_c7 = n7;
    m_c8 = n8;
    m_c9 = n9;
    m_c10 = n10;
    m_c11 = n11;
    m_c12 = n12;
    m_c13 = n13;
    m_c14 = n14;
    m_c15 = n15;
    m_c16 = n16;

    emit dataChanged();
}

void SensorBackend::readSerial()
{
    buffer += serial.readAll();

    while (buffer.contains("\n"))
    {
        int idx = buffer.indexOf("\n");
        QString line = buffer.left(idx);
        buffer.remove(0, idx + 1);

        auto values = line.split("\t");

        if (values.size() == 16)
        {
            float c1 = values[0].toFloat();
            float c2 = values[1].toFloat();
            float c3 = values[2].toFloat();
            float c4 = values[3].toFloat();
            float c5 = values[4].toFloat();
            float c6 = values[5].toFloat();
            float c7 = values[6].toFloat();
            float c8 = values[7].toFloat();
            float c9 = values[8].toFloat();
            float c10 = values[9].toFloat();
            float c11 = values[10].toFloat();
            float c12 = values[11].toFloat();
            float c13 = values[12].toFloat();
            float c14 = values[13].toFloat();
            float c15 = values[14].toFloat();
            float c16 = values[15].toFloat();

            updateFromSensors(c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15, c16);
        }
    }
}