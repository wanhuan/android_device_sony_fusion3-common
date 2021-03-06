/*
 * Copyright (C) 2016 The CyanogenMod Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
    /*
     * The proprietary illumination_service binary has a bug - it invokes
     * accept() without initializing *addrlen.  Fix up obviously broken values
     * so that the call does not fail with EINVAL.
     */
    if (addrlen && ((*addrlen < 0) || (*addrlen > sizeof(struct sockaddr_un))))
        *addrlen = sizeof(struct sockaddr_un);

    return accept4(sockfd, addr, addrlen, 0);
}
