﻿
// Timeout in milliseconds for API call
var timeout = 10000;

// underComm = 0 : No communication state, >= 1 : Communication state
var underComm = 0;

// [0] : for API-1, [1] : for API-2, [2] : for API-3, ...
var statusCode = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
var responseData = [{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}];

// For login info
var initLoginModalFlag = false;
var loginId = "";
var loginPw = "";

// Init flag of loading modal
var initLoadingModalFlag = false;

// Client messages
var clientMsg = {};
var clientLanguage = 0;

function initLoginModal(func) {
    var loginModal = $('<div id="login_Modal" class="modal fade" tabindex="-1" role="dialog" data-keyboard="false" data-backdrop="static">');
    var modalDialog = $('<div class="modal-dialog">');
    var modalContent = $('<div class="modal-content">');
    var modalHeader = $('<div class="modal-header" style="padding: 0px; text-align: center;"><h3 style="margin-top: 5px;">Login</h3></div>');
    var modalBody = $('<div class="modal-body"><div style="height:150px"><div class="form-group"><input type="text" class="form-control" id="loginId" placeholder="Your Email *" value="" /></div><div class="form-group"><input type="password" class="form-control" id="loginPw" placeholder="Your Password *" value="" /></div><div id="login_Modal_Body"></div><button type="button" id="commandBtnAdd" class="btn btn-primary" onclick="tryLogin(' + func + ')">Login</button></div></div>');

    modalContent.append(modalHeader);
    modalContent.append(modalBody);
    modalDialog.append(modalContent);
    loginModal.append(modalDialog);
    $('body').append(loginModal);
}

function tryLogin(func) {
    loginId = $("#loginId").val();
    loginPw = $("#loginPw").val();
    if (func() == true) {
        $('#login_Modal').modal('hide');
    } else {
        $('#login_Modal_Body').empty();
        $('#login_Modal_Body').append('The email address or password is incorrect.');
    }
}

function showLoginModal(func) {
    if (initLoginModalFlag == false) {
        initLoginModalFlag = true;
        initLoginModal(func);
    }
    $('#login_Modal').modal('show');
}

function initLoadingModal() {
    var loadingModal = $('<div id="loading_Modal" class="modal fade" tabindex="-1" role="dialog" data-keyboard="false" data-backdrop="static">');
    var modalDialog = $('<div class="modal-dialog">');
    var modalContent = $('<div class="modal-content">');
    var modalHeader = $('<div class="modal-header" style="padding: 0px; text-align: center;"><h3 style="margin-top: 5px;">Now loading ...</h3></div>');
    var modalBody = $('<div class="modal-body"><div style="height:20px"><div class="progress"><div class="progress-bar progress-bar-striped active" role="progressbar" aria-valuenow="40" aria-valuemin="0" aria-valuemax="100" style="width:100%"> </div></div></div></div>');

    modalContent.append(modalHeader);
    modalContent.append(modalBody);
    modalDialog.append(modalContent);
    loadingModal.append(modalDialog);
    $('body').append(loadingModal);
}

function addClientMessage(code, msg) {
    if (msg.en !== undefined && msg.ja !== undefined) {
        clientMsg[code] = msg;
    }
}

function deleteClientMessage(code) {
    delete clientMsg[code];
}

function getClientMessageEn(code) {
    return clientMsg[code].en;
}

function getClientMessageJa(code) {
    return clientMsg[code].ja;
}

function setClientLanguage(lang) {
    clientLanguage = lang;
}

function getClientMessage(code) {
    if (clientLanguage == 0) {
        return clientMsg[code].en;
    }
    if (clientLanguage == 1) {
        return clientMsg[code].ja;
    }
}

function displayAlertSuccess(parent, msg) {
    $(parent + ' .alert').remove();
    $(parent).append('<div class="alert alert-success" role="alert">' + msg + '</div>');
}

function displayAlertDanger(parent, msg) {
    $(parent + ' .alert').remove();
    $(parent).append('<div class="alert alert-danger" role="alert">' + msg + '</div>');
}

function displayAlertWarning(parent, msg) {
    $(parent + ' .alert').remove();
    $(parent).append('<div class="alert alert-warning" role="alert">' + msg + '</div>');
}

function displayAlertInfo(parent, msg) {
    $(parent + ' .alert').remove();
    $(parent).append('<div class="alert alert-info" role="alert">' + msg + '</div>');
}

function apiCall(method, url, request, index, targetFunc) {
    if (method != null && url != null && index != -1) {
        sendRequestRecvResponse(method, url, request, index, true);
    }
    if (targetFunc != null) {
        setTimeout(function() {waitForResponse(0, targetFunc);}, 1);
    }
}

function waitForResponse(count, targetFunc) {
    if (initLoadingModalFlag == false) {
        initLoadingModalFlag = true;
        initLoadingModal();
    }
    if (targetFunc == null) {
        return;
    }
    if (count < 10) {
        if (underComm == 0) {
            targetFunc();
        } else {
            setTimeout(function() {waitForResponse(count + 1, targetFunc);}, 50);
        }
        return;
    }
    if (underComm == 0) {
        $('#loading_Modal').modal('hide');
        targetFunc();
        return;
    }
    $('#loading_Modal').modal('show');
    setTimeout(function() {waitForResponse(count + 1, targetFunc);}, 500);
}

function sendRequestRecvResponse(method, url, request, index, asyncFlag) {
    underComm++;
    if (method === 'GET' || method === 'DELETE') {
        $.ajax({
            type: method,
            dataType: 'json',
            url: url,
            data: request,
            async: asyncFlag,
            timeout: timeout,
            beforeSend: function( xhr, settings ) {
                xhr.setRequestHeader('Authorization', 'Bearer ' + loginId + loginPw);
            },
            success: function(msg, textStatus, xhr) {
                statusCode[index] = xhr.status;
                responseData[index] = {};
                $.extend(responseData[index], msg);
                underComm--;
            },
            error: function(xhr, textStatus, errorThrown) {
                if (textStatus === 'timeout') {
                    statusCode[index] = -1;
                    responseData[index] = {};
                } else {
                    statusCode[index] = xhr.status;
                    try {
                        $.extend(responseData[index], JSON.parse(xhr.responseText));
                    } catch (e) {
                        responseData[index] = {};
                    }
                }
                underComm--;
            }
        });
    } else {
        $.ajax({
            type: method,
            dataType: 'json',
            url: url,
            data: JSON.stringify(request),
            contentType: 'application/json',
            async: asyncFlag,
            timeout: timeout,
            beforeSend: function( xhr, settings ) {
                xhr.setRequestHeader('Authorization', 'Bearer ' + loginId + loginPw);
            },
            success: function(msg, textStatus, xhr) {
                statusCode[index] = xhr.status;
                responseData[index] = {};
                $.extend(responseData[index], msg);
                underComm--;
            },
            error: function(xhr, textStatus, errorThrown) {
                if (textStatus === 'timeout') {
                    statusCode[index] = -1;
                    responseData[index] = {};
                } else {
                    statusCode[index] = xhr.status;
                    try {
                        $.extend(responseData[index], JSON.parse(xhr.responseText));
                    } catch (e) {
                        responseData[index] = {};
                    }
                }
                underComm--;
            }
        });
    }
    return;
}
