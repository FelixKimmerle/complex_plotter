#pragma once
#include "Result.hpp"

class SStack
{
  private:
    Complex *mem;
    unsigned int pos;
    unsigned int msize;

  public:
    SStack(unsigned int size)
    {
        pos = 0;
        msize = size;
        mem = new Complex[size];
    }
    ~SStack()
    {
        delete[] mem;
    }
    Complex &top()
    {
        return mem[pos-1];
    }
    void pop()
    {
        pos--;
    }
    void push(Complex x)
    {
        mem[pos++] = x;
    }
    void Print()
    {
        std::cout << "------------------" << std::endl;
        for (unsigned int i = 0; i < msize; i++)
        {
            std::cout << mem[i] << std::endl;
        }
    }
};

class Programm
{
  private:
    unsigned int m_uiStackSize;
    std::vector<Item> m_Programm;

  public:
    Programm(std::vector<Item> p_Programm);
    Programm();
    void SetProgramm(std::vector<Item> p_Programm);
    ~Programm();
    void Print();
    Complex Calc(Complex input);
    void CalcStack();
};
