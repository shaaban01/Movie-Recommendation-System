import QtQuick 2.12
import QtQuick.Controls 2.5
import user.controller 1.0

Page {
    property string username: ""
        property string password: ""
            property int age: 0
                property alias userController: userController

                    UserController {
                        id: userController
                        onRegistrationSuccessful: {
                            console.log("Registration Successful");
                            stackView.clear(); // after successful Registration
                        }
                        onRegistrationFailed: {
                            console.log("Registration Failed");
                            // TODO: show a message box here
                        }
                    }

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
                            onTextChanged: {
                                username = usernameField.text
                            }
                        }

                        TextField {
                            id: ageField
                            placeholderText: "Age"
                            width: 200
                            validator: IntValidator { bottom: 1; top: 120 }
                            onTextChanged: {
                                age = parseInt(ageField.text)
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
                                userController.registerUser(username, password, age)
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
