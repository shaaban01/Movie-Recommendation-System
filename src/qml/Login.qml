import QtQuick 2.12
import QtQuick.Controls 2.5
import user.controller 1.0

Page {
    property string username: ""
        property string password: ""
            property alias userController: userController

                UserController {
                    id: userController
                    onLoginSuccessful: {
                        console.log("Login Successful");
                        stackView.clear(); // after successful login
                    }
                    onLoginFailed: {
                        console.log("Login Failed");
                        // TODO: to show a message box here
                    }
                }
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
                        onTextChanged: {
                            username = usernameField.text
                        }
                    }

                    TextField {
                        id: passwordField
                        placeholderText: "Password"
                        width: 200
                        echoMode: TextInput.Password
                        onTextChanged: {
                            password = passwordField.text
                        }
                    }

                    Button {
                        id: loginButton
                        text: "Log In"
                        width: 200
                        onClicked: {
                            console.log("Logging in...")
                            userController.loginUser(username, password);
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

