pragma Singleton
import QtQuick

QtObject {

    // will be injected from Main.qml
    property var stack
    property var authViewController

    function login() {
        var page = stack.push(Qt.resolvedUrl("../LoginView.qml"), {
            stackView: stack
        })

        page.loginRequested.connect(function(email, password) {
            authViewController.login(email, password)
        })

        page.goToRegister.connect(function() {
            register()
        })
    }

    function register() {
        var page = stack.push(Qt.resolvedUrl("../RegisterView.qml"), {
            stackView: stack
        })

        page.registerRequested.connect(function(registerUserModel) {
            authViewController.registerUser(registerUserModel)
        })

        page.goToLogin.connect(function() {
            stack.pop()
        })
    }
}