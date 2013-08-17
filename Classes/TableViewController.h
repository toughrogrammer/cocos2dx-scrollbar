
#ifndef _TABLEVIEW_CONTROLLER_H_
#define _TABLEVIEW_CONTROLLER_H_

#include "cocos2d.h"
#include "cocos-ext.h"

#include "TableViewCell.h"
#include "DataManager.h"
#include "ScrollBar.h"

USING_NS_CC;
USING_NS_CC_EXT;

const int COLOR_LAYER_TAG = 44;

class TableViewController : public CCTableViewDataSource, public CCTableViewDelegate 
{
private:
	DataManager *_dmgr;
	CCSize _cellSize;
	ScrollBar *_bar;


public:
	TableViewController( CCSize size );
	~TableViewController();

	CCSize GetCellSize() { return _cellSize; }
	void SetCellSize( CCSize size ) { _cellSize = size; }
	
	void LaunchScrollBar( ScrollBar *bar ) { _bar = bar; _bar->Refresh(); }

	// DataSource
	virtual unsigned int numberOfCellsInTableView(CCTableView *table);
	virtual CCSize cellSizeForTable(CCTableView *table);
	virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);

	// Delegator
	virtual void scrollViewDidScroll(CCScrollView* view);
	virtual void scrollViewDidZoom(CCScrollView* view);
	virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
	virtual void tableCellHighlight(CCTableView* table, CCTableViewCell* cell);
	virtual void tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell);
};

#endif