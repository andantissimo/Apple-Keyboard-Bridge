/**
 * Apple Keyboard Bridge https://github.com/andantissimo/Apple-Keyboard-Bridge
 */
#include "EditForm.h"

#include "acl.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::IO;
using namespace System::Diagnostics;
using namespace System::Runtime::InteropServices;

namespace akbcf
{
	ref class ScopedFlag sealed
	{
		Boolean^ _ref;
		Boolean  _val;
	public:
		explicit ScopedFlag(Boolean^ flag)
			: _ref(flag), _val(*flag)
		{
			_ref = true;
		}
		~ScopedFlag()
		{
			_ref = _val;
		}
	};

	static void Config_SetDefaults(Config^ config)
	{
		config->Signature = CONFIG_SIGNATURE;
		/* single action keys */
		config->Key.Power = CONFIG_INIT_KEY_POWER;
		config->Key.Eject = CONFIG_INIT_KEY_EJECT;
		config->Key.Alnum = CONFIG_INIT_KEY_ALNUM;
		config->Key.Kana  = CONFIG_INIT_KEY_KANA;
		/* Fn combination keys */
		config->Fn.F1     = CONFIG_INIT_FN_F1;
		config->Fn.F2     = CONFIG_INIT_FN_F2;
		config->Fn.F3     = CONFIG_INIT_FN_F3;
		config->Fn.F4     = CONFIG_INIT_FN_F4;
		config->Fn.F5     = CONFIG_INIT_FN_F5;
		config->Fn.F6     = CONFIG_INIT_FN_F6;
		config->Fn.F7     = CONFIG_INIT_FN_F7;
		config->Fn.F8     = CONFIG_INIT_FN_F8;
		config->Fn.F9     = CONFIG_INIT_FN_F9;
		config->Fn.F10    = CONFIG_INIT_FN_F10;
		config->Fn.F11    = CONFIG_INIT_FN_F11;
		config->Fn.F12    = CONFIG_INIT_FN_F12;
		config->Fn.Del    = CONFIG_INIT_FN_DEL;
		config->Fn.Up     = CONFIG_INIT_FN_UP;
		config->Fn.Down   = CONFIG_INIT_FN_DOWN;
		config->Fn.Left   = CONFIG_INIT_FN_LEFT;
		config->Fn.Right  = CONFIG_INIT_FN_RIGHT;
		config->Fn.Eject  = CONFIG_INIT_FN_EJECT;
		/* length of command */
		config->cbCmds = gcnew array<WORD>(CONFIG_NUM_CMDS);
	}

