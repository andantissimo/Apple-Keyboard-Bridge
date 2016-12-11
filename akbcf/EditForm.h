/**
 * Apple Keyboard Bridge https://github.com/andantissimo/Apple-Keyboard-Bridge
 */
#pragma once

#include "../common/akb.h"

namespace akbcf
{
	/// <summary>
	/// Apple Keyboard Bridge - Configuration Editor
	/// </summary>
	public ref class EditForm : public System::Windows::Forms::Form
	{
	public:
		EditForm(array<System::String^>^ args)
		{
			InitializeComponent();
			
			LoadResources();
			this->ConfigPath = System::IO::Path::Combine(System::AppDomain::CurrentDomain->BaseDirectory, L"akb.cf");
			this->ConfigData = gcnew Config();
			this->ConfigCmds = gcnew array<System::String^>(CONFIG_NUM_CMDS);
			for (int i = 0; i < this->ConfigCmds->Length; i++)
				this->ConfigCmds[i] = L"";
			LoadConfig(args);
		}

	protected:
		~EditForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::Windows::Forms::TabControl^ Tab;
		System::Windows::Forms::TabPage^ Singles;
		System::Windows::Forms::TabPage^ Combinations;

		System::Windows::Forms::RadioButton^ F1;
		System::Windows::Forms::RadioButton^ F2;
		System::Windows::Forms::RadioButton^ F3;
		System::Windows::Forms::RadioButton^ F4;
		System::Windows::Forms::RadioButton^ F5;
		System::Windows::Forms::RadioButton^ F6;
		System::Windows::Forms::RadioButton^ F7;
		System::Windows::Forms::RadioButton^ F8;
		System::Windows::Forms::RadioButton^ F9;
		System::Windows::Forms::RadioButton^ F10;
		System::Windows::Forms::RadioButton^ F11;
		System::Windows::Forms::RadioButton^ F12;
		System::Windows::Forms::RadioButton^ Eject;
		System::Windows::Forms::RadioButton^ Del;
		System::Windows::Forms::RadioButton^ Alnum;
		System::Windows::Forms::RadioButton^ Space;
		System::Windows::Forms::RadioButton^ Kana;
		System::Windows::Forms::RadioButton^ Up;
		System::Windows::Forms::RadioButton^ Left;
		System::Windows::Forms::RadioButton^ Down;
		System::Windows::Forms::RadioButton^ Right;

		System::Windows::Forms::RadioButton^ FnF1;
		System::Windows::Forms::RadioButton^ FnF2;
		System::Windows::Forms::RadioButton^ FnF3;
		System::Windows::Forms::RadioButton^ FnF4;
		System::Windows::Forms::RadioButton^ FnF6;
		System::Windows::Forms::RadioButton^ FnF7;
		System::Windows::Forms::RadioButton^ FnF8;
		System::Windows::Forms::RadioButton^ FnF5;
		System::Windows::Forms::RadioButton^ FnF9;
		System::Windows::Forms::RadioButton^ FnF10;
		System::Windows::Forms::RadioButton^ FnF11;
		System::Windows::Forms::RadioButton^ FnF12;
		System::Windows::Forms::RadioButton^ FnEject;
		System::Windows::Forms::RadioButton^ FnDel;
		System::Windows::Forms::RadioButton^ FnAlnum;
		System::Windows::Forms::RadioButton^ FnSpace;
		System::Windows::Forms::RadioButton^ FnKana;
		System::Windows::Forms::RadioButton^ FnUp;
		System::Windows::Forms::RadioButton^ FnLeft;
		System::Windows::Forms::RadioButton^ FnDown;
		System::Windows::Forms::RadioButton^ FnRight;

		System::Windows::Forms::GroupBox^ Action;
		System::Windows::Forms::RadioButton^ DoNothing;
		System::Windows::Forms::RadioButton^ InputKey;
		System::Windows::Forms::ComboBox^ InputKeyList;
		System::Windows::Forms::RadioButton^ Special;
		System::Windows::Forms::ComboBox^ SpecialList;
		System::Windows::Forms::RadioButton^ Exec;
		System::Windows::Forms::TextBox^ ExecCommand;
		System::Windows::Forms::Button^ ExecFind;

		System::Windows::Forms::Button^ Cancel;
		System::Windows::Forms::Button^ Apply;

		System::Windows::Forms::OpenFileDialog^ FileDlg;

	private:
		/// <summary>
		/// 必要なデザイナ変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナ サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディタで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->Tab = (gcnew System::Windows::Forms::TabControl());
			this->Singles = (gcnew System::Windows::Forms::TabPage());
			this->F1 = (gcnew System::Windows::Forms::RadioButton());
			this->F2 = (gcnew System::Windows::Forms::RadioButton());
			this->F3 = (gcnew System::Windows::Forms::RadioButton());
			this->F4 = (gcnew System::Windows::Forms::RadioButton());
			this->F5 = (gcnew System::Windows::Forms::RadioButton());
			this->F6 = (gcnew System::Windows::Forms::RadioButton());
			this->F7 = (gcnew System::Windows::Forms::RadioButton());
			this->F8 = (gcnew System::Windows::Forms::RadioButton());
			this->F9 = (gcnew System::Windows::Forms::RadioButton());
			this->F10 = (gcnew System::Windows::Forms::RadioButton());
			this->F11 = (gcnew System::Windows::Forms::RadioButton());
			this->F12 = (gcnew System::Windows::Forms::RadioButton());
			this->Eject = (gcnew System::Windows::Forms::RadioButton());
			this->Del = (gcnew System::Windows::Forms::RadioButton());
			this->Alnum = (gcnew System::Windows::Forms::RadioButton());
			this->Space = (gcnew System::Windows::Forms::RadioButton());
			this->Kana = (gcnew System::Windows::Forms::RadioButton());
			this->Up = (gcnew System::Windows::Forms::RadioButton());
			this->Left = (gcnew System::Windows::Forms::RadioButton());
			this->Down = (gcnew System::Windows::Forms::RadioButton());
			this->Right = (gcnew System::Windows::Forms::RadioButton());
			this->Combinations = (gcnew System::Windows::Forms::TabPage());
			this->FnF1 = (gcnew System::Windows::Forms::RadioButton());
			this->FnF2 = (gcnew System::Windows::Forms::RadioButton());
			this->FnF3 = (gcnew System::Windows::Forms::RadioButton());
			this->FnF4 = (gcnew System::Windows::Forms::RadioButton());
			this->FnF5 = (gcnew System::Windows::Forms::RadioButton());
			this->FnF6 = (gcnew System::Windows::Forms::RadioButton());
			this->FnF7 = (gcnew System::Windows::Forms::RadioButton());
			this->FnF8 = (gcnew System::Windows::Forms::RadioButton());
			this->FnF9 = (gcnew System::Windows::Forms::RadioButton());
			this->FnF10 = (gcnew System::Windows::Forms::RadioButton());
			this->FnF11 = (gcnew System::Windows::Forms::RadioButton());
			this->FnF12 = (gcnew System::Windows::Forms::RadioButton());
			this->FnEject = (gcnew System::Windows::Forms::RadioButton());
			this->FnDel = (gcnew System::Windows::Forms::RadioButton());
			this->FnAlnum = (gcnew System::Windows::Forms::RadioButton());
			this->FnSpace = (gcnew System::Windows::Forms::RadioButton());
			this->FnKana = (gcnew System::Windows::Forms::RadioButton());
			this->FnUp = (gcnew System::Windows::Forms::RadioButton());
			this->FnLeft = (gcnew System::Windows::Forms::RadioButton());
			this->FnDown = (gcnew System::Windows::Forms::RadioButton());
			this->FnRight = (gcnew System::Windows::Forms::RadioButton());
			this->Action = (gcnew System::Windows::Forms::GroupBox());
			this->DoNothing = (gcnew System::Windows::Forms::RadioButton());
			this->InputKey = (gcnew System::Windows::Forms::RadioButton());
			this->InputKeyList = (gcnew System::Windows::Forms::ComboBox());
			this->Special = (gcnew System::Windows::Forms::RadioButton());
			this->SpecialList = (gcnew System::Windows::Forms::ComboBox());
			this->Exec = (gcnew System::Windows::Forms::RadioButton());
			this->ExecCommand = (gcnew System::Windows::Forms::TextBox());
			this->ExecFind = (gcnew System::Windows::Forms::Button());
			this->Cancel = (gcnew System::Windows::Forms::Button());
			this->Apply = (gcnew System::Windows::Forms::Button());
			this->FileDlg = (gcnew System::Windows::Forms::OpenFileDialog());
			this->Tab->SuspendLayout();
			this->Singles->SuspendLayout();
			this->Combinations->SuspendLayout();
			this->Action->SuspendLayout();
			this->SuspendLayout();
			// 
			// Tab
			// 
			this->Tab->Appearance = System::Windows::Forms::TabAppearance::FlatButtons;
			this->Tab->Controls->Add(this->Singles);
			this->Tab->Controls->Add(this->Combinations);
			this->Tab->Dock = System::Windows::Forms::DockStyle::Top;
			this->Tab->Location = System::Drawing::Point(0, 0);
			this->Tab->Margin = System::Windows::Forms::Padding(0);
			this->Tab->Name = L"Tab";
			this->Tab->SelectedIndex = 0;
			this->Tab->Size = System::Drawing::Size(654, 145);
			this->Tab->TabIndex = 0;
			this->Tab->SelectedIndexChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// Singles
			// 
			this->Singles->Controls->Add(this->F1);
			this->Singles->Controls->Add(this->F2);
			this->Singles->Controls->Add(this->F3);
			this->Singles->Controls->Add(this->F4);
			this->Singles->Controls->Add(this->F5);
			this->Singles->Controls->Add(this->F6);
			this->Singles->Controls->Add(this->F7);
			this->Singles->Controls->Add(this->F8);
			this->Singles->Controls->Add(this->F9);
			this->Singles->Controls->Add(this->F10);
			this->Singles->Controls->Add(this->F11);
			this->Singles->Controls->Add(this->F12);
			this->Singles->Controls->Add(this->Eject);
			this->Singles->Controls->Add(this->Del);
			this->Singles->Controls->Add(this->Alnum);
			this->Singles->Controls->Add(this->Space);
			this->Singles->Controls->Add(this->Kana);
			this->Singles->Controls->Add(this->Up);
			this->Singles->Controls->Add(this->Left);
			this->Singles->Controls->Add(this->Down);
			this->Singles->Controls->Add(this->Right);
			this->Singles->Location = System::Drawing::Point(4, 24);
			this->Singles->Margin = System::Windows::Forms::Padding(0);
			this->Singles->Name = L"Singles";
			this->Singles->Padding = System::Windows::Forms::Padding(3);
			this->Singles->Size = System::Drawing::Size(646, 117);
			this->Singles->TabIndex = 0;
			this->Singles->Text = L"単独";
			this->Singles->UseVisualStyleBackColor = true;
			// 
			// F1
			// 
			this->F1->Appearance = System::Windows::Forms::Appearance::Button;
			this->F1->Enabled = false;
			this->F1->Location = System::Drawing::Point(0, 0);
			this->F1->Margin = System::Windows::Forms::Padding(0);
			this->F1->Name = L"F1";
			this->F1->Size = System::Drawing::Size(45, 25);
			this->F1->TabIndex = 1;
			this->F1->Text = L"F1";
			this->F1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->F1->UseVisualStyleBackColor = true;
			this->F1->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// F2
			// 
			this->F2->Appearance = System::Windows::Forms::Appearance::Button;
			this->F2->Enabled = false;
			this->F2->Location = System::Drawing::Point(50, 0);
			this->F2->Margin = System::Windows::Forms::Padding(0);
			this->F2->Name = L"F2";
			this->F2->Size = System::Drawing::Size(45, 25);
			this->F2->TabIndex = 2;
			this->F2->Text = L"F2";
			this->F2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->F2->UseVisualStyleBackColor = true;
			this->F2->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// F3
			// 
			this->F3->Appearance = System::Windows::Forms::Appearance::Button;
			this->F3->Enabled = false;
			this->F3->Location = System::Drawing::Point(100, 0);
			this->F3->Margin = System::Windows::Forms::Padding(0);
			this->F3->Name = L"F3";
			this->F3->Size = System::Drawing::Size(45, 25);
			this->F3->TabIndex = 3;
			this->F3->Text = L"F3";
			this->F3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->F3->UseVisualStyleBackColor = true;
			this->F3->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// F4
			// 
			this->F4->Appearance = System::Windows::Forms::Appearance::Button;
			this->F4->Enabled = false;
			this->F4->Location = System::Drawing::Point(150, 0);
			this->F4->Margin = System::Windows::Forms::Padding(0);
			this->F4->Name = L"F4";
			this->F4->Size = System::Drawing::Size(45, 25);
			this->F4->TabIndex = 4;
			this->F4->Text = L"F4";
			this->F4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->F4->UseVisualStyleBackColor = true;
			this->F4->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// F5
			// 
			this->F5->Appearance = System::Windows::Forms::Appearance::Button;
			this->F5->Enabled = false;
			this->F5->Location = System::Drawing::Point(200, 0);
			this->F5->Margin = System::Windows::Forms::Padding(0);
			this->F5->Name = L"F5";
			this->F5->Size = System::Drawing::Size(45, 25);
			this->F5->TabIndex = 5;
			this->F5->Text = L"F5";
			this->F5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->F5->UseVisualStyleBackColor = true;
			this->F5->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// F6
			// 
			this->F6->Appearance = System::Windows::Forms::Appearance::Button;
			this->F6->Enabled = false;
			this->F6->Location = System::Drawing::Point(250, 0);
			this->F6->Margin = System::Windows::Forms::Padding(0);
			this->F6->Name = L"F6";
			this->F6->Size = System::Drawing::Size(45, 25);
			this->F6->TabIndex = 6;
			this->F6->Text = L"F6";
			this->F6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->F6->UseVisualStyleBackColor = true;
			this->F6->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// F7
			// 
			this->F7->Appearance = System::Windows::Forms::Appearance::Button;
			this->F7->Enabled = false;
			this->F7->Location = System::Drawing::Point(300, 0);
			this->F7->Margin = System::Windows::Forms::Padding(0);
			this->F7->Name = L"F7";
			this->F7->Size = System::Drawing::Size(45, 25);
			this->F7->TabIndex = 7;
			this->F7->Text = L"F7";
			this->F7->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->F7->UseVisualStyleBackColor = true;
			this->F7->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// F8
			// 
			this->F8->Appearance = System::Windows::Forms::Appearance::Button;
			this->F8->Enabled = false;
			this->F8->Location = System::Drawing::Point(350, 0);
			this->F8->Margin = System::Windows::Forms::Padding(0);
			this->F8->Name = L"F8";
			this->F8->Size = System::Drawing::Size(45, 25);
			this->F8->TabIndex = 8;
			this->F8->Text = L"F8";
			this->F8->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->F8->UseVisualStyleBackColor = true;
			this->F8->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// F9
			// 
			this->F9->Appearance = System::Windows::Forms::Appearance::Button;
			this->F9->Enabled = false;
			this->F9->Location = System::Drawing::Point(400, 0);
			this->F9->Margin = System::Windows::Forms::Padding(0);
			this->F9->Name = L"F9";
			this->F9->Size = System::Drawing::Size(45, 25);
			this->F9->TabIndex = 9;
			this->F9->Text = L"F9";
			this->F9->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->F9->UseVisualStyleBackColor = true;
			this->F9->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// F10
			// 
			this->F10->Appearance = System::Windows::Forms::Appearance::Button;
			this->F10->Enabled = false;
			this->F10->Location = System::Drawing::Point(450, 0);
			this->F10->Margin = System::Windows::Forms::Padding(0);
			this->F10->Name = L"F10";
			this->F10->Size = System::Drawing::Size(45, 25);
			this->F10->TabIndex = 10;
			this->F10->Text = L"F10";
			this->F10->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->F10->UseVisualStyleBackColor = true;
			this->F10->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// F11
			// 
			this->F11->Appearance = System::Windows::Forms::Appearance::Button;
			this->F11->Enabled = false;
			this->F11->Location = System::Drawing::Point(500, 0);
			this->F11->Margin = System::Windows::Forms::Padding(0);
			this->F11->Name = L"F11";
			this->F11->Size = System::Drawing::Size(45, 25);
			this->F11->TabIndex = 11;
			this->F11->Text = L"F11";
			this->F11->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->F11->UseVisualStyleBackColor = true;
			this->F11->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// F12
			// 
			this->F12->Appearance = System::Windows::Forms::Appearance::Button;
			this->F12->Enabled = false;
			this->F12->Location = System::Drawing::Point(550, 0);
			this->F12->Margin = System::Windows::Forms::Padding(0);
			this->F12->Name = L"F12";
			this->F12->Size = System::Drawing::Size(45, 25);
			this->F12->TabIndex = 12;
			this->F12->Text = L"F12";
			this->F12->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->F12->UseVisualStyleBackColor = true;
			this->F12->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// Eject
			// 
			this->Eject->Appearance = System::Windows::Forms::Appearance::Button;
			this->Eject->Location = System::Drawing::Point(600, 0);
			this->Eject->Margin = System::Windows::Forms::Padding(0);
			this->Eject->Name = L"Eject";
			this->Eject->Size = System::Drawing::Size(45, 25);
			this->Eject->TabIndex = 13;
			this->Eject->Text = L"▲";
			this->Eject->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->Eject->UseVisualStyleBackColor = true;
			this->Eject->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// Del
			// 
			this->Del->Appearance = System::Windows::Forms::Appearance::Button;
			this->Del->Enabled = false;
			this->Del->Location = System::Drawing::Point(600, 30);
			this->Del->Margin = System::Windows::Forms::Padding(0);
			this->Del->Name = L"Del";
			this->Del->Size = System::Drawing::Size(45, 25);
			this->Del->TabIndex = 14;
			this->Del->Text = L"delete";
			this->Del->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->Del->UseVisualStyleBackColor = true;
			this->Del->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// Alnum
			// 
			this->Alnum->Appearance = System::Windows::Forms::Appearance::Button;
			this->Alnum->Location = System::Drawing::Point(150, 90);
			this->Alnum->Margin = System::Windows::Forms::Padding(0);
			this->Alnum->Name = L"Alnum";
			this->Alnum->Size = System::Drawing::Size(45, 25);
			this->Alnum->TabIndex = 15;
			this->Alnum->Text = L"英数";
			this->Alnum->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->Alnum->UseVisualStyleBackColor = true;
			this->Alnum->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// Space
			// 
			this->Space->Appearance = System::Windows::Forms::Appearance::Button;
			this->Space->Enabled = false;
			this->Space->Location = System::Drawing::Point(200, 90);
			this->Space->Margin = System::Windows::Forms::Padding(0);
			this->Space->Name = L"Space";
			this->Space->Size = System::Drawing::Size(145, 25);
			this->Space->TabIndex = 16;
			this->Space->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->Space->UseVisualStyleBackColor = true;
			this->Space->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// Kana
			// 
			this->Kana->Appearance = System::Windows::Forms::Appearance::Button;
			this->Kana->Location = System::Drawing::Point(350, 90);
			this->Kana->Margin = System::Windows::Forms::Padding(0);
			this->Kana->Name = L"Kana";
			this->Kana->Size = System::Drawing::Size(45, 25);
			this->Kana->TabIndex = 17;
			this->Kana->Text = L"かな";
			this->Kana->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->Kana->UseVisualStyleBackColor = true;
			this->Kana->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// Up
			// 
			this->Up->Appearance = System::Windows::Forms::Appearance::Button;
			this->Up->Enabled = false;
			this->Up->Location = System::Drawing::Point(550, 60);
			this->Up->Margin = System::Windows::Forms::Padding(0);
			this->Up->Name = L"Up";
			this->Up->Size = System::Drawing::Size(45, 25);
			this->Up->TabIndex = 18;
			this->Up->Text = L"↑";
			this->Up->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->Up->UseVisualStyleBackColor = true;
			this->Up->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// Left
			// 
			this->Left->Appearance = System::Windows::Forms::Appearance::Button;
			this->Left->Enabled = false;
			this->Left->Location = System::Drawing::Point(500, 90);
			this->Left->Margin = System::Windows::Forms::Padding(0);
			this->Left->Name = L"Left";
			this->Left->Size = System::Drawing::Size(45, 25);
			this->Left->TabIndex = 19;
			this->Left->Text = L"←";
			this->Left->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->Left->UseVisualStyleBackColor = true;
			this->Left->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// Down
			// 
			this->Down->Appearance = System::Windows::Forms::Appearance::Button;
			this->Down->Enabled = false;
			this->Down->Location = System::Drawing::Point(550, 90);
			this->Down->Margin = System::Windows::Forms::Padding(0);
			this->Down->Name = L"Down";
			this->Down->Size = System::Drawing::Size(45, 25);
			this->Down->TabIndex = 20;
			this->Down->Text = L"↓";
			this->Down->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->Down->UseVisualStyleBackColor = true;
			this->Down->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// Right
			// 
			this->Right->Appearance = System::Windows::Forms::Appearance::Button;
			this->Right->Enabled = false;
			this->Right->Location = System::Drawing::Point(600, 90);
			this->Right->Margin = System::Windows::Forms::Padding(0);
			this->Right->Name = L"Right";
			this->Right->Size = System::Drawing::Size(45, 25);
			this->Right->TabIndex = 21;
			this->Right->Text = L"→";
			this->Right->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->Right->UseVisualStyleBackColor = true;
			this->Right->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// Combinations
			// 
			this->Combinations->Controls->Add(this->FnF1);
			this->Combinations->Controls->Add(this->FnF2);
			this->Combinations->Controls->Add(this->FnF3);
			this->Combinations->Controls->Add(this->FnF4);
			this->Combinations->Controls->Add(this->FnF5);
			this->Combinations->Controls->Add(this->FnF6);
			this->Combinations->Controls->Add(this->FnF7);
			this->Combinations->Controls->Add(this->FnF8);
			this->Combinations->Controls->Add(this->FnF9);
			this->Combinations->Controls->Add(this->FnF10);
			this->Combinations->Controls->Add(this->FnF11);
			this->Combinations->Controls->Add(this->FnF12);
			this->Combinations->Controls->Add(this->FnEject);
			this->Combinations->Controls->Add(this->FnDel);
			this->Combinations->Controls->Add(this->FnAlnum);
			this->Combinations->Controls->Add(this->FnSpace);
			this->Combinations->Controls->Add(this->FnKana);
			this->Combinations->Controls->Add(this->FnUp);
			this->Combinations->Controls->Add(this->FnLeft);
			this->Combinations->Controls->Add(this->FnDown);
			this->Combinations->Controls->Add(this->FnRight);
			this->Combinations->Location = System::Drawing::Point(4, 24);
			this->Combinations->Name = L"Combinations";
			this->Combinations->Padding = System::Windows::Forms::Padding(3);
			this->Combinations->Size = System::Drawing::Size(646, 117);
			this->Combinations->TabIndex = 1;
			this->Combinations->Text = L"Fn +";
			this->Combinations->UseVisualStyleBackColor = true;
			// 
			// FnF1
			// 
			this->FnF1->Appearance = System::Windows::Forms::Appearance::Button;
			this->FnF1->Location = System::Drawing::Point(0, 0);
			this->FnF1->Margin = System::Windows::Forms::Padding(0);
			this->FnF1->Name = L"FnF1";
			this->FnF1->Size = System::Drawing::Size(45, 25);
			this->FnF1->TabIndex = 1;
			this->FnF1->Text = L"F1";
			this->FnF1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->FnF1->UseVisualStyleBackColor = true;
			this->FnF1->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// FnF2
			// 
			this->FnF2->Appearance = System::Windows::Forms::Appearance::Button;
			this->FnF2->Location = System::Drawing::Point(50, 0);
			this->FnF2->Margin = System::Windows::Forms::Padding(0);
			this->FnF2->Name = L"FnF2";
			this->FnF2->Size = System::Drawing::Size(45, 25);
			this->FnF2->TabIndex = 2;
			this->FnF2->Text = L"F2";
			this->FnF2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->FnF2->UseVisualStyleBackColor = true;
			this->FnF2->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// FnF3
			// 
			this->FnF3->Appearance = System::Windows::Forms::Appearance::Button;
			this->FnF3->Location = System::Drawing::Point(100, 0);
			this->FnF3->Margin = System::Windows::Forms::Padding(0);
			this->FnF3->Name = L"FnF3";
			this->FnF3->Size = System::Drawing::Size(45, 25);
			this->FnF3->TabIndex = 3;
			this->FnF3->Text = L"F3";
			this->FnF3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->FnF3->UseVisualStyleBackColor = true;
			this->FnF3->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// FnF4
			// 
			this->FnF4->Appearance = System::Windows::Forms::Appearance::Button;
			this->FnF4->Location = System::Drawing::Point(150, 0);
			this->FnF4->Margin = System::Windows::Forms::Padding(0);
			this->FnF4->Name = L"FnF4";
			this->FnF4->Size = System::Drawing::Size(45, 25);
			this->FnF4->TabIndex = 4;
			this->FnF4->Text = L"F4";
			this->FnF4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->FnF4->UseVisualStyleBackColor = true;
			this->FnF4->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// FnF5
			// 
			this->FnF5->Appearance = System::Windows::Forms::Appearance::Button;
			this->FnF5->Location = System::Drawing::Point(200, 0);
			this->FnF5->Margin = System::Windows::Forms::Padding(0);
			this->FnF5->Name = L"FnF5";
			this->FnF5->Size = System::Drawing::Size(45, 25);
			this->FnF5->TabIndex = 5;
			this->FnF5->Text = L"F5";
			this->FnF5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->FnF5->UseVisualStyleBackColor = true;
			this->FnF5->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// FnF6
			// 
			this->FnF6->Appearance = System::Windows::Forms::Appearance::Button;
			this->FnF6->Location = System::Drawing::Point(250, 0);
			this->FnF6->Margin = System::Windows::Forms::Padding(0);
			this->FnF6->Name = L"FnF6";
			this->FnF6->Size = System::Drawing::Size(45, 25);
			this->FnF6->TabIndex = 6;
			this->FnF6->Text = L"F6";
			this->FnF6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->FnF6->UseVisualStyleBackColor = true;
			this->FnF6->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// FnF7
			// 
			this->FnF7->Appearance = System::Windows::Forms::Appearance::Button;
			this->FnF7->Location = System::Drawing::Point(300, 0);
			this->FnF7->Margin = System::Windows::Forms::Padding(0);
			this->FnF7->Name = L"FnF7";
			this->FnF7->Size = System::Drawing::Size(45, 25);
			this->FnF7->TabIndex = 7;
			this->FnF7->Text = L"F7";
			this->FnF7->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->FnF7->UseVisualStyleBackColor = true;
			this->FnF7->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// FnF8
			// 
			this->FnF8->Appearance = System::Windows::Forms::Appearance::Button;
			this->FnF8->Location = System::Drawing::Point(350, 0);
			this->FnF8->Margin = System::Windows::Forms::Padding(0);
			this->FnF8->Name = L"FnF8";
			this->FnF8->Size = System::Drawing::Size(45, 25);
			this->FnF8->TabIndex = 8;
			this->FnF8->Text = L"F8";
			this->FnF8->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->FnF8->UseVisualStyleBackColor = true;
			this->FnF8->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// FnF9
			// 
			this->FnF9->Appearance = System::Windows::Forms::Appearance::Button;
			this->FnF9->Location = System::Drawing::Point(400, 0);
			this->FnF9->Margin = System::Windows::Forms::Padding(0);
			this->FnF9->Name = L"FnF9";
			this->FnF9->Size = System::Drawing::Size(45, 25);
			this->FnF9->TabIndex = 9;
			this->FnF9->Text = L"F9";
			this->FnF9->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->FnF9->UseVisualStyleBackColor = true;
			this->FnF9->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// FnF10
			// 
			this->FnF10->Appearance = System::Windows::Forms::Appearance::Button;
			this->FnF10->Location = System::Drawing::Point(450, 0);
			this->FnF10->Margin = System::Windows::Forms::Padding(0);
			this->FnF10->Name = L"FnF10";
			this->FnF10->Size = System::Drawing::Size(45, 25);
			this->FnF10->TabIndex = 10;
			this->FnF10->Text = L"F10";
			this->FnF10->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->FnF10->UseVisualStyleBackColor = true;
			this->FnF10->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// FnF11
			// 
			this->FnF11->Appearance = System::Windows::Forms::Appearance::Button;
			this->FnF11->Location = System::Drawing::Point(500, 0);
			this->FnF11->Margin = System::Windows::Forms::Padding(0);
			this->FnF11->Name = L"FnF11";
			this->FnF11->Size = System::Drawing::Size(45, 25);
			this->FnF11->TabIndex = 11;
			this->FnF11->Text = L"F11";
			this->FnF11->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->FnF11->UseVisualStyleBackColor = true;
			this->FnF11->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// FnF12
			// 
			this->FnF12->Appearance = System::Windows::Forms::Appearance::Button;
			this->FnF12->Location = System::Drawing::Point(550, 0);
			this->FnF12->Margin = System::Windows::Forms::Padding(0);
			this->FnF12->Name = L"FnF12";
			this->FnF12->Size = System::Drawing::Size(45, 25);
			this->FnF12->TabIndex = 12;
			this->FnF12->Text = L"F12";
			this->FnF12->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->FnF12->UseVisualStyleBackColor = true;
			this->FnF12->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// FnEject
			// 
			this->FnEject->Appearance = System::Windows::Forms::Appearance::Button;
			this->FnEject->Location = System::Drawing::Point(600, 0);
			this->FnEject->Margin = System::Windows::Forms::Padding(0);
			this->FnEject->Name = L"FnEject";
			this->FnEject->Size = System::Drawing::Size(45, 25);
			this->FnEject->TabIndex = 13;
			this->FnEject->Text = L"▲";
			this->FnEject->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->FnEject->UseVisualStyleBackColor = true;
			this->FnEject->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// FnDel
			// 
			this->FnDel->Appearance = System::Windows::Forms::Appearance::Button;
			this->FnDel->Location = System::Drawing::Point(600, 30);
			this->FnDel->Margin = System::Windows::Forms::Padding(0);
			this->FnDel->Name = L"FnDel";
			this->FnDel->Size = System::Drawing::Size(45, 25);
			this->FnDel->TabIndex = 14;
			this->FnDel->Text = L"delete";
			this->FnDel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->FnDel->UseVisualStyleBackColor = true;
			this->FnDel->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// FnAlnum
			// 
			this->FnAlnum->Appearance = System::Windows::Forms::Appearance::Button;
			this->FnAlnum->Enabled = false;
			this->FnAlnum->Location = System::Drawing::Point(150, 90);
			this->FnAlnum->Margin = System::Windows::Forms::Padding(0);
			this->FnAlnum->Name = L"FnAlnum";
			this->FnAlnum->Size = System::Drawing::Size(45, 25);
			this->FnAlnum->TabIndex = 15;
			this->FnAlnum->Text = L"英数";
			this->FnAlnum->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->FnAlnum->UseVisualStyleBackColor = true;
			this->FnAlnum->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// FnSpace
			// 
			this->FnSpace->Appearance = System::Windows::Forms::Appearance::Button;
			this->FnSpace->Enabled = false;
			this->FnSpace->Location = System::Drawing::Point(200, 90);
			this->FnSpace->Margin = System::Windows::Forms::Padding(0);
			this->FnSpace->Name = L"FnSpace";
			this->FnSpace->Size = System::Drawing::Size(145, 25);
			this->FnSpace->TabIndex = 16;
			this->FnSpace->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->FnSpace->UseVisualStyleBackColor = true;
			this->FnSpace->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// FnKana
			// 
			this->FnKana->Appearance = System::Windows::Forms::Appearance::Button;
			this->FnKana->Enabled = false;
			this->FnKana->Location = System::Drawing::Point(350, 90);
			this->FnKana->Margin = System::Windows::Forms::Padding(0);
			this->FnKana->Name = L"FnKana";
			this->FnKana->Size = System::Drawing::Size(45, 25);
			this->FnKana->TabIndex = 17;
			this->FnKana->Text = L"かな";
			this->FnKana->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->FnKana->UseVisualStyleBackColor = true;
			this->FnKana->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// FnUp
			// 
			this->FnUp->Appearance = System::Windows::Forms::Appearance::Button;
			this->FnUp->Location = System::Drawing::Point(550, 60);
			this->FnUp->Margin = System::Windows::Forms::Padding(0);
			this->FnUp->Name = L"FnUp";
			this->FnUp->Size = System::Drawing::Size(45, 25);
			this->FnUp->TabIndex = 18;
			this->FnUp->Text = L"↑";
			this->FnUp->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->FnUp->UseVisualStyleBackColor = true;
			this->FnUp->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// FnLeft
			// 
			this->FnLeft->Appearance = System::Windows::Forms::Appearance::Button;
			this->FnLeft->Location = System::Drawing::Point(500, 90);
			this->FnLeft->Margin = System::Windows::Forms::Padding(0);
			this->FnLeft->Name = L"FnLeft";
			this->FnLeft->Size = System::Drawing::Size(45, 25);
			this->FnLeft->TabIndex = 19;
			this->FnLeft->Text = L"←";
			this->FnLeft->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->FnLeft->UseVisualStyleBackColor = true;
			this->FnLeft->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// FnDown
			// 
			this->FnDown->Appearance = System::Windows::Forms::Appearance::Button;
			this->FnDown->Location = System::Drawing::Point(550, 90);
			this->FnDown->Margin = System::Windows::Forms::Padding(0);
			this->FnDown->Name = L"FnDown";
			this->FnDown->Size = System::Drawing::Size(45, 25);
			this->FnDown->TabIndex = 20;
			this->FnDown->Text = L"↓";
			this->FnDown->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->FnDown->UseVisualStyleBackColor = true;
			this->FnDown->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// FnRight
			// 
			this->FnRight->Appearance = System::Windows::Forms::Appearance::Button;
			this->FnRight->Location = System::Drawing::Point(600, 90);
			this->FnRight->Margin = System::Windows::Forms::Padding(0);
			this->FnRight->Name = L"FnRight";
			this->FnRight->Size = System::Drawing::Size(45, 25);
			this->FnRight->TabIndex = 21;
			this->FnRight->Text = L"→";
			this->FnRight->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->FnRight->UseVisualStyleBackColor = true;
			this->FnRight->CheckedChanged += gcnew System::EventHandler(this, &EditForm::SelectedChanged);
			// 
			// Action
			// 
			this->Action->Controls->Add(this->DoNothing);
			this->Action->Controls->Add(this->InputKey);
			this->Action->Controls->Add(this->InputKeyList);
			this->Action->Controls->Add(this->Special);
			this->Action->Controls->Add(this->SpecialList);
			this->Action->Controls->Add(this->Exec);
			this->Action->Controls->Add(this->ExecCommand);
			this->Action->Controls->Add(this->ExecFind);
			this->Action->Location = System::Drawing::Point(5, 140);
			this->Action->Margin = System::Windows::Forms::Padding(0);
			this->Action->Name = L"Action";
			this->Action->Size = System::Drawing::Size(450, 70);
			this->Action->TabIndex = 1;
			this->Action->TabStop = false;
			this->Action->Text = L"アクション";
			// 
			// DoNothing
			// 
			this->DoNothing->AutoSize = true;
			this->DoNothing->Checked = true;
			this->DoNothing->Location = System::Drawing::Point(10, 18);
			this->DoNothing->Name = L"DoNothing";
			this->DoNothing->Size = System::Drawing::Size(73, 16);
			this->DoNothing->TabIndex = 0;
			this->DoNothing->TabStop = true;
			this->DoNothing->Text = L"何もしない";
			this->DoNothing->UseVisualStyleBackColor = true;
			this->DoNothing->CheckedChanged += gcnew System::EventHandler(this, &EditForm::DoNothing_CheckedChanged);
			// 
			// InputKey
			// 
			this->InputKey->AutoSize = true;
			this->InputKey->Location = System::Drawing::Point(95, 18);
			this->InputKey->Name = L"InputKey";
			this->InputKey->Size = System::Drawing::Size(43, 16);
			this->InputKey->TabIndex = 1;
			this->InputKey->TabStop = true;
			this->InputKey->Text = L"キー";
			this->InputKey->UseVisualStyleBackColor = true;
			// 
			// InputKeyList
			// 
			this->InputKeyList->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->InputKeyList->FormattingEnabled = true;
			this->InputKeyList->Location = System::Drawing::Point(140, 16);
			this->InputKeyList->Name = L"InputKeyList";
			this->InputKeyList->Size = System::Drawing::Size(150, 20);
			this->InputKeyList->TabIndex = 2;
			this->InputKeyList->SelectedIndexChanged += gcnew System::EventHandler(this, &EditForm::InputKeyList_SelectedIndexChanged);
			// 
			// Special
			// 
			this->Special->AutoSize = true;
			this->Special->Location = System::Drawing::Point(310, 18);
			this->Special->Name = L"Special";
			this->Special->Size = System::Drawing::Size(47, 16);
			this->Special->TabIndex = 3;
			this->Special->TabStop = true;
			this->Special->Text = L"特殊";
			this->Special->UseVisualStyleBackColor = true;
			// 
			// SpecialList
			// 
			this->SpecialList->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->SpecialList->FormattingEnabled = true;
			this->SpecialList->Location = System::Drawing::Point(360, 16);
			this->SpecialList->Name = L"SpecialList";
			this->SpecialList->Size = System::Drawing::Size(80, 20);
			this->SpecialList->TabIndex = 4;
			this->SpecialList->SelectedIndexChanged += gcnew System::EventHandler(this, &EditForm::SpecialList_SelectedIndexChanged);
			// 
			// Exec
			// 
			this->Exec->AutoSize = true;
			this->Exec->Location = System::Drawing::Point(10, 45);
			this->Exec->Name = L"Exec";
			this->Exec->Size = System::Drawing::Size(47, 16);
			this->Exec->TabIndex = 5;
			this->Exec->TabStop = true;
			this->Exec->Text = L"実行";
			this->Exec->UseVisualStyleBackColor = true;
			// 
			// ExecCommand
			// 
			this->ExecCommand->Location = System::Drawing::Point(65, 43);
			this->ExecCommand->Name = L"ExecCommand";
			this->ExecCommand->Size = System::Drawing::Size(350, 19);
			this->ExecCommand->TabIndex = 6;
			this->ExecCommand->TextChanged += gcnew System::EventHandler(this, &EditForm::ExecCommand_TextChanged);
			// 
			// ExecFind
			// 
			this->ExecFind->Location = System::Drawing::Point(420, 43);
			this->ExecFind->Name = L"ExecFind";
			this->ExecFind->Size = System::Drawing::Size(20, 19);
			this->ExecFind->TabIndex = 7;
			this->ExecFind->Text = L"...";
			this->ExecFind->UseVisualStyleBackColor = true;
			this->ExecFind->Click += gcnew System::EventHandler(this, &EditForm::ExecFind_Click);
			// 
			// Cancel
			// 
			this->Cancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->Cancel->Location = System::Drawing::Point(470, 180);
			this->Cancel->Name = L"Cancel";
			this->Cancel->Size = System::Drawing::Size(80, 24);
			this->Cancel->TabIndex = 2;
			this->Cancel->Text = L"キャンセル";
			this->Cancel->UseVisualStyleBackColor = true;
			this->Cancel->Click += gcnew System::EventHandler(this, &EditForm::Cancel_Click);
			// 
			// Apply
			// 
			this->Apply->Location = System::Drawing::Point(560, 180);
			this->Apply->Name = L"Apply";
			this->Apply->Size = System::Drawing::Size(80, 24);
			this->Apply->TabIndex = 3;
			this->Apply->Text = L"OK";
			this->Apply->UseVisualStyleBackColor = true;
			this->Apply->Click += gcnew System::EventHandler(this, &EditForm::Apply_Click);
			// 
			// FileDlg
			// 
			this->FileDlg->AddExtension = false;
			// 
			// EditForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->Cancel;
			this->ClientSize = System::Drawing::Size(654, 216);
			this->Controls->Add(this->Action);
			this->Controls->Add(this->Tab);
			this->Controls->Add(this->Cancel);
			this->Controls->Add(this->Apply);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->ImeMode = System::Windows::Forms::ImeMode::Off;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"EditForm";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->Text = L"Apple Keyboard Bridge - Configuration Editor";
			this->Load += gcnew System::EventHandler(this, &EditForm::EditForm_Load);
			this->Tab->ResumeLayout(false);
			this->Singles->ResumeLayout(false);
			this->Combinations->ResumeLayout(false);
			this->Action->ResumeLayout(false);
			this->Action->PerformLayout();
			this->ResumeLayout(false);
		}
#pragma endregion

