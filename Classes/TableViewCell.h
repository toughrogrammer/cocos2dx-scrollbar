#ifndef _TABLEVIEW_CELL_H_
#define _TABLEVIEW_CELL_H_

#include "cocos2d.h"
#include "cocos-ext.h"

class TableViewCell : public cocos2d::extension::CCTableViewCell
{
private:
	cocos2d::CCLabelTTF *_label;

public:
	TableViewCell();
	~TableViewCell();

	virtual void draw();
	
	cocos2d::CCLabelTTF* GetLabel() { return _label; }
};

#endif /* __CUSTOMTABELVIEWCELL_H__ */

