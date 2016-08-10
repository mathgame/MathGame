#include "iUniStream.h"
#include "oUniStream.h"

using namespace MGTools;

///////////////////////////////////////////////////////////////////////////
void iUniStream::PushSTLBack(unsigned char c)
{
    m_buff->push_back(c);
}

///////////////////////////////////////////////////////////////////////////
//void iUniStream::PopSTLFront(unsigned char& c)
//{
//    c = m_buff->front();
//    //m_buff->pop_front();
//}

///////////////////////////////////////////////////////////////////////////
void iUniStream::ClearSTLBuffer()
{
    m_buff->clear();
}

///////////////////////////////////////////////////////////////////////////
size_t iUniStream::GetSTLBufferSize() const
{
    return m_buff->size();
}