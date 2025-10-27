#pragma once

#include "InputContext.hpp"
#include "JsonParser.hpp"
#include "DataObjects/Tileset.hpp"

class NlohmannJsonParser : public JsonParser
{

public:
    // !DEBT! should have a loadAsset<DataObject>(); that would build the classes from the json.
    Animation::TextureData parseTextureData(const std::string& textureDataPath) override;
    static InputContext::Context parseInputContext(const std::string& inputContextId);
    static TileSetDTO parseTileSet(const std::string& tileSetAssetPath);
};
