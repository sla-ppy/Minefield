#include "stdafx.h"

#include "Object.h"


bool Object::GetActive()
{
    return (m_bitFlags & OBF_ACTIVE) ? true : false;
}

void Object::SetActive(bool aActive)
{
    if(aActive)
    {
        m_bitFlags &= OBF_ACTIVE;
    }
    else
    {
        m_bitFlags &= ~OBF_ACTIVE;
    }
}

bool Object::GetInvulnerable()
{
    return (m_bitFlags & OBF_INVULNERABLE) ? true : false;
}

// FIXED: Object::SetInvulnerable(bool aInvulnerable) added, SetInvulnurable
void Object::SetInvulnerable(bool aInvulnerable)
{
    if (aInvulnerable)
    {
        m_bitFlags &= OBF_INVULNERABLE;
    }
    else
    {
        m_bitFlags &= ~OBF_INVULNERABLE;
    }
}