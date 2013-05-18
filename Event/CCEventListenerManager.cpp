#include "CCEventListenerManager.h"

NS_CC_YHLIB_BEGIN

CCEventListenerManager::CCEventListenerManager()
:m_pListeners(NULL)
{

}

CCEventListenerManager::~CCEventListenerManager()
{
	CC_SAFE_RELEASE(m_pListeners);
}

bool CCEventListenerManager::init()
{
	m_pListeners=new CCDictionary();
}

void CCEventListenerManager::addEventListener(CCObject* target,const char* type,CCObject* handleObject,SEL_EventHandle handle)
{

    unsigned int id=target->m_uID;

	CCDictionary* targetListeners=static_cast<CCDictionary*>(m_pListeners->objectForKey(m_uID));
	if(targetListeners==NULL){
		targetListeners=new CCDictionary();
		m_pListeners->setObject(targetListeners,m_uID);
        targetListeners->release();
	}

    CCArray* eventListeners=static_cast<CCArray*>(targetListeners->objectForKey(type));
    if(eventListeners==NULL){
		eventListeners=new CCArray();
		eventListeners->init();
		targetListeners->setObject(eventListeners,type);
        eventListeners->release();
	}

    //is listened. one type event only have a  handle ,have multi-processor function
    //一个事件只有一个触发点，但有很多处理该事件的函数

    if(!isListened(eventListeners,handle,handleObject)) {
        CCEventHandle* eventHandle=new CCEventHandle();
	    eventHandle->initWithTarget(handleObject,handle);
        eventListeners->addObject(eventHandle);
        eventHandle->release();
    }else{
        CCAssert(0,"CCEventListenerManager:Handle has register");
    }

}

void CCEventListenerManager::removeEventListener(CCObject* target,const char* type,CCObject* handleObject,SEL_EventHandle handle)
{
    CCAssert(target!=NULL,"CCEventListenerManager::removeEventListener target is null.");
    CCAssert(handle!=NULL,"CCEventListenerManager::removeEventListener handle is null.");
    CCAssert(handleObject!=NULL,"CCEventListenerManager::removeEventListener handleObject is null.");

    CCArray* targetListeners=static_cast<CCArray*>(m_pListeners->objectForKey(target->m_uID));
    if(targetListeners) {
        if(type) {
            //移除对应的type事件
            CCArray* eventListeners=static_cast<CCArray*>(targetListeners->objectForKey(type));
            if(eventListeners) {
                //某事件有处理函数
                if(handle) {
                    //删除事件中的handler
                    removeListeners(eventListeners,handleObject,handle);
                } else {
                    //删除事件中的处理对象为handleObject的注册项
                    removeListeners(eventListeners,handleObject);
                }
            }
        } else {
           //删除target的所有监听者

        }
    }
}



void removeListeners(CCArray* listeners,CCObject* handleObject)
{
    //使用index删除，效率会高些。但要注意删除后的空位置.
    //如果使用object删除，则效率会低些，但不会有空位引发的问题。
    
    CCObject* pObject = NULL;
    if (listeners && listeners->data->num > 0){         
        int len=listeners->data->num;
        CCObject** arr = listeners->data->arr;
        for(int i=0;i<len;){
		    CCEventHandle* eventHandle=(CCEventHandle*)(*(arr+i));
		    if (eventHandle->getTarget()==handleObject) {
			    listeners->removeObjectAtIndex(i);
                --len;
		    }else{
                ++i;
            }
	    }
    }
}

void removeListeners(CCArray* listeners,CCObject* handleObject,SEL_EventHandle handle)
{
    //使用index删除，效率会高些。但要注意删除后的空位置.
    //如果使用object删除，则效率会低些，但不会有空位引发的问题。

    CCObject* pObject = NULL;
    if (listeners && listeners->data->num > 0){         
        int len=listeners->data->num;
        CCObject** arr = listeners->data->arr;
        for(int i=0;i<len;){
		    CCEventHandle* eventHandle=(CCEventHandle*)(*(arr+i));
		    if (eventHandle->getTarget()==handleObject && eventHandle->getHandle()==handle) {
			    listeners->removeObjectAtIndex(i);
                --len;
		    }else{
                ++i;
            }
	    }
    }
}

void CCEventListenerManager::dispatchEvent(CCObject* target,CCEvent* event)
{
    // Capture no
    
    // Target
    //event.currentTarget=obj;
    this.handleEvent(obj,event);
    // Bubble
    var parent=obj.getParent && obj.getParent();
    while(parent && !event.isDispatchStopped()){
        //event.currentTarget=parent;
        this.handleEvent(parent,event);
        parent=parent.getParent && parent.getParent();
    }
}

void CCEventListenerManager::handleEvent(CCObject* target,CCEvent* event)
{
    if(obj._eventId_) {
        var eventListeners=Events[obj._eventId_];
        if(eventListeners) {
            var listeners=eventListeners[event.type]&&eventListeners[event.type].listeners;
            if(listeners) {
                var listener;
                for(var i=0,l=listeners.length;i<l;i++) {
                   listener=listeners[i];
                   listener.handle.apply(listener.scope,[event].concat(listener.data));
                }
            }
        }
    }
}

bool CCEventListenerManager::isListened(CCArray* listeners,SEL_EventHandle handle,CCObject* handleObject)
{
    CCObject* pObj=NULL;
    CCEventHandle* eventHandle=NULL;

    CCARRAY_FOREACH(listeners,pObj){
        eventHandle=(CCEventHandle*) pObj;
        if (eventHandle->getHandle()==handle && eventHandle->getTarget()==handleObject) {
			return true;
		}
    }
    return false;
}

CCArray* CCEventListenerManager::getEventListeners(CCObject* target,const char* type)
{
    var eventListeners=Events[obj._eventId_];
    if(eventListeners && type){
        eventListeners= eventListeners[type] && eventListeners[type].listeners;
    }
    return eventListeners;
}

//把new EventObject和dispatchEvent和起来，提供简便方法
void CCEventListenerManager::trigger(CCObject* target,const char* type,CCDictionary* data,bool bubbles)
{
    bubbles=typeof bubbles=='undefined'?true:bubbles;
    var e=new EventObject(type,bubbles,true);
    e.data=data;
    this.dispatchEvent(obj,e);
}


NS_CC_YHLIB_END