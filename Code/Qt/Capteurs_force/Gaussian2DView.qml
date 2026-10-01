import QtQuick
import QtQuick.Layouts

Item {
    Layout.fillWidth: true
    Layout.fillHeight: true

    Image {
        id: insoleImg
        anchors.fill: parent
        source: "qrc:/qt/qml/Capteurs_force/images/insole.png"
        fillMode: Image.PreserveAspectFit
        opacity: 0.9
    }

    Canvas {
        id: canvas
        anchors.fill: parent

        onPaint: {
            var ctx = getContext("2d")
            ctx.clearRect(0,0,width,height)

            drawSensor(width * 0.45, height * 0.15, sensorBackend.capteur1)
            drawSensor(width * 0.55, height * 0.15, sensorBackend.capteur2)
            drawSensor(width * 0.43, height * 0.29, sensorBackend.capteur3)
            drawSensor(width * 0.50, height * 0.29, sensorBackend.capteur4)
            drawSensor(width * 0.57, height * 0.29, sensorBackend.capteur5)
            drawSensor(width * 0.43, height * 0.43, sensorBackend.capteur6)
            drawSensor(width * 0.50, height * 0.43, sensorBackend.capteur7)
            drawSensor(width * 0.57, height * 0.43, sensorBackend.capteur8)
            drawSensor(width * 0.43, height * 0.57, sensorBackend.capteur9)
            drawSensor(width * 0.50, height * 0.57, sensorBackend.capteur10)
            drawSensor(width * 0.57, height * 0.57, sensorBackend.capteur11)
            drawSensor(width * 0.43, height * 0.71, sensorBackend.capteur12)
            drawSensor(width * 0.50, height * 0.71, sensorBackend.capteur13)
            drawSensor(width * 0.57, height * 0.71, sensorBackend.capteur14)
            drawSensor(width * 0.45, height * 0.85, sensorBackend.capteur15)
            drawSensor(width * 0.55, height * 0.85, sensorBackend.capteur16)
        }

        function drawSensor(x, y, value)
        {
            var ctx = getContext("2d")

            // normalisation pression (0 / 1)
            var norm = Math.min(value, 1.0)

            // interpolation blanc / rouge
            var r = 255
            var g = Math.floor(255 * (1 - norm))
            var b = Math.floor(255 * (1 - norm))

            var fillColor = "rgb(" + r + "," + g + "," + b + ")"

            var radius = 15  // taille du point

            // cercle
            ctx.beginPath()
            ctx.arc(x, y, radius, 0, 2 * Math.PI)
            ctx.fillStyle = fillColor
            ctx.fill()

            // contour noir
            ctx.lineWidth = 2
            ctx.strokeStyle = "black"
            ctx.stroke()
        }

        Connections {
            target: sensorBackend
            function onDataChanged() {
                canvas.requestPaint()
            }
        }
    }
}