	private:
		System::Void EditForm_Load(System::Object^ /*sender*/, System::EventArgs^ /*e*/);
		System::Void Cancel_Click(System::Object^ /*sender*/, System::EventArgs^ /*e*/);
		System::Void Apply_Click(System::Object^ /*sender*/, System::EventArgs^ /*e*/);
		System::Void ExecFind_Click(System::Object^ /*sender*/, System::EventArgs^ /*e*/);
		System::Void SelectedChanged(System::Object^ /*sender*/, System::EventArgs^ /*e*/);
		System::Void DoNothing_CheckedChanged(System::Object^ /*sender*/, System::EventArgs^ /*e*/);
		System::Void InputKeyList_SelectedIndexChanged(System::Object^ /*sender*/, System::EventArgs^ /*e*/);
		System::Void SpecialList_SelectedIndexChanged(System::Object^ /*sender*/, System::EventArgs^ /*e*/);
		System::Void ExecCommand_TextChanged(System::Object^ /*sender*/, System::EventArgs^ /*e*/);

	private:
		void LoadResources();
		void LoadConfig(array<System::String^>^ /*args*/);
		bool SaveConfig();
		void ShowAction(WORD);
		WORD% GetSelectedAction();
		void ResetActionsExceptFor(System::Windows::Forms::Control^);

	private:
		System::String^         ConfigPath;
		Config^                 ConfigData;
		array<System::String^>^ ConfigCmds;
		System::Boolean         IsSuspended;

	private:
		System::Collections::Generic::Dictionary<WORD, System::String^>^ InputKeys;
		System::Collections::Generic::Dictionary<WORD, System::String^>^ Specials;
	};
}
