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
 * @file        sql_query.h
 * @author      Janusz Kozerski (j.kozerski@samsung.com)
 * @version     1.0
 * @brief       This file is the implementation of SQL queries
 */

#include <list>
#include <string>

#include <dpl/db/sql_connection.h>
#include <cchecker/app.h>

namespace CCHECKER {
namespace DB {
    class SqlQuery {
        public:
            class Exception
            {
                public: DECLARE_EXCEPTION_TYPE(CCHECKER::Exception, Base);
                public: DECLARE_EXCEPTION_TYPE(Base, InternalError);
                public: DECLARE_EXCEPTION_TYPE(Base, TransactionError);
                public: DECLARE_EXCEPTION_TYPE(Base, InvalidArgs);
            };
            SqlQuery() :
                m_connection(NULL),
                m_inUserTransaction(false)
            {};
            SqlQuery(const std::string &path);
            virtual ~SqlQuery();

            // Connecting outside the constructor
            bool connect(const std::string& path);

            // OCSP urls
            /**
             * Returns true if url has been found in database,
             * or false in other case.
             */
            bool get_url(const std::string &issuer, std::string &url);
            void set_url(const std::string &issuer, const std::string &url, const int64_t &date);

            // Apps
            bool add_app_to_check_list(const app_t &app);
            void remove_app_from_check_list(const app_t &app);
            void mark_as_verified(const app_t &app, const app_t::verified_t &verified);
            void get_app_list(std::list<app_t> &apps_buffer);

        protected:
            SqlConnection *m_connection;

        private:
            bool m_inUserTransaction;
            int getDBVersion(void);
            void get_apps(std::list<app_t> &apps_buffer);
            void get_certs(std::list<app_t> &apps_buffer);
            bool check_if_app_exists(const app_t &app);
            bool get_check_id(const app_t &app, int32_t &check_id);
            int verified_enum_to_int(const app_t::verified_t &verified);
            app_t::verified_t verified_int_to_enum(const int &verified);
    };
} // DB
} // CCHECKER
