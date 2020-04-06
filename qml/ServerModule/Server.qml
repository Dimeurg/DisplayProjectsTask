pragma Singleton
import QtQuick 2.0

QtObject{

    function loginToServer(email, password)
    {
        var token
        var request = new XMLHttpRequest()
        request.open('POST', 'https://api.quwi.com/v2/auth/login', false)
        request.onreadystatechange = function() {
            if (request.readyState === XMLHttpRequest.DONE) {
                if (request.status === 200) {
                    var result = JSON.parse(request.responseText)
                    token = result.token
                }

                else {
                    console.log("HTTP:", request.status, request.statusText)
                }
            }
        }

        request.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded')
        request.setRequestHeader('Client-Device', 'windows')
        request.send('email='+ email + '&password=' + password)
        return token
    }

    function getProjectsInfo(token)
    {
        //var request = new XMLHttpRequest()
        //var resultArray = new Array();
        //var index = 0
        //request.open('GET', 'https://api.quwi.com/v2/projects-manage/index')
        //request.onreadystatechange = function() {
        //    if (request.readyState === XMLHttpRequest.DONE) {
        //        if (request.status && request.status === 200) {
        //            var result = JSON.parse(request.responseText)
        //            result.projects.forEach((project)=>{
        //                        resultArray[index++] = {}
        //                    })                                                )
        //
        //        } else {
        //            console.log("HTTP:", request2.status, request2.statusText)
        //        }
        //    }
        //}

       // request.setRequestHeader('Authorization', 'Bearer ' + token)
      //  request.send()
    }
}
