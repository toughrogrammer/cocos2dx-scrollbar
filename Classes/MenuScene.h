#ifndef __MENUSCENE_SCENE_H__
#define __MENUSCENE_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "UIFlowScrollBar.h"

using namespace cocos2d::extension;
using namespace cocos2d;

class MenuScene : public cocos2d::CCLayerColor, public CCTableViewDataSource, public CCTableViewDelegate
{
private:
    CCArray* datalist;
    int count;
    UIFlowScrollBar* bar;
    bool isV;
	CCTableView* tableView;

public:
    ~MenuScene();
    virtual bool init();
    static cocos2d::CCScene* scene();

	void addDataFive( CCObject* sender );
	void addDatalist(int num);

    void menuCloseCallback(CCObject* pSender);
    CREATE_FUNC(MenuScene);
    
    
    //tabview
    virtual void tableCellHighlight(CCTableView* table, CCTableViewCell* cell);
    virtual void tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell);
    virtual void scrollViewDidScroll(CCScrollView* view);
    virtual void scrollViewDidZoom(CCScrollView* view) {}
    
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    virtual CCSize cellSizeForTable(CCTableView *table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
};

#endif // __MENUSCENE_SCENE_H__
