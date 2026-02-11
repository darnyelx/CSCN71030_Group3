import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 640
    height: 480
    visible: true
    title: "Simple Todo App"

    ListModel { id: todoModel }

Component.onCompleted: {

    todoModel.append({
        textInput: "Shopping List",
        status: "Pending",
        items: [
            { text: "Egg", status: "Done" },
            { text: "Beans", status: "Pending" },
            { text: "Garri", status: "Done" },
            { text: "Rice", status: "Pending" },
            { text: "Tomatoes", status: "Pending" }
        ]
    })

    todoModel.append({
        textInput: "Finish assignment",
        status: "Pending",
        items: [
            { text: "Write introduction", status: "Done" },
            { text: "Solve Question 3", status: "Pending" },
            { text: "Add references", status: "Pending" },
            { text: "Final review", status: "Pending" }
        ]
    })

    todoModel.append({
        textInput: "Church / Worship",
        status: "Pending",
        items: [
            { text: "Practice tenor line", status: "Pending" },
            { text: "Prepare song list", status: "Done" },
            { text: "Midweek rehearsal 6:30PM", status: "Pending" }
        ]
    })

    todoModel.append({
        textInput: "Personal Development",
        status: "Pending",
        items: [
            { text: "Revamp LinkedIn headline", status: "Done" },
            { text: "Apply to 2 jobs", status: "Pending" },
            { text: "Read 20 pages", status: "Pending" }
        ]
    })

    todoModel.append({
        textInput: "Fitness",
        status: "Done",
        items: [
            { text: "30 min walk", status: "Done" },
            { text: "Stretching", status: "Done" }
        ]
    })
}


    function addTodo() {
        const t = input.text.trim()
        if (t.length === 0) return
        console.log(t, "t")
        todoModel.append({ "text": t, "status": "Pending" })
        input.text = ""
        input.forceActiveFocus()
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 12

        RowLayout {
            spacing: 10

            TextField {
                id: input
                Layout.fillWidth: true
                placeholderText: "Enter a new todo item"
                padding: 12
                leftPadding: 14
                rightPadding: 14
                topPadding: 10
                bottomPadding: 10
                onAccepted: addBtn.click()
            }

            Button {
                id: addBtn
                text: "Add"
                onClicked: {
                     const textInput = input.text.trim()
                    if (textInput.length === 0) return
                    todoModel.append({ "textInput": textInput, "status": "Pending" })
                    input.text = ""
                    input.forceActiveFocus()
                }

                background: Rectangle {
                    radius: 6
                    color: "#2e7d32"
                }
                contentItem: Text {
                    text: parent.text
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }

        Label {
            visible: todoModel.count === 0
            text: "No todos yet. Add one above"
            opacity: 0.7
            color: "black";
        }

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: todoModel
            clip: true
            spacing: 8

            delegate: Rectangle {
                width: ListView.view.width
                height: 50
                radius: 6
                color: "#1f1f1f"

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 10
                    spacing: 10

                    Text {
                        Layout.fillWidth: true
                        text: textInput           
                        color: "#ffffff"
                        opacity: status === "Done" ? 0.5 : 1.0
                        elide: Text.ElideRight
                    }

                    Button {
                        text: status
                        onClicked: {
                            const next = (status === "Pending" ? "Done" : "Pending")
                            todoModel.setProperty(index, "status", next)
                        }
                    }

                    Button {
                        text: "Delete"
                        onClicked: todoModel.remove(index)
                    }
                }
                Repeater {
                        model: items
                        delegate: Text {
                            text: "• " + modelData.text + " (" + modelData.status + ")"
                            color: modelData.status === "Done" ? "#888" : "#fff"
                        }
                    }
            }
        }
    }

    ListView {
    anchors.fill: parent
    model: nameModel
    delegate: nameDelegate
    focus: true
    highlight: Rectangle {
        color: "lightblue"
        width: parent.width
    }
    section {
        property: "team"
        criteria: ViewSection.FullString
        delegate: Rectangle {
            color: "#b0dfb0"
            width: parent.width
            height: childrenRect.height + 4
            Text { anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: 16
                font.bold: true
                text: section
            }
        }
    }
}
}
