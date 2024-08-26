#pragma once
//#include "Header3.h"
#include<Windows.h>
#include<stdio.h>
#include <msclr\marshal_cppstd.h>
namespace frontEnd {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form2
	/// </summary>
	
	public ref class Form2 : public System::Windows::Forms::Form
	{
	private:
		String^ pred;
		String^ pred1;

	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::PictureBox^  pic;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;

			 Form^ obj;
	public:
		Form2(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		Form2(Form^ f,String^ args, String^ args1)
		{
			obj = f;
			pred = args;
			pred1= args1;
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form2()
		{
			if (components)
			{
				delete components;
			}
		}

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form2::typeid));
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->pic = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pic))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::Gold;
			this->button2->ForeColor = System::Drawing::Color::Black;
			this->button2->Location = System::Drawing::Point(124, 348);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(109, 78);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Record Again";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &Form2::button2_Click);
			// 
			// pic
			// 
			this->pic->Location = System::Drawing::Point(424, 212);
			this->pic->Name = L"pic";
			this->pic->Size = System::Drawing::Size(277, 209);
			this->pic->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pic->TabIndex = 3;
			this->pic->TabStop = false;
			this->pic->Click += gcnew System::EventHandler(this, &Form2::pictureBox1_Click_1);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 28.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::OrangeRed;
			this->label1->Location = System::Drawing::Point(366, 153);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(410, 56);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Reference Image";
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(929, 348);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(115, 97);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 5;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &Form2::pictureBox1_Click_2);
			// 
			// Form2
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1113, 557);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pic);
			this->Controls->Add(this->button2);
			this->Margin = System::Windows::Forms::Padding(4);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"Form2";
			this->Text = L"Form2";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &Form2::Form2_FormClosed);
			this->Load += gcnew System::EventHandler(this, &Form2::Form2_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pic))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Form2_Load(System::Object^  sender, System::EventArgs^  e) {
				 pic->ImageLocation = pred1;


			 }
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 //int x;
	//fscanf(fp,"%d",&x);
	/*char A[100];
	sprintf(A,"%d.wav",pred);
   wchar_t wtext[20];
  mbstowcs(wtext, A, strlen(A)+1);//Plus null
 LPWSTR ptr = wtext;
	//PlayRecord();
	PlaySound(ptr,NULL,SND_FILENAME);*/
				 //Play();
				 /* pin_ptr<const wchar_t> wch = PtrToStringChars(pred);
				 size_t origsize = wcslen(wch) + 1;
				  const size_t newsizew = origsize;
					wchar_t* wcstring = new wchar_t[newsizew];
					wcscpy_s(wcstring, newsizew, wch);
				PlaySound(wcstring,NULL,SND_ASYNC);
				delete []wcstring;*/
			 }
	private: System::Void Form2_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
				obj->Show();
			 }
	private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			 obj->Show();
		 }
private: System::Void pictureBox1_Click_1(System::Object^  sender, System::EventArgs^  e) {
			  
		 }
private: System::Void pictureBox1_Click_2(System::Object^  sender, System::EventArgs^  e) {
			  pin_ptr<const wchar_t> wch = PtrToStringChars(pred);
				 size_t origsize = wcslen(wch) + 1;
				  const size_t newsizew = origsize;
					wchar_t* wcstring = new wchar_t[newsizew];
					wcscpy_s(wcstring, newsizew, wch);
				PlaySound(wcstring,NULL,SND_ASYNC);
				delete []wcstring;
			 
		 }
};
}
