import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import App 1.0

Page {
    required property var stackView

    signal registerRequested(UserViewModel userViewModel)
    signal goToLogin()

    function setError(message) {
        errorText.text = message
    }

    background: Rectangle {
        color: "#050505"
    }

    UserViewModel{
        id: registerUserModel
    }

    Rectangle {
        anchors.fill: parent
        color: "transparent"

        Rectangle {
            width: 460
            height: 760
            anchors.centerIn: parent
            radius: 20
            color: "#121212"
            border.color: "#252525"
            border.width: 1

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 32
                spacing: 18

                Item {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 10
                }

                Rectangle {
                    Layout.alignment: Qt.AlignHCenter
                    width: 72
                    height: 72
                    radius: 16
                    color: "#17361F"
                    border.color: "#22C55E"
                    border.width: 1

                    Text {
                        anchors.centerIn: parent
                        text: "AC"
                        color: "#22C55E"
                        font.pixelSize: 24
                        font.bold: true
                    }
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 10

                    Text {
                        Layout.alignment: Qt.AlignHCenter
                        Layout.fillWidth: true
                        horizontalAlignment: Text.AlignHCenter

                        text: "Create Account"
                        color: "#F2F2F2"
                        font.pixelSize: 28
                        font.bold: true
                    }

                    Text {
                        Layout.alignment: Qt.AlignHCenter
                        Layout.fillWidth: true
                        horizontalAlignment: Text.AlignHCenter

                        text: "Register to continue to Assignment Coordinator"
                        color: "#9A9A9A"
                        font.pixelSize: 14
                        wrapMode: Text.WordWrap
                    }
                }

                Item {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 4
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 10

                    Text {
                        text: "First Name"
                        color: "#F2F2F2"
                        font.pixelSize: 14
                        font.bold: true
                    }

                    TextField {
                        id: firstNameField
                        text: registerUserModel.firstName
                        onTextChanged: registerUserModel.firstName = text
                        Layout.fillWidth: true
                        Layout.preferredHeight: 50
                        placeholderText: "Enter your first name"
                        color: "#F2F2F2"
                        selectionColor: "#3B82F6"
                        selectedTextColor: "#FFFFFF"
                        placeholderTextColor: "#707070"

                        background: Rectangle {
                            radius: 12
                            color: "#151515"
                            border.color: firstNameField.activeFocus ? "#3B82F6" : "#252525"
                            border.width: 1
                        }
                    }
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 10

                    Text {
                        text: "Last Name"
                        color: "#F2F2F2"
                        font.pixelSize: 14
                        font.bold: true
                    }

                    TextField {
                        id: lastNameField
                        text: registerUserModel.lastName
                        onTextChanged: registerUserModel.lastName = text
                        Layout.fillWidth: true
                        Layout.preferredHeight: 50
                        placeholderText: "Enter your last name"
                        color: "#F2F2F2"
                        selectionColor: "#3B82F6"
                        selectedTextColor: "#FFFFFF"
                        placeholderTextColor: "#707070"
                        background: Rectangle {
                            radius: 12
                            color: "#151515"
                            border.color: lastNameField.activeFocus ? "#3B82F6" : "#252525"
                            border.width: 1
                        }
                    }
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 10

                    Text {
                        text: "Email"
                        color: "#F2F2F2"
                        font.pixelSize: 14
                        font.bold: true
                    }

                    TextField {
                        id: emailField
                        text: registerUserModel.email
                        onTextChanged: registerUserModel.email = text
                        Layout.fillWidth: true
                        Layout.preferredHeight: 50
                        placeholderText: "Enter your email"
                        color: "#F2F2F2"
                        selectionColor: "#3B82F6"
                        selectedTextColor: "#FFFFFF"
                        placeholderTextColor: "#707070"

                        background: Rectangle {
                            radius: 12
                            color: "#151515"
                            border.color: emailField.activeFocus ? "#3B82F6" : "#252525"
                            border.width: 1
                        }
                    }
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 10

                    Text {
                        text: "Password"
                        color: "#F2F2F2"
                        font.pixelSize: 14
                        font.bold: true
                    }

                    TextField {
                        id: passwordField
                        text: registerUserModel.password
                        onTextChanged: registerUserModel.password = text
                        Layout.fillWidth: true
                        Layout.preferredHeight: 50
                        placeholderText: "Enter your password"
                        echoMode: TextInput.Password
                        color: "#F2F2F2"
                        selectionColor: "#3B82F6"
                        selectedTextColor: "#FFFFFF"
                        placeholderTextColor: "#707070"

                        background: Rectangle {
                            radius: 12
                            color: "#151515"
                            border.color: passwordField.activeFocus ? "#3B82F6" : "#252525"
                            border.width: 1
                        }
                    }
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 10

                    Text {
                        text: "Confirm Password"
                        color: "#F2F2F2"
                        font.pixelSize: 14
                        font.bold: true
                    }

                    TextField {
                        id: confirmPasswordField

                        Layout.fillWidth: true
                        Layout.preferredHeight: 50
                        placeholderText: "Confirm your password"
                        echoMode: TextInput.Password
                        color: "#F2F2F2"
                        selectionColor: "#3B82F6"
                        selectedTextColor: "#FFFFFF"
                        placeholderTextColor: "#707070"

                        background: Rectangle {
                            radius: 12
                            color: "#151515"
                            border.color: confirmPasswordField.activeFocus ? "#3B82F6" : "#252525"
                            border.width: 1
                        }

                        onAccepted: {
                            errorText.text = ""

                            if (passwordField.text !== confirmPasswordField.text) {
                                errorText.text = "Passwords do not match"
                                return
                            }

                            registerRequested(
                                userViewModel
                            )
                        }
                    }
                }

                Text {
                    id: errorText
                    Layout.fillWidth: true
                    visible: text.length > 0
                    text: ""
                    color: "#EF4444"
                    font.pixelSize: 13
                    wrapMode: Text.WordWrap
                }

                Button {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 52
                    text: "Register"

                    background: Rectangle {
                        radius: 12
                        color: parent.down ? "#1da851" : "#22C55E"
                        border.color: "#22C55E"
                        border.width: 1
                    }

                    contentItem: Text {
                        text: parent.text
                        color: "#04130A"
                        font.pixelSize: 15
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    onClicked: {
                        errorText.text = ""

                        if (passwordField.text !== confirmPasswordField.text) {
                            errorText.text = "Passwords do not match"
                            return
                        }

                        registerRequested(
                            registerUserModel
                        )
                    }
                }

                Button {
                    Layout.alignment: Qt.AlignHCenter
                    text: "Already have an account? Login"

                    background: Rectangle {
                        color: "transparent"
                    }

                    contentItem: Text {
                        text: parent.text
                        color: "#9A9A9A"
                        font.pixelSize: 13
                        horizontalAlignment: Text.AlignHCenter
                    }

                    onClicked: goToLogin()
                }

                Item {
                    Layout.fillHeight: true
                }

                Text {
                    Layout.alignment: Qt.AlignHCenter
                    text: "Assignment Coordinator v1.0"
                    color: "#9A9A9A"
                    font.pixelSize: 12
                }
            }
        }
    }
}