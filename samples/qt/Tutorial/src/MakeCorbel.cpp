#include "MakeCorbel.h"

#include "gp_Pnt.hxx"
#include "Standard_Handle.hxx"
#include "Geom_TrimmedCurve.hxx"
#include "GC_MakeSegment.hxx"
#include "TopoDS_Edge.hxx"
#include "BRepBuilderAPI_MakeEdge.hxx"
#include "TopoDS_Wire.hxx"
#include "BRepBuilderAPI_MakeWire.hxx"
#include "TopoDS_Face.hxx"
#include "BRepBuilderAPI_MakeFace.hxx"
#include "BRepPrimAPI_MakePrism.hxx"
#include "gp_Vec.hxx"
#include "gp_Dir2d.hxx"
#include "gp_XYZ.hxx"
#include "BRepAlgoAPI_Fuse.hxx"

using TTutorial::CorbelWorkpiece;
using TTutorial::AbstractWorkpiece;

TopoDS_Shape TTutorial::AbstractWorkpiece::Shape()
{
    return m_shape;
}

TTutorial::CorbelWorkpiece::CorbelWorkpiece(double a_web_length,
    double a_web_height,
    double a_web_thickness,
    double a_flange_thickness,
    double a_up_flange_width,
    double a_up_flange_left_offset,
    double a_up_flange_right_offset,
    double a_up_flange_angle,
    double a_bottom_flange_width,
    double a_bottom_flange_left_offset,
    double a_bottom_flange_right_offset,
    double a_rib_thickness,
    double a_rib_width,
    double a_rib_location) :
    m_web_length(a_web_length),
    m_web_height(a_web_height),
    m_web_thickness(a_web_thickness),
    m_flange_thickness(a_flange_thickness),
    m_up_flange_width(a_up_flange_width),
    m_up_flange_left_offset(a_up_flange_left_offset),
    m_up_flange_right_offset(a_up_flange_right_offset),
    m_up_flange_angle(a_up_flange_angle),
    m_bottom_flange_width(a_bottom_flange_width),
    m_bottom_flange_left_offset(a_bottom_flange_left_offset),
    m_bottom_flange_right_offset(a_bottom_flange_right_offset),
    m_rib_thickness(a_rib_thickness),
    m_rib_width(a_rib_width),
    m_rib_location(a_rib_location)
{
}

/**
 * @brief 根据四个角点和拉伸向量生成拉伸体。
 * @param a_left_bottom 左下角点。
 * @param a_right_bottom 右上角点。
 * @param a_right_up 右上角点。
 * @param a_left_up 左上角点。
 * @param a_prism_vec 拉伸方向。
 * @return 生成的拉伸体。
*/
TopoDS_Shape MakePrismByCornerPoints(const gp_Pnt& a_left_bottom, const gp_Pnt& a_right_bottom,
    const gp_Pnt& a_right_up, const gp_Pnt& a_left_up, const gp_Vec& a_prism_vec)
{
    Handle(Geom_TrimmedCurve) bottom_curve = GC_MakeSegment(a_left_bottom, a_right_bottom);
    Handle(Geom_TrimmedCurve) right_curve = GC_MakeSegment(a_right_bottom, a_right_up);
    Handle(Geom_TrimmedCurve) up_curve = GC_MakeSegment(a_right_up, a_left_up);
    Handle(Geom_TrimmedCurve) left_curve = GC_MakeSegment(a_left_up, a_left_bottom);

    TopoDS_Edge bottom_edge = BRepBuilderAPI_MakeEdge(bottom_curve);
    TopoDS_Edge right_edge = BRepBuilderAPI_MakeEdge(right_curve);
    TopoDS_Edge up_edge = BRepBuilderAPI_MakeEdge(up_curve);
    TopoDS_Edge left_edge = BRepBuilderAPI_MakeEdge(left_curve);

    TopoDS_Wire wire = BRepBuilderAPI_MakeWire(bottom_edge, right_edge, up_edge, left_edge);
    TopoDS_Face face = BRepBuilderAPI_MakeFace(wire);

    return BRepPrimAPI_MakePrism(face, a_prism_vec);
}

/**
 * @brief 生成腹板，且腹板的左下角在原点，厚度拉伸方向沿z轴正方向。腹板宽度以左侧宽度为准。
 * @param a_web_length 
 * @param a_web_height 
 * @param a_web_thickness 
 * @param a_up_flange_angle
 * @return 生成的腹板。
*/
TopoDS_Shape MakeWeb(double a_web_length, double a_web_height, double a_web_thickness, double a_up_flange_angle)
{
    gp_Pnt left_bottom(0, 0, 0);
    gp_Pnt right_bottom(a_web_length, 0, 0);
    gp_Pnt left_up(0, a_web_height, 0);
    gp_Pnt right_up(a_web_length, a_web_height + a_web_length * sin(a_up_flange_angle), 0);

    gp_Vec prism_vec(0, 0, a_web_thickness);
    
    return MakePrismByCornerPoints(left_bottom, right_bottom, right_up, left_up, prism_vec);
}

