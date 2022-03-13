#ifndef _CGOBJECT_H_INCLUDED
#define _CGOBJECT_H_INCLUDED
class CGObject : public CObject {
  DECLARE_SERIAL(CGObject)
 public:
  CGObject();
  CGObject(const CString& name);
  virtual ~CGObject();
  //序列化
  virtual void Serialize(CArchive& ar);
  const CString& Name() const { return m_Name; }
  CString& Name() { return m_Name; }

 protected:
  CString m_Name;   //对象名称
  static long sID;  //对象ID
};
#endif  //_CGOBJECT_H_INCLUDED