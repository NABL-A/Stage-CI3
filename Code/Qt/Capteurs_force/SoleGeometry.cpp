#include "SoleGeometry.h"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "tiny_gltf.h"

#include <cmath>

static float gaussian(float x, float z, QVector2D center, float amplitude, float sigma) {
    float dx = x - center.x();
    float dz = z - center.y();
    return amplitude * std::exp(-(dx*dx + dz*dz) / (2.0f * sigma * sigma));
}

SoleGeometry::SoleGeometry(QQuick3DObject *parent) : QQuick3DGeometry(parent) {}

void SoleGeometry::setSource(const QString &path) {
    if (m_source == path) return;
    m_source = path;
    loadGLB(path);
    emit sourceChanged();
}

void SoleGeometry::setSensor1(float v) {
    if (qFuzzyCompare(m_sensor1, v)) return;
    m_sensor1 = v;
    rebuild();
    emit sensor1Changed();
}

void SoleGeometry::setSensor2(float v) {
    if (qFuzzyCompare(m_sensor2, v)) return;
    m_sensor2 = v;
    rebuild();
    emit sensor2Changed();
}

void SoleGeometry::setSensor3(float v) {
    if (qFuzzyCompare(m_sensor3, v)) return;
    m_sensor3 = v;
    rebuild();
    emit sensor3Changed();
}

void SoleGeometry::setSensor4(float v) {
    if (qFuzzyCompare(m_sensor4, v)) return;
    m_sensor4 = v;
    rebuild();
    emit sensor4Changed();
}

void SoleGeometry::setSensor5(float v) {
    if (qFuzzyCompare(m_sensor5, v)) return;
    m_sensor5 = v;
    rebuild();
    emit sensor5Changed();
}

void SoleGeometry::setSensor6(float v) {
    if (qFuzzyCompare(m_sensor6, v)) return;
    m_sensor6 = v;
    rebuild();
    emit sensor6Changed();
}

void SoleGeometry::setSensor7(float v) {
    if (qFuzzyCompare(m_sensor7, v)) return;
    m_sensor7 = v;
    rebuild();
    emit sensor7Changed();
}

void SoleGeometry::setSensor8(float v) {
    if (qFuzzyCompare(m_sensor8, v)) return;
    m_sensor8 = v;
    rebuild();
    emit sensor8Changed();
}

void SoleGeometry::setSensor9(float v) {
    if (qFuzzyCompare(m_sensor9, v)) return;
    m_sensor9 = v;
    rebuild();
    emit sensor9Changed();
}

void SoleGeometry::setSensor10(float v) {
    if (qFuzzyCompare(m_sensor10, v)) return;
    m_sensor10 = v;
    rebuild();
    emit sensor10Changed();
}

void SoleGeometry::setSensor11(float v) {
    if (qFuzzyCompare(m_sensor11, v)) return;
    m_sensor11 = v;
    rebuild();
    emit sensor11Changed();
}

void SoleGeometry::setSensor12(float v) {
    if (qFuzzyCompare(m_sensor12, v)) return;
    m_sensor12 = v;
    rebuild();
    emit sensor12Changed();
}

void SoleGeometry::setSensor13(float v) {
    if (qFuzzyCompare(m_sensor13, v)) return;
    m_sensor13 = v;
    rebuild();
    emit sensor13Changed();
}

void SoleGeometry::setSensor14(float v) {
    if (qFuzzyCompare(m_sensor14, v)) return;
    m_sensor14 = v;
    rebuild();
    emit sensor14Changed();
}

void SoleGeometry::setSensor15(float v) {
    if (qFuzzyCompare(m_sensor15, v)) return;
    m_sensor15 = v;
    rebuild();
    emit sensor15Changed();
}

void SoleGeometry::setSensor16(float v) {
    if (qFuzzyCompare(m_sensor16, v)) return;
    m_sensor16 = v;
    rebuild();
    emit sensor16Changed();
}

