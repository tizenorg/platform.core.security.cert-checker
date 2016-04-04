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
/*
 * @file        cert-checker.cpp
 * @author      Janusz Kozerski (j.kozerski@samsung.com)
 * @version     1.0
 * @brief       Cert-checker daemon main loop.
 */

#include <glib.h>

#include <cchecker/log.h>
#include <cchecker/logic.h>

#include <sys/socket.h>
#include <systemd/sd-daemon.h>

using namespace CCHECKER;

void CertSvcGetSocketFromSystemd(int *pSockfd)
{
       int n = sd_listen_fds(0);
       int fd;

		LogDebug("===================== n : " << n); 
       LogError("GetSocketFromSystemd!");
       LogError("file descriptor : " << n);
       for (fd = SD_LISTEN_FDS_START; fd < SD_LISTEN_FDS_START+n; ++fd) {
               if (0 < sd_is_socket_unix(fd, SOCK_STREAM, 1, "/tmp/CertCheckerSocket", 0)) {
                       *pSockfd = fd;
               }
       }
}

int main(void)
{
    LogDebug("Cert-checker start!");

    setlocale(LC_ALL, "");

	int ret;
	CertSvcGetSocketFromSystemd(&ret);
	LogDebug("===================== fd : " << ret); 

    Logic logic;
    if (logic.setup() != NO_ERROR) {
        LogError("Cannot setup logic. Exit cert-checker!");
        return -1;
    }

    LogDebug("Cert-checker exit!");
    return 0;
}
