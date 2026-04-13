pragma Singleton
import QtQuick

QtObject {
    property QtObject currentUser: null
    property bool isLoggedIn: currentUser !== null

    property string firstName: currentUser ? currentUser.firstName : ""
    property string lastName: currentUser ? currentUser.lastName : ""
    property string email: currentUser ? currentUser.email : ""
    property int id: currentUser ? currentUser.id: -1;

    function login(user) {
        currentUser = user
    }

    function logout() {
        currentUser = null
    }
}