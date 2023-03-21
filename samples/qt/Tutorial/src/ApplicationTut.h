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
	 * @brief ����ţ�ȸ�ģ�͡�
	*/
	void            OnMakeCorbelAction();
	/**
	 * @brief ���浽step��ʽ�С�
	*/
	void            OnSaveToStep();
	void            OnMeasure();

protected:
	virtual DocumentCommon* createNewDocument() override;

private:
	void              createMakeBottleOperation();
	/**
	 * @brief ��õ�ǰ��������ĵ���
	 * @return ��û�л���ĵ�ʱ������nullptr��
	*/
	DocumentTut*      GetActiveDocumentTut();

private:
	QToolBar*					myMakeBottleBar;
};

#endif
