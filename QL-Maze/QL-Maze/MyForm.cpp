#include "MyForm.h"
#include <time.h>

using namespace System;
using namespace System::Windows::Forms;

[STAThread]

void main()
{
    srand((unsigned)time(NULL));

    Application::EnableVisualStyles();

    Application::SetCompatibleTextRenderingDefault(false);

    QLMaze::MyForm form;

    Application::Run(% form);
}