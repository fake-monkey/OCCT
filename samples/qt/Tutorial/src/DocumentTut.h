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
	 * @brief 生成牛腿模型并显示。
	*/
	void                           OnMakeCorbel();
	/**
	 * @brief 保存在step格式中。
	 * @param a_file_string 保存的文件名称。
	*/
	void                           SaveToStep(const Standard_CString& a_file_string);
	double                         Measure();

private:
	/**
	 * @brief 导入新的模型并进行显示，会将旧模型内容删除。
	 * @param a_shape 待显示的模型。
	*/
	void                           LoadTopoDSShape(TopoDS_Shape a_shape);

private:
	SurfConstruction*              mySurfConstructor;
	TopoDS_Shape                   m_current_shape;
};

#endif
