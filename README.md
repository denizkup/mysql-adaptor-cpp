## MySQL adaptor for C++
An adaptor class to execute commit and fetch queries with MySQL and C++.

![MySQL](https://img.shields.io/badge/MySQL-00000F?style=for-the-badge&logo=mysql&logoColor=white)
![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)


It uses `nlohmann/json` to get result from fetch operations. A `json::array` object 
should be given to `fetchQuery` function.

#### Requirements
    mysqlclient

### Dependencies
    nlohmann/json

#### Usage
```cpp
#include <database_adaptor.h>

DatabaseAdaptor dba("username","password","database","localhost");

std::string query = "UPDATE USERS SET NAME = `NEW_USER` WHERE ID = 50" ;
if(dba.commitQuery(query)){
    std::cout << "Commit '"<<  query  << "' has succeeded!" << std::endl;
}
else{
    std::cout << "[ERROR] Commit with query '" << query << "' has failed!" << std::endl;
}

json result_array = json::array();
query = "SELECT * FROM USERS";
if(dba.fetchQuery(json_array,query)){
    std::cout << "Fetch '" << query << "' has succeeded!" << std::endl;
    for(int i = 0; i < json_array.size(); ++i){
        std::string name = result_array[i]["NAME"];
        std::cout << "Result: " << name  << std::endl;
    }
}
else{
    std::cout << "[ERROR] Fetch with query'" << query << "'has failed!" << std::endl;
}

````

    
