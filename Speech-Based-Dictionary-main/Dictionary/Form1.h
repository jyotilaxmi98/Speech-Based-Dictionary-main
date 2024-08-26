#pragma once
#include "MyAudioRecorder.h"
#include "Header2.h"
#include "Form2.h"
#include "Form3.h"
#include <msclr\marshal_cppstd.h>
namespace frontEnd {

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
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::NumericUpDown^  words;
	private: System::Windows::Forms::NumericUpDown^  utter;


	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;


	protected: 

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->words = (gcnew System::Windows::Forms::NumericUpDown());
			this->utter = (gcnew System::Windows::Forms::NumericUpDown());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->words))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->utter))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::Gold;
			this->button1->Font = (gcnew System::Drawing::Font(L"Arial Black", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(701, 121);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(92, 75);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Train";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::Gold;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button2->Location = System::Drawing::Point(648, 233);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(100, 70);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Live Testing";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::Color::Gold;
			this->button3->Font = (gcnew System::Drawing::Font(L"Arial", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button3->Location = System::Drawing::Point(754, 233);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(105, 70);
			this->button3->TabIndex = 2;
			this->button3->Text = L"Show Result";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Red;
			this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 22.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(435, 406);
			this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(70, 35);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Exit";
			this->label1->Click += gcnew System::EventHandler(this, &Form1::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 28.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::Teal;
			this->label2->Location = System::Drawing::Point(163, -6);
			this->label2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(534, 53);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Welcome To Our Dictionary";
			// 
			// words
			// 
			this->words->Location = System::Drawing::Point(125, 176);
			this->words->Name = L"words";
			this->words->Size = System::Drawing::Size(120, 20);
			this->words->TabIndex = 5;
			this->words->ValueChanged += gcnew System::EventHandler(this, &Form1::numericUpDown1_ValueChanged);
			// 
			// utter
			// 
			this->utter->Location = System::Drawing::Point(123, 233);
			this->utter->Name = L"utter";
			this->utter->Size = System::Drawing::Size(120, 20);
			this->utter->TabIndex = 6;
			this->utter->ValueChanged += gcnew System::EventHandler(this, &Form1::numericUpDown2_ValueChanged);
			// 
			// button4
			// 
			this->button4->BackColor = System::Drawing::Color::Gold;
			this->button4->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button4->Location = System::Drawing::Point(153, 296);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 47);
			this->button4->TabIndex = 7;
			this->button4->Text = L"Record And Train";
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click_1);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::Red;
			this->label3->Location = System::Drawing::Point(-4, 146);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(291, 20);
			this->label3->TabIndex = 8;
			this->label3->Text = L"Enter The Number Of Words You Want To Train";
			this->label3->Click += gcnew System::EventHandler(this, &Form1::label3_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Font = (gcnew System::Drawing::Font(L"Arial", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::Color::Red;
			this->label4->Location = System::Drawing::Point(-3, 212);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(354, 18);
			this->label4->TabIndex = 9;
			this->label4->Text = L"Enter The Number Of Utterances  For Each Word";
			this->label4->Click += gcnew System::EventHandler(this, &Form1::label4_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->BackColor = System::Drawing::Color::Transparent;
			this->label5->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label5->ForeColor = System::Drawing::Color::Red;
			this->label5->Location = System::Drawing::Point(12, 311);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(121, 16);
			this->label5->TabIndex = 10;
			this->label5->Text = L"Live Training Part";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(889, 495);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->utter);
			this->Controls->Add(this->words);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"Form1";
			this->Text = L" ";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->words))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->utter))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

				// printf("Please wait we are training the model\n");
				
				 train_model();


			 }
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {

				// StartRecord("audio.txt","audio.wav");
				 system(".\\Recording_module.exe 3 live_data.wav live_data.txt");

			 }
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {

				int x = test_livedata();
				char str[100];
				char str2[100];
				sprintf(str,"%d.wav",x);
				sprintf(str2,"%d.jpg",x);
				 Form2^ form2=gcnew Form2(this,msclr::interop::marshal_as<System::String^>(str),msclr::interop::marshal_as<System::String^>(str2));
				 form2->Show();
				 this->Hide();
			 }
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
			Application::Exit();
		 }
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
            Form3^ form3=gcnew Form3();
			form3->Show();
			this->Hide();
		 }
private: System::Void numericUpDown2_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void label4_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void numericUpDown1_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void button4_Click_1(System::Object^  sender, System::EventArgs^  e) {
			  Decimal^ word1=(words->Value);
			  Decimal^ u=(utter->Value);
			 int x=Convert::ToInt32(word1);
			 int y=Convert::ToInt32(u);
			 FILE* f1=fopen("giveup.txt","w");
			 fprintf(f1,"%d",x);
			 fclose(f1);

			 live_train(x,y);
		 }
};
}

