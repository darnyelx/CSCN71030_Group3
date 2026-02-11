import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 640
    height: 480
    visible: true
    title: "Simple Todo App"

    ListModel {
        id: todoModel
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 12
        RowLayout {
            
            spacing: 10

            TextField {
                id: input
                padding: 20
                Layout.fillWidth: true
                placeholderText: "Enters a new todo item"
                onAccepted: addBtn.clicked()
            }

            Button {
                id: addBtn
                text: "Add"
                background: Rectangle{
                    color: "green"
                    radius: 6
                }
                onClicked: {
                    const t = input.text.trim();
                    
                    if (t.length > 0) {
                        //add it to the model
                        todoModel.append({"text": t, "status": "Pending"});
                        input.text = "";
                        input.forceActiveFocus();
                    }
                }
            }
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
                radius: 4
                color: "#1f1f1f"

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 10
                    spacing: 10

                    Text {
                        Layout.fillWidth: true
                        text: model.text
                        color: "#ffffff"
                        opacity: model.status === "Done"? 0.5 : 1.0
                        elide: Text.ElideRight
                    }

                    Button {
                        text: model.status
                        onClicked: {
                            const next = (model.status === "Pending" ? "Done" : "Pending")
                            todoModel.setProperty(index, "status", next)
                        }
                    }

                    Button {
                        text: "Delete"
                        onClicked: todoModel.remove(index)
                    }
                }
            }
        }
    }

}
