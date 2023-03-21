#pragma once

#include "TopoDS_Shape.hxx"

namespace TTutorial
{
    class AbstractWorkpiece
    {
    public:
        AbstractWorkpiece():m_is_done(false){}
        virtual ~AbstractWorkpiece(){}
        virtual void BuildShape() = 0;
        /**
         * @brief 获得生成的模型。
         * @return 生成的模型。
        */
        TopoDS_Shape Shape();
    protected:
        /**
         * @brief 生成的模型。
        */
        TopoDS_Shape m_shape;
        /**
         * @brief 是否成功生成。
        */
        bool m_is_done;
    };

    class CorbelWorkpiece :public AbstractWorkpiece
    {
    public:
        /**
         * @brief 构建牛腿钢模型。
         * @param a_web_length 腹板长度。
         * @param a_web_height 腹板高度。
         * @param a_web_thickness 腹板厚度。
         * @param a_flange_thickness 翼板厚度。
         * @param a_up_flange_width 上翼板（斜翼板）宽度。
         * @param a_up_flange_left_offset 上翼板左侧回缩距离。
         * @param a_up_flange_right_offset 上翼板右侧回缩距离。
         * @param a_up_flange_angle 上翼板倾斜角度。
         * @param a_bottom_flange_width 下翼板（直翼板）宽度。
         * @param a_bottom_flange_left_offset 下翼板左侧回缩距离。
         * @param a_bottom_flange_right_offset 下翼板右侧回缩距离。
         * @param a_rib_thickness 筋板厚度。
         * @param a_rib_width 筋板宽度。
         * @param a_rib_location 筋板位置，筋板左侧到腹板左侧的距离。
        */
        CorbelWorkpiece(double a_web_length,
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
                        double a_rib_location);

        virtual void BuildShape() override;
        
    private:
        /**
         * @brief 腹板长度。
        */
        double m_web_length;
        /**
         * @brief 腹板高度。
        */
        double m_web_height;
        /**
         * @brief 腹板厚度。
        */
        double m_web_thickness;

        /**
         * @brief 翼板厚度。
        */
        double m_flange_thickness;

        /**
         * @brief 上翼板（斜翼板）宽度。
        */
        double m_up_flange_width;
        /**
         * @brief 上翼板左侧回缩距离。
        */
        double m_up_flange_left_offset;
        /**
         * @brief 上翼板右侧回缩距离。
        */
        double m_up_flange_right_offset;
        /**
         * @brief 上翼板倾斜角度。
        */
        double m_up_flange_angle;

        /**
         * @brief 下翼板（直翼板）宽度。
        */
        double m_bottom_flange_width;
        /**
         * @brief 下翼板左侧回缩距离。
        */
        double m_bottom_flange_left_offset;
        /**
         * @brief 下翼板右侧回缩距离。
        */
        double m_bottom_flange_right_offset;

        /**
         * @brief 筋板厚度。
        */
        double m_rib_thickness;
        /**
         * @brief 筋板宽度。
        */
        double m_rib_width;
        /**
         * @brief 筋板位置，筋板左侧到腹板左侧的距离。
        */
        double m_rib_location;
    };
}
