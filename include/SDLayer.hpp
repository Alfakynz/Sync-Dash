#pragma once
#include <Geode/cocos/cocoa/CCObject.h>
#include <Geode/Geode.hpp>

class SDLayer : public cocos2d::CCLayer {
public:
    static SDLayer* create();
    bool init();

    void onBack(cocos2d::CCObject*);
    void onExport(cocos2d::CCObject*);
    void onImport(cocos2d::CCObject*);

    virtual void keyBackClicked();
};