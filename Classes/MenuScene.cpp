
#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "TableViewCell.h"

using namespace cocos2d;
using namespace CocosDenshion;

enum {
	tagTableView = 10,
};

MenuScene::~MenuScene ()
{
	if(datalist) {
		datalist->release();
		datalist = NULL;
	}
}
CCScene* MenuScene::scene()
{
	CCScene *scene = CCScene::create();
	MenuScene *layer = MenuScene::create();
	scene->addChild(layer);
	layer->setScale( 1.5 );
	return scene;
}

bool MenuScene::init()
{
	isV = true;
	bar = NULL;
	if ( !CCLayerColor::initWithColor(ccc4(0, 0, 255, 255)) )
	{
		return false;
	}

	//종료 버튼
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create( "CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(MenuScene::menuCloseCallback) );
	pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu, 1);

	//data가 저장될 공간 생성
	datalist = CCArray::create();
	datalist->retain();

	//데이터 추가
	count = 0;
	for(int i=0; i < 5; i++)
	{
		addDatalist(count);
		count++;
	}

	tableView = CCTableView::create(this, CCSizeMake(240, 200));

	//kCCScrollViewDirectionVertical : 세로 스크롤, kCCScrollViewDirectionHorizontal : 가로 스크롤
	if( isV )
		tableView->setDirection( kCCScrollViewDirectionVertical );
	else
		tableView->setDirection( kCCScrollViewDirectionHorizontal );

	//추가시 정렬 기준 설정 kCCTableViewFillTopDown : 아래부분으로 추가됨, kCCTableViewFillBottomUp : 위에서 부터 추가됨.
	tableView->setVerticalFillOrder( kCCTableViewFillTopDown );

	tableView->setAnchorPoint( ccp( 0, 0 ) );
	tableView->setPosition( ccp( 400, 150 ) );

	//데이터를 가져오고나 터치 이벤트를 반환해줄 대리자를 이 클래스로 설정.
	tableView->setDelegate(this);
	this->addChild( tableView, 1, tagTableView );

	//tableCellAtIndex 등등 데이터 소스를 다시 한번 부른다. 테이블 뷰를 다시 그리므로 처음으로 포커스가 맞춰진다.
	tableView->reloadData();

	// type_Vertical_in, type_Horizontal_in
	if( isV )
		bar = UIFlowScrollBar::create(tableView, VERTICAL_IN);
	else
		bar = UIFlowScrollBar::create(tableView, HORIZONTAL_IN);

	return true;
}

/**
datalist에 데이터를 추가한다.
@param int num : 추가할 데이터 번호
@returns void
@exception not
*/
void MenuScene::addDatalist(int num)
{
	char str[10] ;
	sprintf(str, "data %d", num);
	datalist->addObject(CCString::create(str));
}

//메뉴 콜백 함수
void MenuScene::addDataFive( CCObject* sender )
{
	CCLog("데이터 5개 추가");
	CCTableView* tb = (CCTableView*) this->getChildByTag(tagTableView);

	for(int i=0; i < 5; i++){
		addDatalist(count);
		count++;
	}

	//테이블 뷰의 크기를 다시 정의 한다. 원하는 퍼퍼먼스는 얻기 힘들었다;
	tb->_updateContentSize();
}

void MenuScene::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}


//테이블 뷰
//tableview -> scrollview
void MenuScene::scrollViewDidScroll(CCScrollView* view) 
{
	if(bar != NULL) 
	{
		bar->Refresh();
	}
}

