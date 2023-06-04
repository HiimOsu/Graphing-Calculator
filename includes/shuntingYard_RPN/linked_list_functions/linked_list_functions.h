#ifndef LINKED_LIST_FUNCTIONS_H
#define LINKED_LIST_FUNCTIONS_H

#include  "../node/node.h"
#include <cassert>
#include <iostream>
using namespace std;

//================================Entering Signatures===================================================
//Linked List General Functions:
     
    //-----------------------------------------------------------------
    //_print_list()
    //implemeneted:
    //Rec:  head = node ptr pointing to the first node.
    //Pre:It is a Std linked list
    //Post:cout each node in the list. Stops when hits a null ptr
    //-----------------------------------------------------------------
    template <typename ITEM_TYPE>
    void _print_list(node<ITEM_TYPE>* head, ostream& outs = cout);

    //recursive fun! :)
    template <typename ITEM_TYPE>
    void _print_list_backwards(node<ITEM_TYPE> *head);

    //-----------------------------------------------------------------
    //node<ITEM_TYPE>* _search_list(node<ITEM_TYPE>* head, ITEM_TYPE key){
    //implemeneted:
    //Rec:  head: node ptr pointing to the first node;
    //          key: key to find in the list
    //Pre:  Head is a Std linked list, the list is not empty
    //Post: If key exists,  return a ptr pointing to that node
    //          if pkey does not exist, return a nullptr
    //-----------------------------------------------------------------    
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _search_list(node<ITEM_TYPE>* head,
                                ITEM_TYPE key);

    //-----------------------------------------------------------------
    //_insert_head(node<ITEM_TYPE> *&head, ITEM_TYPE insert_this)
    //implemeneted:
    //Rec:  head: node ptr pointing to the first node;
    //          insert_this: the data to be hold for the node;
    //Pre:  It is a Std linked list, and ITEM_TYPE have an one argument constructor(insert_this)
    //Post: insert a node before the head. 
    //          After insertion should look like: head->insert_this->original_headNode 
    //          return a ptr pointing to the new_node
    //-----------------------------------------------------------------
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _insert_head(node<ITEM_TYPE> *&head,
                                ITEM_TYPE insert_this);

    //-----------------------------------------------------------------
    //_insert_after(node<ITEM_TYPE> *&head, node<ITEM_TYPE> *after_this, ITEM_TYPE insert_this)
    //implemeneted:
    //Rec:  head: node ptr pointing to the first node;
    //          insert_this: the data to be hold for new_node;
    //          after_this : ptr marks location to insert
    //Pre:  TEM_TYPE have an one argument constructor(insert_this)
    //Post: insert a node after the after_this. 
    //          After insertion : after_this->insert_this->original_after_this_next
    //          ***If head != nullptr, after_this == nullptr, insert node after the last node
    //          ***if head == nullptr, do insert_head
    //          Always: return a ptr pointing to the new_node
    //-----------------------------------------------------------------
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _insert_after(node<ITEM_TYPE>*& head,
                                 node<ITEM_TYPE> *after_this,
                                 ITEM_TYPE insert_this);

    //-----------------------------------------------------------------
    //_insert_after(node<ITEM_TYPE> *&head, node<ITEM_TYPE> *before_this, ITEM_TYPE insert_this)
    //implemeneted:
    //Rec:  head: node ptr pointing to the first node;
    //          insert_this: the data to be hold for new_node;
    //          before_this: ptr marks location to insert
    //Pre: ITEM_TYPE have an one argument constructor(insert_this)
    //Post: insert a node before before_this. 
    //          After insertion : Before_before_this->insert_this->before_this
    //          Always: return a ptr pointing to the new_node
    //-----------------------------------------------------------------
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _insert_before(node<ITEM_TYPE>*& head,
                                  node<ITEM_TYPE>* before_this,
                                  ITEM_TYPE insert_this);
    //-----------------------------------------------------------------
    //node<ITEM_TYPE>* _previous_node(node<ITEM_TYPE>* head, node<ITEM_TYPE>* prev_to_this)
    //implemeneted:
    //Rec:  head: node ptr pointing to the first node;
    //          prev_to_this: the next node of previous_node;
    //Pre:  It is a Std linked list;
    //Post: return the ptr pointing to previous_node where:  previous_node-> prev_to_this, If prev_to_this exists in the list
    //          return nullptr, if prev_to_this does not exist or = head
    //-----------------------------------------------------------------    
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _previous_node(node<ITEM_TYPE>* head,
                                  node<ITEM_TYPE>* prev_to_this);
   
    //-----------------------------------------------------------------
    //ITEM_TYPE _delete_node(node<ITEM_TYPE>*&head, node<ITEM_TYPE>* delete_this)
    //implemeneted:
    //Rec:  head: node ptr pointing to the first node;
    //          delete_this: node to delete;
    //Pre:  It is a Std linked list, node is inside the list;
    //Post: return the item of delete_this, and delete the node, If delete_this exist
    //          return a ITEM_TYPE constructed by a default constr instead, if prev_to_this does not exist;
    //-----------------------------------------------------------------    
    template <typename ITEM_TYPE>
    ITEM_TYPE _delete_node(node<ITEM_TYPE>*&head,
                         node<ITEM_TYPE>* delete_this);
    
    //-----------------------------------------------------------------
    //_copy_list(node<ITEM_TYPE>* head)
    //implemeneted:
    //Rec:  head: node ptr pointing to the first node;
    //
    //Pre:  head can be an empty list or filled list
    //
    //Post: return a ptr of an identical list
    //      If list is empty, return nullptr instead
    //-----------------------------------------------------------------    
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _copy_list(node<ITEM_TYPE>* head);

    //-----------------------------------------------------------------
    //node<T> *_copy_list(node<T>* &dest, node<T> *src);
    //implemeneted:
    //Rec:  dest:   destination to copy to
    //      src:    list to be copy
    //
    //Pre:  src can be an empty list or filled list
    //
    //Post: dest hold a list identical to src,
    //      the original list stored in dest will be cleared, if there is any
    //-----------------------------------------------------------------    
    template <typename T>
    node<T> *_copy_list(node<T>* &dest, node<T> *src);

    //-----------------------------------------------------------------
    //void _clear_list(node<ITEM_TYPE>*& head);
    //implemeneted:
    //Rec:  head: pointer pointing to a list
    //
    //Pre:  head could be empty or filled
    //
    //Post: The original list stored in head will be deleted, if there is any
    //      head will return as nullptr
    //-----------------------------------------------------------------    
    template <typename ITEM_TYPE>
    void _clear_list(node<ITEM_TYPE>*& head);

    //-----------------------------------------------------------------
    //ITEM_TYPE& _at(node<ITEM_TYPE>* head, int pos);
    //implemeneted:
    //Rec:  head:   pointer pointing to a list
    //      pos:    index/position to retrive
    //Pre:  pos cannot be negative or out of bound
    //      head is not an empty list
    //
    //Post: return the item itself at _pos.
    //-----------------------------------------------------------------    
    template <typename ITEM_TYPE>
    ITEM_TYPE& _at(node<ITEM_TYPE>* head, int pos);

    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    //      Sorted List Routines. order: 0: ascending, order: other: descending
    //                              Assume a Sorted List
    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _insert_sorted(node<ITEM_TYPE>* &head,       //insert
                                  ITEM_TYPE item,
                                  bool ascending=true);

    //insert or add if a dup
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _insert_sorted_and_add(node<ITEM_TYPE>* &head,
                                          ITEM_TYPE item,
                                          bool ascending=true);
    //node after which this item goes order: 0 ascending
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _where_this_goes(node<ITEM_TYPE>* head,
                                   ITEM_TYPE item,
                                   bool ascending=true);
    //Last Node in the list
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _last_node(node<ITEM_TYPE>* head);            //never use this function.

