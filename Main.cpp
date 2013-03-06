#include "CSLuint.hpp"
#include "USlint.hpp"

int main(int arg_c,char*argv[])
{
    uslint::USLint A("100030002");
    uslint::USLint B("900060000");
    uslint::USLint C(A.Mul(B));


    std::cout<<A<<std::endl;
    std::cout<<B<<std::endl;
    std::cout<<C<<std::endl;
}
