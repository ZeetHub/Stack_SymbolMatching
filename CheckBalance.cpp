#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstdlib>

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
bool pop(stack<T> *st, T& takePoppedItem = NIL)
{
    if(!isEmpty(*st))
    {
        takePoppedItem = st->baseArray[st->top];
        st->top--;
        return true;
    }
    else
        return false;
}

template<class T>
bool pop(stack<T> *st)
{
    if(!isEmpty(*st))
    {
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

// template<class T>
// void displayStack(stack<T> st)
// {
//     for(int i=0; i<=st.top;i++)
//         cout<< st.baseArray[i]<<" ";
// }

template<class T>
void displayStack(stack<T> st)
{
    for(int i=st.top; i>=0;i--)
        cout<< st.baseArray[i]<<" ";
}


void pushsymbol(ifstream & fin, stack<char> *st);
void output(int curlyOpen, int curlyClose, int bracketOpen, int bracketClose, int parenthOpen, int parenthClose);
int menu();
void select(int choice, string &fileName);

int main()
{
    stack<char> st;
    createStack(&st, 300);

    string fileName{};
    int choice;
    do
    {
        choice = menu();
        select(choice, fileName);

        if(choice != 4)
        {
            ifstream fin;
            fin.open(fileName, ios::in);

            char chOne;

            pushsymbol(fin, &st);

            displayStack(st);

            char symbol;
            int curlyOpen=0,parenthOpen=0,bracketOpen=0,curlyClose=0,parenthClose=0,bracketClose=0;

            cout<<endl<<endl;

            while (st.top != NIL)
            {
                pop(&st, symbol);
                switch (symbol)
                {
                case '}':
                    curlyClose++;
                    break;
                case ')':
                    parenthClose++;
                    break;
                case ']':
                    bracketClose++;
                    break;
                case '{':
                    curlyOpen++;
                    break;
                case '(':
                    parenthOpen++;
                    break;
                case '[':
                    bracketOpen++;
                    break;
                default:
                    break;
                }
            }
            output(curlyOpen, curlyClose, bracketOpen, bracketClose, parenthOpen, parenthClose);
            system("pause");
            system("cls");
            clear(&st);
            fin.close();
        }
    }while(choice != 4);

    return 0;
}

int menu()
{
    int choice, invalid=0;
    do
    {
        if(invalid == 1)
        {
            cout<<setfill('-')<<setw(52)<<'-'<<setfill(' ')<<endl;
            cout << "\aInvalid choice! Please select an appropriate number: "<<endl;
            cout<<setfill('-')<<setw(52)<<'-'<<setfill(' ')<<endl;
        }
        else
        {
            cout<<setfill('-')<<setw(41)<<'-'<<setfill(' ')<<endl;
            cout<< "Choose a source code from the menu below: "<<endl;
            cout<<setfill('-')<<setw(41)<<'-'<<setfill(' ')<<endl;
        }
        cout<< "1. Linked List (Array Implementation)\n2. Login Authentication\n3. Stack (Array Implementation)\n4. Exit \n";
        cout<< endl<<"Enter the number of your choice: ";
        cin>>choice;
        if(choice < 1 || choice > 4)
            invalid = 1;
        else
            invalid = 0;
        system("cls");
    } while (invalid == 1);

    return choice;
}

void select(int choice, string &fileName)
{
    switch(choice)
    {
        case 1:
            fileName = "Linked_List_Array.txt";
            break;
        case 2:
            fileName = "loginAuthentication.txt";
            break;
        case 3:
            fileName = "stackArray.txt";
            break;
        case 4:
            cout<<"Exiting Program\n\n";
                break;
        default:
            break;
    }
}

void pushsymbol(ifstream & fin, stack<char> *st)
{
    string readLine {};
    char chOne, chTwo;
    bool foundAtNext;
    while (fin.peek() != EOF){
        fin.get(chOne);
        if(chOne == '/'){
            fin.get(chTwo);
            if(chTwo == '/')
                getline(fin, readLine);
            else if(chTwo == '*'){
                do{
                    fin.get(chTwo);
                    foundAtNext = fin.peek() == '/';
                } while (chTwo != '*' || !foundAtNext);
                fin.get(chTwo);
            }
        }
        else if(chOne == '"'){
            do
            {
                fin.get(chTwo);
            } while (chTwo != '"');
        }
        else if(chOne == '\''){
            do{
                fin.get(chTwo);
            } while (chTwo != '\'');
            if(fin.peek() == '\'')
                fin.get(chTwo);
        }
        else if(chOne == '{' || chOne == '(' || chOne == '[' || chOne == '}' || chOne == ')' || chOne == ']')
            push(*&st, chOne);
    }
}

void output(int curlyOpen, int curlyClose, int bracketOpen, int bracketClose, int parenthOpen, int parenthClose)
{
    if(curlyOpen == curlyClose)
        cout<<"All open curly braces have a matching close curly brace."<<endl<<"CurlyOpen = "<<curlyOpen<<endl<<"CurlyClose = "<<curlyClose<<endl<<endl;
    else
        cout<<"There is a mismatch between open and close curly braces."<<endl<<"CurlyOpen = "<<curlyOpen<<endl<<"CurlyClose = "<<curlyClose<<endl<<endl;

    if(bracketOpen == bracketClose)
        cout<<"All open brackets have a matching close bracket."<<endl<<"BracketOpen = "<<bracketOpen<<endl<<"BracketClose = "<<bracketClose<<endl<<endl;
    else
        cout<<"There is a mismatch between open and close brackets."<<endl<<"BracketOpen = "<<bracketOpen<<endl<<"BracketClose = "<<bracketClose<<endl<<endl;

    if(parenthOpen == parenthClose)
        cout<<"All open parentheses have a matching close parenthesis."<<endl<<"ParenthesisOpen = "<<parenthOpen<<endl<<"ParenthesisClose = "
        <<parenthClose<<endl<<endl;
    else
        cout<<"There is a mismatch between open and close parentheses."<<endl<<"ParenthesisOpen = "<<parenthOpen<<endl<<"ParenthesisClose = "
        <<parenthClose<<endl<<endl;
}
