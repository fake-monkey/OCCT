#ifndef DOCUMENTTUT_H
#define DOCUMENTTUT_H

#include "DocumentCommon.h"
#include <Geom_BSplineSurface.hxx>
#include "Standard_CString.hxx"
#include "TopoDS_Shape.hxx"

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
	/**
	 * @brief ������step��ʽ�С�
	 * @param a_file_string ������ļ����ơ�
	*/
	void                           SaveToStep(const Standard_CString& a_file_string);
	double                         Measure();

private:
	/**
	 * @brief �����µ�ģ�Ͳ�������ʾ���Ὣ��ģ������ɾ����
	 * @param a_shape ����ʾ��ģ�͡�
	*/
	void                           LoadTopoDSShape(TopoDS_Shape a_shape);

private:
	SurfConstruction*              mySurfConstructor;
	TopoDS_Shape                   m_current_shape;
};

#endif
