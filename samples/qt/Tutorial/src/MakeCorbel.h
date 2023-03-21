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
         * @brief ������ɵ�ģ�͡�
         * @return ���ɵ�ģ�͡�
        */
        TopoDS_Shape Shape();
    protected:
        /**
         * @brief ���ɵ�ģ�͡�
        */
        TopoDS_Shape m_shape;
        /**
         * @brief �Ƿ�ɹ����ɡ�
        */
        bool m_is_done;
    };

    class CorbelWorkpiece :public AbstractWorkpiece
    {
    public:
        /**
         * @brief ����ţ�ȸ�ģ�͡�
         * @param a_web_length ���峤�ȡ�
         * @param a_web_height ����߶ȡ�
         * @param a_web_thickness �����ȡ�
         * @param a_flange_thickness ����ȡ�
         * @param a_up_flange_width ����壨б��壩��ȡ�
         * @param a_up_flange_left_offset ��������������롣
         * @param a_up_flange_right_offset ������Ҳ�������롣
         * @param a_up_flange_angle �������б�Ƕȡ�
         * @param a_bottom_flange_width ����壨ֱ��壩��ȡ�
         * @param a_bottom_flange_left_offset ��������������롣
         * @param a_bottom_flange_right_offset ������Ҳ�������롣
         * @param a_rib_thickness ����ȡ�
         * @param a_rib_width ����ȡ�
         * @param a_rib_location ���λ�ã������ൽ�������ľ��롣
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
         * @brief ���峤�ȡ�
        */
        double m_web_length;
        /**
         * @brief ����߶ȡ�
        */
        double m_web_height;
        /**
         * @brief �����ȡ�
        */
        double m_web_thickness;

        /**
         * @brief ����ȡ�
        */
        double m_flange_thickness;

        /**
         * @brief ����壨б��壩��ȡ�
        */
        double m_up_flange_width;
        /**
         * @brief ��������������롣
        */
        double m_up_flange_left_offset;
        /**
         * @brief ������Ҳ�������롣
        */
        double m_up_flange_right_offset;
        /**
         * @brief �������б�Ƕȡ�
        */
        double m_up_flange_angle;

        /**
         * @brief ����壨ֱ��壩��ȡ�
        */
        double m_bottom_flange_width;
        /**
         * @brief ��������������롣
        */
        double m_bottom_flange_left_offset;
        /**
         * @brief ������Ҳ�������롣
        */
        double m_bottom_flange_right_offset;

        /**
         * @brief ����ȡ�
        */
        double m_rib_thickness;
        /**
         * @brief ����ȡ�
        */
        double m_rib_width;
        /**
         * @brief ���λ�ã������ൽ�������ľ��롣
        */
        double m_rib_location;
    };
}
