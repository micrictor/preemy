#pragma once
#include "Windows.h"
#include <string>

namespace preemy {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  textBox1;
	protected: 
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::Button^  button2;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->AllowDrop = true;
			this->textBox1->Location = System::Drawing::Point(78, 30);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(181, 20);
			this->textBox1->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 33);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(60, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Executable";
			this->label1->Click += gcnew System::EventHandler(this, &Form1::label1_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(265, 28);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Open file...";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->Filter = L"Executables (*.exe)|*.exe";
			// 
			// button2
			// 
			this->button2->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->button2->Location = System::Drawing::Point(0, 263);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(358, 23);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Run";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(358, 286);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Name = L"Form1";
			this->Text = L"Preemy";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) 
	{
	}
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) 
	{
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		this->openFileDialog1->ShowDialog();
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		/* 
		*  Fucking Microsoft virtualizes the registry so these all actually go to
		*    HKLM\SOFTWARE\Wow6432Node\Microsoft\Windows NT\CurrentVersion\Windows
		*  Google says setting the UAC manifest to requireAdmin will fix it
		*  It fucking didn't.
		*  Fuck.
		*  WoW.
		*  Virtualization.
		*
		*  I'm still going to write everything as if these registry edits actually
		*    work, and hopefully I'll be able to break Windowns on Windowns later
		*/
		HKEY key;

		DWORD dwSize = sizeof(DWORD);
		DWORD dwTrue = 1;
		DWORD dwFalse = 0;

		if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Windows"),
		0, KEY_SET_VALUE, &key) != ERROR_SUCCESS)
		{
			MessageBox::Show(
				"ERROR! Registry key could not be opened. Are you running as admin?",
				"ERROR!",
				MessageBoxButtons::OK,
				MessageBoxIcon::Error);
			return;
		}

		// BEGIN ENABLE OF AppInit_DLLs
		if(RegSetValueEx(key, TEXT("LoadAppInit_DLLs"), 0, REG_DWORD, (const BYTE*)&dwTrue, dwSize != ERROR_SUCCESS)
		{
			MessageBox::Show(
				"ERROR! Registry key could not be written. Are you running as admin?",
				"ERROR!",
				MessageBoxButtons::OK,
				MessageBoxIcon::Error);
			RegCloseKey(key);
			return;
		}
		if(RegSetValueEx(key, TEXT("RequireSignedAppInit_DLLs"), 0, REG_DWORD, (PBYTE)&dwFalse, dwSize) != ERROR_SUCCESS)
		{
			MessageBox::Show(
				"ERROR! Registry key could not be written. Are you running as admin?",
				"ERROR!",
				MessageBoxButtons::OK,
				MessageBoxIcon::Error);
			RegCloseKey(key);
			return;
		}
		// END ENABLE OF AppInit_DLLs

		// TODO
		// Add in selected modules to AppInit_DLLs
		// Pointless to do this before we unfuck WoW

		// BEGIN DISABLE OF AppInit_DLLs
		if(RegSetValueEx(key, TEXT("LoadAppInit_DLLs"), 0, REG_DWORD, (const BYTE*)&dwFalse, dwSize != ERROR_SUCCESS)
		{
			MessageBox::Show(
				"ERROR! Registry key could not be written. Are you running as admin?",
				"ERROR!",
				MessageBoxButtons::OK,
				MessageBoxIcon::Error);
			RegCloseKey(key);
			return;
		}
		if(RegSetValueEx(key, TEXT("RequireSignedAppInit_DLLs"), 0, REG_DWORD, (PBYTE)&dwTrue, dwSize) != ERROR_SUCCESS)
		{
			MessageBox::Show(
				"ERROR! Registry key could not be written. Are you running as admin?",
				"ERROR!",
				MessageBoxButtons::OK,
				MessageBoxIcon::Error);
			RegCloseKey(key);
			return;
		}
		// END DISABLE OF AppInit_DLLs

		RegCloseKey(key);
	}
};
}