/**
 * @brief 生成上翼板。
 * @param a_web_length 腹板长度。
 * @param a_web_height 腹板高度。
 * @param a_web_thickness 腹板厚度。
 * @param a_flange_thickness 翼板厚度。
 * @param a_up_flange_width 上翼板宽度。
 * @param a_up_flange_angle 上翼板倾斜角度。
 * @return 生成的上翼板。
*/
TopoDS_Shape MakeUpFlange(double a_web_length, double a_web_height, double a_web_thickness,
    double a_flange_thickness, double a_up_flange_width, double a_up_flange_angle)
{
    double front_z = a_web_thickness / 2 - a_up_flange_width / 2;  // 前底板的z坐标。
    gp_Pnt left_bottom(0, a_web_height, front_z);
    gp_Pnt right_bottom(a_web_length, a_web_height + a_web_length * sin(a_up_flange_angle), front_z);
    gp_Dir2d offset_dir(cos(a_up_flange_angle + M_PI_2), sin(a_up_flange_angle + M_PI_2));
    gp_Vec2d offset_vec_2d = a_flange_thickness * offset_dir;
    gp_Vec offset_vec(offset_vec_2d.X(), offset_vec_2d.Y(), 0);
    gp_Pnt left_up(left_bottom.XYZ() + offset_vec.XYZ());
    gp_Pnt right_up(right_bottom.XYZ() + offset_vec.XYZ());

    gp_Vec prism_vec(0, 0, a_up_flange_width);

    return MakePrismByCornerPoints(left_bottom, right_bottom, right_up, left_up, prism_vec);
}

/**
 * @brief 生成下翼板。
 * @param a_web_length 腹板长度。
 * @param a_web_thickness 腹板厚度。
 * @param a_flange_thickness 翼板厚度。
 * @param a_bottom_flange_width 下翼板宽度。
 * @return 生成的下翼板。
*/
TopoDS_Shape MakeBottomFlange(double a_web_length, double a_web_thickness,
    double a_flange_thickness, double a_bottom_flange_width)
{
    double front_z = a_web_thickness / 2 - a_bottom_flange_width / 2;  // 前底板的z坐标。
    gp_Pnt left_up(0, 0, front_z);
    gp_Pnt right_up(a_web_length, 0, front_z);
    gp_Pnt left_bottom(left_up.X(), left_up.Y() - a_flange_thickness, left_up.Z());
    gp_Pnt right_bottom(right_up.X(), right_up.Y() - a_flange_thickness, right_up.Z());

    gp_Vec prism_vec(0, 0, a_bottom_flange_width);

    return MakePrismByCornerPoints(left_bottom, right_bottom, right_up, left_up, prism_vec);
}

/**
 * @brief 生成加强筋。
 * @param a_rib_thickness 筋板厚度。
 * @param a_rib_width 筋板宽度。
 * @param a_rib_location 筋板位置。
 * @return 生成的筋板。
*/
TopoDS_Shape MakeRib(double a_web_height, double a_web_thickness,
    double a_up_flange_angle,
    double a_rib_thickness, double a_rib_width, double a_rib_location)
{
    double front_z = a_web_thickness / 2 - a_rib_width / 2;  // 前底板的z坐标。
    double right_x = a_rib_location + a_rib_thickness;
    gp_Pnt left_bottom(a_rib_location, 0, front_z);
    gp_Pnt right_bottom(right_x, 0, front_z);
    gp_Pnt right_up(right_x, a_web_height + right_x * sin(a_up_flange_angle), front_z);
    gp_Pnt left_up(a_rib_location, a_web_height + a_rib_location * sin(a_up_flange_angle), front_z);

    gp_Vec prism_vec(0, 0, a_rib_width);

    return MakePrismByCornerPoints(left_bottom, right_bottom, right_up, left_up, prism_vec);
}

void TTutorial::CorbelWorkpiece::BuildShape()
{
    TopoDS_Shape web = MakeWeb(m_web_length, m_web_height, m_web_thickness, m_up_flange_angle);
    TopoDS_Shape up_flange = MakeUpFlange(m_web_length, m_web_height, m_web_thickness,
        m_flange_thickness, m_up_flange_width, m_up_flange_angle);
    TopoDS_Shape result = BRepAlgoAPI_Fuse(web, up_flange);
    TopoDS_Shape bottom_flange = MakeBottomFlange(m_web_length, m_web_thickness, m_flange_thickness, m_bottom_flange_width);
    result = BRepAlgoAPI_Fuse(result, bottom_flange);

    TopoDS_Shape rib = MakeRib(m_web_height, m_web_thickness, m_up_flange_angle, m_rib_thickness, m_rib_width, m_rib_location);
    result = BRepAlgoAPI_Fuse(result, rib);
    m_shape = result;
    m_is_done = true;
}
