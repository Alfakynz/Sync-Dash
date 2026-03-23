#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

#include "../include/SDLayer.hpp"

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto menu = this->getChildByID("bottom-menu");
        if (!menu) return true;

        // Sync Dash button
        auto sprite = CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png");
        sprite->setScale(1);

        auto button = CCMenuItemSpriteExtra::create(
            sprite,
            this,
            menu_selector(MyMenuLayer::onOpenMenu)
        );

        menu->addChild(button);
        menu->updateLayout();

        return true;
    }

    void onOpenMenu(CCObject*) {
        auto layer = SDLayer::create();

        auto scene = CCScene::create();
        scene->addChild(layer);

        CCDirector::sharedDirector()->pushScene(
            CCTransitionFade::create(0.4f, scene)
        );
    }
};