
#include "TableViewController.h"


//
// DataSource
//
TableViewController::TableViewController( CCSize size ) 
	: _bar(0)
{
	_dmgr = DataManager::Self();
	
	SetCellSize( size );
}

TableViewController::~TableViewController() 
{

}

unsigned int TableViewController::numberOfCellsInTableView(CCTableView *table) {
	return _dmgr->GetData().size();
}

CCSize TableViewController::cellSizeForTable(CCTableView *table) {
	return _cellSize;
}

CCTableViewCell* TableViewController::tableCellAtIndex(CCTableView *table, unsigned int idx) {

	TableViewCell *cell = (TableViewCell*)table->dequeueCell();

	if (cell == NULL) {
		cell = new TableViewCell;
		cell->setContentSize( _cellSize );
	}

	CCString *str = CCString::createWithFormat( "C%d", _dmgr->GetData()[idx] );
	cell->GetLabel()->setString( str->getCString() );

	return cell;
}


//
// Delegate
//
void TableViewController::scrollViewDidScroll(CCScrollView* view) 
{
	if(_bar != NULL) 
	{
		_bar->Refresh();
	}
}

void TableViewController::scrollViewDidZoom(CCScrollView* view)
{

}

void TableViewController::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
	int p = cell->getIdx();

	CCPoint offset = table->getContentOffset();

	table->removeCellAtIndex(p);
	table->reloadData();
	
	//여기까지 하면 잘 지워지지만 포코스가 무조건 맨 위로 맞춰진다. 그렇다고 원하는 인덱스 위치로 이동하는 메소드는 없다. 테이블뷰를 확장할 수도 있겠지만, 일단 제공되는 기능만으로 원하는 퍼퍼먼스를 만들어 보겠다.
	if(p > 4) 
		table->setContentOffset(offset); //위에서 지우는 당시 스크롤 뷰의 오프셋을 기억했다가 다시로딩 후 설정해준다. 숫자 4 (화면에 보여지는 셀 갯수)는 맨위의 4개가 눌러졌을 때.. 오프셋이 다시 설정되면 이상하게 작동하기 때문이다. 그리고 리로드하면 맨 위로 가는데 굳이 실행할 필요가 없어서 이기도 하다.
}

void TableViewController::tableCellHighlight(CCTableView* table, CCTableViewCell* cell)
{
	CCLayerColor* mask;
	mask = CCLayerColor::create( ccc4(200, 0, 0, 100), _cellSize.width, _cellSize.height );
	cell->addChild( mask, 100, COLOR_LAYER_TAG );
}

void TableViewController::tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell)
{
	cell->removeChildByTag( COLOR_LAYER_TAG, true );
}