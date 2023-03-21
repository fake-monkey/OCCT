#ifndef DOCUMENTTUT_H
#define DOCUMENTTUT_H

#include "DocumentCommon.h"
#include <Geom_BSplineSurface.hxx>

class SurfConstruction;
class ApplicationCommon;

class DocumentTut : public DocumentCommon
{
	Q_OBJECT

public:
   DocumentTut( const int, ApplicationCommonWindow* );
	~DocumentTut();

	void                           onMakeBottle();
	/**
	 * @brief ����ţ��ģ�Ͳ���ʾ��
	*/
	void                           OnMakeCorbel();

private:
	/**
	 * @brief �����µ�ģ�Ͳ�������ʾ���Ὣ��ģ������ɾ����
	 * @param a_shape ����ʾ��ģ�͡�
	*/
	void                           LoadTopoDSShape(const TopoDS_Shape& a_shape);

private:
	SurfConstruction*			         mySurfConstructor;
};

#endif
