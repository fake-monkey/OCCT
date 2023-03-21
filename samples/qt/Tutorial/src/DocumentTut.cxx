#include "DocumentTut.h"

#include <Standard_WarningsDisable.hxx>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <Standard_WarningsRestore.hxx>

#include <TopoDS_Shape.hxx>
#include <AIS_Shape.hxx>

#include "MakeCorbel.h"

using TTutorial::AbstractWorkpiece;
using TTutorial::CorbelWorkpiece;

TopoDS_Shape
MakeBottle(const Standard_Real myWidth , const Standard_Real myHeight , const Standard_Real myThickness);

DocumentTut::DocumentTut( const int theIndex, ApplicationCommonWindow* app )
: DocumentCommon( theIndex, app )
{
}

DocumentTut::~DocumentTut()
{
}

void DocumentTut::onMakeBottle()
{
    TopoDS_Shape shape=MakeBottle(50,70,30);
    LoadTopoDSShape(shape);
}

void DocumentTut::OnMakeCorbel()
{
    const AbstractWorkpiece& workpiece = CorbelWorkpiece(100, 80, 10, 8,
        90, 5, 6, M_PI / 6,
        95, 4, 5,
        6, 80, 45);
    const TopoDS_Shape& shape = workpiece.Shape();
    LoadTopoDSShape(shape);
}

void DocumentTut::LoadTopoDSShape(const TopoDS_Shape& a_shape)
{
    getContext()->RemoveAll(true);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    Handle(AIS_Shape) AISBottle = new AIS_Shape(a_shape);
    getContext()->SetMaterial(AISBottle, Graphic3d_NameOfMaterial_Gold, Standard_False);
    getContext()->SetDisplayMode(AISBottle, 1, Standard_False);
    getContext()->Display(AISBottle, Standard_False);
    const Handle(AIS_InteractiveObject)& anIOAISBottle = AISBottle;
    getContext()->SetSelected(anIOAISBottle, Standard_False);
    emit selectionChanged();
    fitAll();
    QApplication::restoreOverrideCursor();
}