	void EditForm::LoadResources()
	{
		// Key code => Key name
		this->InputKeys = gcnew Dictionary<WORD, String^>();
		this->InputKeys[VK_F13              ] = L"F13";
		this->InputKeys[VK_F14              ] = L"F14";
		this->InputKeys[VK_F15              ] = L"F15";
		this->InputKeys[VK_F16              ] = L"F16";
		this->InputKeys[VK_F17              ] = L"F17";
		this->InputKeys[VK_F18              ] = L"F18";
		this->InputKeys[VK_F19              ] = L"F19";
		this->InputKeys[VK_F20              ] = L"F20";
		this->InputKeys[VK_F21              ] = L"F21";
		this->InputKeys[VK_F22              ] = L"F22";
		this->InputKeys[VK_F23              ] = L"F23";
		this->InputKeys[VK_F24              ] = L"F24";
		this->InputKeys[VK_INSERT           ] = L"Insert";
		this->InputKeys[VK_DELETE           ] = L"Delete";
		this->InputKeys[VK_HOME             ] = L"Home";
		this->InputKeys[VK_END              ] = L"End";
		this->InputKeys[VK_PRIOR            ] = L"Page Up";
		this->InputKeys[VK_NEXT             ] = L"Page Down";
		this->InputKeys[VK_KANJI            ] = L"半角/全角";
		this->InputKeys[VK_NONCONVERT       ] = L"無変換";
		this->InputKeys[VK_CONVERT          ] = L"変換";
		this->InputKeys[VK_SNAPSHOT         ] = L"Print Screen";
		this->InputKeys[VK_BROWSER_BACK     ] = L"戻る";
		this->InputKeys[VK_BROWSER_FORWARD  ] = L"進む";
		this->InputKeys[VK_BROWSER_REFRESH  ] = L"更新";
		this->InputKeys[VK_BROWSER_STOP     ] = L"中止";
		this->InputKeys[VK_BROWSER_SEARCH   ] = L"検索";
		this->InputKeys[VK_BROWSER_FAVORITES] = L"お気に入り";
		this->InputKeys[VK_BROWSER_HOME     ] = L"ホームページ";
		this->InputKeys[VK_VOLUME_MUTE      ] = L"ミュート";
		this->InputKeys[VK_VOLUME_DOWN      ] = L"音量を下げる";
		this->InputKeys[VK_VOLUME_UP        ] = L"音量を上げる";
		this->InputKeys[VK_MEDIA_PREV_TRACK ] = L"前のトラックへ";
		this->InputKeys[VK_MEDIA_NEXT_TRACK ] = L"次のトラックへ";
		this->InputKeys[VK_MEDIA_PLAY_PAUSE ] = L"再生/一時停止";
		this->InputKeys[VK_MEDIA_STOP       ] = L"停止";
		this->InputKeys[VK_LAUNCH_MAIL      ] = L"メール";

		// Special key code => Special action name
		this->Specials = gcnew Dictionary<WORD, String^>();
		this->Specials[FIRE_EJECT    ] = L"取り出し";
		this->Specials[FIRE_FLIP3D   ] = L"フリップ3D";
		this->Specials[FIRE_BRIGHT_DN] = L"暗く";
		this->Specials[FIRE_BRIGHT_UP] = L"明るく";
		this->Specials[FIRE_ALPHA_DN ] = L"透明に";
		this->Specials[FIRE_ALPHA_UP ] = L"不透明に";
	}

	void EditForm::LoadConfig(array<String^>^ args)
	{
		try {
			// decode configuration data transferred from non-elevated instance
			Queue<String^>^ queue = gcnew Queue<String^>(args);
			if (queue->Count > 0) {
				String^ data = queue->Dequeue();
				String^ cmds = String::Join(L" ", queue->ToArray());
				array<Byte>^ buf = Convert::FromBase64String(data);
				if (buf->Length != Marshal::SizeOf(this->ConfigData))
					throw 0;
				IntPtr ptr = Marshal::AllocCoTaskMem(buf->Length);
				try {
					Marshal::Copy(buf, 0, ptr, buf->Length);
					Marshal::PtrToStructure(ptr, this->ConfigData);
				} finally {
					Marshal::FreeCoTaskMem(ptr);
				}
				for (int i = 0; i < CONFIG_NUM_CMDS; i++) {
					if (WORD n = this->ConfigData->cbCmds[i]) {
						this->ConfigCmds[i] = cmds->Substring(0, n);
						cmds = cmds->Remove(0, n);
					}
				}
				return;
			}
		} catch (...) {
			// failed to decode arguments
		}
		try {
			// load the configuration file
			FileStream s(this->ConfigPath, FileMode::Open, FileAccess::Read);
			array<Byte>^ buf = gcnew array<Byte>(Marshal::SizeOf(this->ConfigData));
			if (s.Read(buf, 0, buf->Length) != buf->Length)
				throw 0;
			IntPtr ptr = Marshal::AllocCoTaskMem(buf->Length);
			try {
				Marshal::Copy(buf, 0, ptr, buf->Length);
				Marshal::PtrToStructure(ptr, this->ConfigData);
			} finally {
				Marshal::FreeCoTaskMem(ptr);
			}
		#ifndef UNICODE
			StreamReader r(%s);
		#else
			StreamReader r(%s, System::Text::Encoding::Unicode);
		#endif
			for (int i = 0; i < CONFIG_NUM_CMDS; i++) {
				if (this->ConfigData->cbCmds[i] > 0) {
					array<wchar_t>^ cmd = gcnew array<wchar_t>(this->ConfigData->cbCmds[i]);
					r.ReadBlock(cmd, 0, cmd->Length);
					this->ConfigCmds[i] = gcnew String(cmd);
				}
			}
		} catch (...) {
			// if failed to load configuration data, set default settings
			Config_SetDefaults(this->ConfigData);
		}
	}

