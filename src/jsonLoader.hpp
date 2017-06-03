#ifndef JSONLOADER_HPP
#define JSONLOADER_HPP

#include <vector>
#include <string>
#include "structs.hpp"

class JsonLoader {
  
  private:
    std::vector<ObjectData*> returnData_;
  
  public:
    void loadJson( std::string filename );
    std::vector<ObjectData*> getObjectData( std::string filename );
    
};

#endif //JSONLOADER_HPP
