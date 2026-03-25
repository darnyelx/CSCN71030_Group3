import QtQuick
import QtQuick.Controls

Page {
    required property var stackView

    signal loginRequested(string email, string password)

    function setError(message) {
        errorText.text = message
    }

    Rectangle {
        anchors.fill: parent
        color: "#050505"

        Column {
            anchors.centerIn: parent
            spacing: 16

            TextField {
                id: emailField
                width: 300
                placeholderText: "Email"
            }

            TextField {
                id: passwordField
                width: 300
                placeholderText: "Password"
                echoMode: TextInput.Password
            }

            Text {
                id: errorText
                color: "red"
                text: ""
            }

            Button {
                text: "Login"
                onClicked: {
                    errorText.text = ""
                    loginRequested(emailField.text, passwordField.text)
                }
            }
        }
    }
}