	bool EditForm::SaveConfig()
	{
		// store the length of the commands
		for (int i = 0; i < CONFIG_NUM_CMDS; i++) {
			this->ConfigData->cbCmds[i] = WORD(this->ConfigCmds[i]->Length);
		}
		try {
			if (!Acl::Principal::Current->HasRight(this->ConfigPath, Acl::Principal::Rights::Write)) {
				if (Environment::OSVersion->Version->Major < 6) {
					// XP or earlier: modify ACL
					Acl::Principal::Current->AddRight(this->ConfigPath, Acl::Principal::Rights::Write);
				} else {
					// Vista or later: start an elevated instance with current configurations
					array<Byte>^ buf = gcnew array<Byte>(Marshal::SizeOf(this->ConfigData));
					IntPtr ptr = Marshal::AllocCoTaskMem(Marshal::SizeOf(this->ConfigData));
					try {
						Marshal::StructureToPtr(this->ConfigData, ptr, false);
						Marshal::Copy(ptr, buf, 0, buf->Length);
					} finally {
						Marshal::FreeCoTaskMem(ptr);
					}
					array<String^>^ args = gcnew array<String^>{
						Convert::ToBase64String(buf),
						String::Join(L"", this->ConfigCmds)
					};
					ProcessStartInfo info;
					info.Verb             = L"runas";
					info.FileName         = Application::ExecutablePath;
					info.WorkingDirectory = AppDomain::CurrentDomain->BaseDirectory;
					info.Arguments        = String::Join(L" ", args);
					Process::Start(%info);
					this->Close();
					return false;
				}
			}
			FileStream s(this->ConfigPath, FileMode::Create);
			array<Byte>^ buf = gcnew array<Byte>(Marshal::SizeOf(this->ConfigData));
			IntPtr ptr = Marshal::AllocCoTaskMem(Marshal::SizeOf(this->ConfigData));
			try {
				Marshal::StructureToPtr(this->ConfigData, ptr, false);
				Marshal::Copy(ptr, buf, 0, buf->Length);
			} finally {
				Marshal::FreeCoTaskMem(ptr);
			}
			s.Write(buf, 0, buf->Length);
		#ifndef UNICODE
			StreamWriter w(%s);
		#else
			StreamWriter w(%s, System::Text::Encoding::Unicode);
		#endif
			for (int i = 0; i < CONFIG_NUM_CMDS; i++) {
				w.Write(this->ConfigCmds[i]);
			}
		} catch (...) {
			return false;
		}
		return true;
	}

	void EditForm::ShowAction(WORD action)
	{
		ScopedFlag flag(this->IsSuspended);

		// Do Nothing
		this->DoNothing->Checked = (action == FIRE_NOTHING);

		// Input Key
		if (0 < action && action < 0x100) {
			this->InputKey->Checked = true;
			if (this->InputKeys->ContainsKey(action))
				this->InputKeyList->SelectedItem = this->InputKeys[action];
			else
				this->InputKeyList->SelectedIndex = -1;
		} else {
			this->InputKey->Checked = false;
			this->InputKeyList->SelectedIndex = -1;
		}

		// Special
		if (FIRE_CMD_0 + CONFIG_NUM_CMDS <= action && action < FIRE_NOTHING) {
			this->Special->Checked = true;
			if (this->Specials->ContainsKey(action))
				this->SpecialList->SelectedItem = this->Specials[action];
			else
				this->SpecialList->SelectedIndex = -1;
		} else {
			this->Special->Checked = false;
			this->SpecialList->SelectedIndex = -1;
		}

		// Execute
		if (FIRE_CMD_0 <= action && action < FIRE_CMD_0 + CONFIG_NUM_CMDS) {
			this->Exec->Checked = true;
			this->ExecCommand->Text = this->ConfigCmds[action - FIRE_CMD_0];
		} else {
			this->Exec->Checked = false;
			this->ExecCommand->Text = L"";
		}
	}

