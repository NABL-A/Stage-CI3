#ifndef SENSORBACKEND_H
#define SENSORBACKEND_H

#endif // SENSORBACKEND_H

#pragma once
#include <QObject>
#include <QVector3D>
#include <QVariantList>
#include <QSerialPort>


class SensorBackend : public QObject
{
    Q_OBJECT

public:
    explicit SensorBackend(QObject *parent = nullptr);

    Q_PROPERTY(float capteur1 READ lectureCapteur1 NOTIFY dataChanged)
    Q_PROPERTY(float capteur2 READ lectureCapteur2 NOTIFY dataChanged)
    Q_PROPERTY(float capteur3 READ lectureCapteur3 NOTIFY dataChanged)
    Q_PROPERTY(float capteur4 READ lectureCapteur4 NOTIFY dataChanged)
    Q_PROPERTY(float capteur5 READ lectureCapteur5 NOTIFY dataChanged)
    Q_PROPERTY(float capteur6 READ lectureCapteur6 NOTIFY dataChanged)
    Q_PROPERTY(float capteur7 READ lectureCapteur7 NOTIFY dataChanged)
    Q_PROPERTY(float capteur8 READ lectureCapteur8 NOTIFY dataChanged)
    Q_PROPERTY(float capteur9 READ lectureCapteur9 NOTIFY dataChanged)
    Q_PROPERTY(float capteur10 READ lectureCapteur10 NOTIFY dataChanged)
    Q_PROPERTY(float capteur11 READ lectureCapteur11 NOTIFY dataChanged)
    Q_PROPERTY(float capteur12 READ lectureCapteur12 NOTIFY dataChanged)
    Q_PROPERTY(float capteur13 READ lectureCapteur13 NOTIFY dataChanged)
    Q_PROPERTY(float capteur14 READ lectureCapteur14 NOTIFY dataChanged)
    Q_PROPERTY(float capteur15 READ lectureCapteur15 NOTIFY dataChanged)
    Q_PROPERTY(float capteur16 READ lectureCapteur16 NOTIFY dataChanged)


signals:
    void capteursChanged();
    void dataChanged();

public:
    float lectureCapteur1() const { return m_c1; }
    float lectureCapteur2() const { return m_c2; }
    float lectureCapteur3() const { return m_c3; }
    float lectureCapteur4() const { return m_c4; }
    float lectureCapteur5() const { return m_c5; }
    float lectureCapteur6() const { return m_c6; }
    float lectureCapteur7() const { return m_c7; }
    float lectureCapteur8() const { return m_c8; }
    float lectureCapteur9() const { return m_c9; }
    float lectureCapteur10() const { return m_c10; }
    float lectureCapteur11() const { return m_c11; }
    float lectureCapteur12() const { return m_c12; }
    float lectureCapteur13() const { return m_c13; }
    float lectureCapteur14() const { return m_c14; }
    float lectureCapteur15() const { return m_c15; }
    float lectureCapteur16() const { return m_c16; }


private slots:
    void readSerial();

private:
    void updateFromSensors(float c1, float c2, float c3, float c4, float c5, float c6, float c7, float c8, float c9, float c10, float c11, float c12, float c13, float c14, float c15, float c16);

    QSerialPort serial;
    QString buffer;

    float m_c1 = 0;
    float m_c2 = 0;
    float m_c3 = 0;
    float m_c4 = 0;
    float m_c5 = 0;
    float m_c6 = 0;
    float m_c7 = 0;
    float m_c8 = 0;
    float m_c9 = 0;
    float m_c10 = 0;
    float m_c11 = 0;
    float m_c12 = 0;
    float m_c13 = 0;
    float m_c14 = 0;
    float m_c15 = 0;
    float m_c16 = 0;


};