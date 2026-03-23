#include "export.hpp"

#include <fstream>

#include <Geode/loader/Loader.hpp>
#include <Geode/loader/Mod.hpp>

#include <matjson.hpp>

using namespace geode::prelude;

matjson::Value exportMods() {
    auto modsArray = matjson::Value::array();

    for (auto mod : Loader::get()->getAllMods()) {
        if (!mod->isOrWillBeEnabled()) continue;

        auto modObj = matjson::Value::object();
        modObj["id"] = mod->getID();
        modObj["version"] = mod->getVersion().toNonVString();

        modsArray.push(modObj);
    }

    auto root = matjson::Value::object();
    root["name"] = "My Modpack";
    root["version"] = "1.0.0";
    root["gameVersion"] = Loader::get()->getGameVersion();
    root["mods"] = modsArray;

    return root;
}

void saveModsToFile(const std::string& path) {
    auto json = exportMods();

    std::ofstream file(path);
    if (!file.is_open()) {
        log::error("Failed to open file: {}", path);
        return;
    }

    file << json.dump(4);
    file.close();

    log::info("Exported modpack to {}", path);
}