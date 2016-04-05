#ifndef __Dominus_OnItemClickedListener_h__
#define __Dominus_OnItemClickedListener_h__

class UIComponent;

class OnItemClickedListener {
public:
    virtual void onItemClicked(UIComponent* component) = 0;
};

#endif /* _ON_ITEM_CLICK_LISTENER_H_ */