//***************************************************************************************************************
//=========================================Entering Definition===================================================


//Linked List General Functions:
    //LOW-LEVEL 
    //#Fin

 //print functions  
    //#Fin    
    template <typename ITEM_TYPE>
    void _print_list(node<ITEM_TYPE>* head, ostream& outs){
        node<ITEM_TYPE>* walker = head;

        while(walker != nullptr){
            outs << "[" << *walker << "]-> ";

            walker = walker->_next;

        }   
        
        outs << "|||";
    }

    //#Fin    
    template <typename ITEM_TYPE>
    void _print_list_backwards(node<ITEM_TYPE> *head){
        if(head == nullptr){
            return;
        }
        
        if(head->_next != nullptr){
            _print_list_backwards(head->_next);
        }

        cout << head->_item << " ";
        return;
    }
//------------------------------------------------------------------------------------------------------------------
//Search & Insertion
    //#Fin    
    //LOW-LEVEL
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _search_list(node<ITEM_TYPE>* head, ITEM_TYPE key){
        assert(head != nullptr && "ERROR _search_list()]: List cannot be empty");   
        node<ITEM_TYPE>* walker = head;

        while(walker != nullptr && walker->_item != key){
            walker = walker->_next;
        }     
        
        return walker;
    }

    //#Fin    
    //LOW-LEVEL
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _insert_head(node<ITEM_TYPE> *&head, ITEM_TYPE insert_this){
        node<ITEM_TYPE>* new_node    = new node<ITEM_TYPE>(insert_this, head);  
        //visualize:
        //head->new_node->old_head
        head = new_node;     //head points back to new_head = new_node
        return new_node;
    }

    //#Fin    
    //LOW-LEVEL
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _insert_after(node<ITEM_TYPE>*& head, node<ITEM_TYPE> *after_this, ITEM_TYPE insert_this){
        // assert(after_this != nullptr && "ERROR [_insert_after()]: Beyond the bond, cannot insert after the end");
        if(head == nullptr){
            return _insert_head(head, insert_this);
        }  
        if(after_this == nullptr){
                after_this = _previous_node<ITEM_TYPE>(head, nullptr);
        }
        
        node<ITEM_TYPE>* new_node    = new node<ITEM_TYPE>(insert_this, after_this->_next);
        after_this->_next   = new_node;
        return new_node;
    }

    //#Fin    
    //LOW-LEVEL
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _insert_before(node<ITEM_TYPE>*& head, node<ITEM_TYPE>* before_this, ITEM_TYPE insert_this){
        if(head == before_this){
            return _insert_head(head, insert_this);
        }
       
        node<ITEM_TYPE>* previous_node = _previous_node<ITEM_TYPE>(head, before_this);
        node<ITEM_TYPE>*   new_node    = new node<ITEM_TYPE>(insert_this, before_this);
        previous_node->_next  = new_node;

        return new_node;
    }

