#ifndef YHLIB_ISOMETRIC_CCISOOBJECTINFO_H_
#define YHLIB_ISOMETRIC_CCISOOBJECTINFO_H_

#include "cocos2d.h"
#include "YHLibMacros.h"

NS_CC_YHLIB_BEGIN

class CCISOObjectInfo : public CCObject{

public:
    
    CCISOObjectInfo();
    
    ~CCISOObjectInfo();
    
    inline void setName(const char* sName)
    {
        m_sName = sName;
    }
    
    inline const char* getName()
    {
        return m_sName.c_str();
    }
    
    inline void setType(const char* sType)
    {
        m_sType = sType;
    }
    
    inline const char* getType()
    {
        return m_sType.c_str();
    }
    
    inline void setGid(unsigned int uGid)
    {
        m_uGid = uGid;
    }
    
    inline unsigned int getGid()
    {
        return m_uGid;
    }
    
    inline void setPosition(CCPoint& tPosition)
    {
        m_tPosition = tPosition;
    }
    
    inline CCPoint& getPosition()
    {
        return m_tPosition;
    }
    
    inline void setSize(CCSize& tSize)
    {
        m_tSize = tSize;
    }
    
    inline CCSize& getSize()
    {
        return m_tSize;
    }
    
    inline void setVisible(bool bVisible)
    {
        m_bVisible = bVisible;
    }
    
    inline bool getVisible()
    {
        return m_bVisible;
    }
    
    inline void setProperties(CCDictionary* pProperties)
    {
        CC_SAFE_RETAIN(pProperties);
        CC_SAFE_RELEASE(m_pProperties);
        m_pProperties = pProperties;
    }
    
    inline CCDictionary* getProperties()
    {
        return m_pProperties;
    }
    
protected:
    
    std::string m_sName;
    std::string m_sType;
    unsigned int m_uGid;
    CCPoint m_tPosition;
    CCSize m_tSize;
    bool m_bVisible;
    CCDictionary* m_pProperties;
    
};


NS_CC_YHLIB_END

#endif //YHLIB_ISOMETRIC_CCISOOBJECTINFO_H_
