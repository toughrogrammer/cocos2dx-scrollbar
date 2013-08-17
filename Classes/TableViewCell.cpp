#include "TableViewCell.h"

using namespace cocos2d;
using namespace cocos2d::extension;

TableViewCell::TableViewCell()
{
	_label = CCLabelTTF::create( "Cell", "Arial", 20 );
	_label->setAnchorPoint( ccp( 0, 0 ) );
	_label->setPosition( ccp( 0, 0 ) );
	this->addChild( _label );
}

TableViewCell::~TableViewCell()
{
	this->removeChild( _label );
}

void TableViewCell::draw()
{
	CCTableViewCell::draw();

	//draw bounding box
	CCPoint pos = getPosition();
	CCSize size = CCSizeMake(178, 200);
	CCPoint vertices[4]={
		ccp(pos.x + 1, pos.y + 1),
		ccp(pos.x + size.width - 1, pos.y + 1),
		ccp(pos.x + size.width - 1, pos.y + size.height - 1),
		ccp(pos.x + 1, pos.y + size.height - 1),
	};
	ccDrawColor4B(0, 0, 255, 255);
	ccDrawPoly(vertices, 4, true);
}
