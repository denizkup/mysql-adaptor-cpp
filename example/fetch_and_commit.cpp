#include <database_adaptor.h>

int main(int argc,char** argv)
{
    DatabaseAdaptor dba("deniz","deniz","TEST","localhost");

    std::string query = "UPDATE USERS SET NAME = `NEW_USER` WHERE ID = 50" ;
    if(dba.commitQuery(query)){
        std::cout << "Commit '"<<  query  << "' has succeeded!" << std::endl;
    }
    else{
        std::cout << "[ERROR] Commit with query '" << query << "' has failed!" << std::endl;
    }
    
    json result_array = json::array();
    query = "SELECT * FROM USERS";
    if(dba.fetchQuery(result_array,query)){
        std::cout << "Fetch '" << query << "' has succeeded!" << std::endl;
        for(int i = 0; i < result_array.size(); ++i){
            std::string name = result_array[i]["NAME"];
            std::cout << "Result: " << name  << std::endl;
        }
    }
    else{
        std::cout << "[ERROR] Fetch with query '" << query << "' has failed!" << std::endl;

    }
}
