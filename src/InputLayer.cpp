#include "../include/InputLayer.hpp"

#include <Geode/cocos/cocoa/CCObject.h>
#include <Geode/binding/CCTextInputNode.hpp>
#include <Geode/cocos/menu_nodes/CCMenuItem.h>
#include <Geode/binding/FLAlertLayer.hpp>

using namespace geode::prelude;

InputLayer* InputLayer::create(
    const std::string& title,
    const std::string& message,
    const std::string& placeholder1,
    const std::string& placeholder2,
    const std::function<void(std::string, std::string)>& callback
) {
    auto ret = new InputLayer();
    if (ret && ret->init(title, message, placeholder1, placeholder2, callback)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool InputLayer::init(
    const std::string& title,
    const std::string& message,
    const std::string& placeholder1,
    const std::string& placeholder2,
    const std::function<void(std::string, std::string)>& callback
) {
    if (!CCLayerColor::initWithColor({0, 0, 0, 150})) return false;

    m_callback = callback;

    auto winSize = CCDirector::sharedDirector()->getWinSize();

    // Background
    auto bg = CCScale9Sprite::create("GJ_square01.png");
    bg->setContentSize({300, 200});
    bg->setPosition(winSize / 2);
    this->addChild(bg);

    // Title
    auto titleLabel = CCLabelBMFont::create(title.c_str(), "goldFont.fnt");
    titleLabel->setPosition({winSize.width / 2, winSize.height / 2 + 80});
    this->addChild(titleLabel);

    // Message
    auto messageLabel = CCLabelBMFont::create(message.c_str(), "chatFont.fnt");
    messageLabel->setPosition({winSize.width / 2, winSize.height / 2 + 40});
    this->addChild(messageLabel);

    // Input field 1
    m_input1 = CCTextInputNode::create(200, 20, placeholder1.c_str(), "bigFont.fnt");
    m_input1->setPosition({winSize.width / 2, winSize.height / 2});
    this->addChild(m_input1);

    // Input field 2
    m_input2 = CCTextInputNode::create(200, 20, placeholder2.c_str(), "bigFont.fnt");
    m_input2->setPosition({winSize.width / 2, winSize.height / 2 - 40});
    this->addChild(m_input2);

    // Confirm button
    auto confirmSprite = ButtonSprite::create("Confirm", "goldFont.fnt", "GJ_button_01.png");
    auto confirmButton = CCMenuItemSpriteExtra::create(confirmSprite, this, menu_selector(InputLayer::onConfirm));
    confirmButton->setPosition({winSize.width / 2, winSize.height / 2 - 100});

    auto menu = CCMenu::create(confirmButton, nullptr);
    menu->setPosition(CCPointZero);
    this->addChild(menu);

    return true;
}

void InputLayer::onConfirm(CCObject*) {
    auto input1 = std::string(m_input1->getString());
    auto input2 = std::string(m_input2->getString());

    if (m_callback) {
        m_callback(input1, input2);
    }

    this->removeFromParentAndCleanup(true);
}

void InputLayer::show() {
    CCDirector::sharedDirector()->getRunningScene()->addChild(this);
}
