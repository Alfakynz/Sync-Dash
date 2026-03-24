#include <functional>
#include <string>

#include <Geode/cocos/layers_scenes_transitions_nodes/CCLayer.h>
#include <Geode/cocos/cocoa/CCObject.h>
#include <Geode/binding/CCTextInputNode.hpp>

class InputLayer : public cocos2d::CCLayerColor {
protected:
    CCTextInputNode* m_input1;
    CCTextInputNode* m_input2;
    std::function<void(std::string, std::string)> m_callback;

    bool init(
        const std::string& title,
        const std::string& message,
        const std::string& placeholder1,
        const std::string& placeholder2,
        const std::function<void(std::string, std::string)>& callback
    );

    void onConfirm(cocos2d::CCObject*);

public:
    static InputLayer* create(
        const std::string& title,
        const std::string& message,
        const std::string& placeholder1,
        const std::string& placeholder2,
        const std::function<void(std::string, std::string)>& callback
    );
    void show();
};
