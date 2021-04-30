#include "pch.h"
#include "PrincipalMenu.h"
using namespace ZionEscape;
int main()
{
    Application::EnableVisualStyles();
    Application::Run(gcnew PrincipalMenu());
    return 0;
}
