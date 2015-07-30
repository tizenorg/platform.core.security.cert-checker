/*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd All Rights Reserved
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
 * @file        certs_.h
 * @author      Janusz Kozerski (j.kozerski@samsung.com)
 * @version     1.0
 * @brief       Implementation of Certs for testing
 */

#include <cchecker/certs.h>

#ifndef CCHECKER_CERTS__H
#define CCHECKER_CERTS__H

using namespace CCHECKER;

class Certs_ : public Certs {
    public:
        virtual ~Certs_();
        ocsp_response_t check_ocsp_chain_ (const chain_t &chain);
        void find_app_signatures_ (app_t &app, const std::string &app_path, ocsp_urls_t &ocsp_urls);
};

#endif //CCHECKER_CERTS__H