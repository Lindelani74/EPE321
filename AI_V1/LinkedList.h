#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;
#include "Node.h"
template <class T>
class LinkedList
{
public:


    Node<T> *head;

    LinkedList(){
        head=nullptr;
    }
    LinkedList(const LinkedList<T> &other){

        Node<T> *temp = other.head;
        head = new Node<T>(temp->element);
        Node<T> *tmp=nullptr;
        head->next=tmp;

        while(temp->next!=nullptr){
            temp=temp->next;
            tmp->next = new Node<T>(temp->element);
            tmp=tmp->next;
        }



    }

    ~LinkedList(){
        delete head;
    }

    void insert(int index,T element){
        //cout<<"Inserting"<<endl;
        if(index==this->size() || index==0){
            if(index==0){

                Node<T> *temp=new Node<T>(element);

                temp->next = head;
                head = temp;

                //System.out.println(this.isEmpty());
            }

            else{
            Node<T> *temp=head;

            while(temp->next!=nullptr){
                temp=temp->next;
                //System.out.print(temp.element);
            }

            temp->next = new Node<T>(element);
            }
        }

        else if(index<this->size()){
            Node<T> *temp=head;

            for(int count=0;count<index;count++)
                temp=temp->next;

            temp->next= new Node<T>(element);

        }

        else
            return ;

    }

    T remove(T elem){

        Node<T> *temp=head;
        Node<T> *tmp=nullptr;

        /*if(isEmpty()==true){
            //throw "Empty list";
            //throw exception
        }*/

        if(elem==head->element){
            head=head->next;
            temp->next=nullptr;
            //return temp.element;
        }

        else{
            int count=0;

            while(temp->next!=nullptr && elem!=temp->element){
                tmp=temp;
                temp=temp->next;
                count++;
            }

            tmp->next=temp->next;
            temp->next=nullptr;

            //return temp.element;

        }

        /*else{
                //throw "Out of Bounds";
                //throw exception
            }*/

        return temp->element;
    }

    T remove(uint8_t index){

        Node<T> *temp=head;
        Node<T> *tmp=nullptr;

        /*if(isEmpty()==true){
            //throw "Empty list";
            //throw exception
        }*/

        if(index>=0 && index<size()){

            if(index==0){
                head = head->next;
                temp->next=nullptr;
                //return temp.element;
            }

            else{
                int count=0;

                while(temp->next!=nullptr && count<index){
                    tmp=temp;
                    temp=temp->next;
                    count++;
                }

                tmp->next=temp->next;
                temp->next=nullptr;

                //return temp.element;

            }


        }

        /*else{
                //throw "Out of Bounds";
                //throw exception
            }*/

            return temp->element;
    }

    bool find(T elem){

        Node<T> *temp=head;
        Node<T> *tmp=nullptr;

        /*if(isEmpty()==true){
            //throw "Empty list";
            //throw exception
        }*/
        if(this->isEmpty())
            return false;

        if(elem==head->element){
            return true;
        }

        else{
            int count=0;

            while(temp->next!=nullptr && elem!=temp->element){
                tmp=temp;
                temp=temp->next;
                count++;
            }

            if(elem==temp->element)
                return true;

        }

        /*else{
                //throw "Out of Bounds";
                //throw exception
            }*/

        return false;
    }

    bool set(int index,T element){
        Node<T> *temp = head;

        /*if(isEmpty()==true){
            //throw "Empty list";
            //throw exception
        }*/

        if(index>=0 && index<size()){

            if(index==0){
                temp->element = element;
                return true;
            }

            else{
                int count=0;

                while(temp->next!=nullptr && count<index){
                    temp=temp->next;
                    count++;
                }

                temp->element = element;
                return true;

            }


        }

        /*else{
                //throw "Out of Bounds";
                //throw exception
            }*/

        return false;
    }

    T* get(int index){

        Node<T> *temp = head;

        /*if(isEmpty()==true){
            //throw "Empty list";
            //throw exception
        }*/

        if(index>=0 && index<size()){

            if(index==0){
                return &temp->element;
            }

            else{
                int count=0;

                while(temp->next!=nullptr && count<index){
                    temp=temp->next;
                    count++;
                }


                return &temp->element;

            }


        }

        /*else{
                //throw "Out of Bounds";
                //throw exception
            }*/

        return nullptr;
    }

    bool isEmpty(){
        if(head==nullptr)
            return true;

        else
            return false;
    }

    void clear(){
        head=nullptr;
    }

    Node<T>* getLeader(){
        return this->head;
    }

    int size(){

        if(head!=nullptr){
            int count=1;
            Node<T> *temp = head;

            for(;temp->next!=nullptr;count++)
                temp=temp->next;

            return count;
        }
        else
            return 0;

    }


};


#endif // LINKEDLIST_H
