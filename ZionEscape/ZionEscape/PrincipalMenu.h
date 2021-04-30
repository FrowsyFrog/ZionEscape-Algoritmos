#pragma once
#include "FormGame.h"
namespace ZionEscape {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de PrincipalMenu
	/// </summary>
	public ref class PrincipalMenu : public System::Windows::Forms::Form
	{
		bool resume = false;
	public:
		PrincipalMenu(void)
		{
			InitializeComponent();
			//
			//TODO: agregar c�digo de constructor aqu�
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se est�n usando.
		/// </summary>
		~PrincipalMenu()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	protected:

	private: System::Windows::Forms::Button^ btnStart;
	private: System::Windows::Forms::Button^ btnReanudar;

	private: System::Windows::Forms::Button^ btnExit;
	private: System::Windows::Forms::PictureBox^ pictureBox2;


	private:
		/// <summary>
		/// Variable del dise�ador necesaria.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// M�todo necesario para admitir el Dise�ador. No se puede modificar
		/// el contenido de este m�todo con el editor de c�digo.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(PrincipalMenu::typeid));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->btnStart = (gcnew System::Windows::Forms::Button());
			this->btnReanudar = (gcnew System::Windows::Forms::Button());
			this->btnExit = (gcnew System::Windows::Forms::Button());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(-6, -6);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(668, 516);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// btnStart
			// 
			this->btnStart->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->btnStart->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->btnStart->Font = (gcnew System::Drawing::Font(L"Georgia", 13.97015F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnStart->Location = System::Drawing::Point(208, 230);
			this->btnStart->Name = L"btnStart";
			this->btnStart->Size = System::Drawing::Size(267, 50);
			this->btnStart->TabIndex = 2;
			this->btnStart->Text = L"Start";
			this->btnStart->UseVisualStyleBackColor = false;
			this->btnStart->Click += gcnew System::EventHandler(this, &PrincipalMenu::btnStart_Click);
			// 
			// btnReanudar
			// 
			this->btnReanudar->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->btnReanudar->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->btnReanudar->Font = (gcnew System::Drawing::Font(L"Georgia", 13.97015F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnReanudar->Location = System::Drawing::Point(208, 323);
			this->btnReanudar->Name = L"btnReanudar";
			this->btnReanudar->Size = System::Drawing::Size(267, 50);
			this->btnReanudar->TabIndex = 3;
			this->btnReanudar->Text = L"Resume";
			this->btnReanudar->UseVisualStyleBackColor = false;
			this->btnReanudar->Click += gcnew System::EventHandler(this, &PrincipalMenu::btnReanudar_Click);
			// 
			// btnExit
			// 
			this->btnExit->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->btnExit->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->btnExit->Font = (gcnew System::Drawing::Font(L"Georgia", 13.97015F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnExit->ForeColor = System::Drawing::Color::Black;
			this->btnExit->Location = System::Drawing::Point(208, 413);
			this->btnExit->Name = L"btnExit";
			this->btnExit->Size = System::Drawing::Size(267, 50);
			this->btnExit->TabIndex = 5;
			this->btnExit->Text = L"Exit";
			this->btnExit->UseVisualStyleBackColor = false;
			this->btnExit->Click += gcnew System::EventHandler(this, &PrincipalMenu::btnExit_Click);
			// 
			// pictureBox2
			// 
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(30, 35);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(445, 133);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox2->TabIndex = 6;
			this->pictureBox2->TabStop = false;
			// 
			// PrincipalMenu
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(659, 508);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->btnExit);
			this->Controls->Add(this->btnReanudar);
			this->Controls->Add(this->btnStart);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"PrincipalMenu";
			this->Text = L"PrincipalMenu";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion
private: System::Void btnStart_Click(System::Object^ sender, System::EventArgs^ e) {
	resume = false;
	FormGame^ form = gcnew FormGame(resume);
	this->Visible = false;
	form->Show();
}
	private: System::Void btnReanudar_Click(System::Object^ sender, System::EventArgs^ e) {
	resume = true;
	FormGame^ form = gcnew FormGame(resume);
	this->Visible = false;
	form->Show();
}
private: System::Void btnExit_Click(System::Object^ sender, System::EventArgs^ e) {
	this->Close();
}
};
}
