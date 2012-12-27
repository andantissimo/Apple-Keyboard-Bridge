/**
 *  Apple Keyboard Bridge - Configuration
 *  
 *  @author  MALU
 *  @version $Id: akbcf.cpp 64 2012-09-24 09:26:38Z malu $
 */

#include "EditForm.h"

using namespace System;
using namespace System::Threading;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args)
{
	// start mutex by current directory
	String^ name = AppDomain::CurrentDomain->BaseDirectory->Replace('\\', '/');
	Mutex mutex(false, name);
	if (args->Length > 0) {
		// elevating: wait until non-elevated instance exits
		if (!mutex.WaitOne(5 * 1000, false))
			return 0;
	} else {
		// normal: exit right now
		if (!mutex.WaitOne(0, false))
			return 0;
	}
	
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 
	Application::Run(gcnew akbcf::EditForm(args));
	return 0;
}
