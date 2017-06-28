#ifndef JSONLOADER_HPP
#define JSONLOADER_HPP

#include <vector>
#include <string>
#include <memory>
#include "structs.hpp"

class JsonLoader {
  
  private:
  
  public:
    
    void loadDataMain( std::vector<std::unique_ptr<ObjectData>>& commonObjectsData, std::vector<std::unique_ptr<ObjectData>>& projectileObjectsData );
    
    void loadLevel( int levelNumber, std::vector<std::unique_ptr<ObjectData>>& levelObjectsData, std::vector<std::unique_ptr<ObjectData>>& projectileObjectsData, std::string& backgroundFilename, int& pointsNeeded );
    
};

#endif //JSONLOADER_HPP