//CCTableViewDelegate
//셀을 터치하면 콜백 된다. 어떤 셀이 터치 되었는지 알 수 있다. 이 함수 외에도 하일라이트 부분 콜백이나, 다시 셀이 재사용될 때 콜백도 있다.
void MenuScene::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
	int p = cell->getIdx();

	CCPoint offset = table->getContentOffset();
	CCSize contentSize = table->getContentSize();
	CCSize tvSize = table->cocos2d::CCNode::getContentSize();
	CCLOG("cell touched at index: %i, tv content size (%3.2f, %3.2f) tv size : (%3.2f, %3.2f)", p, contentSize.width, contentSize.height, tvSize.width, tvSize.height);

	datalist->removeObjectAtIndex(p);
	table->removeCellAtIndex(p);
	
	//여기까지 하면 이빨 빠진 듯 지워진다.
	table->reloadData();
	
	//여기까지 하면 잘 지워지지만 포코스가 무조건 맨 위로 맞춰진다. 그렇다고 원하는 인덱스 위치로 이동하는 메소드는 없다. 테이블뷰를 확장할 수도 있겠지만, 일단 제공되는 기능만으로 원하는 퍼퍼먼스를 만들어 보겠다.
	if(p > 4) 
		table->setContentOffset(offset); //위에서 지우는 당시 스크롤 뷰의 오프셋을 기억했다가 다시로딩 후 설정해준다. 숫자 4 (화면에 보여지는 셀 갯수)는 맨위의 4개가 눌러졌을 때.. 오프셋이 다시 설정되면 이상하게 작동하기 때문이다. 그리고 리로드하면 맨 위로 가는데 굳이 실행할 필요가 없어서 이기도 하다.
}

void MenuScene::tableCellHighlight(CCTableView* table, CCTableViewCell* cell)
{
	CCLayerColor* mask;
	if(isV) 
		mask = CCLayerColor::create(ccc4(200, 0, 0, 100), 200, 80);
	else 
		mask = CCLayerColor::create(ccc4(200, 0, 0, 100), 80, 200);
	cell->addChild(mask,100, 44);
}

void MenuScene::tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell)
{
	cell->removeChildByTag(44, true);
}

//CCTableViewDataSource
//cell(카톡게임에서 친구한명의 정보를 나타내는 영력)의 크기를 정의한다.
CCSize MenuScene::cellSizeForTable(CCTableView *table)
{
	if(isV) 
		return CCSizeMake(200, 80);
	else 
		return CCSizeMake(137, 205);
}

//reload가 호출 되거나, 스크롤이 움직여 안보이는 셀이 보여질 때 호출된다. 
CCTableViewCell* MenuScene::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	//테이블이 사용 중인 셀이 있다면 재활용한다. 테이블 뷰는 똑같은 모양에 데이터만 다른 경우가 많다. 그래서 하나의 셀을 재사용하고 데이터만 바꿔준다.
	CCTableViewCell *cell = table->dequeueCell();

	//datalist에서 데이터를 가져온다. 여기서는 CCString을 했지만, CCObject를 상속받은 커스텀 클래스를 만들어서 여러 정보를 담을 수 있을 것이다.
	CCString* string = (CCString*) datalist->objectAtIndex(idx);

	if (!cell) {
		//커스텀 셀을 이용했는데, 이는 커스텀 셀 부분의 draw 함수를 오버로딩하여 여러가지 효과를 줄 수 있기 때문이다. 이 예제에서는 아무런 추가 내용이 없지만, 이부분을 이용하여 3D리스트 뷰나, 크기가 바뀌는 리스트 뷰 같은 조금 더 다이나믹한 리스트뷰를 만들 수 있을 것 같다. 
		cell = new TableViewCell();
		cell->autorelease();

		CCLabelTTF *label = CCLabelTTF::create(string->getCString(), "Helvetica", 20.0);
		label->setPosition(CCPointZero);
		label->setAnchorPoint(CCPointZero);
		label->setTag(123);
		cell->addChild(label);
	}
	else
	{
		CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(123);
		label->setString(string->getCString());
	}

	return cell;
}

//테이블이 셀 갯수에 대한 정보를 가져가는 곳이다.
unsigned int MenuScene::numberOfCellsInTableView(CCTableView *table)
{
	return datalist->count();
}
