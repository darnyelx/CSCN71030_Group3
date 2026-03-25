import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window


  Page {
      id: mainView

      ListModel {
          id: assignmentModel

          ListElement {
              dotColor: "#3B82F6"
              title: "Essay on World War II"
              subject: "History"
              status: "In Progress"
              description: "Write a 2000-word essay analyzing the causes and consequences of World War II."
              dueDate: "Feb 5, 2026"
              priority: "High Priority"
              priorityColor: "#EF4444"
              subjectBg: "#153620"
              subjectText: "#22C55E"
              statusBg: "#1B2E4A"
              statusText: "#3B82F6"
          }

          ListElement {
              dotColor: "#F59E0B"
              title: "Calculus Problem Set 7"
              subject: "Mathematics"
              status: "Pending"
              description: "Complete problems 1–25 from Chapter 7: Integration by Parts."
              dueDate: "Feb 4, 2026"
              priority: "High Priority"
              priorityColor: "#EF4444"
              subjectBg: "#153620"
              subjectText: "#22C55E"
              statusBg: "#4A3412"
              statusText: "#F59E0B"
          }

          ListElement {
              dotColor: "#F59E0B"
              title: "Lab Report: Chemical Reactions"
              subject: "Chemistry"
              status: "Pending"
              description: "Document the results of the titration experiment. Include graphs and error analysis."
              dueDate: "Feb 7, 2026"
              priority: "Medium Priority"
              priorityColor: "#F59E0B"
              subjectBg: "#153620"
              subjectText: "#22C55E"
              statusBg: "#4A3412"
              statusText: "#F59E0B"
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

                              function labelText(t) {
                                  return Qt.createQmlObject(`
                                    import QtQuick
                                    Text {
                                        text: "${t}"
                                        color: "#D4D4D4"
                                        font.pixelSize: 16
                                        font.bold: true
                                    }
                                `, parent)
                              }

                              Text { text: "Assignment Title"; color: "#D4D4D4"; font.pixelSize: 16; font.bold: true }

                              Rectangle {
                                  width: parent.width
                                  height: 54
                                  radius: 12
                                  color: "#050505"
                                  border.color: borderColor
                                  border.width: 1

                                  TextField {
                                      anchors.fill: parent
                                      anchors.margins: 12
                                      placeholderText: "Enter assignment title"
                                      color: textPrimary
                                      placeholderTextColor: "#6F6F6F"
                                      background: Item {}
                                  }
                              }

                              Text { text: "Subject"; color: "#D4D4D4"; font.pixelSize: 16; font.bold: true }

                              ComboBox {
                                  width: parent.width
                                  height: 54
                                  model: ["Select subject", "History", "Mathematics", "Chemistry", "Biology", "English"]

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
                                      text: parent.displayText
                                      color: textPrimary
                                      font.pixelSize: 16
                                  }
                              }

                              Text { text: "Description"; color: "#D4D4D4"; font.pixelSize: 16; font.bold: true }

                              Rectangle {
                                  width: parent.width
                                  height: 136
                                  radius: 12
                                  color: "#050505"
                                  border.color: borderColor
                                  border.width: 1

                                  TextArea {
                                      anchors.fill: parent
                                      anchors.margins: 12
                                      wrapMode: TextEdit.Wrap
                                      placeholderText: "Describe the assignment details"
                                      placeholderTextColor: "#6F6F6F"
                                      color: textPrimary
                                      background: Item {}
                                  }
                              }

                              Row {
                                  width: parent.width
                                  spacing: 18

                                  Column {
                                      width: (parent.width - 18) / 2
                                      spacing: 10

                                      Text { text: "Due Date"; color: "#D4D4D4"; font.pixelSize: 16; font.bold: true }

                                      Rectangle {
                                          width: parent.width
                                          height: 54
                                          radius: 12
                                          color: "#050505"
                                          border.color: borderColor
                                          border.width: 1

                                          TextField {
                                              anchors.fill: parent
                                              anchors.margins: 12
                                              placeholderText: "yyyy-mm-dd"
                                              color: textPrimary
                                              placeholderTextColor: "#6F6F6F"
                                              background: Item {}
                                          }
                                      }
                                  }

                                  Column {
                                      width: (parent.width - 18) / 2
                                      spacing: 10

                                      Text { text: "Priority"; color: "#D4D4D4"; font.pixelSize: 16; font.bold: true }

                                      ComboBox {
                                          width: parent.width
                                          height: 54
                                          model: ["Low", "Medium", "High"]

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
                                              text: parent.displayText
                                              color: textPrimary
                                              font.pixelSize: 16
                                          }
                                      }
                                  }
                              }

                              Text { text: "Status"; color: "#D4D4D4"; font.pixelSize: 16; font.bold: true }

                              ComboBox {
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
                                      text: parent.displayText
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
                              model: assignmentModel

                              delegate: Rectangle {
                                  width: parent.width
                                  height: 210
                                  radius: 20
                                  color: cardColor
                                  border.color: borderColor
                                  border.width: 1

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

                                              Text {
                                                  anchors.centerIn: parent
                                                  text: subject
                                                  color: subjectText
                                                  font.pixelSize: 14
                                                  font.bold: true
                                              }

                                              width: subjectLabel.implicitWidth + 24

                                              Text {
                                                  id: subjectLabel
                                                  visible: false
                                                  text: subject
                                                  font.pixelSize: 14
                                                  font.bold: true
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
                                                  font.pixelSize: 14
                                                  font.bold: true
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

                                      Rectangle {
                                          width: parent.width
                                          height: 1
                                          color: "#242424"
                                      }

                                      Row {
                                          spacing: 12

                                          Rectangle {
                                              width: 138
                                              height: 42
                                              radius: 10
                                              color: greenDark
                                              border.color: "#1F6C3A"
                                              border.width: 1

                                              Text {
                                                  anchors.centerIn: parent
                                                  text: "⚗  Request Help"
                                                  color: green
                                                  font.pixelSize: 15
                                                  font.bold: true
                                              }

                                              MouseArea {
                                                  anchors.fill: parent
                                                  cursorShape: Qt.PointingHandCursor
                                              }
                                          }

                                          Rectangle {
                                              width: 42
                                              height: 42
                                              radius: 10
                                              color: "#1C1C1C"
                                              border.color: "#2B2B2B"
                                              border.width: 1

                                              Text {
                                                  anchors.centerIn: parent
                                                  text: "✎"
                                                  color: "#CFCFCF"
                                                  font.pixelSize: 18
                                              }

                                              MouseArea {
                                                  anchors.fill: parent
                                                  cursorShape: Qt.PointingHandCursor
                                              }
                                          }

                                          Rectangle {
                                              width: 42
                                              height: 42
                                              radius: 10
                                              color: "#1C1C1C"
                                              border.color: "#2B2B2B"
                                              border.width: 1

                                              Text {
                                                  anchors.centerIn: parent
                                                  text: "🗑"
                                                  color: "#CFCFCF"
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
                          }
                      }
                  }
              }
          }
      }
  }

