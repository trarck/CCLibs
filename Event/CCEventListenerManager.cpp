#include "CCEventListenerManager.h"

NS_CC_YHLIB_BEGIN

CCEventListenerManager::CCEventListenerManager();

CCEventListenerManager::~CCEventListenerManager();

bool CCEventListenerManager::init();

void CCEventListenerManager::addEventListener(CCObject* target,const char* type,SEL_EventHandle handle,CCObject* handleObject,CCObject* data)
{

    unsigned int id=target->m_uID;
    
    var listener= {
        handle:handle,
        scope:scope||obj,
        data:data||[]
    };

    //get listeners
    var listeners,eventListeners=Events[id]||(Events[id]={});

    if(eventListeners[type]){
        listeners=eventListeners[type].listeners;
    }else{
        eventListeners[type]={};
    }
    //is listened. one type event only have a  handle ,have multi-processor function
    //一个事件只有一个触发点，但有很多处理该事件的函数
    if(listeners){
        if(!this.isListened(listeners,handle)) {
            listeners.push(listener);
        }
    }else{
        //add event handle to listene
        eventListeners[type].listeners=[listener];

        // //add to framework listener systerm,trigger by framework automatic. user defined event trigger by user program manual.
        // //事件处理函数。系统中的事件传的参数不一样，要做相应的接口对接，全部转成EventObject。
        // eventListeners[type].handle=this.getEventHandle(type,obj,params);
        // //设置系统触发点。平台事件由系统自动触发。自定义事件要手动触发。
        // this.addTrigger(obj,type,eventListeners[type].handle,params);
    }
}

void CCEventListenerManager::removeEventListener(CCObject* target,const char* type,SEL_EventHandle handle) 
{
    if(obj._eventId_) {
        var eventListeners=Events[obj._eventId_];
        if(eventListeners) {
            //有obj对应的事件
            if(type) {
                var listeners=eventListeners[type] && eventListeners[type].listeners;
                if(listeners) {
                    //某事件有listeners
                    if(handle) {
                        //删除事件中的handler
                        var i=this.getHandlerIndex(listeners,handle);
                        if(i>-1) {
                            listeners.splice(i,1);
                        }
                        if(listeners.length==0){
                            // this.removeTrigger(obj,type,eventListeners[type].handle);
                            delete eventListeners[type];
                        }
                    } else {
                        //删除事件的所有handler，即删除obj的type事件。
                        // this.removeTrigger(obj,type,eventListeners[type].handle);
                        delete eventListeners[type];
                    }
                }
            } else {
                // remove all object events
                
                // for(var i in eventListeners){
                    // //remove trigger
                    // this.removeTrigger(obj,i,eventListeners[i].handle);
                // }
                delete Events[obj._eventId_];
                //delete obj._eventId_;
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

bool CCEventListenerManager::isListened(CCArray* listeners,SEL_EventHandle handle)
{
    return this.getHandlerIndex(listeners,handle)>-1;
}

int CCEventListenerManager::getHandlerIndex(CCArray* listeners,SEL_EventHandle handle)
{
    var p=-1;
    for(var i=0,l=listeners.length;i<l;i++) {
        if(listeners[i].handle==handle) {
            p=i;
            break;
        }
    }
    return p;
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