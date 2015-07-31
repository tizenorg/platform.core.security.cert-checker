/*
 *  Copyright (c) 2015 Samsung Electronics Co., Ltd All Rights Reserved
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License
 */
/**
 * @file        UIBackend.cpp
 * @author      Janusz Kozerski <j.kozerski@samsung.com>
 * @brief       This file implements class for ask user window
 */

#include <bundle.h>
#include <cerrno>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <libintl.h>
#include <notification_internal.h>
#include <notification_error.h>
#include <app_control_internal.h>

#include <cchecker/log.h>
#include <cchecker/UIBackend.h>

namespace CCHECKER {
namespace UI {

namespace { // anonymus
const char *errorToString(int error) {
    if (error == NOTIFICATION_ERROR_INVALID_PARAMETER)
        return "NOTIFICATION_ERROR_INVALID_PARAMETER";
    if (error == NOTIFICATION_ERROR_OUT_OF_MEMORY)
        return "NOTIFICATION_ERROR_OUT_OF_MEMORY";
    if (error == NOTIFICATION_ERROR_FROM_DB)
        return "NOTIFICATION_ERROR_FROM_DB";
    if (error == NOTIFICATION_ERROR_ALREADY_EXIST_ID)
        return "NOTIFICATION_ERROR_ALREADY_EXIST_ID";
    if (error == NOTIFICATION_ERROR_FROM_DBUS)
        return "NOTIFICATION_ERROR_FROM_DBUS";
    if (error == NOTIFICATION_ERROR_NOT_EXIST_ID)
        return "NOTIFICATION_ERROR_NOT_EXIST_ID";
    if (error == NOTIFICATION_ERROR_IO_ERROR)
        return "NOTIFICATION_ERROR_IO_ERROR";
    if (error == NOTIFICATION_ERROR_SERVICE_NOT_READY)
        return "NOTIFICATION_ERROR_SERVICE_NOT_READY";
    if (error == NOTIFICATION_ERROR_NONE)
        return "NOTIFICATION_ERROR_NONE";

    return "UNHANDLED ERROR";
}
} // anonymus

UIBackend::UIBackend(int timeout) :
    m_notification(nullptr),
    m_responseTimeout(timeout)
{}

UIBackend::~UIBackend() {
    notification_free(m_notification);
}

bool UIBackend::create_ui(const std::string &app_id, const std::string &pkg_id)
{
    if(m_notification) {
        notification_free(m_notification);
        m_notification = nullptr;
    }

    m_notification = notification_create(NOTIFICATION_TYPE_NOTI);
    if (m_notification == nullptr) {
        LogError("Failed to create notification.");
        return false;
    }

    int err = notification_set_pkgname(m_notification, "cert-checker");
    if (err != NOTIFICATION_ERROR_NONE) {
        LogError("Unable to set notification pkgname: <" << errorToString(err) << ">");
        return false;
    }

    // Set title
    char *dialogTitle = dgettext(PROJECT_NAME, "SID_TITLE_OCSP_VERIFICATION_FAILED");
    err = notification_set_text(m_notification, NOTIFICATION_TEXT_TYPE_TITLE, dialogTitle, nullptr,
                                NOTIFICATION_VARIABLE_TYPE_NONE);
    if (err != NOTIFICATION_ERROR_NONE) {
        LogError("Unable to set notification title: <" << errorToString(err) << ">");
        return false;
    }

    // Set message
    // App ID may be absent, so in that case we need to use only package ID
    if (app_id == std::string(TEMP_APP_ID)) {
        char *content = dgettext(PROJECT_NAME, "SID_CONTENT_OCSP_PACKAGE VERIFICATION_FAILED");
        err = notification_set_text(m_notification, NOTIFICATION_TEXT_TYPE_CONTENT, content, nullptr,
                                    NOTIFICATION_VARIABLE_TYPE_STRING, pkg_id.c_str(),
                                    NOTIFICATION_VARIABLE_TYPE_NONE);
    }
    else {
        char *content = dgettext(PROJECT_NAME, "SID_CONTENT_OCSP_VERIFICATION_FAILED");
        err = notification_set_text(m_notification, NOTIFICATION_TEXT_TYPE_CONTENT, content, nullptr,
                                    NOTIFICATION_VARIABLE_TYPE_STRING, app_id.c_str(),
                                    NOTIFICATION_VARIABLE_TYPE_STRING, pkg_id.c_str(),
                                    NOTIFICATION_VARIABLE_TYPE_NONE);
    }
    if (err != NOTIFICATION_ERROR_NONE) {
        LogError("Unable to set notification content: <" << errorToString(err) << ">");
        return false;
    }

    char *btn_keep = dgettext(PROJECT_NAME, "SID_BTN_OCSP_KEEP_APP");
    char *btn_uninstall = dgettext(PROJECT_NAME, "SID_BTN_OCSP_UNINSTALL_APP");

    std::string buttons = std::string(btn_keep) + std::string(",") + std::string(btn_uninstall);

    bundle *b = bundle_create();
    if (!b) {
        int erryes = errno;
        LogError("Unable to create bundle: <" << strerror(erryes) << ">");
        return false;
    }

    if (bundle_add(b, "buttons", buttons.c_str())) {
        int erryes = errno;
        LogError("Unable to add button to bundle: <" << strerror(erryes) << ">");
        bundle_free(b);
        return false;
    }

    err = notification_set_execute_option(m_notification, NOTIFICATION_EXECUTE_TYPE_RESPONDING,
                                          nullptr, nullptr, b);
    if (err != NOTIFICATION_ERROR_NONE) {
        LogError("Unable to set execute option: <" << errorToString(err) << ">");
        bundle_free(b);
        return false;
    }
    bundle_free(b);

    err = notification_insert(m_notification, nullptr);
    if (err != NOTIFICATION_ERROR_NONE) {
        LogError("Unable to insert notification: <" << errorToString(err) << ">");
        return false;
    }

    return true;
}

response_e UIBackend::run()
{
    response_e response = response_e(ERROR);
    try {
        int buttonClicked = 0;
        int ret = notification_wait_response(m_notification, m_responseTimeout,
                                             &buttonClicked, nullptr);
        LogDebug("notification_wait_response finished with ret code: [" << ret << "]");

        if (ret == NOTIFICATION_ERROR_NONE) {
            // FIXME: magic numbers
            if (buttonClicked == 1) {
                response = response_e(DONT_UNINSTALL);
                LogDebug("notification_wait_response, button clicked: DON'T UNINSTALL");
            } else if (buttonClicked == 2) {
                response = response_e(UNINSTALL);
                LogDebug("notification_wait_response, Button clicked: UNINSTALL");
            } else {
                response = response_e(ERROR);
                LogError("notification_wait_response, timeouted");
            }
        }
    } catch (const std::exception &e) {
        LogError("Unexpected exception: <" << e.what() << ">");
    } catch (...) {
        LogError("Unexpected unknown exception caught!");
    }
    return response;
}

bool UIBackend::call_popup(const app_t &app)
{
    response_e resp;

    create_ui(app.app_id, app.pkg_id);
    resp = run();
    LogDebug(app.str() << " response: " << resp);
    if (resp == ERROR) {
        return false;
    }

    else if (resp == UNINSTALL) {
        app_control_h service = NULL;
        int result = 0;
        result = app_control_create(&service);
        if (!service || result != APP_CONTROL_ERROR_NONE) {
            return false;
        }
        app_control_set_operation(service, APP_CONTROL_OPERATION_DEFAULT);
        app_control_set_app_id(service, "setting-manage-applications-efl");
        app_control_add_extra_data(service, "viewtype", "application-info");
        app_control_add_extra_data(service, "pkgname", app.pkg_id.c_str());
        app_control_send_launch_request(service, NULL, NULL);
        app_control_destroy(service);
    }
    return true;
}

} // UI
} // CCHECKER
