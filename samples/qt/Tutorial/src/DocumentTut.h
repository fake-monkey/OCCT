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
	void                           OnMakeCorbel();

private:
	void                           LoadTopoDSShape(const TopoDS_Shape& a_shape);

private:
	SurfConstruction*			         mySurfConstructor;
};

#endif
