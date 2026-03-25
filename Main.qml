import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import "view/Store" 1.0

ApplicationWindow {
    id: window
    width: 1440
    height: 900
    visible: true
    title: "Assignment Coordinator"

    color: "#050505"

    property color bgColor: "#050505"
    property color panelColor: "#121212"
    property color cardColor: "#151515"
    property color borderColor: "#252525"
    property color textPrimary: "#F2F2F2"
    property color textSecondary: "#9A9A9A"
    property color green: "#22C55E"
    property color greenDark: "#17361F"
    property color blue: "#3B82F6"
    property color blueDark: "#1B2E4A"
    property color yellow: "#F59E0B"
    property color yellowDark: "#4A3412"
    property color red: "#EF4444"

    StackView {
        id: stack
        anchors.fill: parent

        initialItem: Login {
            stackView: stack

            onLoginRequested: function(email, password) {
                authViewController.login(email, password)
            }
        }
    }

    Connections {
        target: authViewController

        function onLoginSucceeded(user) {
            UserStore.login(user)
            stack.replace(Qt.resolvedUrl("view/AssignmentCoordinatorView.qml"), {
                stackView: stack
            })
        }

        function onLoginFailed(message) {
            if (stack.currentItem && stack.currentItem.setError) {
                stack.currentItem.setError(message)
            }
        }
    }
}