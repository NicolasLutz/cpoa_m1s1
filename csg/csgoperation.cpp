#include "csgoperation.h"

CsgOperation::CsgOperation() : CsgNode()
{}

//----------------------------------------------------------------------------

CsgOperation::CsgOperation(const CsgOperation &other) : CsgNode(other)
{}

//----------------------------------------------------------------------------

CsgOperation::~CsgOperation()
{

}

//----------------------------------------------------------------------------

csgOpType_t CsgOperation::Type()
{
    return m_type;
}
