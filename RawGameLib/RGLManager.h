#ifndef __RGL_MANAGER_H__
#define __RGL_MANAGER_H__

#include "Common.h"

namespace RGL
{

    class RGLManager
    {
    public:
        RGLManager();
        ~RGLManager();

        ReturnValue Initialize();
        ReturnValue Finish();

        bool IsInitialized();

    private:
        bool _isInitialized;

    };

}

#endif
