#include <Geode/Geode.hpp>
#include "Geode/loader/Dirs.hpp"
#include "export.hpp"

using namespace geode::prelude;

$on_mod(Loaded) {
    auto path = (geode::dirs::getGeodeDir() / "modpack.json").string();
saveModsToFile(path);
}