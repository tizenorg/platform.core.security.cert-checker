/*
 *  Copyright (c) 2016 Samsung Electronics Co., Ltd All Rights Reserved
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
/*
 * @file        ocsp.cpp
 * @author      Sangwan Kwon (sagnwan.kwon@samsung.com)
 * @version     1.0
 * @brief       Implementation of CAPI
 */

#include "cchecker/ocsp.h"

#include "client/ocsp-client.h"
#include "client/error.h"

__attribute__((visibility("default")))
int cchecker_ocsp_request()
{
	CCHECKER::OcspClient oc;
	return oc.request() == CCHECKER::E_CC_NONE ? 0 : -1;
};
