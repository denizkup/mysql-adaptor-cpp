/**
 * @file database_adaptor.cpp
 * @author Deniz Küp (deniz.kp@gmail.com)
 * @brief Database adaptor class for MySQL
 * @version 0.1
 * @date 2023-08-13
 * 
 */

#include <database_adaptor.h>

DatabaseAdaptor::DatabaseAdaptor(std::string user_,std::string password_,std::string database_,std::string host_){
    USER     = user_;
    PASSWORD = password_;
    DATABASE = database_;
    HOST     = host_;
}
DatabaseAdaptor::~DatabaseAdaptor(){

}

bool DatabaseAdaptor::connectDatabase(){

    bool result = false;
    try{
        conn_ = mysql_init(0);
        if(mysql_real_connect(conn_, HOST.c_str(), USER.c_str(), PASSWORD.c_str(), DATABASE.c_str(), 0, NULL, 0)){
            result = true;
        }
        else{
            std::cout << "Connection has failed!" << std::endl;
        }
    }
    catch(const std::exception& e){
        std::cout << "Exception occured while trying to establish mysql connection! [Exception]: " << e.what() << std::endl;
    }
    return result;
}

bool DatabaseAdaptor::fetchQuery(json& result_array_ ,std::string& query){
    bool result = false;
    json json_;

    try{
        bool connection = connectDatabase();
        if(connection){
            int query_res = mysql_query(conn_,query.c_str());
            if(query_res == 0){
                res_ = mysql_store_result(conn_);
                int num_fields = mysql_num_fields(res_);

                while((row_ = mysql_fetch_row(res_)) != NULL){
                    unsigned long *lengths;
                    lengths = mysql_fetch_lengths(res_);
                    fields_ = mysql_fetch_fields(res_);
                    for(int i = 0; i < num_fields; i++){
                        json_[fields_[i].name] = row_[i] ? row_[i] : "NULL";
                    }
                    result_array_.push_back(json_);
                }
                result = true;
            }
        }
    }
    catch(const std::exception& e){
        std::cout << "[ERROR] Exception occured while trying to fetching query! [Exception]: " << e.what() << std::endl;
    }

    mysql_close(conn_);

    return result;
}

bool DatabaseAdaptor::commitQuery(std::string& query){
    bool result = false;
    try{
        bool connection = connectDatabase();
        if(connection){
            int query_res = mysql_query(conn_,query.c_str());
            if(query_res == 0){         
                if(!mysql_commit(conn_)){
                    result = true;
                }
            }
        }
    }
    catch(const std::exception& e){
        std::cout << "[ERROR] Exception occured while trying to commit query! [Exception]: " << e.what() << std::endl;
    }

    mysql_close(conn_);

    return result;
}



