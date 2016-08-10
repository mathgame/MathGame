#undef COMPONENT_FACTORY_NAMESPACE
// Set your factory namespace here:
#define COMPONENT_FACTORY_NAMESPACE BaseComponents
//////////////////////////////////////////////////////////////////////

#undef MACRO_XSTR
#undef MACRO_STR
#undef FACTORY_NAMESPACE_STRING
//
#define MACRO_XSTR(x) #x
#define MACRO_STR(x) MACRO_XSTR(x)
#define FACTORY_NAMESPACE_STRING MACRO_STR(COMPONENT_FACTORY_NAMESPACE)
