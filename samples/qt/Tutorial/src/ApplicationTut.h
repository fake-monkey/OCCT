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
	/**
	 * @brief 生成牛腿钢模型。
	*/
	void            OnMakeCorbelAction();
	/**
	 * @brief 保存到step格式中。
	*/
	void            OnSaveToStep();
	void            OnMeasure();

protected:
	virtual DocumentCommon* createNewDocument() override;

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
