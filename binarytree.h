#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

template <class T>
class BinaryTree
{
private:
    struct Tree
    {
        T value;
        Tree *left;
        Tree *right;
        unsigned char height;
        Tree(T value)
        {
            this->value = value;
            left = 0;
            right = 0;
            height = 1;
        }
    };
public:
    int size;
    Tree *opr;
    BinaryTree():size(0),opr(0){};
    BinaryTree(T value):size(1)
    {
        std::cout << value << " : " << "BASED" << std::endl;
        opr = new Tree(value);
    };
    BinaryTree(std::vector<T> values):size(values.size())
    {
        Push_BalanceVector(opr,values,0,values.size()-1);
    }
    std::vector<T> Convert_ToVector()
    {
        std::vector<T> convert_Vector;
        r_vector_out1(opr,convert_Vector);
        return convert_Vector;
    };
    //Область кода для балансировки дерева
    void Balance_1()
    {
        std::vector<T> vec = this->Convert_ToVector();
        r_delete(opr);
        opr = 0;
        Push_BalanceVector(vec,0,size-1);
    }
    // Второй способ подразумевает балансировку при каждом добавлении, это нужно добавить, статья есть на хабре
    unsigned char Height(Tree* actual)
    {
        return actual?actual->height:0;
    }
    int bFactor(Tree* actual)
    {
        return Height(actual->right)-Height(actual->left);
    }
    void fixheight(Tree* actual)
    {
        unsigned char hl = Height(actual->left);
        unsigned char hr = Height(actual->right);
        actual->height = (hl>hr?hl:hr)+1;
    }
    Tree* rotateright(Tree* actual) // правый поворот вокруг p
    {
        Tree* rotate_tree = actual->left;
        actual->left = actual->right;
        rotate_tree->right = actual;
        fixheight(actual);
        fixheight(rotate_tree);
        return rotate_tree;
    }
    Tree* rotateleft(Tree* actual) // правый поворот вокруг p
    {
        Tree* rotate_tree = actual->right;
        actual->left = rotate_tree->right;
        rotate_tree->left = actual;
        fixheight(actual);
        fixheight(rotate_tree);
        return rotate_tree;
    }
    Tree* balance(Tree* p) // балансировка узла p
    {
        fixheight(p);
        if( bFactor(p)==2 )
        {
            if( bFactor(p->right) < 0)
                p->right = rotateright(p->right);
            return rotateleft(p);
        }
        if( bFactor(p)==-2 )
        {
            if(bFactor(p->left) > 0)
                p->left = rotateleft(p->left);
            return rotateright(p);
        }
        return p; // балансировка не нужна
    }
    Tree* insert(Tree* p, int k) // вставка ключа k в дерево с корнем p
    {
        if(!p)
        {
            return new Tree(k);
        }
        if( k<p->value )
            p->left = insert(p->left,k);
        else
            p->right = insert(p->right,k);
        return balance(p);
    }
    Tree* findmin(Tree* p) // поиск узла с минимальным ключом в дереве p
    {
        return p->left?findmin(p->left):p;
    }

    Tree* removemin(Tree* p) // удаление узла с минимальным ключом из дерева p
    {
        if( p->left==0 )
            return p->right;
        p->left = removemin(p->left);
        return balance(p);
    }

