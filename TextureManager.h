#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

#ifndef PROJECT_3_FINAL_TEXTUREMANAGER_H
#define PROJECT_3_FINAL_TEXTUREMANAGER_H

using namespace std;


class TextureManager {

    static unordered_map<string, sf::Texture> textures;
    static void LoadTexture(const string& textureName);
public:
    static sf::Texture& GetTexture(const string& textureName);
    static void Clear();



};


#endif //PROJECT_3_FINAL_TEXTUREMANAGER_H
