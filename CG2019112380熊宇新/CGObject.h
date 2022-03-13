#ifndef _CGOBJECT_H_INCLUDED
#define _CGOBJECT_H_INCLUDED
class CGObject : public CObject {
  DECLARE_SERIAL(CGObject)
 public:
  CGObject();
  CGObject(const CString& name);
  virtual ~CGObject();
  //���л�
  virtual void Serialize(CArchive& ar);
  const CString& Name() const { return m_Name; }
  CString& Name() { return m_Name; }

 protected:
  CString m_Name;   //��������
  static long sID;  //����ID
};
#endif  //_CGOBJECT_H_INCLUDED