//------------------------------------------------------------------------------------------------------------------
//accessor: _PREVIOUS
    //#Fin    
    //LOW-LEVEL
    //ptr to previous node
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _previous_node(node<ITEM_TYPE>* head, node<ITEM_TYPE>* prev_to_this){
        assert(head != nullptr && "ERROR [_previous_node()]: List cannot be empty");
        node<ITEM_TYPE>* walker = head;

        if(head == prev_to_this){
            return nullptr;
        }

        while(walker->_next != prev_to_this && walker->_next != nullptr){
            walker = walker -> _next;
        }
        
        return walker;
    }

//------------------------------------------------------------------------------------------------------------------
//Delete,Copy,Clear
    //#Fin    
    //LOW-LEVEL
    template <typename ITEM_TYPE>
    ITEM_TYPE _delete_node(node<ITEM_TYPE>*&head, node<ITEM_TYPE>* delete_this){
        assert(head != nullptr && "ERROR [_delete_node()]: List cannot be empty");
        assert(delete_this != nullptr && "ERROR[_delete_node()]: cannot delete nullptr");
        ITEM_TYPE return_me;

        if(delete_this == head){
            return_me   = delete_this->_item;
            head        = delete_this->_next;

            delete delete_this;
            return return_me;
        }
        
        node<ITEM_TYPE>* walker = head;
        while(walker != nullptr && walker->_next != delete_this){//check delete_this is in the list 
            walker = walker->_next;
        }
        
        assert(walker != nullptr && "Error[_delete_node]: Deleting non-existing node");

        return_me       = delete_this->_item;
        walker->_next   = delete_this->_next;

        delete delete_this;
        return return_me;
    }

    //#Fin
    //duplicate the list...
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _copy_list(node<ITEM_TYPE>* head){
        if(head == nullptr){
            return nullptr;
        }
        
        node<ITEM_TYPE>* new_head = nullptr;
        node<ITEM_TYPE>* old_head_w = head;
        
        node<ITEM_TYPE>* new_head_w = _insert_head(new_head, old_head_w->_item);
        old_head_w = old_head_w->_next;

        while(old_head_w != nullptr){
            new_head_w = _insert_after(new_head, new_head_w, old_head_w->_item);
            old_head_w = old_head_w->_next;
        }

        return new_head;
    }
    
    //#Fin
    //duplicate list and return the last node of the copy
    template <typename T>
    node<T> *_copy_list(node<T>* &dest, node<T> *src){
        if(dest != nullptr){
            _clear_list(dest);
        }
        
        dest = _copy_list(src);
        return dest;
    }

    //#Fin    
    //delete all the nodes
    template <typename ITEM_TYPE>
    void _clear_list(node<ITEM_TYPE>*& head){
        node<ITEM_TYPE>* w;

        while(head != nullptr){
            w = head;
            head = head->_next;

            delete w;
        }

        return;
    }

