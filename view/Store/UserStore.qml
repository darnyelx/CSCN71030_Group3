pragma Singleton
import QtQuick

QtObject {
    property QtObject currentUser: null
    property bool isLoggedIn: userId > 0

    property int userId: -1
    property string firstName: ""
    property string lastName: ""
    property string email: ""

    function login(user) {
        currentUser = user
        userId = user && user.id !== undefined ? user.id : -1
        firstName = user && user.firstName !== undefined ? user.firstName : ""
        lastName = user && user.lastName !== undefined ? user.lastName : ""
        email = user && user.email !== undefined ? user.email : ""

        console.log("UserStore login userId =", userId)
    }

    function logout() {
        currentUser = null
        userId = -1
        firstName = ""
        lastName = ""
        email = ""
    }
}