    Tree* remove(Tree* p, int k) // удаление ключа k из дерева p
    {
        if( !p ) return 0;
        if( k < p->value )
            p->left = remove(p->left,k);
        else if( k > p->key )
            p->right = remove(p->right,k);
        else //  k == p->key
        {
            Tree* q = p->left;
            Tree* r = p->right;
            delete p;
            if( !r ) return q;
            Tree* min = findmin(r);
            min->right = removemin(r);
            min->left = q;
            return balance(min);
        }
        return balance(p);
    }
    //Область кода для балансировки дерева
    void Push(T value)
    {
        if(!opr)
        {
            std::cout << value << " : " << "BASED" << std::endl;
            opr = new Tree(value);
            return;
        }
        std::string path = "";
        Tree *actual = opr;
        while(true)
        {
            if(value > actual->value)
            {
                path += "r";
                if(actual->right)
                {
                    actual = actual->right;
                    continue;
                }
                else
                {
                    actual->right = new Tree(value);
                    break;
                }
            }
            else
            {
                path += "l";
                if(actual->left)
                {
                    actual = actual->left;
                    continue;
                }
                else
                {
                    actual->left = new Tree(value);
                    break;
                }
            }
        }
        size++;
        std::cout << value << " : " << path << std::endl;
    }
    void Push_BalanceVector(std::vector<T> &vector,int left,int right)
    {
        int mid = int(((left+right)/2.0)+0.5);
        Push(vector[mid]);
        if(mid+1<=right)
            Push_BalanceVector(vector,mid+1,right);
        if(mid-1>=left)
            Push_BalanceVector(vector,left,mid-1);
    }
    bool Remove(T value)
    {
        //Tree ** parent = &opr;
        Tree ** actual = &opr;
        while(true)
        {
            if(value > (*actual)->value)
            {
                //parent = actual;
                actual = &((*actual)->right);
                if(!actual)
                    return false;
            }
            else if(value < (*actual)->value)
            {
                //parent = actual;
                actual = &((*actual)->left);
                if(!(*actual))
                    return false;
            }
            else
            {
                if(!(*actual)->left && !(*actual)->right)
                {
                    delete *actual;
                    *actual = 0;
                    return true;
                }
                else if(!(*actual)->left)
                {
                    *actual = (*actual)->right;
                    return true;
                }
                else if(!(*actual)->right)
                {
                    *actual = (*actual)->left;
                    return true;
                }
                else
                {
                    Tree **now = &((*actual)->right);
                    while((*now)->left)
                    {
                        now = &((*now)->left);
                    }
                    T remove_value = ((*now)->value);
                    Remove(remove_value);
                    (*actual)->value = remove_value;
                    return true;
                }
            }
        }

    }
    bool Search(T value)
    {
        Tree * actual = opr;
        while(true)
        {
            if(value > actual->value)
            {
                actual = actual->right;
                if(!actual)
                    return false;
            }
            else if(value < actual->value)
            {
                actual = actual->left;
                if(!actual)
                    return false;
            }
            else
                return true;
        }
    }
private:
    T* Get(T value)
    {
        Tree * actual = opr;
        while(true)
        {
            if(value > actual->value)
            {
                actual = actual->right;
                if(!actual)
                    return false;
            }
            else if(value < actual->value)
            {
                actual = actual->left;
                if(!actual)
                    return false;
            }
            else
                return actual;
        }
    }
public:
    std::string Out(int type)
    {
        std::string out;
        if(type == 1)
            r_out1(opr,out);
        else if(type == 2)
            r_out2(opr,out);
        else if(type == 3)
            r_out3(opr,out);
        return out;
    }
private:
    void r_out1(Tree *actual,std::string &str)
    {
        str += std::to_string(actual->value) + " ";
        if(actual->left)
        r_out1(actual->left,str);
        if(actual->right)
        r_out1(actual->right,str);
    }
    void r_out2(Tree *actual,std::string &str)
    {
        if(actual->left)
        r_out2(actual->left,str);
        str += std::to_string(actual->value) + " ";
        if(actual->right)
        r_out2(actual->right,str);
    }
    void r_out3(Tree *actual,std::string &str)
    {
        if(actual->left)
        r_out3(actual->left,str);
        if(actual->right)
        r_out3(actual->right,str);
        str += std::to_string(actual->value) + " ";
    }
    void r_vector_out1(Tree *actual,std::vector<T> &convert_Vector)
    {
        convert_Vector.push_back(actual->value);
        if(actual->left)
        r_vector_out1(actual->left,convert_Vector);
        if(actual->right)
        r_vector_out1(actual->right,convert_Vector);
    }
    void r_delete(Tree *actual)
    {
        if(actual->left)
        r_delete(actual->left);
        if(actual->right)
        r_delete(actual->right);
        delete actual;
    }
public:
    ~BinaryTree()
    {

    };
};

#endif // BINARYTREE_H
