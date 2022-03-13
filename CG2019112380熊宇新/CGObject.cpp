#include "pch.h"
#include "CGObject.h"
IMPLEMENT_SERIAL(CGObject, CObject, 1)
long CGObject::sID = 0L;
CGObject::CGObject() {
  sID++;
  m_Name.Format(_T("CGObject%ld"), sID);
}
CGObject::CGObject(const CString& name) : m_Name(name) {
  sID++;
}
CGObject::~CGObject() {}
void CGObject::Serialize(CArchive& ar) {
  CObject::Serialize(ar);
  if (ar.IsStoring()) {
    ar << m_Name;
  } else {
    ar >> m_Name;
  }
}