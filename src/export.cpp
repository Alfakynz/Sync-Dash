#include "../include/export.hpp"

#include <fstream>
#include <filesystem>
#include <string>

#include <Geode/loader/Loader.hpp>
#include <Geode/loader/Mod.hpp>

#include <matjson.hpp>

using namespace geode::prelude;

matjson::Value getMods(std::string name, std::string version) {
    auto modsArray = matjson::Value::array();

    for (auto mod : Loader::get()->getAllMods()) {
        if (!mod->isOrWillBeEnabled()) continue;

        auto modObj = matjson::Value::object();
        modObj["id"] = mod->getID();
        modObj["version"] = mod->getVersion().toNonVString();

        modsArray.push(modObj);
    }

    auto root = matjson::Value::object();
    root["name"] = name;
    root["version"] = version;
    root["gameVersion"] = Loader::get()->getGameVersion();
    root["mods"] = modsArray;

    return root;
}

bool saveModsToFile(auto json, const std::string& path) {
    try {
        std::filesystem::path fsPath(path);
        // Create directories if they don't exist
        std::filesystem::create_directories(fsPath.parent_path());

        std::ofstream file(path);
        if (!file.is_open()) {
            log::error("Failed to open file: {}", path);
            return false;
        }

        file << json.dump(4);
        file.close();

        log::info("Exported modpack to {}", path);
        return true;
    }
    catch (const std::exception& e) {
        log::error("Exception while exporting modpack: {}", e.what());
        return false;
    }
}

bool exportMods(std::string name, std::string version) {
    auto json = getMods(name, version);
    auto path = (geode::dirs::getGeodeDir() / "modpacks" / (name + ".json")).string();
    return saveModsToFile(json, path);
}
