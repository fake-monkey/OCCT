#include "ApplicationTut.h"
#include "DocumentTut.h"

#include <OSD_Environment.hxx>

#include <Standard_WarningsDisable.hxx>
#include <QFileDialog>
#include <QStatusBar>
#include <QMdiSubWindow>
#include <Standard_WarningsRestore.hxx>
#include <QDebug>

ApplicationTut::ApplicationTut()
    : ApplicationCommonWindow( )
{
  createMakeBottleOperation();
}

ApplicationTut::~ApplicationTut()
{
}

void ApplicationTut::createMakeBottleOperation(){
	QPixmap MakeBottleIcon;
	QString dir = getTutResourceDir() + QString( "/" );
  MakeBottleIcon = QPixmap( dir+QObject::tr( "ICON_MAKE_BOTTLE" ) );
	
  QAction * MakeBottleAction = new QAction( MakeBottleIcon, QObject::tr("TBR_MAKEBOT"), this );
  MakeBottleAction->setToolTip( QObject::tr( "TBR_MAKEBOT" ) );
  MakeBottleAction->setStatusTip( QObject::tr("TBR_MAKEBOT") );
  MakeBottleAction->setShortcut( QObject::tr( "CTRL+M" ) );
	connect( MakeBottleAction, SIGNAL( triggered() ) , this, SLOT( onMakeBottleAction() ) );
	
	myMakeBottleBar = addToolBar( tr( "Make Bottle" ) );
  insertToolBar( getCasCadeBar(), myMakeBottleBar );
  myMakeBottleBar->addAction( MakeBottleAction );

	QAction* make_corbel_action = new QAction(QString("make_corbel"), this);
	connect(make_corbel_action, &QAction::triggered, this, &ApplicationTut::OnMakeCorbelAction);
	myMakeBottleBar->addAction(make_corbel_action);

	myMakeBottleBar->hide();
}

DocumentTut* ApplicationTut::GetActiveDocumentTut()
{
	QMdiArea* ws = ApplicationCommonWindow::getWorkspace();
	QMdiSubWindow* active_sub_window = ws->activeSubWindow();
	if (active_sub_window == nullptr)
	{
		// 视图关闭时，getWorkspace()->subWindowList()却不为空，原因未知，这里加个补丁避免崩溃。
		qDebug() << "active_sub_window == nullptr";
		return nullptr;
	}
	DocumentTut* doc = (DocumentTut*)(qobject_cast<MDIWindow*>(ws->activeSubWindow()->widget())->getDocument());
	return doc;
}

void ApplicationTut::updateFileActions()
{
  if ( getWorkspace()->subWindowList().isEmpty() )
  {
	  if ( !isDocument() )
		{
      myMakeBottleBar->show();
    }
    else
    {
      myMakeBottleBar->hide();
    }
  }
  ApplicationCommonWindow::updateFileActions();
}

void ApplicationTut::onMakeBottleAction()
{
	DocumentTut* doc = GetActiveDocumentTut();
	if (doc == nullptr)
	{
		return;
	}
	statusBar()->showMessage( QObject::tr("INF_MAKE_BOTTLE"), 5000 );
	doc->onMakeBottle();
	statusBar()->showMessage(QObject::tr("INF_DONE"));
}

void ApplicationTut::OnMakeCorbelAction()
{
	DocumentTut* doc = GetActiveDocumentTut();
	if (doc == nullptr)
	{
		return;
	}
	statusBar()->showMessage(QString("make_corbel"), 5000);
	doc->onMakeBottle();
	statusBar()->showMessage(QObject::tr("INF_DONE"));
}

QString ApplicationTut::getTutResourceDir()
{
  static QString resDir (OSD_Environment ("CSF_TutorialResourcesDefaults").Value().ToCString());
  if (resDir.isEmpty())
    resDir = QString (OSD_Environment ("CSF_OCCTResourcePath").Value().ToCString()) + "/samples";
  return resDir;
}
