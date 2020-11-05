#include<iostream>
#include<fstream>
/*
        Caller-->Callee
by value: N --> M or *N --> M
by alias: N --> &M or N --> *&M
by pointer: N --> *M or *&N --> *M
*/

using namespace std;

const int NIL{-1};
template<class T>
struct stack
{
    T* baseArray;
    int top;
    int capacity;
    int count;
};

template<class T>
bool createStack(stack<T> *st, int capacity = 50)
{
    st->baseArray = new(nothrow)T[capacity];
    st->top = NIL;
    st->capacity = capacity;
    st->count = 0;
    return true;
}

template<class T>
bool isFull(stack<T> st)
{
    return st.top == st.capacity-1;
}

template<class T>
bool isEmpty(stack<T> st)
{
    return st.top == NIL;
}

template<class T>
bool push(stack<T> *st, T item)
{
    if (!isFull(*st))
        {
            st->baseArray[++st->top] = item;
            st->count++;
            return true;
        }
    else
        return false;
}

template<class T>
bool pop(stack<T> *st/*, T& takePoppedItem = NIL*/)
{
    if(!isEmpty(*st))
    {
        // takePoppedItem = st->baseArray[st->top];
        st->top--;
        return true;
    }
    else
        return false;
}

template<class T>
T peekTop(stack<T> st)
{
    return st.baseArray[st.top];
}

template<class T>
bool resize(stack<T>* st, int capacity)
{
    T* temp;
    int tempCapacity = st->capacity;
    temp = new(nothrow)T[st->capacity];
    if (!temp)
    {
        for(int i=0;i<st->capacity;i++)
            temp[i] = st->baseArray[i];
    
        delete [] st->baseArray;
        
        createStack(*&st, capacity);

        for(int i=0;i<tempCapacity;i++)
        {
            st->baseArray[i] = temp[i];
            st->count++;
            st->top++;
        }

        return true;
    }
    
    return false;

}

template<class T>
void clear(stack<T> *st)
{
    st->top = NIL;
}

template<class T>
void destroy(stack<T> *st)
{
    clear(st);
    delete [] st->baseArray;
}

template<class T>
void displayStack(stack<T> st)
{
    for(int i=st.top; i>=0;i--)
        cout<< st.baseArray[i]<<" ";
}

int main()
{
    stack<int> st;
    createStack(&st, 5);
    push(&st, 45);
	push(&st, 35);
	push(&st, 25);
	push(&st, 15);
	push(&st, 5);

    displayStack(st);

    cout<<endl<<peekTop(st)<<endl;

    resize(&st, 10);

    pop(&st);
    pop(&st);

    cout<<peekTop(st)<<endl;

    displayStack(st);
    destroy(&st);
    displayStack(st);

}