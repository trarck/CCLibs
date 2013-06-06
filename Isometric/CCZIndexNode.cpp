//
//  ZIndex.

#include "CCZIndexNode.h"

NS_CC_YHLIB_BEGIN

CCZIndexNode::CCZIndexNode()
:m_pEntity(NULL)
{

}

CCZIndexNode::~CCZIndexNode()
{

}

void CCZIndexNode::setRect(const CCRect& rect)
{
    m_tRect=rect;
}

const CCRect& CCZIndexNode::getRect()
{
    return m_tRect;
}

void CCZIndexNode::setEntity(CCObject* entity)
{
    m_pEntity=entity;
}

CCObject* CCZIndexNode::getEntity()
{
    return m_pEntity;
}

NS_CC_YHLIB_END