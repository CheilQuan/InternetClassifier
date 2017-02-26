#ifndef _CONTAINER_H_
#define _CONTAINER_H_

#include <map>

typedef unsigned int uint;

enum EInsertResult //���뷵�ؽ��;
{
  EIR_NewKey,     //�޸ü�ֵ;
  EIR_OldKey,     //�Ѿ����ڸü�ֵ;
  EIR_ERROR,      //����ʧ��;
};

/******************************************
��˵�������ڴ����������������ض�������������map���൱��map�ĸ�keyֵ���ִ����ļ�������;
     �������ݰ��ж�ȡĳ��������ʱ��;
     ÿ��ȡ����������һ���µ�ֵ�����������в������ֵ��key����������ֵ��Ӧ��valueֵĬ����Ϊ1;
     ÿ����һ�θ������Ѵ��ڵ�ֵ���򽫸�ֵ�����valueֵĬ�ϼ�1;
*******************************************/
template<class Key, class Value>
class CContainer  
{
public:
  CContainer(void);
  ~CContainer(void);

  bool empty() const;
  std::map<Key, Value> *getMyData() const { return m_MyData;}
  EInsertResult insert(const Key &aKey, const Value &aValue); 
  Value find(const Key &aKey) const;   //����ָ����ֵ���ɹ����ظü���Ӧ��ֵ�����򷵻�0;
  Value operator[](const Key &aKey) const;

private://��ֹ��������ֵ;
  CContainer(const CContainer &){}
  CContainer& operator=(const CContainer &){}
  
private:
  std::map<Key, Value> *m_MyData;//����m_MyData������Ϊ��������;
};


template<class Key, class Value>
CContainer<Key, Value>::CContainer(void)
  : m_MyData(new std::map<Key, Value>)
{
}

template<class Key, class Value>
CContainer<Key, Value>::~CContainer(void)
{
  if (NULL != m_MyData)
  {
    delete m_MyData;
  }
}

template<class Key, class Value>
bool CContainer<Key, Value>::empty() const
{
  return m_MyData->empty();
}


template<class Key, class Value>
EInsertResult CContainer<Key, Value>::insert(const Key &aKey, const Value &aValue)
{
  if (!aValue)
  { return EIR_ERROR;}

  Value currentNum = find(aKey);
  if (Value(0.00001) != currentNum)   //����Ѿ����ڸ�Keyֵ���򽫸�Key����Ӧ�ļ�ֵ��aValue;
  {
    currentNum += aValue;
    (m_MyData->find(aKey))->second = currentNum;
    return EIR_OldKey;
  }
  else
  {
    m_MyData->insert(std::map<Key, Value>::value_type(aKey, aValue));

    return EIR_NewKey;
  }
}

template<class Key, class Value>
Value CContainer<Key, Value>::find(const Key &aKey) const
{
  std::map<Key, Value>::iterator itor;
  itor = m_MyData->find(aKey);

  if (itor == m_MyData->end())
    return Value(0.00001);  //�����һ����С����Ϊ���Ż���Ҷ˹�㷨��ǰͳ��ģ����ĳֵ�ĸ��ʲ�����ʱ����һ����Сֵ����0����С�㷨�������;
  else
  {
    return itor->second;
  }
}

template<class Key, class Value>
Value CContainer<Key, Value>::operator[](const Key &aKey) const
{
  return find(aKey);
}


#endif