#include "../include/SDLayer.hpp"

#include <Geode/cocos/cocoa/CCObject.h>
#include <Geode/cocos/menu_nodes/CCMenuItem.h>
#include <Geode/loader/Dirs.hpp>

#include "../include/export.hpp"

using namespace geode::prelude;

SDLayer* SDLayer::create() {
    auto ret = new SDLayer();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool SDLayer::init() {
    if (!CCLayer::init()) return false;

    // Enable keyboard (ESC support)
    this->setKeypadEnabled(true);

    auto winSize = CCDirector::sharedDirector()->getWinSize();

    // Background
    auto bg = CCSprite::create("GJ_gradientBG.png");

    bg->setPosition({ winSize.width / 2, winSize.height / 2 });

    // Scale to cover screen
    bg->setScaleX(winSize.width / bg->getContentSize().width);
    bg->setScaleY(winSize.height / bg->getContentSize().height);
    bg->setColor({ 50, 50, 50 });

    this->addChild(bg);

    // Title
    auto title = CCLabelBMFont::create("Sync Dash", "bigFont.fnt");
    title->setPosition({ winSize.width / 2, winSize.height - 50 });

    // Back button
    auto backSprite = CCSprite::createWithSpriteFrameName("GJ_arrow_03_001.png");
    auto backButton = CCMenuItemSpriteExtra::create(backSprite, this, menu_selector(SDLayer::onBack));
    backButton->setSizeMult(1.2f);

    // Menu for back button
    auto menuBack = CCMenu::create(backButton, nullptr);
    menuBack->setPosition({24, winSize.height - 23});

    // Export button
    auto exportSprite = ButtonSprite::create("Export Modpack", "goldFont.fnt", "GJ_button_01.png");
    auto exportButton = CCMenuItemSpriteExtra::create(exportSprite, this, menu_selector(SDLayer::onExport));
    exportButton->setPosition({ 0, 50 });

    // Import button
    auto importSprite = ButtonSprite::create("Import Modpack", "goldFont.fnt", "GJ_button_01.png");
    auto importButton = CCMenuItemSpriteExtra::create(importSprite, this, menu_selector(SDLayer::onImport));
    importButton->setPosition({ 0, 0 });

    // Menu
    auto menu = CCMenu::create(exportButton, importButton, nullptr);
    menu->setPosition({ winSize.width / 2, winSize.height / 2 });
    menu->updateLayout();

    this->addChild(title);
    this->addChild(menuBack);
    this->addChild(menu);

    return true;
}

void SDLayer::onBack(CCObject*) {
    CCDirector::sharedDirector()->popSceneWithTransition(0.4f, PopTransition::kPopTransitionFade);
}

void SDLayer::onExport(CCObject*) {
    auto path = (geode::dirs::getGeodeDir() / "modpacks" / "modpack.json").string();
    bool success = saveModsToFile(path);

    if (success) {
        FLAlertLayer::create(
            "Export",
            "Modpack exported successfully!",
            "OK"
        )->show();
    } else {
        FLAlertLayer::create(
            "Export Failed",
            "Failed to export modpack. Check logs for details.",
            "OK"
        )->show();
    }
}

void SDLayer::onImport(CCObject*) {
    FLAlertLayer::create(
        "Import",
        "Importing modpacks is not implemented yet.",
        "OK"
    )->show();
}

// ESC key support
void SDLayer::keyBackClicked() {
    this->onBack(nullptr);
}