	WORD% EditForm::GetSelectedAction()
	{
		if (this->Tab->SelectedIndex == 0) {
		//	if (this->Power->Checked  ) return this->ConfigData->Key.Power;
			if (this->Eject->Checked  ) return this->ConfigData->Key.Eject;
			if (this->Alnum->Checked  ) return this->ConfigData->Key.Alnum;
			if (this->Kana->Checked   ) return this->ConfigData->Key.Kana;
		} else {
			if (this->FnF1->Checked   ) return this->ConfigData->Fn.F1;
			if (this->FnF2->Checked   ) return this->ConfigData->Fn.F2;
			if (this->FnF3->Checked   ) return this->ConfigData->Fn.F3;
			if (this->FnF4->Checked   ) return this->ConfigData->Fn.F4;
			if (this->FnF5->Checked   ) return this->ConfigData->Fn.F5;
			if (this->FnF6->Checked   ) return this->ConfigData->Fn.F6;
			if (this->FnF7->Checked   ) return this->ConfigData->Fn.F7;
			if (this->FnF8->Checked   ) return this->ConfigData->Fn.F8;
			if (this->FnF9->Checked   ) return this->ConfigData->Fn.F9;
			if (this->FnF10->Checked  ) return this->ConfigData->Fn.F10;
			if (this->FnF11->Checked  ) return this->ConfigData->Fn.F11;
			if (this->FnF12->Checked  ) return this->ConfigData->Fn.F12;
			if (this->FnDel->Checked  ) return this->ConfigData->Fn.Del;
			if (this->FnUp->Checked   ) return this->ConfigData->Fn.Up;
			if (this->FnDown->Checked ) return this->ConfigData->Fn.Down;
			if (this->FnLeft->Checked ) return this->ConfigData->Fn.Left;
			if (this->FnRight->Checked) return this->ConfigData->Fn.Right;
			if (this->FnEject->Checked) return this->ConfigData->Fn.Eject;
		}
		static WORD dummy;
		return dummy = 0;
	}

	void EditForm::ResetActionsExceptFor(System::Windows::Forms::Control^ control)
	{
		ScopedFlag flag(this->IsSuspended);

		if (control != this->InputKeyList)
			this->InputKeyList->SelectedIndex = -1;
		if (control != this->SpecialList)
			this->SpecialList->SelectedIndex = -1;
		if (control != this->ExecCommand) {
			this->ExecCommand->Text = L"";
			WORD% action = this->GetSelectedAction();
			if (FIRE_CMD_0 <= action && action < FIRE_CMD_0 + CONFIG_NUM_CMDS)
				this->ConfigCmds[action - FIRE_CMD_0] = L"";
		}
	}

	System::Void EditForm::EditForm_Load(System::Object^ /*sender*/, System::EventArgs^ /*e*/)
	{
		for each (KeyValuePair<WORD, String^>^ it in this->InputKeys)
			this->InputKeyList->Items->Add(it->Value);
		for each (KeyValuePair<WORD, String^>^ it in this->Specials)
			this->SpecialList->Items->Add(it->Value);
		if (!Acl::Principal::Current->HasRight(this->ConfigPath, Acl::Principal::Rights::Write)) {
			if (Environment::OSVersion->Version->Major >= 6) {
				// show the UAC shield icon in the OK button
				this->Apply->FlatStyle = FlatStyle::System;
				HandleRef hButton(this->Apply, this->Apply->Handle);
				::SendMessage(hButton.Handle, BCM_SETSHIELD, WPARAM::Zero, LPARAM(TRUE));
			}
		}
	}