void SoleGeometry::loadGLB(const QString &path) {
    tinygltf::Model model;
    tinygltf::TinyGLTF loader;
    std::string err, warn;

    // Charge le .glb
    bool ok = loader.LoadBinaryFromFile(&model, &err, &warn, path.toStdString());
    if (!ok) {
        qWarning() << "TinyGLTF error:" << QString::fromStdString(err);
        return;
    }

    m_baseVertices.clear();
    m_indices.clear();

    // Parcourt les meshes du fichier
    for (auto &mesh : model.meshes) {
        for (auto &primitive : mesh.primitives) {

            // --- Vertices ---
            const auto &posAccessor = model.accessors[primitive.attributes.at("POSITION")];
            const auto &posView     = model.bufferViews[posAccessor.bufferView];
            const auto &posBuffer   = model.buffers[posView.buffer];

            const float *positions = reinterpret_cast<const float*>(
                posBuffer.data.data() + posView.byteOffset + posAccessor.byteOffset
                );

            for (size_t i = 0; i < posAccessor.count; ++i) {
                m_baseVertices.append(QVector3D(
                    positions[i * 3 + 0],
                    positions[i * 3 + 1],
                    positions[i * 3 + 2]
                    ));
            }

            // --- UVs ---
            m_uvs.clear();
            if (primitive.attributes.count("TEXCOORD_0")) {
                const auto &uvAccessor = model.accessors[primitive.attributes.at("TEXCOORD_0")];
                const auto &uvView     = model.bufferViews[uvAccessor.bufferView];
                const auto &uvBuffer   = model.buffers[uvView.buffer];
                const float *uvData    = reinterpret_cast<const float*>(
                    uvBuffer.data.data() + uvView.byteOffset + uvAccessor.byteOffset);

                for (size_t i = 0; i < uvAccessor.count; ++i) {
                    m_uvs.append(QVector2D(uvData[i * 2 + 0], 1.0f - uvData[i * 2 + 1]));
                }
            } else {
                // Pas d'UVs dans le fichier, on remplit avec des zéros
                m_uvs.resize(m_baseVertices.size(), QVector2D(0, 0));
            }

            // --- Indices ---
            if (primitive.indices >= 0) {
                const auto &idxAccessor = model.accessors[primitive.indices];
                const auto &idxView     = model.bufferViews[idxAccessor.bufferView];
                const auto &idxBuffer   = model.buffers[idxView.buffer];
                const uint8_t *idxData  = idxBuffer.data.data() + idxView.byteOffset + idxAccessor.byteOffset;

                for (size_t i = 0; i < idxAccessor.count; ++i) {
                    // Les indices peuvent être sur 16 ou 32 bits
                    if (idxAccessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT) {
                        m_indices.append(reinterpret_cast<const quint16*>(idxData)[i]);
                    } else {
                        m_indices.append(reinterpret_cast<const quint32*>(idxData)[i]);
                    }
                }
            }
        }
    }

    m_baseNormals.resize(m_baseVertices.size(), QVector3D(0, 0, 0));
    for (int i = 0; i + 2 < m_indices.size(); i += 3) {
        quint32 i0 = m_indices[i], i1 = m_indices[i+1], i2 = m_indices[i+2];
        QVector3D edge1 = m_baseVertices[i1] - m_baseVertices[i0];
        QVector3D edge2 = m_baseVertices[i2] - m_baseVertices[i0];
        QVector3D normal = QVector3D::crossProduct(edge1, edge2).normalized();
        m_baseNormals[i0] += normal;
        m_baseNormals[i1] += normal;
        m_baseNormals[i2] += normal;
    }
    for (auto &n : m_baseNormals) n.normalize();


    m_indexData.resize(m_indices.size() * sizeof(quint32));
    memcpy(m_indexData.data(), m_indices.constData(), m_indexData.size());


    if (!model.images.empty()) {
        const auto &image = model.images[0];
        if (!image.image.empty()) {
            QImage qimg(
                reinterpret_cast<const uchar*>(image.image.data()),
                image.width,
                image.height,
                QImage::Format_RGBA8888
                );
            QString texPath = QStandardPaths::writableLocation(
                                  QStandardPaths::TempLocation) + "/sole_texture.png";
            qimg.save(texPath);
            m_texturePath = QUrl::fromLocalFile(texPath).toString();

            emit texturePathChanged();
        }
    }

    rebuild();
}

