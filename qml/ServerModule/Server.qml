pragma Singleton
import QtQuick 2.0

QtObject{

    function loginToServer(email, password)
    {
        var resultRequest
        var request = new XMLHttpRequest()
        var errArray = new Array()
        request.open('POST', 'https://api.quwi.com/v2/auth/login', false)
        request.onreadystatechange = function() {
            if (request.readyState === XMLHttpRequest.DONE) {
                if (request.status === 200) {
                    var result = JSON.parse(request.responseText)
                    resultRequest = result.token
                }

                else {
                    console.log("HTTP:", request.status, request.statusText)
                    var result = JSON.parse(request.responseText)
                    var errors = result.first_errors
                    resultRequest = errors
                }
            }
        }

        request.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded')
        request.setRequestHeader('Client-Device', 'windows')
        request.send('email='+ email + '&password=' + password)

        return resultRequest
    }

    function getProjectsInfo(token)
    {
        var projectsJson
        var request = new XMLHttpRequest()

        request.open('GET', 'https://api.quwi.com/v2/projects-manage/index', false)
        request.onreadystatechange = function() {
            if (request.readyState === XMLHttpRequest.DONE) {
                if (request.status && request.status === 200) {
                    var result = JSON.parse(request.responseText)
                    projectsJson = result.projects
                } else {
                    console.log("HTTP:", request.status, request.statusText)
                }
            }
        }

        request.setRequestHeader('Authorization', 'Bearer ' + token)
        request.send()
        return projectsJson
    }

    function changeName(token, id, name)
    {
        var request = new XMLHttpRequest()

        request.open('POST', 'https://api.quwi.com/v2/projects-manage/update?id=' + id, false)
        request.onreadystatechange = function() {
            if (request.readyState === XMLHttpRequest.DONE) {
                if (request.status && request.status === 200) {
                    var result = JSON.parse(request.responseText)
                } else {
                    console.log("HTTP:", request.status, request.statusText)
                }
            }
        }

        request.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded')
        request.setRequestHeader('Authorization', 'Bearer ' + token)
        request.send('name=' + name)

    }
}
