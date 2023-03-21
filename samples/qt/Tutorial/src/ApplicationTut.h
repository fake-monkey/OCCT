#ifndef APPLICATIONTUT_H
#define APPLICATIONTUT_H

#include "DocumentTut.h"
#include "ApplicationCommon.h"

class ApplicationTut: public ApplicationCommonWindow
{
    Q_OBJECT

public:
	
  ApplicationTut();
  ~ApplicationTut();

  static QString    getTutResourceDir();
  virtual void      updateFileActions();

public slots:
	
	void            onMakeBottleAction();
	void            OnMakeCorbelAction();

private:
	void              createMakeBottleOperation();
	/**
	 * @brief 获得当前活动的样例文档。
	 * @return 当没有活动的文档时，返回nullptr。
	*/
	DocumentTut*      GetActiveDocumentTut();

private:
	QToolBar*					myMakeBottleBar;
};

#endif
