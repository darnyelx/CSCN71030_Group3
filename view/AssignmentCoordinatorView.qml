import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import App 1.0
import "Store" 1.0


Page {
    required property var stackView

    id: mainView

    property int editingAssignmentId: -1
    property int helpFormAssignmentId: -1
    property string helpModalAssignmentTitle: ""
    property string helpModalError: ""
    property int helpRequestsTab: 0

    function findCourseIndex(courseId) {
        if (courseId < 0)
            return -1
        let i = 0
        while (true) {
            const c = courseViewController.courseModel.get(i)
            if (!c)
                break
            if (c.id === courseId)
                return i
            i++
        }
        return -1
    }

    function assignmentStatusIndex(label) {
        const labels = ["Pending", "In Progress", "Completed"]
        for (let i = 0; i < labels.length; i++) {
            if (labels[i] === label)
                return i
        }
        return 0
    }

    function clearAssignmentForm() {
        editingAssignmentId = -1
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
        createAssignment.status = "Pending"
        statusCombo.currentIndex = 0
    }

    function loadAssignmentForEdit(row) {
        const vm = assignmentController.assignmentModel.get(row)
        if (!vm)
            return
        editingAssignmentId = vm.id
        titleField.text = vm.title
        descriptionField.text = vm.description
        dueDateField.text = vm.dueDate
        createAssignment.title = vm.title
        createAssignment.description = vm.description
        createAssignment.dueDate = vm.dueDate
        createAssignment.courseId = vm.courseId
        createAssignment.priority = Math.max(1, Math.min(3, vm.priority))
        priorityCombo.currentIndex = createAssignment.priority - 1
        courseList.currentIndex = findCourseIndex(vm.courseId)
        createAssignment.status = vm.status && vm.status.length > 0 ? vm.status : "Pending"
        statusCombo.currentIndex = mainView.assignmentStatusIndex(createAssignment.status)
    }

    function openHelpRequestModal(assignmentId, assignmentTitle) {
        helpFormAssignmentId = assignmentId
        helpModalAssignmentTitle = assignmentTitle ? assignmentTitle : ""
        helpModalError = ""
        helpMessageField.text = ""
        helpRequestModal.open()
    }

    AssignmentViewModel {
        id: createAssignment
        userId: UserStore.userId
    }

    Component.onCompleted: {
        console.log("User Store",UserStore.userId)
        courseViewController.getCourses()
        assignmentController.getUserAssignments(UserStore.userId)
        helpRequestController.loadHelpRequests(UserStore.userId)
        helpRequestController.loadOthersHelpRequests(UserStore.userId)
    }

    Connections {
        target: assignmentController

        function onCreateAssignmentSuccess() {
            console.log("User Store",UserStore.userId)

            assignmentController.getUserAssignments(UserStore.userId)
            clearAssignmentForm()
        }

        function onCreateAssignmentError(message) {
            console.log("User Store",UserStore.id)
            console.log("Create assignment failed:", message)
        }

        function onUpdateAssignmentSuccess() {
            console.log("User Store Edit ",UserStore.userId)

            assignmentController.getUserAssignments(UserStore.userId)
            clearAssignmentForm()
        }

        function onUpdateAssignmentError(message) {
            console.log("Update assignment failed:", message)
        }

        function onUserAssignmentGetError(message) {
            console.log("Get assignments failed:", message)
        }
    }

    Connections {
        target: helpRequestController

        function onCreateHelpRequestSuccess() {
            mainView.helpModalError = ""
            helpRequestModal.close()
            helpRequestController.loadHelpRequests(UserStore.userId)
            helpRequestController.loadOthersHelpRequests(UserStore.userId)
        }

        function onCreateHelpRequestError(message) {
            mainView.helpModalError = message
            console.log("Create help request failed:", message)
        }

        function onLoadHelpRequestsError(message) {
            console.log("Load help requests failed:", message)
        }

        function onLoadOthersHelpRequestsError(message) {
            console.log("Load others help requests failed:", message)
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
                                        text: mainView.editingAssignmentId >= 0 ? "✎" : "+"
                                        color: green
                                        font.pixelSize: mainView.editingAssignmentId >= 0 ? 20 : 24
                                    }
                                }

                                Text {
                                    text: mainView.editingAssignmentId >= 0 ? "Edit Assignment" : "Add New Assignment"
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

                                onActivated: function (index) {
                                    createAssignment.status = statusCombo.textAt(index)
                                }
                            }

                            Rectangle {
                                width: parent.width
                                height: 58
                                radius: 12
                                color: green

                                Text {
                                    anchors.centerIn: parent
                                    text: mainView.editingAssignmentId >= 0 ? "Save changes" : "  Add Assignment"
                                    color: "#07240F"
                                    font.pixelSize: 20
                                    font.bold: true
                                }

                                MouseArea {
                                    anchors.fill: parent
                                    cursorShape: Qt.PointingHandCursor
                                    onClicked: {
                                        if (mainView.editingAssignmentId >= 0) {
                                            assignmentController.updateAssignment(mainView.editingAssignmentId,
                                                                                  createAssignment)
                                        } else {
                                            assignmentController.createAssignment(createAssignment)
                                        }
                                    }
                                }
                            }

                            Text {
                                visible: mainView.editingAssignmentId >= 0
                                text: "Cancel editing"
                                color: "#8D8D8D"
                                font.pixelSize: 14
                                font.underline: true

                                MouseArea {
                                    anchors.fill: parent
                                    cursorShape: Qt.PointingHandCursor
                                    onClicked: mainView.clearAssignmentForm()
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

                                property string subject: (courseName && courseName.length > 0)
                                    ? courseName
                                    : ("Course " + courseId)

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

                                    RowLayout {
                                        width: parent.width
                                        spacing: 22

                                        Text {
                                            text: "◷ " + dueDate
                                            color: "#8D8D8D"
                                            font.pixelSize: 15
                                            Layout.alignment: Qt.AlignVCenter
                                        }

                                        Text {
                                            text: "+ " + priority
                                            color: priorityColor
                                            font.pixelSize: 15
                                            Layout.alignment: Qt.AlignVCenter
                                        }

                                        Item { Layout.fillWidth: true }

                                        RowLayout {
                                            Layout.alignment: Qt.AlignVCenter
                                            spacing: 10

                                            Rectangle {
                                                Layout.alignment: Qt.AlignVCenter
                                                height: 36
                                                width: helpReqBtnLabel.width + 28
                                                radius: 10
                                                color: "#2A2A2A"
                                                border.color: borderColor
                                                border.width: 1

                                                Text {
                                                    id: helpReqBtnLabel
                                                    anchors.centerIn: parent
                                                    text: "Request help"
                                                    color: green
                                                    font.pixelSize: 14
                                                    font.bold: true
                                                }

                                                MouseArea {
                                                    anchors.fill: parent
                                                    cursorShape: Qt.PointingHandCursor
                                                    onClicked: mainView.openHelpRequestModal(id, title)
                                                }
                                            }

                                            Rectangle {
                                                Layout.alignment: Qt.AlignVCenter
                                                height: 36
                                                width: editBtnLabel.width + 28
                                                radius: 10
                                                color: "#2A2A2A"
                                                border.color: borderColor
                                                border.width: 1

                                                Text {
                                                    id: editBtnLabel
                                                    anchors.centerIn: parent
                                                    text: "Edit"
                                                    color: green
                                                    font.pixelSize: 14
                                                    font.bold: true
                                                }

                                                MouseArea {
                                                    anchors.fill: parent
                                                    cursorShape: Qt.PointingHandCursor
                                                    onClicked: mainView.loadAssignmentForEdit(index)
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        Text {
                            width: parent.width
                            text: "Help requests"
                            color: textPrimary
                            font.pixelSize: 22
                            font.bold: true
                            topPadding: 28
                        }

                        Row {
                            width: parent.width
                            spacing: 10
                            topPadding: 8

                            Repeater {
                                model: ["Mine", "Other users"]

                                delegate: Rectangle {
                                    width: tabLabel.width + 32
                                    height: 40
                                    radius: 10
                                    color: mainView.helpRequestsTab === index ? "#343434" : "transparent"
                                    border.color: mainView.helpRequestsTab === index ? "#494949" : borderColor
                                    border.width: 1

                                    Text {
                                        id: tabLabel
                                        anchors.centerIn: parent
                                        text: modelData
                                        color: mainView.helpRequestsTab === index ? textPrimary : textSecondary
                                        font.pixelSize: 15
                                        font.bold: mainView.helpRequestsTab === index
                                    }

                                    MouseArea {
                                        anchors.fill: parent
                                        cursorShape: Qt.PointingHandCursor
                                        onClicked: mainView.helpRequestsTab = index
                                    }
                                }
                            }
                        }

                        StackLayout {
                            width: parent.width
                            currentIndex: mainView.helpRequestsTab

                            Column {
                                width: parent.width
                                spacing: 12
                                topPadding: 8

                                Text {
                                    width: parent.width
                                    visible: helpRequestController.helpRequestModel.entryCount() === 0
                                    text: "You have not raised any help requests yet. Use “Request help” on an assignment card to ask for support."
                                    color: textSecondary
                                    font.pixelSize: 15
                                    wrapMode: Text.WordWrap
                                }

                                Repeater {
                                    model: helpRequestController.helpRequestModel

                                    delegate: Rectangle {
                                        width: parent.width
                                        implicitHeight: helpCardColumn.implicitHeight + 36
                                        radius: 16
                                        color: cardColor
                                        border.color: borderColor
                                        border.width: 1

                                        Column {
                                            id: helpCardColumn
                                            anchors.fill: parent
                                            anchors.margins: 18
                                            spacing: 10

                                            RowLayout {
                                                width: parent.width
                                                spacing: 12

                                                Text {
                                                    text: "Raised"
                                                    color: textSecondary
                                                    font.pixelSize: 13
                                                }

                                                Text {
                                                    text: createdAt
                                                    color: textPrimary
                                                    font.pixelSize: 14
                                                    font.bold: true
                                                }

                                                Item { Layout.fillWidth: true }

                                                Text {
                                                    visible: assignmentId >= 0
                                                    text: "Assignment #" + assignmentId
                                                    color: "#93C5FD"
                                                    font.pixelSize: 13
                                                }
                                            }

                                            Text {
                                                width: parent.width
                                                text: message
                                                color: "#B9B9B9"
                                                wrapMode: Text.WordWrap
                                                font.pixelSize: 15
                                            }

                                        }
                                    }
                                }
                            }

                            Column {
                                width: parent.width
                                spacing: 12
                                topPadding: 8

                                Text {
                                    width: parent.width
                                    visible: helpRequestController.othersHelpRequestModel.entryCount() === 0
                                    text: "No help requests from other users yet."
                                    color: textSecondary
                                    font.pixelSize: 15
                                    wrapMode: Text.WordWrap
                                }

                                Repeater {
                                    model: helpRequestController.othersHelpRequestModel

                                    delegate: Rectangle {
                                        width: parent.width
                                        implicitHeight: otherHelpCardColumn.implicitHeight + 36
                                        radius: 16
                                        color: cardColor
                                        border.color: borderColor
                                        border.width: 1

                                        Column {
                                            id: otherHelpCardColumn
                                            anchors.fill: parent
                                            anchors.margins: 18
                                            spacing: 10

                                            Text {
                                                width: parent.width
                                                text: raiserDisplayName && raiserDisplayName.length > 0
                                                    ? ("From: " + raiserDisplayName)
                                                    : ("User #" + userId)
                                                color: textPrimary
                                                font.pixelSize: 15
                                                font.bold: true
                                                wrapMode: Text.WordWrap
                                            }

                                            RowLayout {
                                                width: parent.width
                                                spacing: 12

                                                Text {
                                                    text: "Raised"
                                                    color: textSecondary
                                                    font.pixelSize: 13
                                                }

                                                Text {
                                                    text: createdAt
                                                    color: textPrimary
                                                    font.pixelSize: 14
                                                    font.bold: true
                                                }

                                                Item { Layout.fillWidth: true }

                                                Text {
                                                    visible: assignmentId >= 0
                                                    text: "Assignment #" + assignmentId
                                                    color: "#93C5FD"
                                                    font.pixelSize: 13
                                                }
                                            }

                                            Text {
                                                width: parent.width
                                                text: message
                                                color: "#B9B9B9"
                                                wrapMode: Text.WordWrap
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

    Popup {
        id: helpRequestModal
        parent: Overlay.overlay
        anchors.centerIn: Overlay.overlay
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
        padding: 0
        width: Math.min(520, Overlay.overlay.width - 48)

        onOpened: {
            mainView.helpModalError = ""
            helpMessageField.text = ""
        }

        background: Rectangle {
            color: panelColor
            radius: 16
            border.color: borderColor
            border.width: 1
        }

        contentItem: Column {
            width: helpRequestModal.width
            spacing: 0

            Rectangle {
                width: parent.width
                height: 56
                color: "#0A0A0A"
                radius: 16

                Text {
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Request help"
                    color: textPrimary
                    font.pixelSize: 18
                    font.bold: true
                }

                Item {
                    width: 40
                    height: 40
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    anchors.verticalCenter: parent.verticalCenter

                    Text {
                        anchors.centerIn: parent
                        text: "✕"
                        color: textSecondary
                        font.pixelSize: 18
                    }

                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onClicked: helpRequestModal.close()
                    }
                }
            }

            Column {
                width: parent.width - 40
                anchors.horizontalCenter: parent.horizontalCenter
                topPadding: 20
                bottomPadding: 24
                spacing: 14

                Text {
                    visible: mainView.helpModalError.length > 0
                    width: parent.width
                    text: mainView.helpModalError
                    wrapMode: Text.WordWrap
                    color: red
                    font.pixelSize: 14
                }

                Text {
                    text: "Assignment"
                    color: "#D4D4D4"
                    font.pixelSize: 14
                    font.bold: true
                }

                Rectangle {
                    width: parent.width
                    implicitHeight: Math.max(48, helpAssignSummary.implicitHeight + 24)
                    radius: 12
                    color: "#050505"
                    border.color: borderColor
                    border.width: 1

                    Text {
                        id: helpAssignSummary
                        anchors.fill: parent
                        anchors.margins: 12
                        wrapMode: Text.WordWrap
                        text: mainView.helpModalAssignmentTitle.length > 0
                            ? mainView.helpModalAssignmentTitle
                            : ("Assignment #" + mainView.helpFormAssignmentId)
                        color: textPrimary
                        font.pixelSize: 15
                    }
                }

                Text {
                    text: "What do you need help with?"
                    color: "#D4D4D4"
                    font.pixelSize: 14
                    font.bold: true
                }

                Rectangle {
                    width: parent.width
                    height: 140
                    radius: 12
                    color: "#050505"
                    border.color: borderColor
                    border.width: 1

                    TextArea {
                        id: helpMessageField
                        anchors.fill: parent
                        anchors.margins: 10
                        wrapMode: TextEdit.Wrap
                        placeholderText: "Describe your question or issue…"
                        placeholderTextColor: "#6F6F6F"
                        color: textPrimary
                        background: Item {}
                    }
                }

                RowLayout {
                    width: parent.width
                    spacing: 12

                    Item { Layout.fillWidth: true }

                    Rectangle {
                        width: 100
                        height: 44
                        radius: 10
                        color: "#2A2A2A"
                        border.color: borderColor
                        border.width: 1

                        Text {
                            anchors.centerIn: parent
                            text: "Cancel"
                            color: textSecondary
                            font.pixelSize: 15
                        }

                        MouseArea {
                            anchors.fill: parent
                            cursorShape: Qt.PointingHandCursor
                            onClicked: helpRequestModal.close()
                        }
                    }

                    Rectangle {
                        width: 140
                        height: 44
                        radius: 10
                        color: greenDark

                        Text {
                            anchors.centerIn: parent
                            text: "Submit"
                            color: green
                            font.pixelSize: 15
                            font.bold: true
                        }

                        MouseArea {
                            anchors.fill: parent
                            cursorShape: Qt.PointingHandCursor
                            onClicked: {
                                helpRequestController.createHelpRequest(
                                    UserStore.userId,
                                    mainView.helpFormAssignmentId,
                                    helpMessageField.text)
                            }
                        }
                    }
                }
            }
        }
    }
}