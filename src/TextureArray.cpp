#include "TextureArray.hpp"

TextureArray::TextureArray(std::array<std::string, 2> textures) : _texturesAmount(textures.size())
{
    int width, height, channels;
    unsigned char* firstTex = stbi_load(textures[0].c_str(), &width, &height, &channels, 4);
    if (!firstTex)
        throw std::runtime_error("Failed to load texture: " + textures[0]);
    
    int textureWidth = width;
    int textureHeight = height;

    glGenTextures(1, &_textureArray);
    glBindTexture(GL_TEXTURE_2D_ARRAY, _textureArray);

    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8,
                 width, height, _texturesAmount,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0,
                   0, 0, 0,
                   width, height, 1,
                   GL_RGBA, GL_UNSIGNED_BYTE, firstTex);
    stbi_image_free(firstTex);
    
    for (int i = 1; i < _texturesAmount; i++) {
        unsigned char* data = stbi_load(textures[i].c_str(), &width, &height, &channels, RGBA);
        
        if (!data) {
            std::cerr << "Warning: Failed to load " << textures[i] << std::endl;
            continue;
        }
        
        if (width != textureWidth || height != textureHeight) {
            std::cerr << "Warning: Texture " << textures[i] 
                      << " has different dimensions!" << std::endl;
        }
        
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0,
                       0, 0, i,  // layer i
                       width, height, 1,
                       GL_RGBA, GL_UNSIGNED_BYTE, data);
        
        stbi_image_free(data);
    }
    
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

}

void TextureArray::bind(unsigned int unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D_ARRAY, _textureArray);
}
TextureArray::~TextureArray()
{
}
