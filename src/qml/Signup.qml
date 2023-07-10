import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    Column {
        anchors.centerIn: parent
        spacing: 20

        Label {
           text: "REGISTER"
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
            id: ageField
            placeholderText: "Age"
            width: 200
            validator: IntValidator { bottom: 1; top: 120 }
        }

        TextField {
            id: passwordField
            placeholderText: "Password"
            width: 200
            echoMode: TextInput.Password
        }

        TextField {
            id: confirmPasswordField
            placeholderText: "Confirm Password"
            width: 200
            echoMode: TextInput.Password
        }

        Button {
            id: signupButton
            text: "Sign Up"
            width: 200
            enabled: ageField.acceptableInput &&
                      passwordField.text.length >= 6 &&
                      passwordField.text === confirmPasswordField.text
            onClicked: {
                console.log("Signing up...")
                //stackView.pop() // after successful sign up
            }
        }

        Button {
            id: loginButton
            text: "Go to Login"
            width: 200
            onClicked: stackView.pop()
        }
    }
}
