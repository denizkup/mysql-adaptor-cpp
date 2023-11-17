/**
 * @file database_adaptor.cpp
 * @author Deniz Küp (deniz.kp@gmail.com)
 * @brief Database adaptor class for MySQL
 * @version 0.1
 * @date 2023-08-13
 * 
 */

#include <stdio.h>
#include <iostream>
#include "mysql.h"
#include <json.hpp>

using json = nlohmann::json;

class DatabaseAdaptor{
    /**
     * @brief Main class for mysql database adaptor
     * 
     */
    private:
        MYSQL     *conn_;     // Connection pointer of mysql to establish connection
        MYSQL_RES *res_;      // Result pointer of mysql to get result from query
        MYSQL_ROW  row_;      // Row instance of mysql to get rows from result
        MYSQL_FIELD *fields_; // Field pointer of mysql to get column fields


        /**
         * @brief Function to connect database with specified database credentials
         * 
         * @return true if connection is established
         * @return false if connection is failed
         */
        bool connectDatabase();

    public:
        /**
         * @brief Construct a new Database Adaptor object with given database credentials
         * 
         * @param user_  Database's username
         * @param password_ Database's password
         * @param database_ Database's name
         * @param host_ Database's address
         */
        DatabaseAdaptor(std::string user_,std::string password_,std::string database_,std::string host_);

        /**
         * @brief Destroy the Database Adaptor object
         * 
         */
        ~DatabaseAdaptor();

        /**
         * @brief Function to fetch queries from mysql
         * 
         * @param result_array_  Json array to get result of fetch as an array of json objects
         * @param query  Query string to fetch
         * @return true  if fetch is succeeded
         * @return false if fetch is failed
         */
        bool fetchQuery(json& result_array_ ,std::string& query);


        /**
         * @brief Function to commit queries to mysql
         * 
         * @param query Query string to commit
         * @return true if commit is succeeded
         * @return false if commit is failed
         */
        bool commitQuery(std::string& query);

        std::string USER,PASSWORD,DATABASE,HOST; // String variables to hold database credentials
};
