#ifndef DEBUGTOOLS_H
#define DEBUGTOOLS_H
#include <iostream>
#include <stdlib.h>

#ifdef MG_DEBUG
#define MG_MSG (std::cout)
#define ASSERT(MSG) {MG_MSG << "Assert at : " << __FILE__ << "\nin function : " << __FUNCTION__ << "\nwith msg : " << (MSG) << std::endl; exit(1);}
#else
#define ASSERT(MSG) {}
#define MG_MSG
#endif

#endif // DEBUGTOOLS_H
