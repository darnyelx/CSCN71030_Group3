import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import App 1.0
import "Store" 1.0


Page {
    required property var stackView

    id: mainView


    AssignmentViewModel {
        id: createAssignment
        userId: UserStore.currentUser.id
    }

    Component.onCompleted: {
        courseViewController.getCourses()
        assignmentController.getUserAssignments(UserStore.id)
    }

    Connections {
        target: assignmentController

        function onCreateAssignmentSuccess() {
            titleField.text = ""
            descriptionField.text = ""
            dueDateField.text = ""
            courseList.currentIndex = -1
            priorityCombo.currentIndex = 0
            statusCombo.currentIndex = 0

            createAssignment.title = ""
            createAssignment.description = ""
            createAssignment.dueDate = ""
            createAssignment.courseId = -1
            createAssignment.priority = 1
        }

        function onCreateAssignmentError(message) {
            console.log("Create assignment failed:", message)
        }

        function onUserAssignmentGetError(message) {
            console.log("Get assignments failed:", message)
        }
    }

    Rectangle {
        anchors.fill: parent
        color: bgColor

        Flickable {
            anchors.fill: parent
            contentWidth: width
            contentHeight: rootColumn.implicitHeight + 60
            clip: true

            Column {
                id: rootColumn
                width: parent.width - 120
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 34
                spacing: 28

                RowLayout {
                    width: parent.width
                    spacing: 20

                    Row {
                        spacing: 16
                        Layout.alignment: Qt.AlignVCenter

                        Rectangle {
                            width: 56
                            height: 56
                            radius: 16
                            color: green

                            Text {
                                anchors.centerIn: parent
                                text: "▤"
                                color: "#06250F"
                                font.pixelSize: 24
                                font.bold: true
                            }
                        }

                        Text {
                            text: "Assignment Coordinator"
                            color: textPrimary
                            font.pixelSize: 26
                            font.bold: true
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }

                    Item { Layout.fillWidth: true }

                    Row {
                        spacing: 18

                        Repeater {
                            model: [
                                { value: "0", label: "TOTAL" },
                                { value: "0", label: "PENDING" },
                                { value: "0", label: "COMPLETED" }
                            ]

                            delegate: Rectangle {
                                width: 110
                                height: 86
                                radius: 14
                                color: panelColor
                                border.color: borderColor
                                border.width: 1

                                Column {
                                    anchors.centerIn: parent
                                    spacing: 8

                                    Text {
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        text: modelData.value
                                        color: green
                                        font.pixelSize: 26
                                        font.bold: true
                                    }

                                    Text {
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        text: modelData.label
                                        color: textSecondary
                                        font.pixelSize: 16
                                        font.capitalization: Font.AllUppercase
                                    }
                                }
                            }
                        }

                        Rectangle {
                            width: 170
                            height: 64
                            radius: 14
                            color: panelColor
                            border.color: borderColor
                            border.width: 1

                            Row {
                                anchors.fill: parent
                                anchors.margins: 14
                                spacing: 12

                                Rectangle {
                                    width: 38
                                    height: 38
                                    radius: 19
                                    color: green

                                    Text {
                                        anchors.centerIn: parent
                                        text: "U"
                                        color: "#06250F"
                                        font.bold: true
                                        font.pixelSize: 18
                                    }
                                }

                                Text {
                                    text: "User"
                                    color: textPrimary
                                    font.pixelSize: 18
                                    anchors.verticalCenter: parent.verticalCenter
                                }

                                Item { width: 10 }

                                Text {
                                    text: "⇥"
                                    color: textSecondary
                                    font.pixelSize: 22
                                    anchors.verticalCenter: parent.verticalCenter
                                }
                            }
                        }
                    }
                }

                Rectangle {
                    width: parent.width
                    height: 1
                    color: "#1C1C1C"
                }

                RowLayout {
                    width: parent.width
                    spacing: 34
                    Layout.fillWidth: true

                    Rectangle {
                        Layout.preferredWidth: 430
                        Layout.fillHeight: true
                        radius: 22
                        color: panelColor
                        border.color: borderColor
                        border.width: 1

                        Column {
                            anchors.fill: parent
                            anchors.margins: 26
                            spacing: 18

                            Row {
                                spacing: 12

                                Rectangle {
                                    width: 40
                                    height: 40
                                    radius: 12
                                    color: greenDark

                                    Text {
                                        anchors.centerIn: parent
                                        text: "+"
                                        color: green
                                        font.pixelSize: 24
                                    }
                                }

                                Text {
                                    text: "Add New Assignment"
                                    color: textPrimary
                                    font.pixelSize: 22
                                    font.bold: true
                                    anchors.verticalCenter: parent.verticalCenter
                                }
                            }

                            Text {
                                text: "Assignment Title"
                                color: "#D4D4D4"
                                font.pixelSize: 16
                                font.bold: true
                            }

                            Rectangle {
                                width: parent.width
                                height: 54
                                radius: 12
                                color: "#050505"
                                border.color: borderColor
                                border.width: 1

                                TextField {
                                    id: titleField
                                    anchors.fill: parent
                                    anchors.margins: 12
                                    placeholderText: "Enter assignment title"
                                    color: textPrimary
                                    placeholderTextColor: "#6F6F6F"
                                    background: Item {}

                                    onTextChanged: createAssignment.title = text
                                }
                            }

                            Text {
                                text: "Subject"
                                color: "#D4D4D4"
                                font.pixelSize: 16
                                font.bold: true
                            }

                            ComboBox {
                                id: courseList
                                width: parent.width
                                height: 54
                                model: courseViewController.courseModel
                                textRole: "name"
                                currentIndex: -1

                                background: Rectangle {
                                    radius: 12
                                    color: "#050505"
                                    border.color: borderColor
                                    border.width: 1
                                }

                                contentItem: Text {
                                    leftPadding: 14
                                    rightPadding: 30
                                    verticalAlignment: Text.AlignVCenter
                                    text: courseList.currentIndex < 0
                                        ? "Select subject"
                                        : courseList.displayText
                                    color: textPrimary
                                    font.pixelSize: 16
                                }

                                onActivated: {
                                    const selectedCourse = courseViewController.courseModel.get(currentIndex)
                                    createAssignment.courseId = selectedCourse ? selectedCourse.id : -1
                                }
                            }

                            Text {
                                text: "Description"
                                color: "#D4D4D4"
                                font.pixelSize: 16
                                font.bold: true
                            }

                            Rectangle {
                                width: parent.width
                                height: 136
                                radius: 12
                                color: "#050505"
                                border.color: borderColor
                                border.width: 1

                                TextArea {
                                    id: descriptionField
                                    anchors.fill: parent
                                    anchors.margins: 12
                                    wrapMode: TextEdit.Wrap
                                    placeholderText: "Describe the assignment details"
                                    placeholderTextColor: "#6F6F6F"
                                    color: textPrimary
                                    background: Item {}

                                    onTextChanged: createAssignment.description = text
                                }
                            }

                            Row {
                                width: parent.width
                                spacing: 18

                                Column {
                                    width: (parent.width - 18) / 2
                                    spacing: 10

                                    Text {
                                        text: "Due Date"
                                        color: "#D4D4D4"
                                        font.pixelSize: 16
                                        font.bold: true
                                    }

                                    Rectangle {
                                        width: parent.width
                                        height: 54
                                        radius: 12
                                        color: "#050505"
                                        border.color: borderColor
                                        border.width: 1

                                        TextField {
                                            id: dueDateField
                                            anchors.fill: parent
                                            anchors.margins: 12
                                            placeholderText: "yyyy-mm-dd"
                                            color: textPrimary
                                            placeholderTextColor: "#6F6F6F"
                                            background: Item {}

                                            onTextChanged: createAssignment.dueDate = text
                                        }
                                    }
                                }

                                Column {
                                    width: (parent.width - 18) / 2
                                    spacing: 10

                                    Text {
                                        text: "Priority"
                                        color: "#D4D4D4"
                                        font.pixelSize: 16
                                        font.bold: true
                                    }

                                    ComboBox {
                                        id: priorityCombo
                                        width: parent.width
                                        height: 54
                                        model: ["Low", "Medium", "High"]
                                        currentIndex: 0

                                        background: Rectangle {
                                            radius: 12
                                            color: "#050505"
                                            border.color: borderColor
                                            border.width: 1
                                        }

                                        contentItem: Text {
                                            leftPadding: 14
                                            rightPadding: 30
                                            verticalAlignment: Text.AlignVCenter
                                            text: priorityCombo.displayText
                                            color: textPrimary
                                            font.pixelSize: 16
                                        }

                                        onActivated: createAssignment.priority = currentIndex + 1
                                    }
                                }
                            }

                            Text {
                                text: "Status"
                                color: "#D4D4D4"
                                font.pixelSize: 16
                                font.bold: true
                            }

                            ComboBox {
                                id: statusCombo
                                width: parent.width
                                height: 54
                                model: ["Pending", "In Progress", "Completed"]

                                background: Rectangle {
                                    radius: 12
                                    color: "#050505"
                                    border.color: borderColor
                                    border.width: 1
                                }

                                contentItem: Text {
                                    leftPadding: 14
                                    rightPadding: 30
                                    verticalAlignment: Text.AlignVCenter
                                    text: statusCombo.displayText
                                    color: textPrimary
                                    font.pixelSize: 16
                                }
                            }

                            Rectangle {
                                width: parent.width
                                height: 58
                                radius: 12
                                color: green

                                Text {
                                    anchors.centerIn: parent
                                    text: "+  Add Assignment"
                                    color: "#07240F"
                                    font.pixelSize: 20
                                    font.bold: true
                                }

                                MouseArea {
                                    anchors.fill: parent
                                    cursorShape: Qt.PointingHandCursor
                                    onClicked: {
                                        assignmentController.createAssignment(
                                          createAssignment
                                        )
                                    }
                                }
                            }
                        }
                    }

                    Column {
                        Layout.fillWidth: true
                        spacing: 18

                        Row {
                            width: parent.width

                            Text {
                                text: "Your Assignments"
                                color: textPrimary
                                font.pixelSize: 22
                                font.bold: true
                                anchors.verticalCenter: parent.verticalCenter
                            }

                            Item { width: 1; height: 1 }
                        }

                        Rectangle {
                            width: parent.width
                            height: 64
                            radius: 14
                            color: panelColor
                            border.color: borderColor
                            border.width: 1

                            Row {
                                anchors.right: parent.right
                                anchors.rightMargin: 14
                                anchors.verticalCenter: parent.verticalCenter
                                spacing: 12

                                Repeater {
                                    model: ["All", "Pending", "In Progress", "Completed"]

                                    delegate: Rectangle {
                                        width: modelData === "In Progress" ? 126 : 92
                                        height: 42
                                        radius: 12
                                        color: index === 0 ? "#343434" : "transparent"
                                        border.color: index === 0 ? "#494949" : "transparent"
                                        border.width: 1

                                        Text {
                                            anchors.centerIn: parent
                                            text: modelData
                                            color: index === 0 ? textPrimary : "#B5B5B5"
                                            font.pixelSize: 16
                                        }

                                        MouseArea {
                                            anchors.fill: parent
                                            cursorShape: Qt.PointingHandCursor
                                        }
                                    }
                                }
                            }
                        }

                        Rectangle {
                            width: parent.width
                            height: 58
                            radius: 14
                            color: panelColor
                            border.color: borderColor
                            border.width: 1

                            Row {
                                anchors.fill: parent
                                anchors.leftMargin: 16
                                anchors.rightMargin: 16
                                spacing: 12

                                Text {
                                    text: "⌕"
                                    color: "#A3A3A3"
                                    font.pixelSize: 24
                                    anchors.verticalCenter: parent.verticalCenter
                                }

                                TextField {
                                    width: parent.width - 40
                                    anchors.verticalCenter: parent.verticalCenter
                                    placeholderText: "Search assignments..."
                                    placeholderTextColor: "#6F6F6F"
                                    color: textPrimary
                                    background: Item {}
                                }
                            }
                        }

                        Repeater {
                            model: assignmentController.assignmentModel

                            delegate: Rectangle {
                                width: parent.width
                                height: 210
                                radius: 20
                                color: cardColor
                                border.color: borderColor
                                border.width: 1

                                // ✅ Define missing properties
                                property string subject: "Course " + courseId   // or map later
                                property string status: "Pending"               // until you add it to model

                                property color dotColor: status === "Completed" ? green
                                    : status === "In Progress" ? blue
                                        : yellow

                                property color subjectBg: "#1E293B"
                                property color subjectText: "#93C5FD"

                                property color statusBg: status === "Completed" ? "#022C22"
                                    : status === "In Progress" ? "#1E3A8A"
                                        : "#3F2F0B"

                                property color statusText: status === "Completed" ? "#22C55E"
                                    : status === "In Progress" ? "#60A5FA"
                                        : "#F59E0B"

                                property color priorityColor: priority === 3 ? red
                                    : priority === 2 ? yellow
                                        : green

                                Column {
                                    anchors.fill: parent
                                    anchors.margins: 22
                                    spacing: 18

                                    Row {
                                        spacing: 14

                                        Rectangle {
                                            width: 14
                                            height: 14
                                            radius: 7
                                            color: dotColor
                                            anchors.verticalCenter: parent.verticalCenter
                                        }

                                        Text {
                                            text: title
                                            color: textPrimary
                                            font.pixelSize: 18
                                            font.bold: true
                                        }

                                        Rectangle {
                                            height: 30
                                            radius: 8
                                            color: subjectBg
                                            width: subjectLabel.implicitWidth + 24

                                            Text {
                                                anchors.centerIn: parent
                                                text: subject
                                                color: subjectText
                                                font.pixelSize: 14
                                                font.bold: true
                                            }

                                            Text {
                                                id: subjectLabel
                                                visible: false
                                                text: subject
                                            }
                                        }

                                        Rectangle {
                                            height: 30
                                            radius: 8
                                            color: statusBg
                                            width: statusLabel.implicitWidth + 24

                                            Text {
                                                anchors.centerIn: parent
                                                text: status
                                                color: statusText
                                                font.pixelSize: 14
                                                font.bold: true
                                            }

                                            Text {
                                                id: statusLabel
                                                visible: false
                                                text: status
                                            }
                                        }
                                    }

                                    Text {
                                        width: parent.width - 40
                                        text: description
                                        color: "#B9B9B9"
                                        wrapMode: Text.WordWrap
                                        font.pixelSize: 15
                                    }

                                    Row {
                                        spacing: 22

                                        Text {
                                            text: "◷ " + dueDate
                                            color: "#8D8D8D"
                                            font.pixelSize: 15
                                        }

                                        Text {
                                            text: "+ " + priority
                                            color: priorityColor
                                            font.pixelSize: 15
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}