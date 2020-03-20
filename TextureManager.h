#pragma once
#include <Texture.h>
#include <unordered_map>
#include <string>


class TextureManager {

private:
	std::unordered_map<std::string, std::shared_ptr<aie::Texture>> textures;

public:
	std::shared_ptr<aie::Texture> GetTexture(std::string fileName);
};
extern TextureManager textureManager;