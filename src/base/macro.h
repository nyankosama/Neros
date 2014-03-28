#ifndef BASE_MACRO_H_
#define BASE_MACRO_H_ 

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
TypeName(const TypeName&); \
void operator=(const TypeName&)

#define DISALLOW_ASSIGN(TypeName) \
    void operator=(const TypeName&)

#define DISALLOW_POST_OPERATOR(TypeName) \
    TypeName operator ++ (int); \
    TypeName operator -- (int);

#endif
