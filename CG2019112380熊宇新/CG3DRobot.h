
#include "CG3DRenderable.h"
#include "Vector3.h"

class CG3DRobot : public CG3DRenderable {
  DECLARE_SERIAL(CG3DRobot)
 public:
  CG3DRobot();
  //CG3DRobot(const CG3DRobot& other);
  virtual ~CG3DRobot() {}
  //序列化
  virtual void Serialize(CArchive& ar);

 public:
  virtual void Render(CGRenderContext* pRC);
  void drawALL();
  void drawHead();
  void drawBody();
  void drawArm();
  void drawLeg();
  void drawBall(double R, double x, double y, double z);
  void drawHalfBall(double R, double x, double y, double z);
  void drawSkewed(double l, double w, double h, double x, double y, double z);

  virtual void robotReset();
  virtual void rightArmRotate();
  virtual void leftArmRotate();
  virtual void rightLegRotate();
  virtual void leftLegRotate();
  virtual void bodyLeftRotate();
  virtual void bodyRigRotate();
  virtual void _3DTranslate(double tx, double ty, double tz);  //平移
  virtual void _3DRotate(double angle,
                         double cx,
                         double cy,
                         double cz);  //旋转（逆时针为正，度）
  virtual void _3DScale(double sx, double sy, double sz);  //缩放

 protected:
  double mRotateAngle = 0.0;  //身体角度
  double mLeftArmAngle = 0.0, mRightArmAngle = 0.0, mLeftLegAngle = 0.0,
         mRightLegAngle = 0.0;  //手臂和腿角度
  int mLeftArmDirec = 1, mRightArmDirec = 1, mLeftLegDirec = 1,
      mRightLegDirec = 1;            //初始化手臂和腿运动方向向前
  double mtx = 0, mty = 0, mtz = 0;                //平移量
  double msx = 1.0, msy = 1.0, msz = 1.0;          //缩放量
  double mrx = 0, mry = 0, mrz = 0, mAngle = 0.0;  //旋转
};
