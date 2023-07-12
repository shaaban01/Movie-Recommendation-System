import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    Column {
        anchors.centerIn: parent
        spacing: 20

        Label {
            text: "LOGIN"
            font.pointSize: 24
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            width: 200
        }

        TextField {
            id: usernameField
            placeholderText: "Username"
            width: 200
        }

        TextField {
            id: passwordField
            placeholderText: "Password"
            width: 200
            echoMode: TextInput.Password
        }

        Button {
            id: loginButton
            text: "Log In"
            width: 200
            onClicked: {
                if (userController.loginUserQML(usernameField.text, passwordField.text))
                {
                    console.log("Login successful")
                    stackView.clear() // after successful login
                }else
            {
                console.log("Login failed")
            }
        }
    }

    Button {
        id: signupButton
        text: "Go to Sign Up"
        width: 200
        onClicked: stackView.push(Qt.resolvedUrl("Signup.qml"))
    }
}
}
