#include "TextureManager.h"
TextureManager textureManager;


std::shared_ptr<aie::Texture> TextureManager::GetTexture(std::string fileName){
	if (textures.find(fileName) != textures.end()) {
		return textures[fileName];
	}
	else {
		std::shared_ptr<aie::Texture> temp(new aie::Texture(fileName.c_str()));
		textures[fileName] = temp;
		return temp;
	}
}