import QtQuick
import QtQuick3D
import QtQuick3D.Helpers
import QtQuick.Layouts
import Capteurs_force

Item {
    Layout.fillWidth: true
    Layout.fillHeight: true

    Connections {
        target: sensorBackend
        function onDataChanged() {
            soleGeo.sensor1 = sensorBackend.capteur1
            soleGeo.sensor2 = sensorBackend.capteur2
            soleGeo.sensor3 = sensorBackend.capteur3
            soleGeo.sensor4 = sensorBackend.capteur4
            soleGeo.sensor5 = sensorBackend.capteur5
            soleGeo.sensor6 = sensorBackend.capteur6
            soleGeo.sensor7 = sensorBackend.capteur7
            soleGeo.sensor8 = sensorBackend.capteur8
            soleGeo.sensor9 = sensorBackend.capteur9
            soleGeo.sensor10 = sensorBackend.capteur10
            soleGeo.sensor11 = sensorBackend.capteur11
            soleGeo.sensor12 = sensorBackend.capteur12
            soleGeo.sensor13 = sensorBackend.capteur13
            soleGeo.sensor14 = sensorBackend.capteur14
            soleGeo.sensor15 = sensorBackend.capteur15
            soleGeo.sensor16 = sensorBackend.capteur16
        }
    }

    View3D {
        id: view
        anchors.fill: parent

        environment: SceneEnvironment {
            clearColor: "#2d2d3a"
            backgroundMode: SceneEnvironment.Color
        }

        PerspectiveCamera {
            id: debugCam
            position: Qt.vector3d(0, 300, 500)
            eulerRotation.x: -30
            clipNear: 1
            clipFar: 5000
        }
        camera: debugCam

        DirectionalLight {
            eulerRotation.x: -45
            eulerRotation.y: 30
            brightness: 1.5
        }

        Model {
            scale: Qt.vector3d(100, 100, 100)
            geometry: SoleGeometry {
                id: soleGeo
                source: "C:/Users/alban/OneDrive/Documents/Pour Moi/Stage CI3/Code/Qt/Capteurs_force/mesh/Insole.glb" // à changer !
                sensor1: 0.0
                sensor2: 0.0
                sensor3: 0.0
                sensor4: 0.0
                sensor5: 0.0
                sensor6: 0.0
                sensor7: 0.0
                sensor8: 0.0
                sensor9: 0.0
                sensor10: 0.0
                sensor11: 0.0
                sensor12: 0.0
                sensor13: 0.0
                sensor14: 0.0
                sensor15: 0.0
                sensor16: 0.0
            }
            materials: PrincipledMaterial {
                id: soleMaterial
                roughness: 1.0
                metalness: 0.0
                baseColorMap: Texture {
                    id: soleTexture
                    source: soleGeo.texturePath !== "" ? soleGeo.texturePath : ""
                }
            }
        }

        Connections {
            target: soleGeo
            function onTexturePathChanged() {
                console.log("Texture chargée:", soleGeo.texturePath)
            }
        }

        //AxisHelper { enableXYGrid: true; enableAxisLines: true }
    }



    DebugView { source: view; anchors.top: parent.top; anchors.right: parent.right }

    WasdController { controlledObject: debugCam; speed: 1.0; shiftSpeed: 20.0 }

    Text {
        anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.margins: 12
        text: "WASD : déplacer  |  E/Q : monter/descendre  |  Shift : accélérer"
        color: "#aaaacc"; font.pixelSize: 13
    }
}