//------------------------------------------------------------------------------------------------------------------
//accessor: _AT
    //LOW-LEVEL
    //_item at this position
    template <typename ITEM_TYPE>
    ITEM_TYPE& _at(node<ITEM_TYPE>* head, int pos){
        assert(head != nullptr && "Error (_at()): list is empty");
        assert(pos >= 0 && "Error (_at()): position is negative");
        node<ITEM_TYPE>* w = head;
        for(int i = 0; i < pos; i++){
            w = w->_next;
            assert(w != nullptr && "ERROR [_at(node head, int pos): position is out of bound");
        }

        return w->_item;
    }

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//      Sorted List Routines. order: 0: ascending, order: other: descending
//                              Assume a Sorted List
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _insert_sorted(node<ITEM_TYPE>* &head, ITEM_TYPE item, bool ascending){
        if(head == nullptr){
            _insert_head(head, item);
        }

        node<ITEM_TYPE>* w = head;

        
        w = _where_this_goes(head, item, ascending);

        if(w == head){
            w = _insert_head(head, item);
        }else{
            w = _insert_after(head, w, item);
        }

        return w;
    }

    //insert or add if a dup
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _insert_sorted_and_add(node<ITEM_TYPE>* &head, ITEM_TYPE item, bool ascending){

    }
   
    //node after which this item goes order: 0 ascending
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _where_this_goes(node<ITEM_TYPE>* head, ITEM_TYPE item, bool ascending){     
        node<ITEM_TYPE>* w = head;
        if(ascending){//ascending
            while(w->_next != nullptr && w->_next->_item < item){
                w = w->_next;
            }

            return w;
        }
        else{//descending
            while(w->_next != nullptr && w->_next->_item > item){
                w = w->_next;
            }

            return w;
        }
    }

    //Last Node in the list
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _last_node(node<ITEM_TYPE>* head){
        if(head == nullptr){
            return nullptr;
        }
        return _previous_node<ITEM_TYPE>(head, nullptr);    
    }

//**********************************************************************************************

#endif