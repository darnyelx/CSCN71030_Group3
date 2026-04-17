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

    /** Parse YYYY-MM-DD (or YYYY/MM/DD) as local calendar date; returns null if invalid. */
    function parseLocalDueDate(isoDateStr) {
        if (!isoDateStr || isoDateStr.length === 0)
            return null
        const datePart = isoDateStr.trim().split(/\s+/)[0]
        const parts = datePart.split(/[-/]/)
        if (parts.length < 3)
            return null
        const y = parseInt(parts[0], 10)
        const m = parseInt(parts[1], 10) - 1
        const d = parseInt(parts[2], 10)
        if (isNaN(y) || isNaN(m) || isNaN(d))
            return null
        const dt = new Date(y, m, d)
        if (dt.getFullYear() !== y || dt.getMonth() !== m || dt.getDate() !== d)
            return null
        return dt
    }

    function dueDateDayDiff(isoDateStr) {
        const due = mainView.parseLocalDueDate(isoDateStr)
        if (!due)
            return null
        const today = new Date()
        today.setHours(0, 0, 0, 0)
        due.setHours(0, 0, 0, 0)
        return Math.round((due.getTime() - today.getTime()) / 86400000)
    }

    /** Human-readable time until due or overdue (days only); empty if no valid date. */
    function dueDateRelativeSummary(isoDateStr) {
        const diffDays = mainView.dueDateDayDiff(isoDateStr)
        if (diffDays === null)
            return ""
        if (diffDays > 1)
            return "Due in " + diffDays + " days"
        if (diffDays === 1)
            return "Due in 1 day"
        if (diffDays === 0)
            return "Due today"
        const od = -diffDays
        return od === 1 ? "1 day overdue" : od + " days overdue"
    }

    /** Accent for relative due line: overdue / due soon / default. */
    function dueDateRelativeColor(isoDateStr) {
        const diffDays = mainView.dueDateDayDiff(isoDateStr)
        if (diffDays === null)
            return "#6B7280"
        if (diffDays < 0)
            return "#F87171"
        if (diffDays <= 3)
            return "#FBBF24"
        return "#9CA3AF"
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
        const vm = assignmentController.assignmentFilter.get(row)
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
        console.log("User Store", UserStore.userId)
        courseViewController.getCourses()
        assignmentController.getUserAssignments(UserStore.userId)
        helpRequestController.loadHelpRequests(UserStore.userId)
        helpRequestController.loadOthersHelpRequests(UserStore.userId)
    }

    Connections {
        target: assignmentController

        function onCreateAssignmentSuccess() {
            console.log("User Store", UserStore.userId)

            assignmentController.getUserAssignments(UserStore.userId)
            clearAssignmentForm()
        }

        function onCreateAssignmentError(message) {
            console.log("User Store", UserStore.id)
            console.log("Create assignment failed:", message)
        }

        function onUpdateAssignmentSuccess() {
            console.log("User Store Edit ", UserStore.userId)

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

        Rectangle {
            anchors.fill: parent
            color: "transparent"

            Rectangle {
                width: 460
                height: 460
                radius: 230
                x: -140
                y: -120
                color: green
                opacity: 0.045
            }

            Rectangle {
                width: 520
                height: 520
                radius: 260
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.rightMargin: -150
                anchors.topMargin: -180
                color: blue
                opacity: 0.05
            }
        }

        Flickable {
            anchors.fill: parent
            contentWidth: width
            contentHeight: rootColumn.implicitHeight + 72
            clip: true

            Column {
                id: rootColumn
                width: Math.min(1380, parent.width - 96)
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 28
                spacing: 26

                Rectangle {
                    width: parent.width
                    radius: 26
                    color: panelColor
                    border.color: borderColor
                    border.width: 1

                    Column {
                        anchors.fill: parent
                        anchors.margins: 24
                        spacing: 22

                        RowLayout {
                            width: parent.width
                            spacing: 20

                            Row {
                                spacing: 16
                                Layout.alignment: Qt.AlignVCenter

                                Rectangle {
                                    width: 60
                                    height: 60
                                    radius: 18
                                    color: green

                                    Rectangle {
                                        anchors.fill: parent
                                        anchors.margins: 1
                                        radius: parent.radius - 1
                                        color: "transparent"
                                        border.color: "#1FFFFFFF"
                                        border.width: 1
                                    }

                                    Text {
                                        anchors.centerIn: parent
                                        text: "▤"
                                        color: "#06250F"
                                        font.pixelSize: 24
                                        font.bold: true
                                    }
                                }

                                Column {
                                    spacing: 4
                                    anchors.verticalCenter: parent.verticalCenter

                                    Text {
                                        text: "Assignment Coordinator"
                                        color: textPrimary
                                        font.pixelSize: 28
                                        font.bold: true
                                    }

                                    Text {
                                        text: "Track coursework, priorities, and support requests in one place"
                                        color: textSecondary
                                        font.pixelSize: 14
                                    }
                                }
                            }

                            Item { Layout.fillWidth: true }

                            Row {
                                spacing: 14
                                Layout.alignment: Qt.AlignVCenter

                                Repeater {
                                    model: [
                                        { value: "0", label: "TOTAL" },
                                        { value: "0", label: "PENDING" },
                                        { value: "0", label: "COMPLETED" }
                                    ]

                                    delegate: Rectangle {
                                        width: 118
                                        height: 88
                                        radius: 18
                                        color: cardColor
                                        border.color: borderColor
                                        border.width: 1

                                        Column {
                                            anchors.centerIn: parent
                                            spacing: 6

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
                                                font.pixelSize: 12
                                                font.bold: true
                                                font.capitalization: Font.AllUppercase
                                            }
                                        }
                                    }
                                }

                                Rectangle {
                                    width: 188
                                    height: 64
                                    radius: 18
                                    color: cardColor
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

                                        Column {
                                            anchors.verticalCenter: parent.verticalCenter
                                            spacing: 2

                                            Text {
                                                text: "Workspace"
                                                color: textSecondary
                                                font.pixelSize: 12
                                            }

                                            Text {
                                                text: "User"
                                                color: textPrimary
                                                font.pixelSize: 16
                                                font.bold: true
                                            }
                                        }

                                        Item { width: 8 }

                                        Text {
                                            text: "⇥"
                                            color: textSecondary
                                            font.pixelSize: 20
                                            anchors.verticalCenter: parent.verticalCenter
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                RowLayout {
                    width: parent.width
                    spacing: 26
                    Layout.fillWidth: true

                    Rectangle {

                        Layout.preferredWidth: 430
                        Layout.fillWidth: true
                        implicitHeight: formColumn.implicitHeight + 52

                        radius: 26
                        color: panelColor
                        border.color: borderColor
                        border.width: 1

                        Column {
                            id: formColumn
                            anchors.fill: parent
                            anchors.leftMargin: 26
                            anchors.rightMargin: 26
                            anchors.topMargin: 26
                            anchors.bottomMargin: 26
                            spacing: 16

                            Row {
                                spacing: 12

                                Rectangle {
                                    width: 42
                                    height: 42
                                    radius: 14
                                    color: greenDark

                                    Text {
                                        anchors.centerIn: parent
                                        text: mainView.editingAssignmentId >= 0 ? "✎" : "+"
                                        color: green
                                        font.pixelSize: mainView.editingAssignmentId >= 0 ? 20 : 24
                                        font.bold: true
                                    }
                                }

                                Column {
                                    spacing: 4
                                    anchors.verticalCenter: parent.verticalCenter

                                    Text {
                                        text: mainView.editingAssignmentId >= 0 ? "Edit Assignment" : "Add New Assignment"
                                        color: textPrimary
                                        font.pixelSize: 22
                                        font.bold: true
                                    }

                                    Text {
                                        text: mainView.editingAssignmentId >= 0
                                            ? "Update the selected assignment details"
                                            : "Fill in the details below to create a new task"
                                        color: textSecondary
                                        font.pixelSize: 13
                                    }
                                }
                            }

                            Text {
                                text: "Assignment Title"
                                color: "#D4D4D4"
                                font.pixelSize: 15
                                font.bold: true
                            }

                            Rectangle {
                                width: parent.width
                                height: 56
                                radius: 14
                                color: cardColor
                                border.color: borderColor
                                border.width: 1

                                TextField {
                                    id: titleField
                                    anchors.fill: parent
                                    anchors.leftMargin: 14
                                    anchors.rightMargin: 14
                                    placeholderText: "Enter assignment title"
                                    color: textPrimary
                                    placeholderTextColor: "#6F6F6F"
                                    verticalAlignment: Text.AlignVCenter
                                    background: Item {}

                                    onTextChanged: createAssignment.title = text
                                }
                            }

                            Text {
                                text: "Subject"
                                color: "#D4D4D4"
                                font.pixelSize: 15
                                font.bold: true
                            }

                            ComboBox {
                                id: courseList
                                width: parent.width
                                height: 56
                                model: courseViewController.courseModel
                                textRole: "name"
                                currentIndex: -1

                                background: Rectangle {
                                    radius: 14
                                    color: cardColor
                                    border.color: borderColor
                                    border.width: 1
                                }

                                contentItem: Text {
                                    leftPadding: 14
                                    rightPadding: 34
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
                                font.pixelSize: 15
                                font.bold: true
                            }

                            Rectangle {
                                width: parent.width
                                height: 146
                                radius: 14
                                color: cardColor
                                border.color: borderColor
                                border.width: 1

                                TextArea {
                                    id: descriptionField
                                    anchors.fill: parent
                                    anchors.margins: 14
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
                                spacing: 16

                                Column {
                                    width: (parent.width - 16) / 2
                                    spacing: 10

                                    Text {
                                        text: "Due Date"
                                        color: "#D4D4D4"
                                        font.pixelSize: 15
                                        font.bold: true
                                    }

                                    Rectangle {
                                        width: parent.width
                                        height: 56
                                        radius: 14
                                        color: cardColor
                                        border.color: borderColor
                                        border.width: 1

                                        TextField {
                                            id: dueDateField
                                            anchors.fill: parent
                                            anchors.leftMargin: 14
                                            anchors.rightMargin: 14
                                            placeholderText: "yyyy-mm-dd"
                                            color: textPrimary
                                            placeholderTextColor: "#6F6F6F"
                                            verticalAlignment: Text.AlignVCenter
                                            background: Item {}

                                            onTextChanged: createAssignment.dueDate = text
                                        }
                                    }
                                }

                                Column {
                                    width: (parent.width - 16) / 2
                                    spacing: 10

                                    Text {
                                        text: "Priority"
                                        color: "#D4D4D4"
                                        font.pixelSize: 15
                                        font.bold: true
                                    }

                                    ComboBox {
                                        id: priorityCombo
                                        width: parent.width
                                        height: 56
                                        model: ["Low", "Medium", "High"]
                                        currentIndex: 0

                                        background: Rectangle {
                                            radius: 14
                                            color: cardColor
                                            border.color: borderColor
                                            border.width: 1
                                        }

                                        contentItem: Text {
                                            leftPadding: 14
                                            rightPadding: 34
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
                                font.pixelSize: 15
                                font.bold: true
                            }

                            ComboBox {
                                id: statusCombo
                                width: parent.width
                                height: 56
                                model: ["Pending", "In Progress", "Completed"]

                                background: Rectangle {
                                    radius: 14
                                    color: cardColor
                                    border.color: borderColor
                                    border.width: 1
                                }

                                contentItem: Text {
                                    leftPadding: 14
                                    rightPadding: 34
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
                                radius: 16
                                color: green

                                Text {
                                    anchors.centerIn: parent
                                    text: mainView.editingAssignmentId >= 0 ? "Save changes" : "Add Assignment"
                                    color: "#07240F"
                                    font.pixelSize: 19
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

                            Column {
                                spacing: 4

                                Text {
                                    text: "Your Assignments"
                                    color: textPrimary
                                    font.pixelSize: 24
                                    font.bold: true
                                }

                                Text {
                                    text: "Browse, filter, and manage your current workload"
                                    color: textSecondary
                                    font.pixelSize: 13
                                }

                                Text {
                                    text: "Welcome " + UserStore.firstName + " !"
                                    color: textSecondary
                                    font.pixelSize: 24
                                    font.bold: true
                                }
                            }
                        }

                        Row {
                            width: parent.width
                            spacing: 10

                            Rectangle {
                                width: (parent.width - parent.spacing * 3) / 4
                                height: 76
                                radius: 16
                                color: panelColor
                                border.color: borderColor
                                border.width: 1

                                Column {
                                    anchors.centerIn: parent
                                    spacing: 4

                                    Text {
                                        text: "Total"
                                        color: "#A3A3A3"
                                        font.pixelSize: 12
                                        font.bold: true
                                        anchors.horizontalCenter: parent.horizontalCenter
                                    }

                                    Text {
                                        text: assignmentController.assignmentModel.totalCount
                                        color: textPrimary
                                        font.pixelSize: 24
                                        font.bold: true
                                        anchors.horizontalCenter: parent.horizontalCenter
                                    }
                                }
                            }

                            Rectangle {
                                width: (parent.width - parent.spacing * 3) / 4
                                height: 76
                                radius: 16
                                color: panelColor
                                border.color: borderColor
                                border.width: 1

                                Column {
                                    anchors.centerIn: parent
                                    spacing: 4

                                    Text {
                                        text: "Pending"
                                        color: "#F59E0B"
                                        font.pixelSize: 12
                                        font.bold: true
                                        anchors.horizontalCenter: parent.horizontalCenter
                                    }

                                    Text {
                                        text: assignmentController.assignmentModel.pendingCount
                                        color: textPrimary
                                        font.pixelSize: 24
                                        font.bold: true
                                        anchors.horizontalCenter: parent.horizontalCenter
                                    }
                                }
                            }

                            Rectangle {
                                width: (parent.width - parent.spacing * 3) / 4
                                height: 76
                                radius: 16
                                color: panelColor
                                border.color: borderColor
                                border.width: 1

                                Column {
                                    anchors.centerIn: parent
                                    spacing: 4

                                    Text {
                                        text: "In Progress"
                                        color: "#60A5FA"
                                        font.pixelSize: 12
                                        font.bold: true
                                        anchors.horizontalCenter: parent.horizontalCenter
                                    }

                                    Text {
                                        text: assignmentController.assignmentModel.inProgressCount
                                        color: textPrimary
                                        font.pixelSize: 24
                                        font.bold: true
                                        anchors.horizontalCenter: parent.horizontalCenter
                                    }
                                }
                            }

                            Rectangle {
                                width: (parent.width - parent.spacing * 3) / 4
                                height: 76
                                radius: 16
                                color: panelColor
                                border.color: borderColor
                                border.width: 1

                                Column {
                                    anchors.centerIn: parent
                                    spacing: 4

                                    Text {
                                        text: "Completed"
                                        color: "#22C55E"
                                        font.pixelSize: 12
                                        font.bold: true
                                        anchors.horizontalCenter: parent.horizontalCenter
                                    }

                                    Text {
                                        text: assignmentController.assignmentModel.completedCount
                                        color: textPrimary
                                        font.pixelSize: 24
                                        font.bold: true
                                        anchors.horizontalCenter: parent.horizontalCenter
                                    }
                                }
                            }
                        }

                        Rectangle {
                            width: parent.width
                            height: 70
                            radius: 18
                            color: panelColor
                            border.color: borderColor
                            border.width: 1

                            Row {
                                anchors.fill: parent
                                anchors.leftMargin: 18
                                anchors.rightMargin: 18
                                anchors.verticalCenter: parent.verticalCenter
                                spacing: 10

                                Repeater {
                                    model: ["All", "Pending", "In Progress", "Done"]

                                    delegate: Rectangle {
                                        width: filterPillLabel.implicitWidth + 34
                                        height: 42
                                        radius: 12
                                        readonly property bool selected: assignmentController.assignmentFilter.statusFilter === index
                                        color: selected ? "#343434" : "transparent"
                                        border.color: selected ? "#4C4C4C" : "#262626"
                                        border.width: 1

                                        Text {
                                            id: filterPillLabel
                                            anchors.centerIn: parent
                                            text: modelData
                                            color: selected ? textPrimary : "#B5B5B5"
                                            font.pixelSize: 15
                                            font.bold: selected
                                        }

                                        MouseArea {
                                            anchors.fill: parent
                                            cursorShape: Qt.PointingHandCursor
                                            onClicked: assignmentController.assignmentFilter.statusFilter = index
                                        }
                                    }
                                }
                            }
                        }

                        Rectangle {
                            width: parent.width
                            height: 60
                            radius: 16
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
                                    font.pixelSize: 22
                                    anchors.verticalCenter: parent.verticalCenter
                                }

                                TextField {
                                    id: assignmentSearchField
                                    width: parent.width - 40
                                    anchors.verticalCenter: parent.verticalCenter
                                    placeholderText: "Search assignments..."
                                    placeholderTextColor: "#6F6F6F"
                                    color: textPrimary
                                    background: Item {}
                                    onTextChanged: assignmentController.assignmentFilter.searchText = text
                                }
                            }
                        }

                        Repeater {
                            model: assignmentController.assignmentFilter

                            delegate: Rectangle {
                                width: parent.width
                                implicitHeight: cardColumn.implicitHeight + 40
                                radius: 22
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

                                readonly property string dueRelativeLine: mainView.dueDateRelativeSummary(dueDate)

                                Column {
                                    id: cardColumn
                                    anchors.fill: parent
                                    anchors.margins: 22
                                    spacing: 16

                                    Row {
                                        width: parent.width
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
                                            font.pixelSize: 19
                                            font.bold: true
                                            anchors.verticalCenter: parent.verticalCenter
                                        }

                                        Rectangle {
                                            height: 30
                                            radius: 9
                                            color: subjectBg
                                            width: subjectLabel.implicitWidth + 24
                                            anchors.verticalCenter: parent.verticalCenter

                                            Text {
                                                anchors.centerIn: parent
                                                text: subject
                                                color: subjectText
                                                font.pixelSize: 13
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
                                            radius: 9
                                            color: statusBg
                                            width: statusLabel.implicitWidth + 24
                                            anchors.verticalCenter: parent.verticalCenter

                                            Text {
                                                anchors.centerIn: parent
                                                text: status
                                                color: statusText
                                                font.pixelSize: 13
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
                                        width: parent.width
                                        text: description
                                        color: "#B9B9B9"
                                        wrapMode: Text.WordWrap
                                        font.pixelSize: 15
                                        lineHeight: 1.2
                                    }

                                    RowLayout {
                                        width: parent.width
                                        spacing: 18

                                        Rectangle {
                                            radius: 10
                                            color: "#141414"
                                            border.color: borderColor
                                            border.width: 1
                                            implicitWidth: Math.max(dueDateText.implicitWidth, dueRelativeText.implicitWidth) + 24
                                            implicitHeight: dueDateColumn.implicitHeight + 16

                                            Column {
                                                id: dueDateColumn
                                                anchors.centerIn: parent
                                                spacing: 2

                                                Text {
                                                    id: dueDateText
                                                    text: dueDate && dueDate.length > 0 ? ("◷ " + dueDate) : "◷ No due date"
                                                    color: "#8D8D8D"
                                                    font.pixelSize: 14
                                                }

                                                Text {
                                                    id: dueRelativeText
                                                    visible: dueRelativeLine.length > 0
                                                    text: dueRelativeLine
                                                    color: mainView.dueDateRelativeColor(dueDate)
                                                    font.pixelSize: 12
                                                    font.bold: true
                                                }
                                            }
                                        }

                                        Rectangle {
                                            radius: 10
                                            color: "#141414"
                                            border.color: borderColor
                                            border.width: 1
                                            implicitWidth: priorityText.implicitWidth + 24
                                            implicitHeight: 34

                                            Text {
                                                id: priorityText
                                                anchors.centerIn: parent
                                                text: "+ " + priority
                                                color: priorityColor
                                                font.pixelSize: 14
                                                font.bold: true
                                            }
                                        }

                                        Item { Layout.fillWidth: true }

                                        RowLayout {
                                            Layout.alignment: Qt.AlignVCenter
                                            spacing: 10

                                            Rectangle {
                                                Layout.alignment: Qt.AlignVCenter
                                                height: 38
                                                width: helpReqBtnLabel.width + 30
                                                radius: 11
                                                color: "#202020"
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
                                                height: 38
                                                width: editBtnLabel.width + 30
                                                radius: 11
                                                color: "#202020"
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

                        Rectangle {
                            width: parent.width
                            radius: 24
                            color: panelColor
                            border.color: borderColor
                            border.width: 1

                            Column {
                                width: parent.width - 40
                                anchors.horizontalCenter: parent.horizontalCenter
                                topPadding: 22
                                bottomPadding: 22
                                spacing: 16

                                Column {
                                    spacing: 4

                                    Text {
                                        text: "Help requests"
                                        color: textPrimary
                                        font.pixelSize: 24
                                        font.bold: true
                                    }

                                    Text {
                                        text: "View support questions you raised and requests from other users"
                                        color: textSecondary
                                        font.pixelSize: 13
                                    }
                                }

                                Row {
                                    width: parent.width
                                    spacing: 10

                                    Repeater {
                                        model: ["Mine", "Other users"]

                                        delegate: Rectangle {
                                            width: tabLabel.width + 34
                                            height: 42
                                            radius: 12
                                            color: mainView.helpRequestsTab === index ? "#343434" : "transparent"
                                            border.color: mainView.helpRequestsTab === index ? "#4C4C4C" : borderColor
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

                                        Text {
                                            width: parent.width
                                            visible: false
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
                                                radius: 18
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

                                        Text {
                                            width: parent.width
                                            visible: helpRequestController.othersHelpRequestModel.entryCount() === 0
                                            text: "No help requests yet."
                                            color: textSecondary
                                            font.pixelSize: 15
                                            wrapMode: Text.WordWrap
                                        }

                                        Repeater {
                                            model: helpRequestController.othersHelpRequestModel

                                            delegate: Rectangle {
                                                width: parent.width
                                                implicitHeight: otherHelpCardColumn.implicitHeight + 36
                                                radius: 18
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

                        Rectangle {
                            width: parent.width
                            radius: 22
                            color: panelColor
                            border.color: borderColor
                            border.width: 1
                            implicitHeight: helpRequestsContent.implicitHeight + 36

                            Column {
                                id: helpRequestsContent
                                anchors.fill: parent
                                anchors.leftMargin: 20
                                anchors.rightMargin: 20
                                anchors.topMargin: 18
                                anchors.bottomMargin: 18
                                spacing: 16

                                Rectangle {
                                    width: parent.width
                                    height: 52
                                    radius: 14
                                    color: cardColor
                                    border.color: borderColor
                                    border.width: 1

                                    Row {
                                        anchors.fill: parent
                                        anchors.leftMargin: 8
                                        anchors.rightMargin: 8
                                        spacing: 10

                                        Repeater {
                                            model: ["Mine", "Other users"]

                                            delegate: Rectangle {
                                                width: Math.max(120, tabLabel.implicitWidth + 34)
                                                height: 36
                                                radius: 10
                                                anchors.verticalCenter: parent.verticalCenter
                                                color: mainView.helpRequestsTab === index ? greenDark : "transparent"
                                                border.color: mainView.helpRequestsTab === index ? green : "transparent"
                                                border.width: 1

                                                Text {
                                                    id: tabLabel
                                                    anchors.centerIn: parent
                                                    text: modelData
                                                    color: mainView.helpRequestsTab === index ? green : textSecondary
                                                    font.pixelSize: 14
                                                    font.bold: true
                                                }

                                                MouseArea {
                                                    anchors.fill: parent
                                                    cursorShape: Qt.PointingHandCursor
                                                    onClicked: mainView.helpRequestsTab = index
                                                }
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

                                        Rectangle {
                                            visible: helpRequestController.helpRequestModel.entryCount() === 0
                                            width: parent.width
                                            radius: 16
                                            color: cardColor
                                            border.color: borderColor
                                            border.width: 1
                                            implicitHeight: emptyMineText.implicitHeight + 32

                                            Text {
                                                id: emptyMineText
                                                anchors.fill: parent
                                                anchors.margins: 16
                                                text: "You have not raised any help requests yet. Use “Request help” on an assignment card to ask for support."
                                                color: textSecondary
                                                font.pixelSize: 15
                                                wrapMode: Text.WordWrap
                                            }
                                        }

                                        Repeater {
                                            model: helpRequestController.helpRequestModel

                                            delegate: Rectangle {
                                                width: parent.width
                                                implicitHeight: helpCardColumn.implicitHeight + 32
                                                radius: 18
                                                color: cardColor
                                                border.color: borderColor
                                                border.width: 1

                                                Column {
                                                    id: helpCardColumn
                                                    anchors.fill: parent
                                                    anchors.leftMargin: 18
                                                    anchors.rightMargin: 18
                                                    anchors.topMargin: 16
                                                    anchors.bottomMargin: 16
                                                    spacing: 12

                                                    RowLayout {
                                                        width: parent.width
                                                        spacing: 10

                                                        Rectangle {
                                                            width: 34
                                                            height: 34
                                                            radius: 10
                                                            color: greenDark
                                                            Layout.alignment: Qt.AlignTop

                                                            Text {
                                                                anchors.centerIn: parent
                                                                text: "?"
                                                                color: green
                                                                font.pixelSize: 18
                                                                font.bold: true
                                                            }
                                                        }

                                                        ColumnLayout {
                                                            Layout.fillWidth: true
                                                            spacing: 6

                                                            RowLayout {
                                                                Layout.fillWidth: true
                                                                spacing: 10

                                                                Text {
                                                                    text: "Help Request"
                                                                    color: textPrimary
                                                                    font.pixelSize: 15
                                                                    font.bold: true
                                                                }

                                                                Item { Layout.fillWidth: true }

                                                                Rectangle {
                                                                    visible: assignmentId >= 0
                                                                    radius: 8
                                                                    color: "#1E293B"
                                                                    implicitWidth: assignmentTag.implicitWidth + 18
                                                                    height: 26

                                                                    Text {
                                                                        id: assignmentTag
                                                                        anchors.centerIn: parent
                                                                        text: "Assignment #" + assignmentId
                                                                        color: "#93C5FD"
                                                                        font.pixelSize: 12
                                                                        font.bold: true
                                                                    }
                                                                }
                                                            }

                                                            RowLayout {
                                                                Layout.fillWidth: true
                                                                spacing: 6

                                                                Text {
                                                                    text: "Raised"
                                                                    color: textSecondary
                                                                    font.pixelSize: 12
                                                                }

                                                                Text {
                                                                    text: createdAt
                                                                    color: textPrimary
                                                                    font.pixelSize: 13
                                                                    font.bold: true
                                                                }
                                                            }
                                                        }
                                                    }

                                                    Rectangle {
                                                        width: parent.width
                                                        radius: 12
                                                        color: panelColor
                                                        border.color: borderColor
                                                        border.width: 1
                                                        implicitHeight: helpMessageText.implicitHeight + 24

                                                        Text {
                                                            id: helpMessageText
                                                            anchors.fill: parent
                                                            anchors.margins: 12
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

                                    Column {
                                        width: parent.width
                                        spacing: 12

                                        Rectangle {
                                            visible: helpRequestController.othersHelpRequestModel.entryCount() === 0
                                            width: parent.width
                                            radius: 16
                                            color: cardColor
                                            border.color: borderColor
                                            border.width: 1
                                            implicitHeight: emptyOthersText.implicitHeight + 32

                                            Text {
                                                id: emptyOthersText
                                                anchors.fill: parent
                                                anchors.margins: 16
                                                text: "No help requests from other users yet."
                                                color: textSecondary
                                                font.pixelSize: 15
                                                wrapMode: Text.WordWrap
                                                visible: helpRequestController.othersHelpRequestModel.rowCount() === 0
                                            }
                                        }

                                        Repeater {
                                            model: helpRequestController.othersHelpRequestModel

                                            delegate: Rectangle {
                                                width: parent.width
                                                implicitHeight: otherHelpCardColumn.implicitHeight + 32
                                                radius: 18
                                                color: cardColor
                                                border.color: borderColor
                                                border.width: 1

                                                Column {
                                                    id: otherHelpCardColumn
                                                    anchors.fill: parent
                                                    anchors.leftMargin: 18
                                                    anchors.rightMargin: 18
                                                    anchors.topMargin: 16
                                                    anchors.bottomMargin: 16
                                                    spacing: 12

                                                    RowLayout {
                                                        width: parent.width
                                                        spacing: 10

                                                        Rectangle {
                                                            width: 34
                                                            height: 34
                                                            radius: 10
                                                            color: "#1E293B"
                                                            Layout.alignment: Qt.AlignTop

                                                            Text {
                                                                anchors.centerIn: parent
                                                                text: "👤"
                                                                font.pixelSize: 15
                                                            }
                                                        }

                                                        ColumnLayout {
                                                            Layout.fillWidth: true
                                                            spacing: 6

                                                            RowLayout {
                                                                Layout.fillWidth: true
                                                                spacing: 10

                                                                Text {
                                                                    text: raiserDisplayName && raiserDisplayName.length > 0
                                                                        ? ("From: " + raiserDisplayName)
                                                                        : ("User #" + userId)
                                                                    color: textPrimary
                                                                    font.pixelSize: 15
                                                                    font.bold: true
                                                                    Layout.fillWidth: true
                                                                    wrapMode: Text.WordWrap
                                                                }

                                                                Rectangle {
                                                                    visible: assignmentId >= 0
                                                                    radius: 8
                                                                    color: "#1E293B"
                                                                    implicitWidth: otherAssignmentTag.implicitWidth + 18
                                                                    height: 26

                                                                    Text {
                                                                        id: otherAssignmentTag
                                                                        anchors.centerIn: parent
                                                                        text: "Assignment #" + assignmentId
                                                                        color: "#93C5FD"
                                                                        font.pixelSize: 12
                                                                        font.bold: true
                                                                    }
                                                                }
                                                            }

                                                            RowLayout {
                                                                Layout.fillWidth: true
                                                                spacing: 6

                                                                Text {
                                                                    text: "Raised"
                                                                    color: textSecondary
                                                                    font.pixelSize: 12
                                                                }

                                                                Text {
                                                                    text: createdAt
                                                                    color: textPrimary
                                                                    font.pixelSize: 13
                                                                    font.bold: true
                                                                }
                                                            }
                                                        }
                                                    }

                                                    Rectangle {
                                                        width: parent.width
                                                        radius: 12
                                                        color: panelColor
                                                        border.color: borderColor
                                                        border.width: 1
                                                        implicitHeight: otherHelpMessageText.implicitHeight + 24

                                                        Text {
                                                            id: otherHelpMessageText
                                                            anchors.fill: parent
                                                            anchors.margins: 12
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
            radius: 20
            border.color: borderColor
            border.width: 1
        }

        contentItem: Column {
            width: helpRequestModal.width
            spacing: 0

            Rectangle {
                width: parent.width
                height: 64
                color: "#0A0A0A"
                radius: 20

                Rectangle {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    height: 22
                    color: "#0A0A0A"
                }

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
                    anchors.rightMargin: 12
                    anchors.verticalCenter: parent.verticalCenter

                    Rectangle {
                        anchors.fill: parent
                        radius: 12
                        color: "#1B1B1B"
                        border.color: borderColor
                        border.width: 1
                    }

                    Text {
                        anchors.centerIn: parent
                        text: "✕"
                        color: textSecondary
                        font.pixelSize: 16
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
                topPadding: 22
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
                    implicitHeight: Math.max(52, helpAssignSummary.implicitHeight + 24)
                    radius: 14
                    color: cardColor
                    border.color: borderColor
                    border.width: 1

                    Text {
                        id: helpAssignSummary
                        anchors.fill: parent
                        anchors.margins: 14
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
                    height: 146
                    radius: 14
                    color: cardColor
                    border.color: borderColor
                    border.width: 1

                    TextArea {
                        id: helpMessageField
                        anchors.fill: parent
                        anchors.margins: 12
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
                        width: 104
                        height: 44
                        radius: 12
                        color: "#242424"
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
                        width: 144
                        height: 44
                        radius: 12
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
