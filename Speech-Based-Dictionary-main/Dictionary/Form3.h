#pragma once
#include<stdio.h>
//#pragma once
//#include "Header2.h"
namespace frontEnd {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form3
	/// </summary>
	public ref class Form3 : public System::Windows::Forms::Form
	{
		 //Form^ obj1;
	public:
		Form3(void)
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
		~Form3()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::NumericUpDown^  words;
	private: System::Windows::Forms::NumericUpDown^  utter;
	protected: 

	protected: 

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  button1;
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form3::typeid));
			this->words = (gcnew System::Windows::Forms::NumericUpDown());
			this->utter = (gcnew System::Windows::Forms::NumericUpDown());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->words))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->utter))->BeginInit();
			this->SuspendLayout();
			// 
			// words
			// 
			this->words->Location = System::Drawing::Point(350, 91);
			this->words->Name = L"words";
			this->words->Size = System::Drawing::Size(120, 20);
			this->words->TabIndex = 0;
			this->words->ValueChanged += gcnew System::EventHandler(this, &Form3::numericUpDown1_ValueChanged);
			// 
			// utter
			// 
			this->utter->Location = System::Drawing::Point(350, 151);
			this->utter->Name = L"utter";
			this->utter->Size = System::Drawing::Size(120, 20);
			this->utter->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::Cyan;
			this->label1->Location = System::Drawing::Point(44, 93);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(269, 15);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Enter The Number Of Words You Want To Train";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::Cyan;
			this->label2->Location = System::Drawing::Point(44, 153);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(248, 15);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Enter The Number Of Utterances Per Word";
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::Yellow;
			this->button1->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(371, 215);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 38);
			this->button1->TabIndex = 4;
			this->button1->Text = L"Record And Train";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &Form3::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(151, 215);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 38);
			this->button2->TabIndex = 5;
			this->button2->Text = L"Go Back";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form3::button2_Click);
			// 
			// Form3
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(611, 319);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->utter);
			this->Controls->Add(this->words);
			this->Name = L"Form3";
			this->Text = L"Form3";
			this->Load += gcnew System::EventHandler(this, &Form3::Form3_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->words))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->utter))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Form3_Load(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void numericUpDown1_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				 
			 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 Decimal^ word1=(words->Value);
			 Decimal^ u=(utter->Value);
			 int x=Convert::ToInt32(word1);
			 int y=Convert::ToInt32(u);
				//live_train(x,y);
		 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			// obj1->Show();
		 }
};
}
