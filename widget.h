#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Damage
{
public:
    enum{
        BAI_ZI      = 0,
        HUANG_ZI    = 1,
        BAO_SHANG   = 2,
        ZUI_ZHONG   = 3,
        SAN_GONG    = 4,
        LI_ZHI      = 5
    };

    inline void init()
    {
        for(int i = 0; i < 6; i++)
            mValue[i] = 0.0f;
    }

    float mValue[6];

    float getDamageTotal();
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void on_check_halo_stateChanged(int arg1);

private:
    void calculateDamage();
    void calculateDamage_Halo();

    short mType[4];
    short mHaloSelection;

    short mHalo[3];

    Ui::Widget *ui;

    Damage mDamage;
};
#endif // WIDGET_H
