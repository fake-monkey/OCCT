#include "DocumentTut.h"

#include <Standard_WarningsDisable.hxx>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <Standard_WarningsRestore.hxx>

#include <TopoDS_Shape.hxx>
#include <AIS_Shape.hxx>

#include "MakeCorbel.h"
#include "STEPControl_Writer.hxx"
#include "IFSelect_ReturnStatus.hxx"
#include "STEPControl_StepModelType.hxx"
#include "BRepBuilderAPI_Copy.hxx"
#include "StdSelect_ShapeTypeFilter.hxx"

using TTutorial::AbstractWorkpiece;
using TTutorial::CorbelWorkpiece;

TopoDS_Shape
MakeBottle(const Standard_Real myWidth , const Standard_Real myHeight , const Standard_Real myThickness);

DocumentTut::DocumentTut( const int theIndex, ApplicationCommonWindow* app )
: DocumentCommon( theIndex, app )
{
    Handle(StdSelect_ShapeTypeFilter) edge_filter = new StdSelect_ShapeTypeFilter(TopAbs_EDGE);
    myContext->AddFilter(edge_filter);
    myContext->Activate(AIS_Shape::SelectionMode(TopAbs_ShapeEnum::TopAbs_SOLID));
    const auto& highlight_style = myContext->HighlightStyle();
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
    AbstractWorkpiece& workpiece = CorbelWorkpiece(100, 80, 10, 8,
        90, 5, 6, M_PI / 6,
        95, 4, 5,
        6, 80, 45);
    workpiece.BuildShape();
    TopoDS_Shape shape = workpiece.Shape();
    LoadTopoDSShape(shape);
}

void DocumentTut::SaveToStep(const Standard_CString& a_file_string)
{
    STEPControl_Writer step_writer;
    IFSelect_ReturnStatus status;
    status = step_writer.Transfer(m_current_shape, STEPControl_StepModelType::STEPControl_AsIs);
    status = step_writer.Write(a_file_string);
}

double DocumentTut::Measure()
{
    return 0.0;
}

void DocumentTut::LoadTopoDSShape(TopoDS_Shape a_shape)
{
    m_current_shape = a_shape;
    getContext()->RemoveAll(false);
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
