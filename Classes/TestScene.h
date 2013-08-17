#ifndef __TEST_SCENE_H__
#define __TEST_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class TableViewController;
class ScrollBar;
class TestScene : public cocos2d::CCLayerColor
{
private:
	CCTableView *_tableView;
	TableViewController *_tableViewController;
	ScrollBar *_scrollBar;

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();

	virtual void onExit();
    
    // a selector callback
	void generateItem(CCObject* pSender);
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(TestScene);
};

#endif // __HELLOWORLD_SCENE_H__
