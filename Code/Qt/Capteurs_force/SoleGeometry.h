#pragma once
#include <QQuick3DGeometry>
#include <QVector3D>
#include <QVector2D>
#include <QQuick3DObject>
#include <QStandardPaths>
#include <QImage>


class SoleGeometry : public QQuick3DGeometry {
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(float sensor1 READ sensor1 WRITE setSensor1 NOTIFY sensor1Changed)
    Q_PROPERTY(float sensor2 READ sensor2 WRITE setSensor2 NOTIFY sensor2Changed)
    Q_PROPERTY(float sensor3 READ sensor3 WRITE setSensor3 NOTIFY sensor3Changed)
    Q_PROPERTY(float sensor4 READ sensor4 WRITE setSensor4 NOTIFY sensor4Changed)
    Q_PROPERTY(float sensor5 READ sensor5 WRITE setSensor5 NOTIFY sensor5Changed)
    Q_PROPERTY(float sensor6 READ sensor6 WRITE setSensor6 NOTIFY sensor6Changed)
    Q_PROPERTY(float sensor7 READ sensor7 WRITE setSensor7 NOTIFY sensor7Changed)
    Q_PROPERTY(float sensor8 READ sensor8 WRITE setSensor8 NOTIFY sensor8Changed)
    Q_PROPERTY(float sensor9 READ sensor9 WRITE setSensor9 NOTIFY sensor9Changed)
    Q_PROPERTY(float sensor10 READ sensor10 WRITE setSensor10 NOTIFY sensor10Changed)
    Q_PROPERTY(float sensor11 READ sensor11 WRITE setSensor11 NOTIFY sensor11Changed)
    Q_PROPERTY(float sensor12 READ sensor12 WRITE setSensor12 NOTIFY sensor12Changed)
    Q_PROPERTY(float sensor13 READ sensor13 WRITE setSensor13 NOTIFY sensor13Changed)
    Q_PROPERTY(float sensor14 READ sensor14 WRITE setSensor14 NOTIFY sensor14Changed)
    Q_PROPERTY(float sensor15 READ sensor15 WRITE setSensor15 NOTIFY sensor15Changed)
    Q_PROPERTY(float sensor16 READ sensor16 WRITE setSensor16 NOTIFY sensor16Changed)
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QString texturePath READ texturePath NOTIFY texturePathChanged)


public:
    explicit SoleGeometry(QQuick3DObject *parent = nullptr);

    float sensor1() const { return m_sensor1; }
    float sensor2() const { return m_sensor2; }
    float sensor3() const { return m_sensor3; }
    float sensor4() const { return m_sensor4; }
    float sensor5() const { return m_sensor5; }
    float sensor6() const { return m_sensor6; }
    float sensor7() const { return m_sensor7; }
    float sensor8() const { return m_sensor8; }
    float sensor9() const { return m_sensor9; }
    float sensor10() const { return m_sensor10; }
    float sensor11() const { return m_sensor11; }
    float sensor12() const { return m_sensor12; }
    float sensor13() const { return m_sensor13; }
    float sensor14() const { return m_sensor14; }
    float sensor15() const { return m_sensor15; }
    float sensor16() const { return m_sensor16; }
    QString source() const { return m_source; }
    QString texturePath() const { return m_texturePath; }

    void setSensor1(float v);
    void setSensor2(float v);
    void setSensor3(float v);
    void setSensor4(float v);
    void setSensor5(float v);
    void setSensor6(float v);
    void setSensor7(float v);
    void setSensor8(float v);
    void setSensor9(float v);
    void setSensor10(float v);
    void setSensor11(float v);
    void setSensor12(float v);
    void setSensor13(float v);
    void setSensor14(float v);
    void setSensor15(float v);
    void setSensor16(float v);
    void setSource(const QString &path);

signals:
    void sensor1Changed();
    void sensor2Changed();
    void sensor3Changed();
    void sensor4Changed();
    void sensor5Changed();
    void sensor6Changed();
    void sensor7Changed();
    void sensor8Changed();
    void sensor9Changed();
    void sensor10Changed();
    void sensor11Changed();
    void sensor12Changed();
    void sensor13Changed();
    void sensor14Changed();
    void sensor15Changed();
    void sensor16Changed();
    void sourceChanged();
    void texturePathChanged();

private:
    void loadGLB(const QString &path);
    void rebuild();

    float m_sensor1 = 0.0f;
    float m_sensor2 = 0.0f;
    float m_sensor3 = 0.0f;
    float m_sensor4 = 0.0f;
    float m_sensor5 = 0.0f;
    float m_sensor6 = 0.0f;
    float m_sensor7 = 0.0f;
    float m_sensor8 = 0.0f;
    float m_sensor9 = 0.0f;
    float m_sensor10 = 0.0f;
    float m_sensor11 = 0.0f;
    float m_sensor12 = 0.0f;
    float m_sensor13 = 0.0f;
    float m_sensor14 = 0.0f;
    float m_sensor15 = 0.0f;
    float m_sensor16 = 0.0f;
    QString m_source;

    // Vertices originaux chargés depuis le .glb (positions de base)
    QVector<QVector3D> m_baseVertices;
    QVector<quint32>   m_indices;

    // Positions fixes des deux capteurs sur la semelle 
    const QVector2D m_pos1 = { -0.30f,  -1.6f };   // avant-pied
    const QVector2D m_pos2 = { 0.30f, -1.6f };   // talon

    const QVector2D m_pos3 = { -0.50f,  -0.9f };   // avant-pied
    const QVector2D m_pos4 = { 0.0f, -0.9f };   // talon
    const QVector2D m_pos5 = { 0.50f,  -0.9f };   // avant-pied

    const QVector2D m_pos6 = { -0.50f, -0.2f };   // talon
    const QVector2D m_pos7 = { 0.0f,  -0.2f };   // avant-pied
    const QVector2D m_pos8 = { 0.50f, -0.2f };   // talon

    const QVector2D m_pos9 = { -0.40f,  0.5f };   // avant-pied
    const QVector2D m_pos10 = { 0.0f, 0.5f };   // talon
    const QVector2D m_pos11 = { 0.40f,  0.5f };   // avant-pied

    const QVector2D m_pos12 = { -0.30f, 1.2f };   // talon
    const QVector2D m_pos13 = { 0.0f,  1.2f };   // avant-pied
    const QVector2D m_pos14 = { 0.30f, 1.2f };   // talon

    const QVector2D m_pos15 = { -0.20f,  1.9f };   // avant-pied
    const QVector2D m_pos16 = { 0.30f, 1.9f };   // talon

    QVector<QVector2D> m_uvs;

    QVector<QVector3D> m_baseNormals;

    QByteArray m_indexData;

    QString m_texturePath;
};