	System::Void EditForm::Cancel_Click(System::Object^ /*sender*/, System::EventArgs^ /*e*/)
	{
		this->Close();
	}

	System::Void EditForm::Apply_Click(System::Object^ /*sender*/, System::EventArgs^ /*e*/)
	{
		if (SaveConfig()) {
			// notify the main application to reload configurations
			HWND hWnd = ::FindWindow(App::Class, App::Title);
			if (hWnd != HWND::Zero) {
				::PostMessage(hWnd, WM_APP_RELOAD, WPARAM::Zero, LPARAM::Zero);
			}
		}
		this->Close();
	}

	System::Void EditForm::ExecFind_Click(System::Object^ /*sender*/, System::EventArgs^ /*e*/)
	{
		if (File::Exists(this->ExecCommand->Text))
			this->FileDlg->FileName = this->ExecCommand->Text;
		else if (Directory::Exists(this->ExecCommand->Text))
			this->FileDlg->InitialDirectory = this->ExecCommand->Text;
		if (this->FileDlg->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			this->ExecCommand->Text = this->FileDlg->FileName;
		}
	}

	System::Void EditForm::SelectedChanged(System::Object^ /*sender*/, System::EventArgs^ /*e*/)
	{
		ShowAction(GetSelectedAction());
	}

	System::Void EditForm::DoNothing_CheckedChanged(System::Object^ /*sender*/, System::EventArgs^ /*e*/)
	{
		if (this->IsSuspended)
			return;

		if (this->DoNothing->Checked) {
			ResetActionsExceptFor(nullptr);
			GetSelectedAction() = FIRE_NOTHING;
		}
	}

	System::Void EditForm::InputKeyList_SelectedIndexChanged(System::Object^ /*sender*/, System::EventArgs^ /*e*/)
	{
		if (this->IsSuspended)
			return;

		for each (KeyValuePair<WORD, String^>^ it in this->InputKeys) {
			if (this->InputKeyList->Text == it->Value) {
				this->InputKey->Checked = true;
				ResetActionsExceptFor(this->InputKeyList);
				GetSelectedAction() = it->Key;
				break;
			}
		}
	}

	System::Void EditForm::SpecialList_SelectedIndexChanged(System::Object^ /*sender*/, System::EventArgs^ /*e*/)
	{
		if (this->IsSuspended)
			return;

		for each (KeyValuePair<WORD, String^>^ it in this->Specials) {
			if (this->SpecialList->Text == it->Value) {
				this->Special->Checked = true;
				ResetActionsExceptFor(this->SpecialList);
				GetSelectedAction() = it->Key;
				break;
			}
		}
	}

	System::Void EditForm::ExecCommand_TextChanged(System::Object^ /*sender*/, System::EventArgs^ /*e*/)
	{
		if (this->IsSuspended)
			return;

		WORD% action = GetSelectedAction();
		if (action == 0)
			return;
		int index = -1;
		if (FIRE_CMD_0 <= action && action < FIRE_CMD_0 + CONFIG_NUM_CMDS)
			index = action - FIRE_CMD_0;
		else for (int i = 0; i < CONFIG_NUM_CMDS; i++) {
			if (this->ConfigCmds[i]->Length == 0) {
				index = i;
				break;
			}
		}
		if (index >= 0 && this->ExecCommand->Text->Length > 0) {
			this->ConfigCmds[index] = this->ExecCommand->Text;
			this->Exec->Checked = true;
			ResetActionsExceptFor(this->ExecCommand);
			action = WORD(FIRE_CMD_0 + index);
		} else if (this->Exec->Checked) {
			this->DoNothing->Checked = true;
			ResetActionsExceptFor(nullptr);
			action = FIRE_NOTHING;
		} else {
			this->ExecCommand->Text = L"";
		}
	}
}
