import QtQuick
import QtQuick3D

Node {
    id: node

    // Resources
    PrincipledMaterial {
        id: principledMaterial
        metalness: 1
        roughness: 1
        alphaMode: PrincipledMaterial.Opaque
    }

    // Nodes:
    Model {
        id: plane_003
        objectName: "Plane.003"
        source: "meshes/plane_006_mesh.mesh"
        materials: [
            principledMaterial
        ]
    }

    // Animations:
}