void SoleGeometry::rebuild() {
    if (m_baseVertices.isEmpty()) return;

    // --- Remplissage du buffer vertex ---
    QByteArray vertexData;

    // Resize pour 8 floats : position(3) + normale(3) + uv(2)

    vertexData.resize(m_baseVertices.size() * 8 * sizeof(float));
    float *vPtr = reinterpret_cast<float*>(vertexData.data());

    for (int i = 0; i < m_baseVertices.size(); ++i) {

        const QVector3D &v = m_baseVertices[i];

        if (v.y() == 0) {

            float x = v.x();
            float z = v.z();

            float dy = gaussian(x, z, m_pos1,  m_sensor1  * 0.5f, 0.1f)
                       + gaussian(x, z, m_pos2,  m_sensor2  * 0.5f, 0.1f)
                       + gaussian(x, z, m_pos3,  m_sensor3  * 0.5f, 0.1f)
                       + gaussian(x, z, m_pos4,  m_sensor4  * 0.5f, 0.1f)
                       + gaussian(x, z, m_pos5,  m_sensor5  * 0.5f, 0.1f)
                       + gaussian(x, z, m_pos6,  m_sensor6  * 0.5f, 0.1f)
                       + gaussian(x, z, m_pos7,  m_sensor7  * 0.5f, 0.1f)
                       + gaussian(x, z, m_pos8,  m_sensor8  * 0.5f, 0.1f)
                       + gaussian(x, z, m_pos9,  m_sensor9  * 0.5f, 0.1f)
                       + gaussian(x, z, m_pos10, m_sensor10 * 0.5f, 0.1f)
                       + gaussian(x, z, m_pos11, m_sensor11 * 0.5f, 0.1f)
                       + gaussian(x, z, m_pos12, m_sensor12 * 0.5f, 0.1f)
                       + gaussian(x, z, m_pos13, m_sensor13 * 0.5f, 0.1f)
                       + gaussian(x, z, m_pos14, m_sensor14 * 0.5f, 0.1f)
                       + gaussian(x, z, m_pos15, m_sensor15 * 0.5f, 0.1f)
                       + gaussian(x, z, m_pos16, m_sensor16 * 0.5f, 0.1f);
            *vPtr++ = x;
            *vPtr++ = v.y() + dy;
            *vPtr++ = z;
            *vPtr++ = m_baseNormals[i].x();
            *vPtr++ = m_baseNormals[i].y();
            *vPtr++ = m_baseNormals[i].z();
            // Après les 6 floats existants, ajoute :
            *vPtr++ = m_uvs[i].x();
            *vPtr++ = m_uvs[i].y();
        }

        else {

            float x = v.x();
            float y = v.y();
            float z = v.z();


            *vPtr++ = x;
            *vPtr++ = y;
            *vPtr++ = z;
            *vPtr++ = m_baseNormals[i].x();
            *vPtr++ = m_baseNormals[i].y();
            *vPtr++ = m_baseNormals[i].z();
            *vPtr++ = m_uvs[i].x();
            *vPtr++ = m_uvs[i].y();

        }
    }


    // --- Envoi à Qt3D ---
    clear();


    addAttribute(QQuick3DGeometry::Attribute::PositionSemantic,  0,                 QQuick3DGeometry::Attribute::F32Type);
    addAttribute(QQuick3DGeometry::Attribute::NormalSemantic,    3 * sizeof(float), QQuick3DGeometry::Attribute::F32Type);
    addAttribute(QQuick3DGeometry::Attribute::TexCoordSemantic,  6 * sizeof(float), QQuick3DGeometry::Attribute::F32Type);
    addAttribute(QQuick3DGeometry::Attribute::IndexSemantic,     0,                 QQuick3DGeometry::Attribute::U32Type);
    setStride(8 * sizeof(float));
    setVertexData(vertexData);
    setIndexData(m_indexData);
    setPrimitiveType(QQuick3DGeometry::PrimitiveType::Triangles);
    update();
}