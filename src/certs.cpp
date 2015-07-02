/*
 * Copyright (c) 2015 Samsung Electronics Co., Ltd All Rights Reserved
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */
/*
 * @file        certs.cpp
 * @author      Janusz Kozerski (j.kozerski@samsung.com)
 * @version     1.0
 * @brief       This file is the implementation of certificates logic
 *              Getting out findinf app signature, getting certificates out of
 *              signature. Checking OCSP
 */
#include <sys/types.h>
#include <dirent.h>
#include <list>
#include <memory>
#include <string>
#include <set>
#include <vector>
#include <vcore/Certificate.h>
#include <vcore/SignatureReader.h>
#include <vcore/SignatureFinder.h>
#include <vcore/WrtSignatureValidator.h>
#include <vcore/VCore.h>

#include <cchecker/certs.h>
#include <cchecker/log.h>

namespace {
const std::string signatureXmlSchemaPath = std::string(tzplatform_getenv(TZ_SYS_SHARE))
        + std::string("/app-installers/signature_schema.xsd");
}

namespace CCHECKER {

Certs::Certs()
{
    ValidationCore::VCoreInit();
}

Certs::~Certs()
{
    ValidationCore::VCoreDeinit();
}

void Certs::get_certificates (app_t &app, ocsp_urls_t &ocsp_urls)
{
    std::vector<std::string> signatures;
    (void) signatures;

    if (0 != tzplatform_set_user(app.uid)) {
        LogError("Cannot set user: tzplatform_set_user has failed");
        return;
    }

    if (app.app_id == TEMP_APP_ID) {
        LogDebug("Temporary app_id. Searching for apps in package.");
        search_app(app, ocsp_urls);
    }
    else {
        const char *pkg_path = tzplatform_mkpath(TZ_USER_APP, app.pkg_id.c_str());
        std::string app_path = std::string(pkg_path) + std::string("/") + app.app_id;
        find_app_signatures (app, app_path, ocsp_urls);
    }

}

/* Since there's no information about application in signal,
 * and we've got information only about package, we have to check
 * all applications that belongs to that package
 */
void Certs::search_app (app_t &app, ocsp_urls_t &ocsp_urls)
{
    DIR *dp;
    struct dirent *entry;
    const char *pkg_path = tzplatform_mkpath(TZ_USER_APP, app.pkg_id.c_str());
    if (!pkg_path) {
        LogError("tzplatform_mkpath has returned NULL for TZ_USER_APP");
        return;
    }

    dp = opendir(pkg_path);
    if (dp != NULL) {
        while ((entry = readdir(dp))) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 && entry->d_type == DT_DIR) {
                LogDebug("Found app: " << entry->d_name);
                std::string app_path = std::string(pkg_path) + std::string("/") + std::string(entry->d_name);
                find_app_signatures(app, app_path, ocsp_urls);
            }
        }
        closedir(dp); //close directory
    }
    else
        LogError("Couldn't open the package directory.");
}

// Together with certificates we can pull out OCSP URLs
void Certs::find_app_signatures (app_t &app, const std::string &app_path, ocsp_urls_t &ocsp_urls)
{
    ValidationCore::SignatureFinder signature_finder(app_path);
    ValidationCore::SignatureFileInfoSet signature_files;

    if (signature_finder.find(signature_files) !=
            ValidationCore::SignatureFinder::NO_ERROR) {
           LogError("Error while searching for signatures in " << app_path.c_str());
           return;
    }
    LogDebug("Number of signature files: " << signature_files.size());

    LogDebug("Searching for certificates");
    for (auto iter = signature_files.begin(); iter != signature_files.end(); iter++){
        LogDebug("Checking signature");
        ValidationCore::SignatureData data(app_path + std::string("/") + (*iter).getFileName(),
                (*iter).getFileNumber());
        LogDebug("signatureXmlSchemaPath: " << signatureXmlSchemaPath);
        try {
            ValidationCore::SignatureReader reader;
            reader.initialize(data, signatureXmlSchemaPath);
            reader.read(data);
            ValidationCore::CertificateList certs = data.getCertList();
            for (auto cert_iter = certs.begin(); cert_iter != certs.end(); cert_iter++ ){
                std::string app_cert = (*cert_iter)->getBase64();
                app.certificates.push_back(app_cert);
                LogDebug("Certificate: " << app_cert << " has been added");

                // check OCSP URL
                std::string ocsp_url = DPL::ToUTF8String((*cert_iter)->getOCSPURL());
                if (ocsp_url != std::string("")) {
                    std::string issuer = DPL::ToUTF8String(
                            (*cert_iter)->getCommonName(ValidationCore::Certificate::FIELD_ISSUER));
                    int64_t time = (*cert_iter)->getNotBefore();
                    url_t url(issuer, ocsp_url, time);
                    ocsp_urls.push_back(url);
                    LogDebug("Found OCSP URL: " << ocsp_url << " for issuer: " <<  issuer << ", time: " << time);

                }
            }
        } catch (const ValidationCore::ParserSchemaException::Base& exception) {
            // Needs to catch parser exceptions
            LogError("Error occured in ParserSchema: " << exception.DumpToString());
        }
    }
}

} // CCHECKER
