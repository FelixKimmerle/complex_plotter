#include "Programm.hpp"
#include <stack>
Programm::Programm()
{
    unsigned int curr = 0;
}

void Programm::CalcStack()
{
    unsigned int curr = 0;
    m_uiStackSize = 0;
    for (auto x = m_Programm.begin(); x != m_Programm.end(); x++)
    {
        switch (x->op)
        {
        case OPUSH:
            x++;
            curr++;
            m_uiStackSize = std::max(curr, m_uiStackSize);
            break;
        case OPUSHX:
            curr++;
            m_uiStackSize = std::max(curr, m_uiStackSize);
            break;
        case OMUL:
        case OLOG:
        case ODIV:
        case OSUB:
        case OADD:
        case OPOW:
            curr--;
            m_uiStackSize = std::max(curr, m_uiStackSize);
            break;
        default:
            break;
        }
    }
}

void Programm::SetProgramm(std::vector<Item> p_Programm)
{
    unsigned int curr = 0;
    m_uiStackSize = 0;
    m_Programm = p_Programm;
    for (auto x = m_Programm.begin(); x != m_Programm.end(); x++)
    {
        switch (x->op)
        {
        case OPUSH:
            x++;
            curr++;
            m_uiStackSize = std::max(curr, m_uiStackSize);
            break;
        case OPUSHX:
            curr++;
            m_uiStackSize = std::max(curr, m_uiStackSize);
            break;
        case OMUL:
        case OLOG:
        case ODIV:
        case OSUB:
        case OADD:
        case OPOW:
            curr--;
            m_uiStackSize = std::max(curr, m_uiStackSize);
            break;
        default:
            break;
        }
    }
}

Programm::Programm(std::vector<Item> p_Programm)
{
    unsigned int curr = 0;
    m_uiStackSize = 0;
    m_Programm = p_Programm;
    for (auto x = m_Programm.begin(); x != m_Programm.end(); x++)
    {
        switch (x->op)
        {
        case OPUSH:
            x++;
            curr++;
            m_uiStackSize = std::max(curr, m_uiStackSize);
            break;
        case OPUSHX:
            curr++;
            m_uiStackSize = std::max(curr, m_uiStackSize);
            break;
        case OMUL:
        case OLOG:
        case ODIV:
        case OSUB:
        case OADD:
        case OPOW:
            curr--;
            m_uiStackSize = std::max(curr, m_uiStackSize);
            break;
        default:
            break;
        }
    }
}

Programm::~Programm()
{
}

Complex Programm::Calc(Complex input)
{
    SStack stack(m_uiStackSize);

    Complex a;
    Complex b;

    for (auto x = m_Programm.begin(); x != m_Programm.end(); x++)
    {
        switch (x->op)
        {
        case OPUSH:
            stack.push((++x)->number);
            break;
        case OPUSHX:
            stack.push(input);
            break;
        case OADD:
            a = stack.top();
            stack.pop();
            b = stack.top();
            stack.pop();
            stack.push(a + b);
            break;
        case OSUB:
            a = stack.top();
            stack.pop();
            b = stack.top();
            stack.pop();
            stack.push(b - a);
            break;
        case OMUL:
            a = stack.top();
            stack.pop();
            b = stack.top();
            stack.pop();
            stack.push(a * b);
            break;
        case ODIV:
            a = stack.top();
            stack.pop();
            b = stack.top();
            stack.pop();
            stack.push(b / a);
            break;
        case OPOW:
            a = stack.top();
            stack.pop();
            b = stack.top();
            stack.pop();
            stack.push(pow(b, a));
            break;
        case OSIN:
            a = stack.top();
            stack.pop();
            stack.push(sin(a));
            break;
        case OASIN:
            a = stack.top();
            stack.pop();
            stack.push(asin(a));
            break;
        case OCOS:
            a = stack.top();
            stack.pop();
            stack.push(cos(a));
            break;
        case OACOS:
            a = stack.top();
            stack.pop();
            stack.push(acos(a));
            break;
        case OSQRT:
            a = stack.top();
            stack.pop();
            stack.push(sqrt(a));
            break;
        case OTAN:
            a = stack.top();
            stack.pop();
            stack.push(tan(a));
            break;
        case OATAN:
            a = stack.top();
            stack.pop();
            stack.push(atan(a));
            break;
        case OLOG:
            a = stack.top();
            stack.pop();
            stack.push(log(a));
            break;
        case OPLOG:
            a = stack.top();
            stack.pop();
            b = stack.top();
            stack.pop();
            stack.push(log(a) / log(b));
            break;
        case ONEG:
            a = stack.top();
            stack.pop();
            stack.push(-a);
            break;
        case OImag:
            a = stack.top();
            stack.pop();
            stack.push(a.imag());
            break;
        case OReal:
            a = stack.top();
            stack.pop();
            stack.push(a.real());
            break;
        case OABS:
            a = stack.top();
            stack.pop();
            stack.push(std::abs(a));
            break;
        }
    }
    return stack.top();
}

void Programm::Print()
{
    std::cout << "++++++++++++++++++" << std::endl;
    for (auto x = m_Programm.begin(); x != m_Programm.end(); x++)
    {
        if (x->op == OPUSH)
        {
            std::cout << "PUSH: " << (++x)->number << std::endl;
        }
        else if (x->op == OPUSHX)
        {
            std::cout << "PUSH: X" << std::endl;
        }
        else
        {
            std::cout << "OP: " << x->op << std::endl;
        }
    }
}